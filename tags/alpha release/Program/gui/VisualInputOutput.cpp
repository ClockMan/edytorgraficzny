#include <vcl.h>
#pragma hdrstop
#include "VisualInputOutput.h"
#pragma package(smart_init)

__fastcall VisualInputOutput::VisualInputOutput(Classes::TComponent* AOwner)
	: TPanel(Owner)
{
	Width = 17;
	Height = 17;
	Cursor = crHandPoint;
	BevelInner = bvLowered;
	BevelOuter = bvNone;
	ShowHint = True;
	BevelWidth = 2;
	BorderWidth = 0;
	//DoubleBuffered=true;
	OnShowHistory=NULL;
	ParentShowHint=false;
	OnMouseEnter=MouseEnterF;
	OnMouseLeave=MouseLeaveF;
	OnMouseDown=MouseDownF;
}

void __fastcall VisualInputOutput::MouseEnterF(TObject *Sender)
{
	this->BevelWidth=3;
}

void __fastcall VisualInputOutput::MouseLeaveF(TObject *Sender)
{
	 this->BevelWidth=2;
}

void __fastcall VisualInputOutput::MouseDownF(TObject *Sender, TMouseButton Button,
	  TShiftState Shift, int X, int Y)
{
   if ((this->OnShowHistory!=NULL)&&(Button==mbRight))
   {
		this->Enabled=false;
		this->OnShowHistory(Sender);
		this->Enabled=true;
   }
}
