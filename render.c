#include "utils.h"
#include "raylib.h"

void renderLevel(struct Point levelPoints[ROWS][COLS])
{
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      if (levelPoints[i][j].direction != NODIRECTION)
      {	      
        DrawSphere(levelPoints[i][j].pos, 0.25, BLUE);
      }
      else if (levelPoints[i][j].pointState == STARTPOINT)
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
