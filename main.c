#include "raylib.h"
#include "utils.h"
#include "initialise.c"
#include "render.c"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Level Editor");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    SetTargetFPS(60);                  
    
    //initialise level points matrix
    struct Point levelPoints[ROWS][COLS];
    initLevelPoints(levelPoints); 
    
    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        //Update
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
          ClearBackground(RAYWHITE);
        
	//render 3D goes here
          BeginMode3D(camera);
            renderLevel(levelPoints); 
	  EndMode3D();

        //render 2D goes here
        
	//GUI
        if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "START POINT"));        
        if (GuiButton((Rectangle){ 24, 48, 120, 30 }, "PATH POINT"));        
        if (GuiButton((Rectangle){ 24, 72, 120, 30 }, "REMOVE POINT"));        
        if (GuiButton((Rectangle){ 24, 96, 120, 30 }, "TEST PATH"));        
        if (GuiButton((Rectangle){ 24, 120, 120, 30 }, "EXPORT PATH"));        
	
	EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

