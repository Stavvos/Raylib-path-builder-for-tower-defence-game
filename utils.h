#include "raylib.h"

#ifndef UTILS_H
#define UTILS_H

typedef enum PointState
{
  STARTPOINT,
  PATHPOINT,
  NOPOINT
} PointState;

struct Point
{
  Vector3 pos;
  PointState pointState;
};

#endif
