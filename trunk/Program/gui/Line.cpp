#include <vcl.h>
#pragma hdrstop
#include "Line.h"
#pragma package(smart_init)

__fastcall TLine::TLine(TWinControl* Owner, bool vertical) : TWinControl(Owner)
{
   fresize=false;
   fresized=false;
   Parent=Owner;
   fvertical=vertical;
}

