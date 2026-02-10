#include "raylib.h"
#include "utils.h"
#include "initialise.c"
#include "render.c"
#include "GUI.c"
#include "camera.c"
#include "path.c"
#include "raymath.h"

Vector3 midpoint(Vector3 a, Vector3 b)
{
    return (Vector3){
        (a.x + b.x) * 0.5f,
        (a.y + b.y) * 0.5f,
        (a.z + b.z) * 0.5f
    };
}

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
  float levelWidth = (ROWS - 1.0f) * 6.0f; 
  float levelHeight = (COLS - 1.0f) * 6.0f;
  Vector3 levelCentre = (Vector3){-30.0f + levelWidth * 0.5f, 0.5f, -30.0f + levelHeight * 0.5f};
  Mesh levelMesh = GenMeshCube(levelWidth, 1.0f, levelHeight);
  Model levelModel = LoadModelFromMesh(levelMesh);
  
  //vertical path
  float pathVerticalWidth = 3.0f;
  float pathVerticalHeight = 6.0f;
  Vector3 pathVerticalCentre = midpoint(levelPoints[0][0].pos, levelPoints[1][0].pos);
  pathVerticalCentre.y = 0.6; 
  Mesh pathVerticalMesh = GenMeshCube(pathVerticalWidth, 1.0f, pathVerticalHeight);
  Model pathVerticalModel = LoadModelFromMesh(pathVerticalMesh);
  
  //horizontal path 
  float pathHorizontalWidth = 6.0f;
  float pathHorizontalHeight = 3.0f;
  Vector3 pathHorizontalCentre = midpoint(levelPoints[1][0].pos, levelPoints[1][1].pos);
  pathHorizontalCentre.y = 0.6; 
  Mesh pathHorizontalMesh = GenMeshCube(pathHorizontalWidth, 1.0f, pathHorizontalHeight);
  Model pathHorizontalModel = LoadModelFromMesh(pathHorizontalMesh);

  float pathCornerWidth = 3.0f;
  float pathCornerHeight = 3.0f;
  Vector3 pathCornerCentre = levelPoints[1][0].pos;
  pathCornerCentre.y = 0.6; 
  Mesh pathCornerMesh = GenMeshCube(pathCornerWidth, 1.0f, pathCornerHeight);
  Model pathCornerModel = LoadModelFromMesh(pathCornerMesh);

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
          DrawModelEx(levelModel, levelCentre, (Vector3){ 0, 1, 0 }, 0.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, GREEN);
          DrawModelEx(pathVerticalModel, 
		      pathVerticalCentre, 
		      (Vector3){ 0, 1, 0 }, 0.0f, 
		      (Vector3){ 1.0f, 1.0f, 1.0f }, 
		      BROWN);
          DrawModelEx(pathHorizontalModel, 
		      pathHorizontalCentre, 
		      (Vector3){ 0, 1, 0 }, 
		      0.0f, 
		      (Vector3){ 1.0f, 1.0f, 1.0f }, 
		      BROWN);
          DrawModelEx(pathCornerModel, 
		      pathCornerCentre, 
		      (Vector3){ 0, 1, 0 }, 
		      0.0f, 
		      (Vector3){ 1.0f, 1.0f, 1.0f }, 
		      BROWN);
        EndMode3D();

        //render 2D goes here
	//GUI
        renderButtons(&editMode);

      EndDrawing();
    }
  
  //de-initialise
  UnloadModel(levelModel);
  UnloadModel(pathVerticalModel);
  UnloadModel(pathHorizontalModel);
  UnloadModel(pathCornerModel);
  //Close window and OpenGL context
  CloseWindow();


  return 0;
}
