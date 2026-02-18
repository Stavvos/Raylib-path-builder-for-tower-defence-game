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

  SetTargetFPS(60);

  // Define the camera to look into our 3d world
  Camera3D camera = { 0 };
  struct Cam cam;
  initCamera(&camera, &cam);
   
  //initialise level points matrix
  struct Point levelPoints[ROWS][COLS];
  initLevelPoints(levelPoints); 
  
  struct EditMode editMode;
  editMode.editState = NULLSTATE;
  
  //level
  struct Level level;
  initLevel(&level);
   
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
