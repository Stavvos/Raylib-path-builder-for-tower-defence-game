#include "raylib.h"
#include "utils.h"
#include "dependencies/cJSON.h"

// Function to serialize a Vector3 to JSON
cJSON* vector3_to_json(Vector3 v) {
  cJSON* json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "x", v.x);
  cJSON_AddNumberToObject(json, "y", v.y);
  cJSON_AddNumberToObject(json, "z", v.z);
  return json;
}

// Function to serialize a Point struct to JSON
cJSON* pathToJson(struct Point point) {
  
  cJSON* json = cJSON_CreateObject();
  cJSON_AddItemToObject(json, "point", vector3_to_json(point.pos));

  return json;
}

// Function to write the array of paths to a JSON file
void writePathToJson(Node* head, const char* fileName) {
  
  cJSON* jsonArray = cJSON_CreateArray();
 
  Node* current = head;

  while (current != NULL)
  {
    cJSON* pathJson = pathToJson(current->point);
    cJSON_AddItemToArray(jsonArray, pathJson);
    current = current->next; 
  } 

  char* jsonString = cJSON_Print(jsonArray);

  // Write the JSON string to a file
  FILE* file = fopen(fileName, "w");
  if (file)
  {
     fprintf(file, "%s", jsonString);
     fclose(file);
     printf("Data written to %s\n", fileName);
  }
  else
  {
     printf("Error opening file for writing\n");
  }

  // Clean up
  cJSON_Delete(jsonArray);
  free(jsonString);
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
