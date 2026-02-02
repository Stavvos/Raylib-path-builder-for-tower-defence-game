#include "raylib.h"

#ifndef UTILS_H
#define UTILS_H

#define ROWS 10
#define COLS 10

typedef enum PointState
{
  STARTPOINT,
  PATHPOINT,
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
  ADDPATHPOINT,
  REMOVEPATHPOINT
} EditState;

struct EditMode
{
  EditState editState;
};

struct Point
{
  Vector3 pos;
  PointState pointState;
};

struct Cam
{
  CameraState cameraState;
};

#endif
