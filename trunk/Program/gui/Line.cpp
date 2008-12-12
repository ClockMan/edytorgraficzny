#include <vcl.h>
#pragma hdrstop
#include "Line.h"
#pragma package(smart_init)

__fastcall Line::Line(TWinControl* Owner, bool vertical) : TWinControl(Owner)
{
   moving=false;
   Resized=false;
   Parent=Owner;
   Vertical=vertical;
   ShowHint=true;
   CanBeMoved=true;
   OnLineMove=NULL;
   OnConnectionSelectRequest=NULL;
   OnMouseDown=LineMouseDown;
   OnMouseUp=LineMouseUp;
   OnMouseMove=LineMouseMove;
}


void __fastcall Line::LineMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (Button==mbLeft)
   {
	 //zaznaczamy
	 if (OnConnectionSelectRequest!=NULL)
			OnConnectionSelectRequest(this);
	 if (CanBeMoved) {
		moving=true;
		GetCursorPos(&oldPos);
	 }
   }
}

void __fastcall Line::LineMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	moving=false;
	Cursor=crDefault;
}

void __fastcall Line::LineMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	if (!moving) return;
	TPoint pos;
	GetCursorPos(&pos);
	if (Vertical)
	{
	   Cursor=crSizeWE;
	   this->Left=this->Left+pos.x-oldPos.x;
	   if (((pos.x-oldPos.x)!=0)&&(OnLineMove!=NULL))
			OnLineMove(this,pos.x-oldPos.x);
	}
	else
	{
	   Cursor=crSizeNS;
	   this->Top=this->Top+pos.y-oldPos.y;
	   if (((pos.y-oldPos.y)!=0)&&(OnLineMove!=NULL))
			OnLineMove(this,pos.y-oldPos.y);
	}
    oldPos=pos;
}

