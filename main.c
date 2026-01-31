#include "raylib.h"
#include "utils.h"
#include "initialise.c"
#include "render.c"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

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

int main(void)
{
    // Initialization
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "Level Editor");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    SetTargetFPS(60);                  
    
    //initialise level points matrix
    struct Point levelPoints[ROWS][COLS];
    initLevelPoints(levelPoints); 
    
    struct Cam cam;
    cam.cameraState = FIXED;

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        //Update
        switchCameraMode(&camera, &cam); 

        BeginDrawing();
          ClearBackground(RAYWHITE);
        
       	//render 3D goes here
          BeginMode3D(camera);
            renderLevel(levelPoints); 
	  EndMode3D();

        //render 2D goes here
        
	//GUI
        if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "START POINT"));        
        if (GuiButton((Rectangle){ 24, 56, 120, 30 }, "PATH POINT"));        
        if (GuiButton((Rectangle){ 24, 88, 120, 30 }, "REMOVE POINT"));        
        if (GuiButton((Rectangle){ 24, 120, 120, 30 }, "TEST PATH"));        
        if (GuiButton((Rectangle){ 24, 152, 120, 30 }, "EXPORT PATH"));        
	
	EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}
