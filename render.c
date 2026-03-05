#include "utils.h"
#include "raylib.h"
#include <stddef.h>

void renderLevel(struct Level level)
{
  DrawModelEx(level.model, level.centre, (Vector3){ 0, 1, 0 }, 0.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, GREEN);
}

void renderPath(Node* head, struct Path cubePath)
{
  //no head case
  if (head == NULL)
  {
    return;
  }
  
  Node* current = head;

  while(current != NULL)
  { 
    DrawModelEx(cubePath.model,
                current->point.pos,
                (Vector3){ 0, 1, 0 },
                0.0f,
                (Vector3){ 1.0f, 1.0f, 1.0f },
                BROWN);
  
    current = current->next;
  }
}

void renderPositionPoints(struct Point levelPoints[ROWS][COLS])
{
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      if (levelPoints[i][j].pointState == POINT)
      {	      
        DrawSphere(levelPoints[i][j].pos, 0.25, BLUE);
      }
      else if (levelPoints[i][j].pointState == DOUBLEPOINT)
      {
        DrawSphere(levelPoints[i][j].pos, 0.25, RED); 
      }
      else
      { 
        DrawSphere(levelPoints[i][j].pos, 0.25, BLACK);
      }
    } 
  }
}
