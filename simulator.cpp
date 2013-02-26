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
  _nbIter(0)
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
    std::cerr << "Model not implemented!" << std::endl;
  else
    mod = new Dynamicmodel(timg);
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
}

void Simulator::run()
{
  int i = 0;
  while (_continue && !_windowClosed && i < 2)
  {
    //usleep(1000000);
    step();
    i++;
  }
  _continue = true;
  if (_display)
    while (!_windowClosed)
      _windowClosed = _display->update();    
  _windowClosed = false;
}

void Simulator::generatePerfImage()
{
  TGAImage *img = new TGAImage(_sceneWidth,_sceneHeight);
  short lastWitdth = 0;
  short lastheight = 0;
  for(int j = 0; j < _sceneWidth / 20 ; j++)
  {
    for(int i = 0; i < _sceneHeight / 20 ;i++)
    {
      setRobotPos( j * 20, i * 20 );
      //setRobotPos( 500, 500 );
      std::cout << "run number" << (j * _sceneHeight / 20) + i  <<std::endl;
      run();
      short width = j * 20;
      short height = i * 20;
      //declare a temporary color variable
      Colour c;
      //draw objectif
      c.r = 255;
      c.g = 0;
      c.b = 0;
      c.a = 255;
      for (int g = 0; g < 20; ++g)
      {
        //img->setPixel(c,_goalPosX + g, _goalPosY);
        _drawArrow(_goalPosX, _goalPosY, 5, 10, img);
        //img->setPixel(c,_goalPosX + g, _goalPosY + g);
      }
      if(fabs(_robotPosX - _goalPosX) < 5 && fabs(_robotPosY - _goalPosY) < 5)
      {
        //Loop through image and set all pixels to red
        for(int x = width; x < width + 20; x++)
        //int x = j ;
          for(int y = height; y < height + 20; y++)
          {
            c.r = 20;
            c.g = 20;
            c.b = 190;
            c.a = 255;
            img->setPixel(c, x, y);
          }
          lastheight = height;
      }
      else
      {
        for(int x = width; x < width + 20; x++)
          for(int y = height; y < height + 20; y++)
          {
            c.r = 255;
            c.g = 255;
            c.b = 255;
            c.a = 255;
            img->setPixel(c, x, y);
          }
          lastheight = height;
      }
      setRobotPos( j * 20, i * 20 );
      step();
      float moveX = (float)_robot->getMoveX();
      float moveY = (float)_robot->getMoveY();
      std::cout << "_robotX " << moveX << "_robotY " << moveY << std::endl;
      //TODO gerer le cas div par 0
      if(moveX == 0)
      {
        if (moveY == 0)
        {
        }
        else if (moveY > 0)
        {
          _drawArrow(width, height, 0, 10, img);
        }
        else if (moveY < 0)
        {
          _drawArrow(width, height, 4, 10, img);
        }
      }
      else if (moveY == 0)
      {
        if (moveX > 0)
        {
          _drawArrow(width, height, 6, 10, img);
        }
        else
        {
          _drawArrow(width, height, 2, 10, img);
        }
      }
      else if (fabs(moveX / moveY) > 2.42)
      {
        if (moveY > 0)
        {
          _drawArrow(width, height, 0, 10, img);
        }
        else
        {
          _drawArrow(width, height, 4, 10, img);
        }
      }
      else if (fabs(moveX / moveY) > 0.41)
      {
        if (moveY > 0 && moveX > 0)
        {
          _drawArrow(width, height, 7, 10, img);
        }
        else if (moveY > 0 && moveX < 0)
        {
          _drawArrow(width, height, 1, 10, img);
        }
        else if (moveY < 0 && moveX > 0)
        {
          _drawArrow(width, height, 5, 10, img);
        }
        else if (moveY < 0 && moveX < 0)
        {
          _drawArrow(width, height, 3, 10, img);
        }
      }
      else
      {
        if(moveX < 0)
        {
          _drawArrow(width, height, 2, 10, img);
        }
        else if (moveX > 0)
        {
          _drawArrow(width, height, 6, 10, img);
        }
      }
    }
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

  float PreStepX = _robotPosX;
  float PreStepY = _robotPosX;

  _robot->step(img);
  _robotPosX += _robot->getMoveX();
  _robotPosY += _robot->getMoveY();

  float PostStepX = _robotPosX;
  float PostStepY = _robotPosX;

  if (_robot->getMoveX() == 0 && _robot->getMoveY() == 0)
    _continue = false;
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

void Simulator::_drawArrow(short positionX, short positionY, int direction, int size, TGAImage *img)
{
//direction : 0 south, 1 south-weast, 2 weast, 3 north-west, 4 north, 5 north-east, 6 east, 7 south-east 
  
  std::cout<<"_drawArrow pos X "<<positionX << std::endl;
  std::cout<<"_drawArrow pos Y "<<positionY << std::endl;
  size = 10;
  Colour c;
  c.r = 0;
  c.g = 0;
  c.b = 0;
  c.a = 255;
  switch (direction)
  {
    case 0 :
    {
      for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX + (size / 2), positionY + i + (size / 2)); 
      }
      for (int i = 0; i < (size / 2) - 1; ++i)
      {
        img->setPixel(c, positionX + i + (size / 2), positionY + size - i + (size / 2));
        img->setPixel(c, positionX - i + (size / 2), positionY + size - i + (size / 2));
      }
      break;
    }
    case 1 :
    {
      for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX + size - i + (size / 2), positionY + i + (size / 2)); 
      }
      for (int i = 0; i < (size / 2) - 1; ++i)
      {
        img->setPixel(c, positionX + i + (size / 2), positionY + size + (size / 2));
        img->setPixel(c, positionX + (size / 2), positionY + size - i + (size / 2));
      }
      break;
    }
    case 2 :
    {
      for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX + i + (size / 2), positionY + (size / 2) + (size / 2)); 
      }
      for (int i = 0; i < (size / 2) - 1; ++i)
      {
        img->setPixel(c, positionX + i + (size / 2), positionY + (size / 2) - i + (size / 2));
        img->setPixel(c, positionX + i + (size / 2), positionY + (size / 2) + i + (size / 2));
      }
      break;
    }
    case 3 :
    {
    for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX + i + (size / 2), positionY + i + (size / 2)); 
      }
      for (int i = 0; i < (size / 2) - 1; ++i)
      {
        img->setPixel(c, positionX + i + (size / 2), positionY + (size / 2));
        img->setPixel(c, positionX + (size / 2), positionY + i + (size / 2));
      }
      break;
    }
    case 4 :
    {
      for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX + (size / 2) + (size / 2), positionY + i + (size / 2)); 
      }
      for (int i = 0; i < (size / 2) - 1; ++i)
      {
        img->setPixel(c, positionX + (size / 2) + i + (size / 2), positionY + i + (size / 2));
        img->setPixel(c, positionX + (size / 2) - i + (size / 2), positionY + i + (size / 2));
      }
      break;
    }

    case 5 :
    {
    for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX + size - i + (size / 2), positionY + i + (size / 2)); 
      }
      for (int i = 0; i < (size / 2) - 1; ++i)
      {
        img->setPixel(c, positionX + size - i + (size / 2), positionY + (size / 2));
        img->setPixel(c, positionX + size + (size / 2), positionY + i + (size / 2));
      }
      break;
    }
    case 6 :
    {
      for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX + i + (size / 2), positionY + (size / 2) + (size / 2)); 
      }
      for (int i = 0; i < (size / 2) - 1; ++i)
      {
        img->setPixel(c, positionX + size - i + (size / 2), positionY + (size / 2) - i + (size / 2));
        img->setPixel(c, positionX + size - i + (size / 2), positionY + (size / 2) + i + (size / 2));
      }
      break;
    }
    case 7 :
    {
      for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX + i + (size / 2), positionY + i + (size / 2));  
      }
      for (int i = 0; i < (size / 2) - 1; ++i)
      {
        img->setPixel(c, positionX + size - i + (size / 2), positionY + size + (size / 2));
        img->setPixel(c, positionX + size + (size / 2), positionY + size - i + (size / 2));
      }
      break;
    }
  }
  std::cout<<"_drawArrow fin " << std::endl;
}
