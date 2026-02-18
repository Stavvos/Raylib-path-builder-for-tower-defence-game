#include "raylib.h"
#include "utils.h"
#include "initialise.c"
#include "render.c"
#include "GUI.c"
#include "camera.c"
#include "path.c"
#include "raymath.h"

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
  
  //level
  struct Level level;
  level.width = (ROWS - 1.0f) * 6.0f; 
  level.height = (COLS - 1.0f) * 6.0f;
  level.centre = (Vector3){-30.0f + level.width * 0.5f, 0.5f, -30.0f + level.height * 0.5f};
  level.mesh = GenMeshCube(level.width, 1.0f, level.height);
  level.model = LoadModelFromMesh(level.mesh);
  
   
  //initialise path pieces
  struct Path verticalPath;
  struct Path horizontalPath;
  struct Path cornerPath;
  struct Path cornerPieces[ROWS*COLS];
  struct Path pathPieces[ROWS*COLS];
  initPathPieces(&verticalPath, &horizontalPath, &cornerPath, cornerPieces, pathPieces);

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
      //Update
      switchCameraMode(&camera, &cam); 
      pointStateAllocator(levelPoints, camera, &editMode);
      findStartPoints(levelPoints, pathPieces, horizontalPath, verticalPath, cornerPieces);
            
      BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //render 3D goes here
        BeginMode3D(camera);
          renderLevel(level);
	  renderPositionPoints(levelPoints);
          renderPath(pathPieces, cornerPieces);
        EndMode3D();

        //render 2D goes here
	//GUI
        renderButtons(&editMode);

      EndDrawing();
    }
  
  //de-initialise
  UnloadModel(level.model);
  UnloadModel(verticalPath.model);
  UnloadModel(horizontalPath.model);
  UnloadModel(cornerPath.model);
  //Close window and OpenGL context
  CloseWindow();

  return 0;
}
