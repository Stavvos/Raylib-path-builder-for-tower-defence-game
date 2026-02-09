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
  camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
  camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

  SetTargetFPS(60);                  
  
  //height map  
  Image image = LoadImage("heightMap/heightMap.png");// Load heightmap image (RAM)
  Texture2D texture = LoadTextureFromImage(image);// Convert image to texture (VRAM)
  
  //the levelPoints matrix: rows = 9, spacing = 6; therefore the mesh row and col is  9 * 6 = 54
  Mesh levelMesh = GenMeshHeightmap(image, (Vector3){ 54, 1, 54 }); // Generate heightmap mesh (RAM and VRAM)
  Model levelModel = LoadModelFromMesh(levelMesh);// Load model from generated mesh

  levelModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set map diffuse texture
  Vector3 levelModelPosition = { -30.0f, 0.0f, -30.0f };// Define model position

  UnloadImage(image);// Unload heightmap image from RAM, already uploaded to VRAM 
    
  //initialise level points matrix
  struct Point levelPoints[ROWS][COLS];
  Matrix transform = MatrixIdentity(); // Start with identity
  transform = MatrixTranslate(levelModelPosition.x, levelModelPosition.y, levelModelPosition.z);
  initLevelPoints(levelPoints, levelMesh, transform); 
 
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
          DrawModel(levelModel, levelModelPosition, 1.0f, GREEN);

        EndMode3D();

        //render 2D goes here
        //GUI
        renderButtons(&editMode);

      EndDrawing();
    }
  
  //de-initialise
  UnloadTexture(texture);     // Unload texture
  UnloadModel(levelModel);
  //Close window and OpenGL context
  CloseWindow();


  return 0;
}
