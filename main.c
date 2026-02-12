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
int counter = 0;

void searchLevelPoints(int i, int j, struct Point points[ROWS][COLS], struct VerticalPath verticalPaths[])
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
    searchLevelPoints(i, j - 1, points, verticalPaths);
  }

  //right 
  if (j + 1 < COLS && visitedPoints[i][j + 1] == false && points[i][j + 1].direction == RIGHT)
  {
    searchLevelPoints(i, j + 1, points, verticalPaths);
  }
  
  //up
  if (i - 1 >= 0 && visitedPoints[i - 1][j] == false && points[i - 1][j].direction == UP)
  {
    verticalPaths[counter].centre = midpoint(points[i][j].pos, points[i - 1][j].pos);
    verticalPaths[counter].draw = true;
    counter++;
    searchLevelPoints(i - 1, j, points, verticalPaths);
  }

  //down
  if (i + 1 < ROWS && visitedPoints[i + 1][j] == false && points[i + 1][j].direction == DOWN)
  {
    verticalPaths[counter].centre = midpoint(points[i][j].pos, points[i + 1][j].pos);
    verticalPaths[counter].draw = true;
    counter++;
    searchLevelPoints(i + 1, j, points, verticalPaths);
  }
}

void findStartPoints(struct Point points[ROWS][COLS], struct VerticalPath verticalPaths[])
{
  //reset the bool array. This way uses less instruction calls when compared to the nested for loop method
  memset(visitedPoints, false, sizeof(visitedPoints));

  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      if(points[i][j].pointState == STARTPOINT)
      {
        searchLevelPoints(i, j, points, verticalPaths);
      }
    }
  }

  counter = 0;
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
  struct VerticalPath verticalPath;
  verticalPath.width = 3.0f;
  verticalPath.height = 6.0f;
  verticalPath.centre = midpoint(levelPoints[0][0].pos, levelPoints[1][0].pos);
  verticalPath.centre.y = 0.6f;
  verticalPath.mesh = GenMeshCube(verticalPath.width, 1.0f, verticalPath.height);
  verticalPath.model = LoadModelFromMesh(verticalPath.mesh);
  
  //vertical paths 
  struct VerticalPath verticalPaths[ROWS*COLS];
  for (int i = 0; i < ROWS*COLS; i++)
  { 
    verticalPaths[i].width = 3.0f;
    verticalPaths[i].height = 6.0f;
    verticalPaths[i].centre.y = 0.6f;
    verticalPaths[i].mesh = GenMeshCube(verticalPath.width, 1.0f, verticalPath.height);
    verticalPaths[i].model = LoadModelFromMesh(verticalPath.mesh);
    verticalPaths[i].draw = false;
  } 

  //horizontal path 
  struct HorizontalPath horizontalPath;
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
  
    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
      //Update
      switchCameraMode(&camera, &cam); 
      pointStateAllocator(levelPoints, camera, &editMode);
      
      findStartPoints(levelPoints, verticalPaths);
       
      BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //render 3D goes here
        BeginMode3D(camera);
          renderLevel(levelPoints);
	  iterateLevelPoints(levelPoints);
          DrawModelEx(levelModel, levelCentre, (Vector3){ 0, 1, 0 }, 0.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, GREEN);
          
	  for (int i = 0; i < ROWS*COLS; i++)
	  {
            if (verticalPaths[i].draw == true)
	    {
	      DrawModelEx(verticalPaths[i].model, 
	       	          verticalPaths[i].centre, 
		          (Vector3){ 0, 1, 0 }, 
			  0.0f, 
		          (Vector3){ 1.0f, 1.0f, 1.0f }, 
		          BROWN);
	    }
	  }

/*          DrawModelEx(verticalPath.model, 
		      verticalPath.centre, 
		      (Vector3){ 0, 1, 0 }, 0.0f, 
		      (Vector3){ 1.0f, 1.0f, 1.0f }, 
		      BROWN);
          DrawModelEx(horizontalPath.model, 
		      horizontalPath.centre, 
		      (Vector3){ 0, 1, 0 }, 
		      0.0f, 
		      (Vector3){ 1.0f, 1.0f, 1.0f }, 
		      BROWN);
          DrawModelEx(cornerPath.model, 
		      cornerPath.centre, 
		      (Vector3){ 0, 1, 0 }, 
		      0.0f, 
		      (Vector3){ 1.0f, 1.0f, 1.0f }, 
		      BROWN);*/
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
