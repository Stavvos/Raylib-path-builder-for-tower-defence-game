#include "utils.h"
#include "raylib.h"
#include "string.h"
#include <stdio.h>

bool visited[ROWS][COLS];

void dfs(int i, int j, struct Point points[ROWS][COLS])
{
  //exit case
  if(i < 0 || i >= ROWS || j < 0 || j >= COLS || visited[i][j] == true)
  {
    return;
  }

  visited[i][j] = true;

  //left
  if (j - 1 >= 0 && visited[i][j - 1] == false && points[i][j - 1].direction == LEFT)
  {
      DrawLine3D(points[i][j].pos, points[i][j - 1].pos, BLACK);
      dfs(i, j - 1, points);
  }

  //right 
  if (j + 1 < COLS && visited[i][j + 1] == false && points[i][j + 1].direction == RIGHT)
  {
      DrawLine3D(points[i][j].pos, points[i][j + 1].pos, BLACK);
      dfs(i, j + 1, points);
  }
  
  //up
  if (i - 1 >= 0 && visited[i - 1][j] == false && points[i - 1][j].direction == UP)
  {
      DrawLine3D(points[i][j].pos, points[i - 1][j].pos, BLACK);
      dfs(i - 1, j, points);
  }

  //down
  if (i + 1 < ROWS && visited[i + 1][j] == false && points[i + 1][j].direction == DOWN)
  {
      DrawLine3D(points[i][j].pos, points[i + 1][j].pos, BLACK);
      dfs(i + 1, j, points);
  }
}

void iterateLevelPoints(struct Point points[ROWS][COLS])
{
  //reset the bool array. This way uses less instruction calls when compared to the nested for loop method
  memset(visited, false, sizeof(visited));

  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      if(points[i][j].pointState == STARTPOINT)
      {
        dfs(i, j, points);
      }
    }
  }
}

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
