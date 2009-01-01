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
#pragma link "cgauges"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

void TForm1::OnLoadProgress(void* Sender, int position, int max, AnsiString info, int id)
{
	if (id==0) {
				 Form2->log->Caption="Zakoñczono wczytywanie typu: "+info;
				 OnLogSuccess(NULL,"Wczytano typ: "+info);
			   }
	if (id==1) {
				 Form2->log->Caption="Zakoñczono wczytywanie funkcji: "+info;
				 OnLogSuccess(NULL,"Wczytano funkcjê: "+info);
			   }
	if (id==2) {
				 Form2->log->Caption="B³êdna DLL typu: "+info;
				 OnLogWarrning(NULL,"B³¹d podczas wczytywania typu, b³êdna DLL: "+info);
			   }
	if (id==3) {
				 Form2->log->Caption="B³êdna DLL funkcji: "+info;
				 OnLogWarrning(NULL,"B³¹d podczas wczytywania funkcji, b³êdna DLL: "+info);
			   }
	Form2->ProgressBar1->Position=position;
	Form2->ProgressBar1->Max=max+2;
	Application->ProcessMessages();
}

void  TForm1::OnFunctionAddClick(void* Sender)
{
	FunctionDLL* fs=(FunctionDLL*)Sender;
	piwo->AddBlock(fs->name);
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Application->CreateForm(__classid(TForm2), &Form2);
	//Form1->DoubleBuffered=true;
	Form2->ProgressBar1->Visible=false;
	Form2->Visible=true;
	piwo=NULL;
	AnsiString dir=ExtractFileDir(Application->ExeName);
	Form2->ProgressBar1->Visible=true;
    OnLogInformation(NULL,"Rozpoczêto wczytywanie pluginów");
	plugins.OnLoadingProgress=OnLoadProgress;
	plugins.OnFunctionAddRequest=OnFunctionAddClick;
	plugins.LoadData(dir+"\\blocks", dir+"\\types", *MainMenu1, *ImageList1, 3, 2, 0, 1);
	OnLogInformation(NULL,"Zakoñczono wczytywanie pluginów");
	AnsiString file;
	if (ParamCount()>0)
		  file=ParamStr(1);

	blockMenu(true);
	Form2->ProgressBar1->Position=Form2->ProgressBar1->Max-1;
	if (!file.IsEmpty()&&file!=""&&FileExists(file)) {
		 Form2->log->Caption="Otwieranie projektu: "+ExtractFileName(file);
		 piwo=new PIWOEngine(this);
		 piwo->Visible=false;
		 piwo->plugins=&plugins;
		 piwo->Align=alClient;
		 piwo->Parent=this;
		 piwo->OnInformation=OnLogInformation;
		 piwo->OnWarrning=OnLogWarrning;
		 piwo->OnError=OnLogError;
		 piwo->OnDebug=OnLogDebug;
		 piwo->OnSuccess=OnLogSuccess;
		 piwo->OnRunInformation=OnLogRunInformation;
		 piwo->OnRunWarrning=OnLogRunWarrning;
		 piwo->OnRunError=OnLogRunError;
		 piwo->OnRunDebug=OnLogRunDebug;
		 piwo->OnRunSuccess=OnLogRunSuccess;
		 piwo->OnRunStart=OnRunStart;
		 piwo->OnRunEnd=OnRunEnd;
		 piwo->OnRunProgress=OnRunProgress;
		 piwo->OnChanged=OnChanged;
		if (!piwo->loadFromFile(file))
		{
		   Application->MessageBox(("Niemo¿na odczytaæ projektu z pliku: "+file).c_str(), "Otwieranie projektu", MB_OK | MB_ICONERROR);
		   delete piwo;
		   piwo=NULL;
		   newProject();
		}
		else
		{
		   fileName=file;
		   blockMenu(false);
		   piwo->Visible=true;
		   Form1->Caption=CAPTION;
		   Form1->Caption=Form1->Caption+" - "+ExtractFileName(file);
		   StatusBar1->SimpleText=OpenDialog1->FileName;
		}
	}
	else
	{
       Form2->log->Caption="Tworzenie nowego projektu";
	   newProject();
    }

	Form2->log->Caption="Wczytywanie interfejsu";
	Form2->ProgressBar1->Position=Form2->ProgressBar1->Max;
	Application->ProcessMessages();
	//Tworzenie szablonu PIWOEngine;
    addExt("piwo");
	Sleep(500);
	Form1->Visible=true;
	Form1->Enabled=false;
	Application->ProcessMessages();
	PageControl1Change(NULL);
	Sleep(500);

	Form2->Visible=false;
	Form1->Enabled=true;
	delete Form2;
	Application->ProcessMessages();
}

