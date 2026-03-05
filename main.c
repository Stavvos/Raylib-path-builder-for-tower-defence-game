#include "raylib.h"
#include "utils.h"
#include "initialise.c"
#include "render.c"
#include "GUI.c"
#include "camera.c"
#include "path.c"
#include "raymath.h"
#include "export.c"

void testLinkedList()
{
  //linked list practice  
  Node* head = NULL;

  head = (Node*) malloc(sizeof(Node));

  /*if (head == NULL)
  {
    return 1;
  }*/
  
  head->point.pos = (Vector3){0.0f,0.0f,0.0f};
  head->next = (Node*)malloc(sizeof(Node));
  head->next->point.pos = (Vector3){1.0f, 0.0f, 0.0f};
  head->next->next = NULL;

  //print values of the linked list
  printLinkedList(head);
  
  struct Point testPoint;
  testPoint.pos = (Vector3){2.0f, 0.0f, 0.0f};
 
  //append value to end of the linked list
  pushEnd(head, testPoint);
  printLinkedList(head);
  
  //append value to the front of the linked list
  pushFront(&head, testPoint);
  printLinkedList(head);
  
  //remove the first item of the linked list
  popFront(&head);
  printLinkedList(head);
  
  //remove the last item of the linked list 
  popBack(head);
  printLinkedList(head);
  
  //remove item in linked list as per a vector3 search
  removeNodeByVectorValue(&head, testPoint.pos); 
  printLinkedList(head);
  
  // Free allocated memory from linked list
  deleteLinkedList(&head);
}

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
  struct Path pathPiece;
  initPathPiece(&pathPiece);
  
  //test linked list  
  testLinkedList();

  Node* head = NULL;
  head = (Node*) malloc(sizeof(Node));
  
  if (head == NULL)
  {
    return 1;
  }

  // Main game loop
  while (!WindowShouldClose())        // Detect window close button or ESC key
  {
    //Update
    switchCameraMode(&camera, &cam); 
    pathClickHandler(levelPoints, camera, &editMode, head);
          
    /*if (editMode.editState == EXPORT)
    {
      write_paths_to_json(pathPieces, "JSON/paths.json");
      write_paths_to_json(cornerPieces, "JSON/corners.json");
      writeLevelTojson(level, "JSON/level.json");
      editMode.editState = NULLSTATE;
    }*/

    BeginDrawing();
      ClearBackground(RAYWHITE);
        
      //render 3D goes here
      BeginMode3D(camera);
        renderLevel(level);
        renderPositionPoints(levelPoints);
        renderPath(head, pathPiece);
      EndMode3D();
       
      //render 2D goes here
      //GUI
      renderButtons(&editMode);

    EndDrawing();
  }
  
  //de-initialise
  UnloadModel(level.model);
  UnloadModel(pathPiece.model);
  
  if (head != NULL)
  {
    deleteLinkedList(&head);
  } 

  //Close window and OpenGL context
  CloseWindow();

  return 0;
}
