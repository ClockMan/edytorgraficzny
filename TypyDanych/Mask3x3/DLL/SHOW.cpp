//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SHOW.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
	for(int i=1;i<10;i++)
	{
		TPanel *pn=(TPanel*)(this->FindComponent("Panel"+IntToStr(i)));
		pn->Height=(int)(this->Height/3);
		pn->Width=(int)(this->Width/3);
		pn->Top=(((int)(i/3))*((int)(this->Height/3)));
		pn->Left=(((int)((i%3)-1))*((int)(this->Width/3)));
		// 1 2 3
		// 4 5 6
		// 7 8 9 
	}
}
//---------------------------------------------------------------------------