void TForm1::OnLogInformation(TObject* Sender, const AnsiString message)
{
  TListItem *item=ListView1->Items->Add();
  item->SubItems->Add(message);
  TTime tmp;
  item->Caption=FormatDateTime("hh:mm:ss", tmp.CurrentTime());
  item->ImageIndex=0;
  ListView1->Width=ListView1->Width-1;
  PageControl1Resize(NULL);
  ListView1->Scroll(0,99999999);
  Application->ProcessMessages();

  item=ListView3->Items->Add();
  item->SubItems->Add(message);
  item->Caption=FormatDateTime("hh:mm:ss-zzz", tmp.CurrentTime());
  item->ImageIndex=0;
  ListView3->Width=ListView3->Width-1;
  PageControl1Resize(NULL);
  ListView3->Scroll(0,99999999);
  Application->ProcessMessages();
}

void TForm1::OnLogDebug(TObject* Sender, const AnsiString message)
{
  TListItem *item=ListView3->Items->Add();
  item->SubItems->Add(message);
  TTime tmp;
  item->Caption=FormatDateTime("hh:mm:ss-zzz", tmp.CurrentTime());
  item->ImageIndex=1;
  ListView3->Width=ListView3->Width-1;
  PageControl1Resize(NULL);
  ListView3->Scroll(0,99999999);
  Application->ProcessMessages();
}

void TForm1::OnLogSuccess(TObject* Sender, const AnsiString message)
{
  TListItem *item=ListView1->Items->Add();
  item->SubItems->Add(message);
  TTime tmp;
  item->Caption=FormatDateTime("hh:mm:ss", tmp.CurrentTime());
  item->ImageIndex=2;
  ListView1->Width=ListView1->Width-1;
  PageControl1Resize(NULL);
  ListView1->Scroll(0,99999999);
  Application->ProcessMessages();

  item=ListView3->Items->Add();
  item->SubItems->Add(message);
  item->Caption=FormatDateTime("hh:mm:ss-zzz", tmp.CurrentTime());
  item->ImageIndex=2;
  ListView3->Width=ListView3->Width-1;
  PageControl1Resize(NULL);
  ListView3->Scroll(0,99999999);
  Application->ProcessMessages();
}

void TForm1::OnLogWarrning(TObject* Sender, const AnsiString message)
{
  TListItem *item=ListView1->Items->Add();
  item->SubItems->Add(message);
  TTime tmp;
  item->Caption=FormatDateTime("hh:mm:ss", tmp.CurrentTime());
  item->ImageIndex=3;
  ListView1->Width=ListView1->Width-1;
  PageControl1Resize(NULL);
  ListView1->Scroll(0,99999999);
  Application->ProcessMessages();

  item=ListView3->Items->Add();
  item->SubItems->Add(message);
  item->Caption=FormatDateTime("hh:mm:ss-zzz", tmp.CurrentTime());
  item->ImageIndex=3;
  ListView3->Width=ListView3->Width-1;
  PageControl1Resize(NULL);
  ListView3->Scroll(0,99999999);
  Application->ProcessMessages();
}

void TForm1::OnLogError(TObject* Sender, const AnsiString message)
{
  TListItem *item=ListView1->Items->Add();
  item->SubItems->Add(message);
  TTime tmp;
  item->Caption=FormatDateTime("hh:mm:ss", tmp.CurrentTime());
  item->ImageIndex=4;
  ListView1->Width=ListView1->Width-1;
  PageControl1Resize(NULL);
  ListView1->Scroll(0,99999999);
  Application->ProcessMessages();

  item=ListView3->Items->Add();
  item->SubItems->Add(message);
  item->Caption=FormatDateTime("hh:mm:ss-zzz", tmp.CurrentTime());
  item->ImageIndex=4;
  ListView3->Width=ListView3->Width-1;
  PageControl1Resize(NULL);
  ListView3->Scroll(0,99999999);
  Application->ProcessMessages();
}

