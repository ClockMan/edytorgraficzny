//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
extern "C" __declspec(dllimport) TForm* show(TComponent*, TypeConfig*);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
   DLLHandle= LoadLibrary("../DLL/Bitmap24bit.dll");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
	  if(DLLHandle != NULL)
	  {
		 typedef TForm* ( *aAbout )(TComponent*, TypeConfig*);
		 aAbout z=(aAbout)GetProcAddress(DLLHandle, "_show");
		 TypeConfig *c=new TypeConfig("Bitmap24bit");
		 c->addBitmap("bitmapa", *(Form1->Image1->Picture->Bitmap));
		 z(Application, c);
		 //delete c;
	  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	  if(DLLHandle != NULL)
	  {
		 typedef bool ( *aAbout )(TypeConfig*);
		 aAbout z=(aAbout)GetProcAddress(DLLHandle, "_isValid");
		 TypeConfig *c=new TypeConfig("Bitmap24bit");
		 c->addBitmap("bitmapa", *(Form1->Image1->Picture->Bitmap));

		 ShowMessage(BoolToStr(z(c),true));
		 //delete c;
	  }
}
//---------------------------------------------------------------------------

