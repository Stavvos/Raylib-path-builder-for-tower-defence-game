#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void renderButtons(struct EditMode* editMode)
{
  if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "START POINT"))
  {
    editMode->editState = ADDSTARTPOINT;
  }
  
  if (GuiButton((Rectangle){ 24, 56, 120, 30 }, "PATH POINT"))
  {
    editMode->editState = ADDPATHPOINT;
  }
  
  if (GuiButton((Rectangle){ 24, 88, 120, 30 }, "REMOVE POINT"))
  {
    editMode->editState = REMOVEPATHPOINT;
  }

  if (GuiButton((Rectangle){ 24, 120, 120, 30 }, "TEST PATH"))
  {
  
  }
  
  if (GuiButton((Rectangle){ 24, 152, 120, 30 }, "EXPORT PATH"))
  {
  
  }
}
