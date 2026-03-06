#define RAYGUI_IMPLEMENTATION
#include "dependencies/raygui.h"

void renderButtons(struct EditMode* editMode)
{
  if (GuiButton((Rectangle){ 24, 24, 156, 30 }, "BUILD PATH"))
  {
    editMode->editState = ADDPOINT;
  }

  if (GuiButton((Rectangle){ 24, 56, 156, 30 }, "UNDO LAST PIECE"))
  {
    editMode->editState = UNDO;
  }
}
