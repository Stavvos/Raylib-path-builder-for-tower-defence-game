#include "raylib.h"
#include "utils.h"
#include "initialise.c"
#include "render.c"
#include "GUI.c"
#include "camera.c"
#include "path.c"

int main(void)
{
  // Initialization
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();

  InitWindow(screenWidth, screenHeight, "Level Editor");

  // Define the camera to look into our 3d world
  Camera3D camera = { 0 };
  camera.position = (Vector3){ 0.0f, 90.0f, 0.0f }; // Camera position
  camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
  camera.up = (Vector3){ 0.0f, 0.0f, -1.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

  SetTargetFPS(60);                  
    
  //initialise level points matrix
  struct Point levelPoints[ROWS][COLS];
  initLevelPoints(levelPoints); 

  struct Cam cam;
  cam.cameraState = FIXED;
  
  struct EditMode editMode;
  editMode.editState = NULLSTATE;

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
      //Update
      switchCameraMode(&camera, &cam); 
      pointStateAllocator(levelPoints, camera, &editMode);
      
      BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //render 3D goes here
        BeginMode3D(camera);
          renderLevel(levelPoints);
          iterateLevelPoints(levelPoints);
        EndMode3D();

        //render 2D goes here
        
        //GUI
        renderButtons(&editMode);

      EndDrawing();
    }
  
  // Close window and OpenGL context
  CloseWindow();

  return 0;
}
