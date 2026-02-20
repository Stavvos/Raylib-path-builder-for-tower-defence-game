#define RAYGUI_IMPLEMENTATION
#include "dependencies/raygui.h"

void renderButtons(struct EditMode* editMode)
{
  if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "START POINT"))
  {
    editMode->editState = ADDSTARTPOINT;
  }
  
  if (GuiButton((Rectangle){ 24, 56, 120, 30 }, "UP"))
  {
    editMode->editState = ADDUPDIRECTION;
  }
  
  if (GuiButton((Rectangle){ 24, 88, 120, 30 }, "DOWN"))
  {
    editMode->editState = ADDDOWNDIRECTION; 
  }

  if (GuiButton((Rectangle){ 24, 120, 120, 30 }, "LEFT"))
  {
  
    editMode->editState = ADDLEFTDIRECTION; 
  }
  
  if (GuiButton((Rectangle){ 24, 152, 120, 30 }, "RIGHT"))
  {
  
    editMode->editState = ADDRIGHTDIRECTION; 
  }

  if (GuiButton((Rectangle){ 24, 184, 120, 30 }, "REMOVE POINT"))
  {
    editMode->editState = REMOVEPATHPOINT;
  }

  if (GuiButton((Rectangle){ 24, 216, 120, 30 }, "TEST PATH"))
  {
  
  }
  
  if (GuiButton((Rectangle){ 24, 248, 120, 30 }, "EXPORT PATH"))
  {
  }
}
