//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "reflection.h"
#include "configWindow.h"

#include "IBitmap1bit.h"
#include "IBitmap4bit.h"
#include "IBitmap8bit.h"
#include "IBitmap16bit.h"
#include "IBitmap24bit.h"
#include "IBitmap32bit.h"
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
	delete cfgWindow;
	return true;
}

//---------------------------------------------------------------------------
int __stdcall validate(Block *aBlock)
{
	//error code 0 - ok, 1 - warrning, 2- error (można użyć tylko w funkcji run)
	//return code= 0 validate - bez zmian, 1 - zmiana wartości error, 2 - zmieniła sie liczba wejśc / wyjśc
	if((aBlock->input.size() == 0)&&(aBlock->output.size() == 0))
	{
		BlockInput input1("input1");
		input1.allowedTypes.push_back("Bitmap1bit");
		input1.allowedTypes.push_back("Bitmap4bit");
		input1.allowedTypes.push_back("Bitmap8bit");
		input1.allowedTypes.push_back("Bitmap16bit");
		input1.allowedTypes.push_back("Bitmap24bit");
		input1.allowedTypes.push_back("Bitmap32bit");
		input1.setDescription("Domyslne wejście");
		input1.setErrorCode(1);
		input1.setErrorDescription("Brak obiektu na wejściu");
		aBlock->input.push_back(input1);
		
		
		BlockOutput output1("output1");
		output1.setOutputType("Bitmap24bit");
		output1.setDescription("Domyślne wyjście");
		output1.setErrorCode(1);
		input1.setErrorDescription("Brak obiektu na wejściu");
		aBlock->output.push_back(output1);

		return 2;
	}
	else
	{
		if(aBlock->input[0].getConnectedType().IsEmpty())
		{
			aBlock->input[0].setErrorCode(1);
			aBlock->input[0].setErrorDescription("Brak obiektu na wejściu");
			aBlock->output[0].setErrorCode(1);
			aBlock->output[0].setErrorDescription("Brak obiektu na wejściu");
			aBlock->output[0].setOutputType("Bitmap24bit");
			return 1;
		} 
		else
		{
			if (aBlock->output[0].getOutputType()!=aBlock->input[0].getConnectedType())
			{
				aBlock->output[0].setOutputType(aBlock->input[0].getConnectedType());
				aBlock->input[0].setErrorCode(0);
				aBlock->output[0].setErrorCode(0);
				aBlock->input[0].setErrorDescription("");
				aBlock->output[0].setErrorDescription("");
				return 1;
			}
		}
	}
	
			aBlock->input[0].setErrorCode(0);
			aBlock->output[0].setErrorCode(0);
			aBlock->input[0].setErrorDescription("");
			aBlock->output[0].setErrorDescription("");
	return 0;
}
//---------------------------------------------------------------------------
int __stdcall run(Block *aBlock)
{
	//return code: 0 - wykonalo sie, 1 - brak potrzebnych danych, 2 - error
	if(aBlock->input.size() != 1 || aBlock->input[0].getConnectedType().IsEmpty()) return 1;

	Graphics::TBitmap* picture;

	if(aBlock->input[0].getConnectedType() == "Bitmap1bit")
		picture = IBitmap1bit::getBitmap(aBlock->input[0].getObject());
	else 	if(aBlock->input[0].getConnectedType() == "Bitmap4bit")
		picture = IBitmap4bit::getBitmap(aBlock->input[0].getObject());
	else 	if(aBlock->input[0].getConnectedType() == "Bitmap8bit")
		picture = IBitmap8bit::getBitmap(aBlock->input[0].getObject());
	else 	if(aBlock->input[0].getConnectedType() == "Bitmap16bit")
		picture = IBitmap16bit::getBitmap(aBlock->input[0].getObject());
	else 	if(aBlock->input[0].getConnectedType() == "Bitmap24bit")
		picture = IBitmap24bit::getBitmap(aBlock->input[0].getObject());
	else 	if(aBlock->input[0].getConnectedType() == "Bitmap32bit")
		picture = IBitmap32bit::getBitmap(aBlock->input[0].getObject());

	int mode = aBlock->getConfig()->getInt("mode");		

	if(mode == 0)
		if(!ReflectionVertically(picture)) { aBlock->output[0].setErrorCode(2);	aBlock->output[0].setErrorDescription("sdsd"); return 2;}
	else
		if(!ReflectionHorizontally(picture)) { aBlock->output[0].setErrorCode(2);	aBlock->output[0].setErrorDescription("sdsd"); return 2;}

	TypeConfig* copy;

	if(aBlock->input[0].getConnectedType() == "Bitmap1bit")
	{
		copy = IBitmap1bit::getNew();
		IBitmap1bit::setBitmap(copy, *picture);
	}
	else 	if(aBlock->input[0].getConnectedType() == "Bitmap4bit")
	{
		copy = IBitmap4bit::getNew();
		IBitmap4bit::setBitmap(copy, *picture);
	}
	else 	if(aBlock->input[0].getConnectedType() == "Bitmap8bit")
	{
		copy = IBitmap8bit::getNew();
		IBitmap8bit::setBitmap(copy, *picture);
	}
	else 	if(aBlock->input[0].getConnectedType() == "Bitmap16bit")
	{
		copy = IBitmap16bit::getNew();
		IBitmap16bit::setBitmap(copy, *picture);
	}
	else 	if(aBlock->input[0].getConnectedType() == "Bitmap24bit")
	{
		copy = IBitmap24bit::getNew();
		IBitmap24bit::setBitmap(copy, *picture);
	}
	else 	if(aBlock->input[0].getConnectedType() == "Bitmap32bit")
	{
		copy = IBitmap32bit::getNew();
		IBitmap32bit::setBitmap(copy, *picture);
	}

	aBlock->output[0].setObject(*copy);

	return 0;
}
//---------------------------------------------------------------------------
