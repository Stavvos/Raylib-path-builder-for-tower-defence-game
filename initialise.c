#include "utils.h"

void initCamera(Camera* camera, struct Cam* cam)
{
  camera->position = (Vector3){ 0.0f, 90.0f, 0.0f }; // Camera position
  camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
  camera->up = (Vector3){ 0.0f, 0.0f, -1.0f };          // Camera up vector (rotation towards target)
  camera->fovy = 45.0f;                                // Camera field-of-view Y
  camera->projection = CAMERA_PERSPECTIVE;             // Camera projection type
						       
  cam->cameraState = FIXED;
}

void initLevel(struct Level* level)
{
  level->width = (ROWS - 1.0f) * 6.0f;
  level->height = (COLS - 1.0f) * 6.0f;
  level->centre = (Vector3){-30.0f + level->width * 0.5f, 0.5f, -30.0f + level->height * 0.5f};
  level->mesh = GenMeshCube(level->width, 1.0f, level->height);
  level->model = LoadModelFromMesh(level->mesh);
}

void initLevelPoints(struct Point levelPoints[ROWS][COLS])
{
  int X = POSX;
  int Z = POSZ;

  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      levelPoints[i][j].pos = (Vector3){X, 1.0f, Z};
      levelPoints[i][j].pointState = NOPOINT;
      levelPoints[i][j].direction = NODIRECTION;
      X += SPACING;
    }
    X = POSX;
    Z += SPACING;
  }
}

void initPathPieces(struct Path* verticalPath, struct Path* horizontalPath, struct Path* cornerPath, struct Path cornerPieces[], struct Path pathPieces[])
{
  //vertical path
  verticalPath->width = 3.0f;
  verticalPath->height = 6.0f;
  verticalPath->centre.y = 0.6f;
  verticalPath->mesh = GenMeshCube(verticalPath->width, 1.0f, verticalPath->height);
  verticalPath->model = LoadModelFromMesh(verticalPath->mesh);

  //horizontal path 
  horizontalPath->width = 6.0f;
  horizontalPath->height = 3.0f;
  horizontalPath->centre.y = 0.6f;
  horizontalPath->mesh = GenMeshCube(horizontalPath->width, 1.0f, horizontalPath->height);
  horizontalPath->model = LoadModelFromMesh(horizontalPath->mesh);

  //corner path
  cornerPath->width = 3.0f;
  cornerPath->height = 3.0f;
  cornerPath->centre.y = 0.6f;
  cornerPath->mesh = GenMeshCube(cornerPath->width, 1.0f, cornerPath->height);
  cornerPath->model = LoadModelFromMesh(cornerPath->mesh);

  for(int i = 0; i < ROWS*COLS; i++)
  {
    cornerPieces[i] = *cornerPath;
  }

  for (int i = 0; i < ROWS*COLS; i++)
  {
    pathPieces[i].draw = false;
    pathPieces[i].pathType = NULLTYPE;
  }
}
