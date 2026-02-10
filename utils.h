#include "raylib.h"

#ifndef UTILS_H
#define UTILS_H

#define ROWS 10 
#define COLS 10 

typedef enum PointState
{
  STARTPOINT,
  NOPOINT
} PointState;

typedef enum CameraState
{
  FREEROAM,
  FIXED
} CameraState;

typedef enum EditState
{
  NULLSTATE, 
  ADDSTARTPOINT,
  REMOVEPATHPOINT,
  ADDUPDIRECTION,
  ADDDOWNDIRECTION,
  ADDLEFTDIRECTION,
  ADDRIGHTDIRECTION
} EditState;

typedef enum Direction
{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  NODIRECTION
} Direction;

struct EditMode
{
  EditState editState;
};

struct Point
{
  Vector3 pos;
  PointState pointState;
  Direction direction;
};

struct Cam
{
  CameraState cameraState;
};

#endif
