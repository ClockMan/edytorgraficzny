//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SHOW.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action=caFree;	
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
	for(int i=1;i<26;i++)
	{
		TPanel *pn=(TPanel*)(this->FindComponent("Panel"+IntToStr(i)));
		pn->Height=(int)(this->Height/5);
		pn->Width=(int)(this->Width/5);
		pn->Top=(((int)(i/5))*((int)(this->Height/5)));
		pn->Left=(((int)((i%5)-1))*((int)(this->Width/5)));
		// 1  2  3  4  5
		// 6  7  8  9  10
		// 11 12 13 14 15
		// 16 17 18 19 20
		// 21 22 23 24 25
	}
}
//---------------------------------------------------------------------------

