//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "OpenImage.h"
#include "configWindow.h"

//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#pragma argsused

#pragma link "MEMMGR.LIB"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------

bool __stdcall showConfig(TComponent *owner, Block *aBlock)
{
	cfgWindow = new TcfgWindow(owner);
	cfgWindow->SetConfig(aBlock);
	cfgWindow->ShowModal();
	return true;
}
//---------------------------------------------------------------------------
int __stdcall validate(Block *aBlock)
{
  // brak wejscia, jedno wyjscie
	if(aBlock->output.size() == 0)
	{
		BlockOutput output1("output1");
		output1.setOutputType("Bitmap24bit");
		output1.setDescription("Domyœlne wyjœcie");
		output1.setErrorCode(1);
		output1.setErrorDescription("Brak obiektu na wyjœciu");
		aBlock->output.push_back(output1);
		
		aBlock->getConfig()->addString("bitrate","Bitmap24bit");
		aBlock->getConfig()->addString("path","");
		
		return 2;
	}
	else
	{
		if(aBlock->output[0].getOutputType()!= aBlock->getConfig()->getString("bitrate"))
		{
			aBlock->output[0].setOutputType(aBlock->getConfig()->getString("bitrate"));
			aBlock->output[0].setErrorCode(0);
			aBlock->output[0].setErrorDescription("");

			return 1;
		}
		else if(aBlock->output[0].getErrorCode() != 0) 
		{
			aBlock->output[0].setErrorCode(0);
			aBlock->output[0].setErrorDescription("");
			
			return 1;
    }
		else	
			return 0;
	}
}
//---------------------------------------------------------------------------
int __stdcall run(Block *aBlock)
{
	Graphics::TBitmap* picture = new Graphics::TBitmap();
	AnsiString path(aBlock->getConfig()->getString("path"));

	if(!OpenImage(picture,path))
	{
		aBlock->output[0].setErrorCode(2);
		aBlock->output[0].setErrorDescription("B³¹d wczytywania obrazu");
		picture->Free();
		return 2;
	}

	TypeConfig* copy;
	AnsiString bitrate(aBlock->getConfig()->getString("bitrate"));

	if(bitrate == "Bitmap1bit")
	{
		copy = IBitmap1bit::getNew();
		IBitmap1bit::setBitmap(copy, *picture);
	}
	else if(bitrate == "Bitmap4bit")
	{
		copy = IBitmap4bit::getNew();
		IBitmap4bit::setBitmap(copy, *picture);
	}
	else if(bitrate == "Bitmap8bit")
	{
		copy = IBitmap8bit::getNew();
		IBitmap8bit::setBitmap(copy, *picture);
	}
	else if(bitrate == "Bitmap16bit")
	{
		copy = IBitmap16bit::getNew();
		IBitmap16bit::setBitmap(copy, *picture);
	}
	else	if(bitrate == "Bitmap24bit")
	{
		copy = IBitmap24bit::getNew();
		IBitmap24bit::setBitmap(copy, *picture);
	}
	else	if(bitrate == "Bitmap32bit")
	{
		copy = IBitmap32bit::getNew();
		IBitmap32bit::setBitmap(copy, *picture);
	}

	aBlock->output[0].setObject(*copy);
	
	picture->Free();
	delete copy;

	return 0;	
}
//---------------------------------------------------------------------------
