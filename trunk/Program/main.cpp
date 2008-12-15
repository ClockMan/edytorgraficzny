//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#include "engine/item.h"
#pragma hdrstop

#include "main.h"
#include "gui/Line.h"
#include "splash.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

void TForm1::OnLoadProgress(void* Sender, int position, int max, AnsiString info, int id)
{
	if (id==0) Form2->log->Caption="Zakoñczono wczytywanie typu: "+info;
	if (id==1) Form2->log->Caption="Zakoñczono wczytywanie funkcji: "+info;
	if (id==2) {
				Form2->log->Caption="B³êdna DLL typu: "+info;
				ShowMessage("B³êdna DLL typu: "+info);
			   }
	if (id==3) {
				Form2->log->Caption="B³êdna DLL funkcji: "+info;
				ShowMessage("B³êdna DLL funckji: "+info);
			   }
	Form2->ProgressBar1->Position=position;
	Form2->ProgressBar1->Max=max+1;
	Application->ProcessMessages();
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Application->CreateForm(__classid(TForm2), &Form2);
	Form2->ProgressBar1->Visible=false;
    Form2->Visible=true;
	AnsiString dir=ExtractFileDir(Application->ExeName);
	Form2->ProgressBar1->Visible=true;
	plugins.OnLoadingProgress=&OnLoadProgress;
	plugins.LoadData(dir+"\\blocks", dir+"\\types", *MainMenu1, *ImageList1, 3, 2, 0, 1);
	Form2->log->Caption="Wczytywanie interfejsu";
	Form2->ProgressBar1->Position=Form2->ProgressBar1->Max;
	Application->ProcessMessages();
	Sleep(500);
	Form1->Visible=true;
	Form1->Enabled=false;
	Application->ProcessMessages();
	Sleep(500);
	Form2->Visible=false;
	Form1->Enabled=true;
	delete Form2;
}
//---------------------------------------------------------------------------



