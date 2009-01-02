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
	for(int i=1;i<26;i++)
	{
		TPanel *pn=(TPanel*)(this->FindComponent("Panel"+IntToStr(i)));
		pn->Height=(int)(this->Height/5);
		pn->Width=(int)(this->Width/5);
		int x1=((i-1)%5)+1;
		int y1=(int)(((i-1)/5)+1);
		pn->Top=(((int)(x1-1))*((int)(this->Height/5)));
		pn->Left=((int)(y1-1)*((int)(this->Width/5)));
		// 1  2  3  4  5
		// 6  7  8  9  10
		// 11 12 13 14 15
		// 16 17 18 19 20
		// 21 22 23 24 25
	}
}
//---------------------------------------------------------------------------

