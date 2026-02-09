#include "utils.h"

void initLevelPoints(struct Point levelPoints[ROWS][COLS], Mesh level, Matrix transform)
{
  int spacing = 6;
  int X = -30.0f;
  int Z = -30.0f;
  
  Ray ray;
  ray.direction = (Vector3){0.0f,1.0f,0.0f};

  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      ray.position = (Vector3){X, 0.0f, Z};
      RayCollision hit = GetRayCollisionMesh(ray, level, transform);
      levelPoints[i][j].pos = (Vector3){X, hit.point.y, Z};
      levelPoints[i][j].pointState = NOPOINT;
      levelPoints[i][j].direction = NODIRECTION;
      X += spacing;
    }
    X = -30.0f;
    Z += spacing;
  }
}