void TForm1::OnLogRunInformation(TObject* Sender, const AnsiString message)
{
  TListItem *item=ListView2->Items->Add();
  item->SubItems->Add(message);
  TTime tmp;
  item->Caption=FormatDateTime("hh:mm:ss", tmp.CurrentTime());
  item->ImageIndex=0;
  ListView2->Width=ListView2->Width-1;
  PageControl1Resize(NULL);
  ListView2->Scroll(0,99999999);
  Application->ProcessMessages();

  item=ListView3->Items->Add();
  item->SubItems->Add("RUN: "+message);
  item->Caption=FormatDateTime("hh:mm:ss-zzz", tmp.CurrentTime());
  item->ImageIndex=0;
  ListView3->Width=ListView3->Width-1;
  PageControl1Resize(NULL);
  ListView3->Scroll(0,99999999);
  Application->ProcessMessages();
}

void TForm1::OnLogRunDebug(TObject* Sender, const AnsiString message)
{
  TListItem *item=ListView3->Items->Add();
  item->SubItems->Add("RUN: "+message);
  TTime tmp;
  item->Caption=FormatDateTime("hh:mm:ss-zzz", tmp.CurrentTime());
  item->ImageIndex=1;
  ListView3->Width=ListView3->Width-1;
  PageControl1Resize(NULL);
  ListView3->Scroll(0,99999999);
  Application->ProcessMessages();
}

void TForm1::OnLogRunSuccess(TObject* Sender, const AnsiString message)
{
  TListItem *item=ListView2->Items->Add();
  item->SubItems->Add(message);
  TTime tmp;
  item->Caption=FormatDateTime("hh:mm:ss", tmp.CurrentTime());
  item->ImageIndex=2;
  ListView2->Width=ListView2->Width-1;
  PageControl1Resize(NULL);
  ListView2->Scroll(0,99999999);
  Application->ProcessMessages();

  item=ListView3->Items->Add();
  item->SubItems->Add("RUN: "+message);
  item->Caption=FormatDateTime("hh:mm:ss-zzz", tmp.CurrentTime());
  item->ImageIndex=2;
  ListView3->Width=ListView3->Width-1;
  PageControl1Resize(NULL);
  ListView3->Scroll(0,99999999);
  Application->ProcessMessages();
}

void TForm1::OnLogRunWarrning(TObject* Sender, const AnsiString message)
{
  TListItem *item=ListView2->Items->Add();
  item->SubItems->Add(message);
  TTime tmp;
  item->Caption=FormatDateTime("hh:mm:ss", tmp.CurrentTime());
  item->ImageIndex=3;
  ListView2->Width=ListView2->Width-1;
  PageControl1Resize(NULL);
  ListView2->Scroll(0,99999999);
  Application->ProcessMessages();

  item=ListView3->Items->Add();
  item->SubItems->Add("RUN: "+message);
  item->Caption=FormatDateTime("hh:mm:ss-zzz", tmp.CurrentTime());
  item->ImageIndex=3;
  ListView3->Width=ListView3->Width-1;
  PageControl1Resize(NULL);
  ListView3->Scroll(0,99999999);
  Application->ProcessMessages();
}

void TForm1::OnLogRunError(TObject* Sender, const AnsiString message)
{
  TListItem *item=ListView2->Items->Add();
  item->SubItems->Add(message);
  TTime tmp;
  item->Caption=FormatDateTime("hh:mm:ss", tmp.CurrentTime());
  item->ImageIndex=4;
  ListView2->Width=ListView2->Width-1;
  PageControl1Resize(NULL);
  ListView2->Scroll(0,99999999);
  Application->ProcessMessages();

  item=ListView3->Items->Add();
  item->SubItems->Add("RUN: "+message);
  item->Caption=FormatDateTime("hh:mm:ss-zzz", tmp.CurrentTime());
  item->ImageIndex=4;
  ListView3->Width=ListView3->Width-1;
  PageControl1Resize(NULL);
  ListView3->Scroll(0,99999999);
  Application->ProcessMessages();
}

