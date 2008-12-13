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
   Visible=false;
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
	   {
			Resized=true;
			OnLineMove(this);
	   }
	}
	else
	{
	   Cursor=crSizeNS;
	   this->Top=this->Top+pos.y-oldPos.y;
	   if (((pos.y-oldPos.y)!=0)&&(OnLineMove!=NULL))
	   {
			Resized=true;
			OnLineMove(this);
	   }
	}
    oldPos=pos;
}

bool Line::setXY(int x1, int y1, int x2, int y2)
{
  if (x1==x2)
  {
	//pionowa
	if (y1-y2==0) { Visible=false; return false;}
	Left=x1-1;
	Width=3;
	Height=abs(y1-y2);
	Top=(y1<y2)?y1:y2;
	Visible=true;
	Vertical=true;
	return true;
  }
  else
  if (y1==y2) {
	//pozioma
	if (x1-x2==0) { Visible=false; return false;}
	Top=y1-1;
	Width=abs(x1-x2);
	Height=3;
	Left=(x1<x2)?x1:x2;
	Visible=true;
	Vertical=false;
	return true;
  }
  else
  {
   //skos
   Visible=false;
   return false;
  }
}

TPoint Line::getPoint1()
{
  TPoint tmp;
  tmp.x=Left+(Vertical)?-1:0;
  tmp.y=Top+(Vertical)?0:-1;
  return tmp;
}

TPoint Line::getPoint2()
{
  TPoint tmp;
  tmp.x=Left+Width+(Vertical)?-1:0;
  tmp.y=Top+Height+(Vertical)?0:-1;
  return tmp;
}

