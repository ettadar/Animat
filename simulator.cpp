#include "simulator.hpp"


#include <ctime>
#include <cmath>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <cfloat>

Simulator::Simulator(bool display, std::string sceneFile, int modelNumber) :  _display(NULL),
  _robot(NULL),

  _sceneWidth(0),
  _sceneHeight(0),
  
  _robotPosX(0),
  _robotPosY(0),

  _goalPosX(0),
  _goalPosY(0),
  
  _cylinderList(NULL),
  
  _continue(true),
  _windowClosed(false),
  _nbIter(0),
  _knownPos(std::set<std::pair<float, float> >())
{
  _cylinderList = new std::vector<Cylinder*>();

  // read scene file
  std::string line;
  std::ifstream myfile(sceneFile.c_str());
  if (myfile.is_open())
  {
    getline(myfile, line);
    int bPos = 0;
    int ePos = line.find(' ');
    _sceneWidth = std::atoi(line.substr(bPos, ePos - bPos).c_str());
    bPos = ePos + 1;
    ePos = line.find(' ', bPos);
    _sceneHeight = std::atoi(line.substr(bPos, ePos - bPos).c_str());

    getline(myfile, line);
    bPos = 0;
    ePos = line.find(' ');
    _goalPosX = std::atoi(line.substr(bPos, ePos - bPos).c_str());
    bPos = ePos + 1;
    ePos = line.find(' ', bPos);
    _goalPosY = std::atoi(line.substr(bPos, ePos - bPos).c_str());
    while ( myfile.good() )
    {
      getline(myfile, line);
      int bPos = 0;
      int ePos = line.find(' ');
      int c = std::atoi(line.substr(bPos, ePos - bPos).c_str());
      bPos = ePos + 1;
      ePos = line.find(' ', bPos);
      int x = std::atoi(line.substr(bPos, ePos - bPos).c_str());
      bPos = ePos + 1;
      ePos = line.find(' ', bPos);
      int y = std::atoi(line.substr(bPos, ePos - bPos).c_str());
      _cylinderList->push_back(new Cylinder(x, y, c, 20));
    }
    myfile.close();
  }
  else
    std::cerr << "Unable to open file " << sceneFile << std::endl;

  Image* timg = _getImage(_goalPosX, _goalPosY);
  Model* mod = NULL;
  if (modelNumber == 1)
    mod = new CCmodel(timg);
  else if (modelNumber == 2)
    mod = new DynamicModelNoColor(timg);
  else
    mod = new DynamicModelColor(timg);
  _robot = new Robot(mod);

  if (display)
  {
    _display = new Display(_cylinderList, _sceneWidth, _sceneHeight);
    _display->setTargetPos(_goalPosX, _goalPosY);
    _display->setTargetView(timg);
    _display->setRobotPos(_robotPosX, _robotPosY);
  }
}

Simulator::~Simulator()
{
  _cylinderList->clear();
  delete _cylinderList;

  delete _robot;
  delete _display;
}

void Simulator::setRobotPos(float robotPosX, float robotPosY)
{
  _robotPosX = robotPosX;
  _robotPosY = robotPosY;

  _knownPos.clear();
}

void Simulator::run()
{
  while (_continue && !_windowClosed)
  {
    //usleep(1000000);
    step();
  }
  _continue = true;
  if (_display)
    while (!_windowClosed)
      _windowClosed = _display->update();    
  _windowClosed = false;
}

void Simulator::generatePerfImage()
{
  Perfimage *img = new Perfimage(_sceneWidth,_sceneHeight);
  short lastWitdth = 0;
  short lastheight = 0;
  //declare a temporary color variable
  Colour c;
  c.r = 255;
  c.g = 255;
  c.b = 255;
  c.a = 255;
  img->setAllPixels(c);
  for(int j = 0; j < _sceneWidth / SIZEPIXEL; j++)
  {
    for(int i = 0; i < _sceneHeight / SIZEPIXEL; i++)
    {
      setRobotPos( j * 20 + (SIZEPIXEL / 2), i * 20 + (SIZEPIXEL / 2));
      //setRobotPos( 500, 500 );
      std::cout << "run number" << (j * _sceneHeight / 20) + i  <<std::endl;
      run();
      short width = j * SIZEPIXEL;
      short height = i * SIZEPIXEL;

      //draw objectif
      img->drawGoal(_goalPosX, _goalPosY);

      if(fabs(_robotPosX - _goalPosX) < 5 && fabs(_robotPosY - _goalPosY) < 5)
      {
        img->colorPixel(width,height);
      }

      setRobotPos( j * SIZEPIXEL + (SIZEPIXEL / 2), i * SIZEPIXEL + (SIZEPIXEL / 2) );
      step();
      float moveX = (float)_robot->getMoveX();
      float moveY = (float)_robot->getMoveY();
      float newSize = sqrt(pow(moveX, 2) + pow(moveY,2)) * (SIZEPIXEL / 2) ;
      img->chooseArrow( width, height, moveX, moveY, newSize);
    }
  }
  for (int i = 0; i < _cylinderList->size(); ++i)
  {
    img->drawLandmark(_cylinderList->at(i));
  }
  //write the image to disk
  string filename = "./test.tga";
  img->WriteImage(filename);
}

void Simulator::step()
{
  Image* img = _getImage(_robotPosX, _robotPosY);

  if (_display)
  {
    _display->setRobotPos(_robotPosX, _robotPosY);
    _display->setRobotView(img);
    _windowClosed = _display->update();
  }

  _robot->step(img);
  _robotPosX += _robot->getMoveX();
  _robotPosY += _robot->getMoveY();


  if (_robotPosX < 0 || _robotPosX >= _sceneWidth ||
    _robotPosY < 0 || _robotPosY >= _sceneHeight ||
    _knownPos.count(std::pair<float, float>(floor(_robotPosX * 100) / 100, floor(_robotPosY * 100) / 100)) != 0)
  {
    _continue = false;
  }

  _knownPos.insert(std::pair<float, float>(floor(_robotPosX * 100) / 100, floor(_robotPosY * 100) / 100));  
}

// WARNING : Do not handle differant size cylinder
Image* Simulator::_getImage(float posX, float posY)
{
  Image* img = new Image();
  for (int iPixel = 0; iPixel < VIEW_ANGLE + 1; ++iPixel)
  {
    float angle = (iPixel - VIEW_ANGLE / 2) / 360. * 2 * PI;
    float minDist = FLT_MAX;
    int color = BLACK;

    for (int iCylinder = 0; iCylinder < _cylinderList->size(); ++iCylinder)
    {
      float x1 = cos(angle);
      float y1 = sin(angle);
      x1 /= sqrt(pow(x1, 2) + pow(y1, 2));
      y1 /= sqrt(pow(x1, 2) + pow(y1, 2));

      float x2 = _cylinderList->at(iCylinder)->x - posX;
      float y2 = _cylinderList->at(iCylinder)->y - posY;
      // std::cout << x2 << ", " << y2 << std::endl;

      float prod = x1 * x2 + y1 * y2;
      // std::cout << "prod : " << prod << std::endl;
      if (prod <= 0)
        continue;

      float squareDist = pow(x1 * prod - x2, 2) + pow(y1 * prod - y2, 2);
      // std::cout << "dist : " << squareDist << std::endl;
      if (squareDist > pow(_cylinderList->at(iCylinder)->r, 2))
        continue;

      if (prod < minDist)
      {
        minDist = prod;
        color = _cylinderList->at(iCylinder)->color;
      }
    }
    img->push_back(color);
  }
  return img;
}

