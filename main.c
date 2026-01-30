#include "raylib.h"

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

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        //Update
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
          ClearBackground(RAYWHITE);
        
	//render 3D goes here
          BeginMode3D(camera);
            DrawGrid(10, 1.0f);
          EndMode3D();

        //render 2D goes here
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

