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
  
  //vertical path
  struct Path verticalPath;
  verticalPath.width = 3.0f;
  verticalPath.height = 6.0f;
  verticalPath.centre.y = 0.6f;
  verticalPath.mesh = GenMeshCube(verticalPath.width, 1.0f, verticalPath.height);
  verticalPath.model = LoadModelFromMesh(verticalPath.mesh);
  
  //horizontal path 
  struct Path horizontalPath;
  horizontalPath.width = 6.0f;
  horizontalPath.height = 3.0f;
  horizontalPath.centre.y = 0.6f;
  horizontalPath.mesh = GenMeshCube(horizontalPath.width, 1.0f, horizontalPath.height);
  horizontalPath.model = LoadModelFromMesh(horizontalPath.mesh);

  //corner path
  struct Path cornerPath;
  cornerPath.width = 3.0f;
  cornerPath.height = 3.0f;
  cornerPath.centre = levelPoints[1][0].pos;
  cornerPath.centre.y = 0.6f;
  cornerPath.mesh = GenMeshCube(cornerPath.width, 1.0f, cornerPath.height);
  cornerPath.model = LoadModelFromMesh(cornerPath.mesh);
  
  struct Path pathPieces[ROWS*COLS];
  for (int i = 0; i < ROWS*COLS; i++)
  {
    pathPieces[i].draw = false;
  }

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
      //Update
      switchCameraMode(&camera, &cam); 
      pointStateAllocator(levelPoints, camera, &editMode);
      findStartPoints(levelPoints, pathPieces, horizontalPath, verticalPath);
       
      BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //render 3D goes here
        BeginMode3D(camera);
          renderLevel(level);
	  renderPositionPoints(levelPoints);
          renderPath(pathPieces);	  
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
