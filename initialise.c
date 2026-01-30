#include "utils.h"

void initLevelPoints(struct Point levelPoints[ROWS][COLS])
{
  int spacing = 6;
  int X = -30.0f;
  int Y = -30.0f;

  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      levelPoints[i][j].pos = (Vector3){X, 0.0, Y};
      levelPoints[i][j].pointState = NOPOINT;
      X += spacing;
    }
    X = -30.0f;
    Y += spacing;
  }
}
