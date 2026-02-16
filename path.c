#include "raylib.h"

bool visitedPoints[ROWS][COLS];
int pathIndex = 0;

Vector3 midpoint(Vector3 a, Vector3 b)
{
    return (Vector3){
        (a.x + b.x) * 0.5f,
        (a.y + b.y) * 0.5f,
        (a.z + b.z) * 0.5f
    };
}

void leftPathInit(struct Path* pathPiece, struct Path horizontalPath, struct Point points[ROWS][COLS], int i, int j)
{
  *pathPiece = horizontalPath;
  pathPiece->centre = midpoint(points[i][j].pos, points[i][j - 1].pos);
  pathPiece->pathType = LEFTPATH;
  pathPiece->draw = true;
}

void rightPathInit(struct Path* pathPiece, struct Path horizontalPath, struct Point points[ROWS][COLS], int i, int j)
{
  *pathPiece = horizontalPath;
  pathPiece->centre = midpoint(points[i][j].pos, points[i][j + 1].pos);
  pathPiece->pathType = RIGHTPATH;
  pathPiece->draw = true;
}

void downPathInit(struct Path* pathPiece, struct Path verticalPath, struct Point points[ROWS][COLS], int i, int j)
{
  *pathPiece = verticalPath;
  pathPiece->centre = midpoint(points[i][j].pos, points[i + 1][j].pos);
  pathPiece->pathType = DOWNPATH;
  pathPiece->draw = true;
}

void upPathInit(struct Path* pathPiece, struct Path verticalPath, struct Point points[ROWS][COLS], int i, int j)
{
  *pathPiece = verticalPath;
  pathPiece->centre = midpoint(points[i][j].pos, points[i - 1][j].pos);
  pathPiece->pathType = UPPATH;
  pathPiece->draw = true;
}

void initCornerPathPiece(struct Path* cornerPiece, struct Point points[ROWS][COLS], int i, int j)
{
  if(points[i][j].pointState != STARTPOINT)
  {
    cornerPiece->centre = points[i][j].pos; 
    cornerPiece->draw = true;
  }
}

void searchLevelPoints(int i, int j, struct Point points[ROWS][COLS], struct Path pathPieces[], struct Path horizontalPath, struct Path verticalPath, struct Path cornerPieces[])
{
  //exit case
  if(i < 0 || i >= ROWS || j < 0 || j >= COLS || visitedPoints[i][j] == true)
  {
    return;
  }

  visitedPoints[i][j] = true;

  //left
  if (j - 1 >= 0 && visitedPoints[i][j - 1] == false && points[i][j - 1].direction == LEFT)
  {
    leftPathInit(&pathPieces[pathIndex], horizontalPath, points, i, j); 
    initCornerPathPiece(&cornerPieces[pathIndex], points, i, j);
    pathIndex++;
    searchLevelPoints(i, j - 1, points, pathPieces, horizontalPath, verticalPath, cornerPieces);
  }
  
  //right 
  if (j + 1 < COLS && visitedPoints[i][j + 1] == false && points[i][j + 1].direction == RIGHT)
  {
    rightPathInit(&pathPieces[pathIndex], horizontalPath, points, i, j); 
    initCornerPathPiece(&cornerPieces[pathIndex], points, i, j);
    pathIndex++;
    searchLevelPoints(i, j + 1, points, pathPieces, horizontalPath, verticalPath, cornerPieces);
  }

  //up
  if (i - 1 >= 0 && visitedPoints[i - 1][j] == false && points[i - 1][j].direction == UP)
  {
    upPathInit(&pathPieces[pathIndex], verticalPath, points, i, j);
    initCornerPathPiece(&cornerPieces[pathIndex], points, i, j);
    pathIndex++;
    searchLevelPoints(i - 1, j, points, pathPieces, horizontalPath, verticalPath, cornerPieces);
  }
  
  //down
  if (i + 1 < ROWS && visitedPoints[i + 1][j] == false && points[i + 1][j].direction == DOWN)
  {
    downPathInit(&pathPieces[pathIndex], verticalPath, points, i, j);
    initCornerPathPiece(&cornerPieces[pathIndex], points, i, j);
    pathIndex++;
    searchLevelPoints(i + 1, j, points, pathPieces, horizontalPath, verticalPath, cornerPieces);
  }
}

void findStartPoints(struct Point points[ROWS][COLS], struct Path pathPieces[], struct Path horizontalPath, struct Path verticalPath, struct Path cornerPieces[])
{
  //reset the bool array. This way uses less instruction calls when compared to the nested for loop method
  memset(visitedPoints, false, sizeof(visitedPoints));

  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      if(points[i][j].pointState == STARTPOINT)
      {
        searchLevelPoints(i, j, points, pathPieces, horizontalPath, verticalPath, cornerPieces);
      }
    }
  }

  pathIndex = 0;
}

void pointStateAllocator(struct Point points[ROWS][COLS], Camera3D camera, struct EditMode* editMode)
{
  Ray ray = GetMouseRay(GetMousePosition(), camera);
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    for (int i = 0; i < ROWS; i++)
    {
      for (int j = 0; j < COLS; j++)
      {
        RayCollision collision = GetRayCollisionSphere(ray, points[i][j].pos, 0.25);
        
	if (collision.hit && editMode->editState == ADDSTARTPOINT)
        {
          points[i][j].pointState = STARTPOINT;
        }
        else if (collision.hit && editMode->editState == REMOVEPATHPOINT)
        {
          points[i][j].pointState = NOPOINT;
	  points[i][j].direction = NODIRECTION;
        }
        else if (collision.hit && editMode->editState == ADDUPDIRECTION)
        {
          points[i][j].direction = UP;
        }
	else if (collision.hit && editMode->editState == ADDDOWNDIRECTION)
        {
          points[i][j].direction = DOWN;
        }
	else if (collision.hit && editMode->editState == ADDLEFTDIRECTION)
        {
          points[i][j].direction = LEFT;
        }
	else if (collision.hit && editMode->editState == ADDRIGHTDIRECTION)
        {
          points[i][j].direction = RIGHT;
        }
      }
    }
  }
}
