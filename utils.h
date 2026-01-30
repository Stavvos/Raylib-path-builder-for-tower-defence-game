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

struct Point
{
  Vector3 pos;
  PointState pointState;
};

#endif
