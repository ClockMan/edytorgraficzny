#include <vcl.h>
#pragma hdrstop
#include "Line.h"
#pragma package(smart_init)

__fastcall Line::Line(TWinControl* Owner, bool vertical) : TWinControl(Owner)
{
   Resize=false;
   Resized=false;
   Parent=Owner;
   Vertical=vertical;
   ShowHint=true;
}

