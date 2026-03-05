#include "raylib.h"

void pathClickHandler(struct Point points[ROWS][COLS], Camera3D camera, struct EditMode* editMode, Node** head)
{
  Ray ray = GetMouseRay(GetMousePosition(), camera);
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    for (int i = 0; i < ROWS; i++)
    {
      for (int j = 0; j < COLS; j++)
      {
        RayCollision collision = GetRayCollisionSphere(ray, points[i][j].pos, 0.5);
        
        if (collision.hit && editMode->editState == ADDPOINT && points[i][j].pointState == POINT)
        {
          points[i][j].pointState = DOUBLEPOINT;
	  pushEnd(head, points[i][j]);
        }	
	else if (collision.hit && editMode->editState == ADDPOINT && points[i][j].pointState != DOUBLEPOINT)
        {
          points[i][j].pointState = POINT;
	  pushEnd(head, points[i][j]);
        }
      }
    }
  }

  printLinkedList(*head);
}
