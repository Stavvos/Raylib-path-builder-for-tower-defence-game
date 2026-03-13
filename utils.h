#include "raylib.h"

#ifndef UTILS_H
#define UTILS_H

#define ROWS 20 
#define COLS 20 
#define SPACING 3 
#define POSX -30.0f
#define POSZ -30.0f

struct Level
{
  float width;
  float height;
  Vector3 centre;
  Mesh mesh;
  Model model;
};

struct Path
{
  float width;
  float height;
  Vector3 centre;
  Mesh mesh;
  Model model;
};

typedef enum PointState
{
  POINT,
  DOUBLEPOINT,
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
  ADDPOINT,
  UNDO, 
  EXPORT
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

typedef struct Node
{
  struct Point point;
  struct Node* next;
} Node;

//function declarations
void printLinkedList(Node* head);
void pushEnd(Node** head, struct Point newPoint);
bool popBack(Node** head);
void deleteLinkedList(Node** head);

#endif
