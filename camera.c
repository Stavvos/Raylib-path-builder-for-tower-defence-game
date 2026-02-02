#include "utils.h"
#include "raylib.h"

void switchCameraMode(Camera3D* camera, struct Cam* cam)
{
  if(IsKeyPressed(KEY_C) && cam->cameraState == FIXED)
  {
    cam->cameraState = FREEROAM;
  }
  else if (IsKeyPressed(KEY_C) && cam->cameraState == FREEROAM)
  {
    cam->cameraState = FIXED;
  }

  if(cam->cameraState == FREEROAM)
  {
    UpdateCamera(camera, CAMERA_FREE);
  }
}
