#include "raylib.h"

void buildPath(Node* head, struct Point point)
{
  //no head case
  if (head == NULL)
  {
    return;
  }
  
  Node* current = head;

  //only head case
  if (current->next == NULL)
  {
    pushEnd(head, point);
    return; 
  }

  //more than head case
  while (current->next != NULL)
  {
    current = current->next;
  }

  pushEnd(head, point);
}

void pathClickHandler(struct Point points[ROWS][COLS], Camera3D camera, struct EditMode* editMode, Node* head)
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
	  buildPath(head, points[i][j]);
        }	
	else if (collision.hit && editMode->editState == ADDPOINT && points[i][j].pointState != DOUBLEPOINT)
        {
          points[i][j].pointState = POINT;
	  buildPath(head, points[i][j]);
        }
      }
    }
  }

  printLinkedList(head);
}
