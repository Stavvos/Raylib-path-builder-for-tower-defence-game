#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void renderButtons()
{
  if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "START POINT"));
  if (GuiButton((Rectangle){ 24, 56, 120, 30 }, "PATH POINT"));
  if (GuiButton((Rectangle){ 24, 88, 120, 30 }, "REMOVE POINT"));
  if (GuiButton((Rectangle){ 24, 120, 120, 30 }, "TEST PATH"));
  if (GuiButton((Rectangle){ 24, 152, 120, 30 }, "EXPORT PATH"));
}
