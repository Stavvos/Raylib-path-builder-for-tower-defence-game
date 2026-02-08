#include "raylib.h"

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
