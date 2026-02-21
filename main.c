#include "raylib.h"
#include "utils.h"
#include "initialise.c"
#include "render.c"
#include "GUI.c"
#include "camera.c"
#include "path.c"
#include "raymath.h"
#include "dependencies/cJSON.h"

// Function to serialize a Vector3 to JSON
cJSON* vector3_to_json(Vector3 v) {
  cJSON* json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "x", v.x);
  cJSON_AddNumberToObject(json, "y", v.y);
  cJSON_AddNumberToObject(json, "z", v.z);
  return json;
}

// Function to serialize a PathType to JSON
const char* path_type_to_string(PathType type) {
 switch (type) 
 {
   case UPPATH: return "UPPATH";
   case DOWNPATH: return "DOWNPATH";
   case LEFTPATH: return "LEFTPATH";
   case RIGHTPATH: return "RIGHTPATH";
   case NULLTYPE: return "NULLTYPE";
   default: return "UNKNOWN";
 }
}

// Function to serialize a Path struct to JSON
cJSON* path_to_json(struct Path path) {
  cJSON* json = cJSON_CreateObject();

  // Add primitive types to the JSON object
  cJSON_AddNumberToObject(json, "width", path.width);
  cJSON_AddNumberToObject(json, "height", path.height);
  cJSON_AddItemToObject(json, "centre", vector3_to_json(path.centre));
  cJSON_AddStringToObject(json, "pathType", path_type_to_string(path.pathType));
  cJSON_AddBoolToObject(json, "draw", path.draw);

  return json;
}

// Function to write the array of paths to a JSON file
void write_paths_to_json(struct Path* paths, const char* filename) {
  cJSON* json_array = cJSON_CreateArray();

  // Iterate over the array and convert each Path to a JSON object
  int i = 0; 
  while(paths[i].pathType != NULLTYPE)
  {
     cJSON* path_json = path_to_json(paths[i]);
     cJSON_AddItemToArray(json_array, path_json);
     i++;
  }

  // Convert the JSON array to a string
  char* json_string = cJSON_Print(json_array);

  // Write the JSON string to a file
  FILE* file = fopen(filename, "w");
  if (file) 
  {
     fprintf(file, "%s", json_string);
     fclose(file);
     printf("Data written to %s\n", filename);
  } 
  else 
  {
     printf("Error opening file for writing\n");
  }

  // Clean up
  cJSON_Delete(json_array);
  free(json_string);
}

// Function to serialize level struct to JSON
cJSON* levelToJson(struct Level level) 
{
  cJSON* json = cJSON_CreateObject();

  // Add primitive types to the JSON object
  cJSON_AddNumberToObject(json, "width", level.width);
  cJSON_AddNumberToObject(json, "height", level.height);
  cJSON_AddItemToObject(json, "centre", vector3_to_json(level.centre));
  cJSON_AddNumberToObject(json, "ROWS", ROWS);
  cJSON_AddNumberToObject(json, "COLS", COLS);
  cJSON_AddNumberToObject(json, "SPACING", SPACING);
  cJSON_AddNumberToObject(json, "POSX", POSX);
  cJSON_AddNumberToObject(json, "POSZ", POSZ);
  
  return json;
}

// Function to write level to JSON file 
void writeLevelTojson(struct Level level, const char* filename) {
  cJSON* jsonArray = cJSON_CreateArray();

  // Iterate over the array and convert each Path to a JSON object
  cJSON* levelJson = levelToJson(level);
  cJSON_AddItemToArray(jsonArray, levelJson);

  // Convert the JSON array to a string
  char* jsonString = cJSON_Print(jsonArray);

  // Write the JSON string to a file
  FILE* file = fopen(filename, "w");
  if (file) 
  {
     fprintf(file, "%s", jsonString);
     fclose(file);
     printf("Data written to %s\n", filename);
  } 
  else 
  {
     printf("Error opening file for writing\n");
  }

  // Clean up
  cJSON_Delete(jsonArray);
  free(jsonString);
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
      
      if (editMode.editState == EXPORT)
      {
        write_paths_to_json(pathPieces, "JSON/paths.json");
        writeLevelTojson(level, "JSON/level.json");
	editMode.editState = NULLSTATE;
      }

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
