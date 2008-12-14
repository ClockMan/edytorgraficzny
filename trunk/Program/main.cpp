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


void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Application->CreateForm(__classid(TForm2), &Form2);
	Form2->ProgressBar1->Visible=false;
	Form2->Visible=true;
	AnsiString dir=ExtractFileDir(Application->ExeName);

	std::vector<AnsiString> types;
	SearchDirectory(types,dir+"\\types","dll");
	std::vector<AnsiString> functions;
	SearchDirectory(types,dir+"\\blocks","dll");
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
	   }
	   Form2->ProgressBar1->Position++;
	   Application->ProcessMessages();
	}

	for(i=0;i<functions.size();i++)
	{
	   FunctionDLL *wsk=plugins.getFunction(functions[i]);
	   if (wsk!=NULL)
	   {
       	
		 Form2->log->Caption="Za³adowano funkcjê: "+wsk->name;
	   }
	   else
	   {
		 Form2->log->Caption="Plik \""+ExtractFileName(functions[i])+"\" nie jest DLL funkcji";
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


