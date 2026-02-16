#include "utils.h"
#include "raylib.h"

void renderLevel(struct Level level)
{
  DrawModelEx(level.model, level.centre, (Vector3){ 0, 1, 0 }, 0.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, GREEN);
}

void renderPath(struct Path pathPieces[], struct Path cornerPieces[])
{
 for (int i = 0; i < ROWS*COLS; i++)
 {
    if (pathPieces[i].draw == true)
    {
      DrawModelEx(pathPieces[i].model,
      pathPieces[i].centre,
      (Vector3){ 0, 1, 0 },
      0.0f,
      (Vector3){ 1.0f, 1.0f, 1.0f },
      BROWN);
    }
  }

  for (int i = 0; i < ROWS*COLS; i++)
  {
    if(cornerPieces[i].draw == true)
    {
       DrawModelEx(cornerPieces[i].model,
       cornerPieces[i].centre,
       (Vector3){ 0, 1, 0 },
       0.0f,
       (Vector3){ 1.0f, 1.0f, 1.0f },
       BROWN);
    }
  }
}

void renderPositionPoints(struct Point levelPoints[ROWS][COLS])
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
