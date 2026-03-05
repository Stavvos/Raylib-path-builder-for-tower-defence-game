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
  level->width = (ROWS - 1.0f) * SPACING;
  level->height = (COLS - 1.0f) * SPACING;
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
      X += SPACING;
    }
    X = POSX;
    Z += SPACING;
  }
}

void initPathPiece(struct Path* path)
{
  //corner path
  path->width = 3.0f;
  path->height = 3.0f;
  path->centre.y = 0.0f;
  path->mesh = GenMeshCube(path->width, 0.0f, path->height);
  path->model = LoadModelFromMesh(path->mesh);
}
