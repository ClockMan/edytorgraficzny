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

int TForm1::SearchDirectory(std::vector<AnsiString> &refvecFiles,
					const AnsiString        &refcstrRootDirectory,
					const AnsiString        &refcstrExtension,
					bool                     bSearchSubdirectories)
{
  AnsiString strFilePath;
  AnsiString    strPattern;              // Pattern
  HANDLE          hFile;                   // Handle to file
  WIN32_FIND_DATA FileInformation;         // File information


  strPattern = refcstrRootDirectory + "\\*."+refcstrExtension;

  hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
  if(hFile != INVALID_HANDLE_VALUE)
  {
    do
	{
	  if(FileInformation.cFileName[0] != '.')
	  {
		strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

		if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
          if(bSearchSubdirectories)
          {
			int iRC = SearchDirectory(refvecFiles,
                                      strFilePath,
                                      refcstrExtension,
									  bSearchSubdirectories);
			if(iRC)
			  return iRC;
		  }
		}
        else
        {
			refvecFiles.push_back(strFilePath);
		}
      }
    } while(::FindNextFile(hFile, &FileInformation) == TRUE);

	// Close handle
    ::FindClose(hFile);

	DWORD dwError = ::GetLastError();
	if(dwError != ERROR_NO_MORE_FILES)
	  return dwError;
  }

  return 0;
}

void TForm1::AddMenus(FunctionDLL *info)
{
	TStringList *tmp=new TStringList();
	for(unsigned int i=0;i<info->category.size();i++)
	{
		tmp->Text=StringReplace(StringReplace(info->category[i],"\\","\n",TReplaceFlags() << rfReplaceAll),"/","\n",TReplaceFlags() << rfReplaceAll);
		if (tmp->Count==0||tmp->Strings[0].IsEmpty()) continue;
		//Wyszukiwanie maina, jak niema to dodajemy
		TMenuItem *x=&MainMenu1->Items[0];
		TMenuItem *y=NULL;
		for(int q=0;q<tmp->Count;q++)
		{
			for(int j=0;j<x->Count;j++)
			{
				if (x->Items[j]->GroupIndex==2&&(x->Items[j]->Caption.AnsiCompare(tmp->Strings[q])==0))
				{
					y=x->Items[j];
					break;
				}
			}

			if (y==NULL)
			{
				//niema g³ownego menu, tworzymy go
				y=MainMenu1->CreateMenuItem();
				y->AutoCheck=false;
				y->Caption=tmp->Strings[q];
				y->GroupIndex=2;
				y->Visible=true;
				//znajdujemy miejsce gdzie go dodac
				int pos;
				for(pos=0;pos<x->Count;pos++)
					if ((x->Items[pos]->GroupIndex==2&&tmp->Strings[q].AnsiCompare(x->Items[pos]->Caption)==-1)||(x->Items[pos]->GroupIndex==3)) break;
				x->Insert(pos,y);
			}
			x=y;
			y=NULL;
		}
    	//dodawanie koñcowego itemu, on te¿ musi byæ sortowany, niesprawdzamy czy nazwa taka ju¿ jest


	}

  //	TMenuItem *x=MainMenu1->CreateMenuItem();
  //	x->Caption=info->fullName;
  //	x->Visible=true;
  //	MainMenu1->Items->Add(x);
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Application->CreateForm(__classid(TForm2), &Form2);
	Form2->ProgressBar1->Visible=false;
    Form2->Visible=true;
	AnsiString dir=ExtractFileDir(Application->ExeName);

	std::vector<AnsiString> types;
	SearchDirectory(types,dir+"\\types","dll");
	std::vector<AnsiString> functions;
	SearchDirectory(functions,dir+"\\blocks","dll");
	Form2->ProgressBar1->Max=types.size()+functions.size()+1;
	Form2->ProgressBar1->Position=0;
	Form2->ProgressBar1->Visible=true;
	unsigned int i;
	for(i=0;i<types.size();i++)
	{
	   TypeDLL *wsk=plugins.addType(types[i]);
	   if (wsk!=NULL)
	   {
		 Form2->log->Caption="Za³adowano typ danych: "+wsk->getType();
	   }
	   else
	   {
		 Form2->log->Caption="Plik \""+ExtractFileName(types[i])+"\" nie jest DLL typu danych";
		 ShowMessage(functions[i]+"\n nie jest poprawnym pluginem typu");
	   }

	   Form2->ProgressBar1->Position++;
	   Application->ProcessMessages();
	}

	for(i=0;i<functions.size();i++)
	{
	   FunctionDLL *wsk=plugins.addFunction(functions[i]);
	   if (wsk!=NULL)
	   {
		 AddMenus(wsk);
		 Form2->log->Caption="Za³adowano funkcjê: "+wsk->name;
	   }
	   else
	   {
		 Form2->log->Caption="Plik \""+ExtractFileName(functions[i])+"\" nie jest DLL funkcji";
		 ShowMessage(functions[i]+"\n nie jest poprawnym pluginem bloczku");
	   }

	   Form2->ProgressBar1->Position++;
	   Application->ProcessMessages();
	}

	Form2->log->Caption="Wczytywanie interfejsu";
	Form2->ProgressBar1->Position++;
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


