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
  while (_continue && !_windowClosed && i < 1000)
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
      //declare a temporary color variable
      Colour c;
      //draw objectif
      c.r = 255;
      c.g = 0;
      c.b = 0;
      c.a = 255;
      for (int g = 0; g < SIZEPIXEL; ++g)
      {
        //_drawArrow(_goalPosX,_goalPosY, 0, 10, img);
        img->setPixel(c,_goalPosX + g, _goalPosY + g);
      }
      if(fabs(_robotPosX - _goalPosX) < 5 && fabs(_robotPosY - _goalPosY) < 5)
      {
        //Loop through image and set all pixels to red
        for(int x = width; x < width + SIZEPIXEL; x++)
        //int x = j ;
          for(int y = height; y < height + SIZEPIXEL; y++)
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
        for(int x = width; x < width + SIZEPIXEL; x++)
          for(int y = height; y < height + SIZEPIXEL; y++)
          {
            c.r = 255;
            c.g = 255;
            c.b = 255;
            c.a = 255;
            img->setPixel(c, x, y);
          }
          lastheight = height;
      }
      setRobotPos( j * SIZEPIXEL, i * SIZEPIXEL );
      step();
      float moveX = (float)_robot->getMoveX();
      float moveY = (float)_robot->getMoveY();
      float newSize = sqrt(pow(moveX, 2) + pow(moveY,2)) * (SIZEPIXEL / 4) + 3;
      //float newSize = 8;
      //float moveX = j * 20 - _sceneWidth / 2;
      //float moveY = i * 20 - _sceneHeight/ 2;
      std::cout << "_robotX " << moveX << "_robotY " << moveY << std::endl;
      if(moveX == 0)
      {
        if (moveY == 0)
        {
        }
        else if (moveY > 0)
        {
          _drawArrow(width, height, 0, newSize, img);
        }
        else if (moveY < 0)
        {
          _drawArrow(width, height, 4, newSize, img);
        }
      }
      else if (moveY == 0)
      {
        if (moveX > 0)
        {
          _drawArrow(width, height, 6, newSize, img);
        }
        else
        {
          _drawArrow(width, height, 2, newSize, img);
        }
      }
      else if (fabs(moveY / moveX) > 2.42)
      {
        if (moveY > 0)
        {
          _drawArrow(width, height, 0, newSize, img);
        }
        else
        {
          _drawArrow(width, height, 4, newSize, img);
        }
      }
      else if (fabs(moveY / moveX) > 0.41)
      {
        if (moveY > 0 && moveX > 0)
        {
          _drawArrow(width, height, 7, newSize, img);
        }
        else if (moveY > 0 && moveX < 0)
        {
          _drawArrow(width, height, 1, newSize, img);
        }
        else if (moveY < 0 && moveX > 0)
        {
          _drawArrow(width, height, 5, newSize, img);
        }
        else if (moveY < 0 && moveX < 0)
        {
          _drawArrow(width, height, 3, newSize, img);
        }
      }
      else
      {
        if(moveX < 0)
        {
          _drawArrow(width, height, 2, newSize, img);
        }
        else if (moveX > 0)
        {
          _drawArrow(width, height, 6, newSize, img);
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

  if ((fabs(_robot->getMoveX()) < 0.001 && fabs(_robot->getMoveY()) < 0.001) ||
    _robotPosX < 0 || _robotPosX >= _sceneWidth ||
    _robotPosY < 0 || _robotPosY >= _sceneHeight)
  {
    _continue = false;
  }
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
  //size = 10;
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
        img->setPixel(c, positionX + (SIZEPIXEL / 2), positionY + i + (SIZEPIXEL / 2)); 
      }
      for (int i = 0; i < SIZE_ARROW; ++i)
      {
        img->setPixel(c, positionX + i + (SIZEPIXEL / 2), positionY + size - i + (SIZEPIXEL / 2));
        img->setPixel(c, positionX - i + (SIZEPIXEL / 2), positionY + size - i + (SIZEPIXEL / 2));
      }
      break;
    }
    case 1 :
    {
      for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX - i + (SIZEPIXEL / 2), positionY + i + (SIZEPIXEL / 2)); 
      }
      for (int i = 0; i < SIZE_ARROW; ++i)
      {
        img->setPixel(c, positionX - size + i + (SIZEPIXEL / 2), positionY + size + (SIZEPIXEL / 2));
        img->setPixel(c, positionX - size + (SIZEPIXEL / 2), positionY + size - i + (SIZEPIXEL / 2));
      }
      break;
    }
    case 2 :
    {
      for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX - i + (SIZEPIXEL / 2), positionY + (SIZEPIXEL / 2)); 
      }
      for (int i = 0; i < SIZE_ARROW; ++i)
      {
        img->setPixel(c, positionX - size + i + (SIZEPIXEL / 2), positionY + (SIZEPIXEL / 2) - i);
        img->setPixel(c, positionX - size + i + (SIZEPIXEL / 2), positionY + (SIZEPIXEL / 2) + i);
      }
      break;
    }
    case 3 :
    {
    for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX - i + (SIZEPIXEL / 2), positionY - i + (SIZEPIXEL / 2)); 
      }
      for (int i = 0; i < SIZE_ARROW; ++i)
      {
        img->setPixel(c, positionX - size + i + (SIZEPIXEL / 2), positionY - size + (SIZEPIXEL / 2));
        img->setPixel(c, positionX - size + (SIZEPIXEL / 2), positionY - size + i + (SIZEPIXEL / 2));
      }
      break;
    }
    case 4 :
    {
      for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX + (SIZEPIXEL / 2), positionY - i + (SIZEPIXEL / 2)); 
      }
      for (int i = 0; i < SIZE_ARROW; ++i)
      {
        img->setPixel(c, positionX + (SIZEPIXEL / 2) + i, positionY - size + i + (SIZEPIXEL / 2));
        img->setPixel(c, positionX + (SIZEPIXEL / 2) - i, positionY - size + i + (SIZEPIXEL / 2));
      }
      break;
    }

    case 5 :
    {
    for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX + i + (SIZEPIXEL / 2), positionY - i + (SIZEPIXEL / 2)); 
      }
      for (int i = 0; i < SIZE_ARROW; ++i)
      {
        img->setPixel(c, positionX + size - i + (SIZEPIXEL / 2), positionY - size + (SIZEPIXEL / 2));
        img->setPixel(c, positionX + size + (SIZEPIXEL / 2), positionY - size + i + (SIZEPIXEL / 2));
      }
      break;
    }
    case 6 :
    {
      for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX + i + (SIZEPIXEL / 2), positionY + (SIZEPIXEL / 2)); 
      }
      for (int i = 0; i < SIZE_ARROW; ++i)
      {
        img->setPixel(c, positionX + size - i + (SIZEPIXEL / 2), positionY + (SIZEPIXEL / 2) - i);
        img->setPixel(c, positionX + size - i + (SIZEPIXEL / 2), positionY + (SIZEPIXEL / 2) + i);
      }
      break;
    }
    case 7 :
    {
      for (int i = 0; i < size; ++i)
      {
        img->setPixel(c, positionX + i + (SIZEPIXEL / 2), positionY + i + (SIZEPIXEL / 2));  
      }
      for (int i = 0; i < SIZE_ARROW; ++i)
      {
        img->setPixel(c, positionX + size - i + (SIZEPIXEL / 2), positionY + size + (SIZEPIXEL / 2));
        img->setPixel(c, positionX + size + (SIZEPIXEL / 2), positionY + size - i + (SIZEPIXEL / 2));
      }
      break;
    }
  }
  std::cout<<"_drawArrow fin " << std::endl;
}