void __fastcall TForm1::Zakocz2Click(TObject *Sender)
{
 Close();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zaznaczwszystkiebloki1Click(TObject *Sender)
{
   piwo->SelectAllBlocks();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Odznaczwszystkiebloki1Click(TObject *Sender)
{
	piwo->UnselectAllBlocks();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Odwrzaznaczenieblokw1Click(TObject *Sender)
{
	piwo->InvertBlockSelection();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Usubloki1Click(TObject *Sender)
{
	piwo->DeleteAllBlocks();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Usuzaznaczonebloki1Click(TObject *Sender)
{
	piwo->DeleteSelectedBlocks();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Odznaczzaznaczonepoaczenie1Click(TObject *Sender)
{
	piwo->UnselectSelectedConnection();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Usuwszystkiepoczenia1Click(TObject *Sender)
{
   piwo->DeleteAllConnections();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Usuzaznaczonepoczenie1Click(TObject *Sender)
{
	piwo->DeleteSelectedConnection();	
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Zresetujwszystkiepoczenia1Click(TObject *Sender)
{
	piwo->CancelCustomizationOnAllConnections();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zresetujzaznaczonepoczenie1Click(TObject *Sender)
{
	piwo->CancelCustomizationOnSelectedConnections();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Uruchomwszystko1Click(TObject *Sender)
{
  blockMenu(true);
  piwo->run(false);
  blockMenu(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Uruchom3Click(TObject *Sender)
{
  Uruchom3->Checked=!Uruchom3->Checked;
  piwo->alwaysRun=Uruchom3->Checked;
  piwo->run();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PageControl1Resize(TObject *Sender)
{
   PageControl1->TabWidth=int((PageControl1->Width-40)/3);
   ListView1->Width=TabSheet1->Width;
   ListView2->Width=TabSheet2->Width;
   ListView3->Width=TabSheet3->Width;
   Label1->Width=int((PageControl1->Width-40)/3)+5;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Wyczylogi1Click(TObject *Sender)
{
	ListView1->Items->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuItem1Click(TObject *Sender)
{
	ListView2->Items->Clear();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuItem3Click(TObject *Sender)
{
	ListView3->Items->Clear();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zapiszdopliku1Click(TObject *Sender)
{
	SaveDialog1->FileName="Main Log.log";
	if (SaveDialog1->Execute()) {
	   TStringList *x=new TStringList();
	   AnsiString tmp;
	   for(int i=0;i<ListView1->Items->Count;++i)
	   {
		  tmp=ListView1->Items->Item[i]->Caption+" - ";
		  switch (ListView1->Items->Item[i]->ImageIndex==0)
		  {
			case 0 : tmp+="INFO: ";break;
			case 1 : tmp+="DEBUG: ";break;
			case 2 : tmp+="SUCCESS: ";break;
			case 3 : tmp+="WARRNING: ";break;
			case 4 : tmp+="ERROR: ";break;
		  }
		 tmp+=ListView1->Items->Item[i]->SubItems->Strings[0];
		 x->Add(tmp);
	   }
	   x->SaveToFile(SaveDialog1->FileName);
	   delete x;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuItem2Click(TObject *Sender)
{
	SaveDialog1->FileName="Run Log.log";
	if (SaveDialog1->Execute()) {
	   TStringList *x=new TStringList();
	   AnsiString tmp;
	   for(int i=0;i<ListView2->Items->Count;++i)
	   {
		  tmp=ListView2->Items->Item[i]->Caption+" - ";
		  switch (ListView2->Items->Item[i]->ImageIndex==0)
		  {
			case 0 : tmp+="INFO: ";break;
			case 1 : tmp+="DEBUG: ";break;
			case 2 : tmp+="SUCCESS: ";break;
			case 3 : tmp+="WARRNING: ";break;
			case 4 : tmp+="ERROR: ";break;
		  }
		 tmp+=ListView2->Items->Item[i]->SubItems->Strings[0];
		 x->Add(tmp);
	   }
	   x->SaveToFile(SaveDialog1->FileName);
	   delete x;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuItem4Click(TObject *Sender)
{
	SaveDialog1->FileName="Debug Log.log";
	if (SaveDialog1->Execute()) {
	   TStringList *x=new TStringList();
	   AnsiString tmp;
	   for(int i=0;i<ListView3->Items->Count;++i)
	   {
		  tmp=ListView3->Items->Item[i]->Caption+" - ";
		  switch (ListView3->Items->Item[i]->ImageIndex==0)
		  {
			case 0 : tmp+="INFO: ";break;
			case 1 : tmp+="DEBUG: ";break;
			case 2 : tmp+="SUCCESS: ";break;
			case 3 : tmp+="WARRNING: ";break;
			case 4 : tmp+="ERROR: ";break;
		  }
		 tmp+=ListView3->Items->Item[i]->SubItems->Strings[0];
		 x->Add(tmp);
	   }
	   x->SaveToFile(SaveDialog1->FileName);
	   delete x;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
	if (Key==VK_DELETE&&piwo!=NULL&&piwo->Enabled) {
	   piwo->DeleteSelectedConnection();
	   piwo->DeleteSelectedBlocks(); 
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PageControl1Change(TObject *Sender)
{
  ListView3->Width=ListView3->Width-1;
  ListView2->Width=ListView2->Width-1;
  ListView1->Width=ListView1->Width-1;
  ListView3->Scroll(0,99999999);
  ListView2->Scroll(0,99999999);
  ListView1->Scroll(0,99999999);
  PageControl1Resize(NULL);
}
//---------------------------------------------------------------------------
void TForm1::OnRunStart(TObject* Sender)
{
	ListView2->Items->Clear();
	Timer1->Enabled=true;
	Label1->Caption="";
	CGauge1->Progress=0;
	Application->ProcessMessages();
}

void TForm1::OnRunEnd(TObject* Sender)
{
	Panel2->Visible=false;
	Timer1->Enabled=false;
	Uruchom3->Enabled=true;
	Uruchomwszystko1->Enabled=true;
	Anuluj1->Enabled=false;
}

void TForm1::OnRunProgress(TObject* Sender,const AnsiString message, const double precent)
{
	Label1->Caption=message;
	CGauge1->Progress=int(precent);
	Application->ProcessMessages();
}

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
	if (piwo!=NULL)
	{
       piwo->abort();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  Panel2->Visible=true;
  Timer1->Enabled=false;
}

void TForm1::blockMenu(bool blocked)
{
  if (piwo!=NULL)
  {
	  plugins.setMenuItemsStatus(!blocked);
	  Uruchom3->Enabled=!blocked;
	  Uruchomwszystko1->Enabled=!blocked;
	  Anuluj1->Enabled=blocked;
	  Zaznaczwszystkiebloki1->Enabled=!blocked;
	  Odznaczwszystkiebloki1->Enabled=!blocked;
	  Odwrzaznaczenieblokw1->Enabled=!blocked;
	  Duplikujbloki1->Enabled=!blocked;
	  Usubloki1->Enabled=!blocked;
	  Usuzaznaczonebloki1->Enabled=!blocked;
	  Odznaczzaznaczonepoaczenie1->Enabled=!blocked;
	  Usuwszystkiepoczenia1->Enabled=!blocked;
	  Usuzaznaczonepoczenie1->Enabled=!blocked;
	  Zresetujwszystkiepoczenia1->Enabled=!blocked;
	  Zresetujzaznaczonepoczenie1->Enabled=!blocked;
	  Zapiszjako1->Enabled=!blocked;
	  Exportujjakoobraz1->Enabled=!blocked;
	  Zakocz1->Enabled=!blocked;
	  piwo->Enabled=!blocked;
	  Sprawdprojekt1->Enabled=!blocked;
  }
  else
  {
	  plugins.setMenuItemsStatus(false);
	  Uruchom3->Enabled=false;
	  Uruchomwszystko1->Enabled=false;
	  Anuluj1->Enabled=false;
	  Zaznaczwszystkiebloki1->Enabled=false;
	  Odznaczwszystkiebloki1->Enabled=false;
	  Odwrzaznaczenieblokw1->Enabled=false;
	  Duplikujbloki1->Enabled=false;
	  Usubloki1->Enabled=false;
	  Usuzaznaczonebloki1->Enabled=false;
	  Odznaczzaznaczonepoaczenie1->Enabled=false;
	  Usuwszystkiepoczenia1->Enabled=false;
	  Usuzaznaczonepoczenie1->Enabled=false;
	  Zresetujwszystkiepoczenia1->Enabled=false;
	  Zresetujzaznaczonepoczenie1->Enabled=false;
	  Zapiszjako1->Enabled=false;
	  Exportujjakoobraz1->Enabled=false;
	  Zakocz1->Enabled=false;
	  Sprawdprojekt1->Enabled=false;
  }
}

void TForm1::newProject()
{
	if (!closeProject()) return;
	fileName="";
	piwo=new PIWOEngine(this);
	piwo->plugins=&plugins;
	piwo->Align=alClient;
	piwo->Parent=this;
	piwo->OnInformation=OnLogInformation;
	piwo->OnWarrning=OnLogWarrning;
	piwo->OnError=OnLogError;
	piwo->OnDebug=OnLogDebug;
	piwo->OnSuccess=OnLogSuccess;
	piwo->OnRunInformation=OnLogRunInformation;
	piwo->OnRunWarrning=OnLogRunWarrning;
	piwo->OnRunError=OnLogRunError;
	piwo->OnRunDebug=OnLogRunDebug;
	piwo->OnRunSuccess=OnLogRunSuccess;
	piwo->OnRunStart=OnRunStart;
	piwo->OnRunEnd=OnRunEnd;
	piwo->OnRunProgress=OnRunProgress;
	piwo->OnChanged=OnChanged;
	blockMenu(false);
	Form1->Caption=CAPTION;
	Form1->Caption=Form1->Caption+" - Nowy projekt";
	StatusBar1->SimpleText="Nowy projekt";
}

bool TForm1::closeProject()
{
   if (piwo==NULL) return true;
   if ((piwo->isChanged()&&!fileName.IsEmpty())||(fileName.IsEmpty()&&piwo->getBlockCount()>0))
   {
	  //pytanie o zapis
	 int ret=Application->MessageBox("W projekcie wprowadzono zmiany, czy chcesz je zapisaæ ?", "Zamykanie projektu", MB_YESNOCANCEL | MB_ICONWARNING);
	 if (ret==IDYES)
	 {
		if (fileName.IsEmpty())
		{
		   if (SaveDialog2->Execute())
			   fileName=SaveDialog2->FileName;
			   else return false;
		}
		if (!piwo->saveToFile(fileName))
		{
		   Application->MessageBox("Niemo¿na zapisaæ projektu", "Zapisywanie projektu", MB_OK | MB_ICONERROR);
		   return false;
		}
	 } else
	 if (ret==IDCANCEL) return false;
   }
   delete piwo;
   piwo=NULL;
   blockMenu(true);
   Form1->Caption=CAPTION;
   StatusBar1->SimpleText="";
   return true;
}

void TForm1::openProject()
{
   if (!closeProject()) return;
   if (OpenDialog1->Execute())
   {
		 piwo=new PIWOEngine(this);
		 piwo->Visible=false;
		 piwo->plugins=&plugins;
		 piwo->Align=alClient;
		 piwo->Parent=this;
		 piwo->OnInformation=OnLogInformation;
		 piwo->OnWarrning=OnLogWarrning;
		 piwo->OnError=OnLogError;
		 piwo->OnDebug=OnLogDebug;
		 piwo->OnSuccess=OnLogSuccess;
		 piwo->OnRunInformation=OnLogRunInformation;
		 piwo->OnRunWarrning=OnLogRunWarrning;
		 piwo->OnRunError=OnLogRunError;
		 piwo->OnRunDebug=OnLogRunDebug;
		 piwo->OnRunSuccess=OnLogRunSuccess;
		 piwo->OnRunStart=OnRunStart;
		 piwo->OnRunEnd=OnRunEnd;
		 piwo->OnRunProgress=OnRunProgress;
		 piwo->OnChanged=OnChanged;
		if (!piwo->loadFromFile(OpenDialog1->FileName))
		{
		   Application->MessageBox(("Niemo¿na odczytaæ projektu z pliku: "+OpenDialog1->FileName).c_str(), "Otwieranie projektu", MB_OK | MB_ICONERROR);
		   delete piwo;
		   piwo=NULL;
		   return;
		}
		else
		{
		   fileName=OpenDialog1->FileName;
		   blockMenu(false);
		   piwo->Visible=true;
		   Form1->Caption=CAPTION;
		   Form1->Caption=Form1->Caption+" - "+ExtractFileName(OpenDialog1->FileName);
		   StatusBar1->SimpleText=OpenDialog1->FileName;
		}
   }
}

void TForm1::OnChanged(TObject* Sender)
{
	Form1->Caption=CAPTION;
	if (!fileName.IsEmpty())
		Form1->Caption=Form1->Caption+" - "+ExtractFileName(fileName)+"*";
		else
        Form1->Caption=Form1->Caption+" - Nowy projekt*";
}

void __fastcall TForm1::Nowy1Click(TObject *Sender)
{
	newProject();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zakocz1Click(TObject *Sender)
{
  closeProject();
}


void __fastcall TForm1::Otwrz1Click(TObject *Sender)
{
  openProject();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Duplikujbloki1Click(TObject *Sender)
{
   piwo->DuplcateSelectedBlocks();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Exportujjakoobraz1Click(TObject *Sender)
{
	if (SaveDialog2->Execute())
	{
		 if (!piwo->saveToFile(SaveDialog2->FileName))
		 {
			Application->MessageBox("Niemo¿na zapisaæ projektu", "Zapisywanie projektu", MB_OK | MB_ICONERROR);
		 }
		 else
		 {
			fileName=SaveDialog2->FileName;
			Form1->Caption=CAPTION;
			Form1->Caption=Form1->Caption+" - "+ExtractFileName(SaveDialog2->FileName);
			StatusBar1->SimpleText=SaveDialog2->FileName;
		 }
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zapiszjako1Click(TObject *Sender)
{
  if (fileName.IsEmpty())
  {
	  Exportujjakoobraz1Click(Sender);
	  return;
  }
  if (!piwo->saveToFile(fileName))
  {
	  Application->MessageBox("Niemo¿na zapisaæ projektu", "Zapisywanie projektu", MB_OK | MB_ICONERROR);
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  CanClose=closeProject();
}
//---------------------------------------------------------------------------

void TForm1::addExt(const AnsiString &ExtMyFile)
{
  TRegistry *Reg=new TRegistry();
  try{
  Reg->RootKey= HKEY_CLASSES_ROOT;
  Reg->OpenKey("." + ExtMyFile, True);
  Reg->WriteString("", AnsiUpperCase(ExtMyFile) + "file"); //tworzy wartoœæ zawierajaca
                                                   //nazwe klucza w rejestrze gdzie bed¹ 
                                                   //znajdowa³y siê dane na
                                                   //temat naszego pliku dla nas "XYZfile"
  Reg->CloseKey();  //zamykamy ten klucz i idziemy dalej


  Reg->OpenKey(AnsiUpperCase(ExtMyFile) + "file", true); //tworze powy¿szy klucz

  //teraz podaje opis naszego pliku
  Reg->WriteString("","PIWO Project file 1.0"); //w miejsce kropek podajesz nazwê swojego programu
  Reg->CloseKey();  //zamykamy ten klucz i idziemy dalej

  //teraz przypisujemy plikowi ikonê
  Reg->OpenKey(AnsiUpperCase(ExtMyFile) + "file\\DefaultIcon", true);
  Reg->WriteString("",Application->ExeName + ",2"); //gdzie Application.ExeName to scie¿ka
                                                 //do pliku zawieraj¹cego ikonê w tym
                                                 //przypadku w tym przypadku jest to
                                                 //nazwa i œcie¿ka do Twojego
                                                 //programu ale mo¿e byæ to równie
                                                 //dobrze œcie¿ka do innego programu,
                                                 //œcie¿ka do ikony czy œcie¿ka
                                                 //do jakiejœ biblioteki zarówno DLLki
                                                 //jak i ICLki a 0 to nr ikony, je¿eli
                                                 //plik ma wiêcej ikon nr mo¿e byæ inny
  Reg->CloseKey();  //zamykamy ten klucz i idziemy dalej

  Reg->OpenKey(AnsiUpperCase(ExtMyFile) + "file\\shell", true);
  Reg->WriteString("","open"); //etykieta pozycji w menu kontekstowym
  Reg->CloseKey();
  Reg->OpenKey(AnsiUpperCase(ExtMyFile) + "file\\shell\\open", true);
  Reg->WriteString("","&Otwórz"); //etykieta pozycji w menu kontekstowym
  Reg->CloseKey();
  Reg->OpenKey(AnsiUpperCase(ExtMyFile) + "file\\shell\\open\\command", true);
  Reg->WriteString("",Application->ExeName + " \"%1\"");
  Reg->CloseKey();
  } catch(...)
  {
  }
  delete Reg;
}
void __fastcall TForm1::Sprawdprojekt1Click(TObject *Sender)
{
	piwo->validateAll();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Anuluj1Click(TObject *Sender)
{
	piwo->abort();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton11Click(TObject *Sender)
{
	piwo->DeleteSelectedBlocks();
	piwo->DeleteSelectedConnection();	
}
//---------------------------------------------------------------------------

