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
        if (collision.hit && editMode->editState == ADDPATHPOINT)
        {
          points[i][j].pointState = PATHPOINT;
        }
        else if (collision.hit && editMode->editState == ADDSTARTPOINT)
        {
          points[i][j].pointState = STARTPOINT;
        }
        else if (collision.hit && editMode->editState == REMOVEPATHPOINT)
        {
          points[i][j].pointState = NOPOINT;
        }
      }
    }
  }
}
