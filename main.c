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

bool visitedPoints[ROWS][COLS];
int pathIndex = 0;

struct VerticalPath verticalPath;
struct HorizontalPath horizontalPath;

void searchLevelPoints(int i, int j, struct Point points[ROWS][COLS], struct Path pathPieces[])
{
  //exit case
  if(i < 0 || i >= ROWS || j < 0 || j >= COLS || visitedPoints[i][j] == true)
  {
    return;
  }

  visitedPoints[i][j] = true;

  //left
  if (j - 1 >= 0 && visitedPoints[i][j - 1] == false && points[i][j - 1].direction == LEFT)
  {
    pathPieces[pathIndex].width = 6.0f;
    pathPieces[pathIndex].height = 3.0f; 
    pathPieces[pathIndex].centre = midpoint(points[i][j].pos, points[i][j - 1].pos);
    pathPieces[pathIndex].centre.y = 0.6f;
    pathPieces[pathIndex].model = horizontalPath.model;
    pathPieces[pathIndex].draw = true;
    pathIndex++;
    searchLevelPoints(i, j - 1, points, pathPieces);
  }

  //right 
  if (j + 1 < COLS && visitedPoints[i][j + 1] == false && points[i][j + 1].direction == RIGHT)
  {
    pathPieces[pathIndex].width = 6.0f;
    pathPieces[pathIndex].height = 3.0f; 
    pathPieces[pathIndex].centre = midpoint(points[i][j].pos, points[i][j + 1].pos);
    pathPieces[pathIndex].centre.y = 0.6f;
    pathPieces[pathIndex].model = horizontalPath.model;
    pathPieces[pathIndex].draw = true;
    pathIndex++;
    searchLevelPoints(i, j + 1, points, pathPieces);
  }
  
  //up
  if (i - 1 >= 0 && visitedPoints[i - 1][j] == false && points[i - 1][j].direction == UP)
  {
    
    pathPieces[pathIndex].width = 3.0f;
    pathPieces[pathIndex].height = 6.0f; 
    pathPieces[pathIndex].centre = midpoint(points[i][j].pos, points[i - 1][j].pos);
    pathPieces[pathIndex].centre.y = 0.6f;
    pathPieces[pathIndex].model = verticalPath.model;
    pathPieces[pathIndex].draw = true;
    pathIndex++;
    searchLevelPoints(i - 1, j, points, pathPieces);
  }

  //down
  if (i + 1 < ROWS && visitedPoints[i + 1][j] == false && points[i + 1][j].direction == DOWN)
  {
    
    pathPieces[pathIndex].width = 3.0f;
    pathPieces[pathIndex].height = 6.0f; 
    pathPieces[pathIndex].centre = midpoint(points[i][j].pos, points[i + 1][j].pos);
    pathPieces[pathIndex].centre.y = 0.6f;
    pathPieces[pathIndex].model = verticalPath.model;
    pathPieces[pathIndex].draw = true;
    pathIndex++;
    searchLevelPoints(i + 1, j, points, pathPieces);
  }
}

void findStartPoints(struct Point points[ROWS][COLS], struct Path pathPieces[])
{
  //reset the bool array. This way uses less instruction calls when compared to the nested for loop method
  memset(visitedPoints, false, sizeof(visitedPoints));

  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      if(points[i][j].pointState == STARTPOINT)
      {
        searchLevelPoints(i, j, points, pathPieces);
      }
    }
  }
  
  pathIndex = 0;
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
  verticalPath.width = 3.0f;
  verticalPath.height = 6.0f;
  verticalPath.centre = midpoint(levelPoints[0][0].pos, levelPoints[1][0].pos);
  verticalPath.centre.y = 0.6f;
  verticalPath.mesh = GenMeshCube(verticalPath.width, 1.0f, verticalPath.height);
  verticalPath.model = LoadModelFromMesh(verticalPath.mesh);
  
  //horizontal path 
  horizontalPath.width = 6.0f;
  horizontalPath.height = 3.0f;
  horizontalPath.centre = midpoint(levelPoints[1][0].pos, levelPoints[1][1].pos);
  horizontalPath.centre.y = 0.6f;
  horizontalPath.mesh = GenMeshCube(horizontalPath.width, 1.0f, horizontalPath.height);
  horizontalPath.model = LoadModelFromMesh(horizontalPath.mesh);

  //corner path
  struct CornerPath cornerPath;
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
      findStartPoints(levelPoints, pathPieces);
       
      BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //render 3D goes here
        BeginMode3D(camera);
          renderLevel(levelPoints);
          DrawModelEx(levelModel, levelCentre, (Vector3){ 0, 1, 0 }, 0.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, GREEN);
	  
          for (int i = 0; i < ROWS*COLS; i++)
	  {
            if (pathPieces[i].draw == true)
	    {
	      DrawModelEx(pathPieces[i].model, 
	       	          pathPieces[i].centre, 
		          (Vector3){ 0, 1, 0 }, 
			  0.0f, 
		          (Vector3){ 1.0f, 1.0f, 1.0f }, 
		          BROWN);
	    }
	  }

        EndMode3D();

        //render 2D goes here
	//GUI
        renderButtons(&editMode);

      EndDrawing();
    }
  
  //de-initialise
  UnloadModel(levelModel);
  UnloadModel(verticalPath.model);
  UnloadModel(horizontalPath.model);
  UnloadModel(cornerPath.model);
  //Close window and OpenGL context
  CloseWindow();

  return 0;
}
