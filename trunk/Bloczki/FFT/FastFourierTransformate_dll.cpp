//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "fft.h"

#include "../../TypyDanych/Bitmap1bit/Interface/IBitmap1bit.h"
#include "../../TypyDanych/Bitmap4bit/Interface/IBitmap4bit.h"
#include "../../TypyDanych/Bitmap8bit/Interface/IBitmap8bit.h"
#include "../../TypyDanych/Bitmap16bit/Interface/IBitmap16bit.h"
#include "../../TypyDanych/Bitmap24bit/Interface/IBitmap24bit.h"
#include "../../TypyDanych/Bitmap32bit/Interface/IBitmap32bit.h"
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
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
        return 1;
}
//---------------------------------------------------------------------------
bool __stdcall showConfig(TComponent *owner, Block *aBlock)
{
		return false;
}

//---------------------------------------------------------------------------
int __stdcall validate(Block *aBlock)
{
	if((aBlock->input.size() == 0) && (aBlock->output.size() == 0))
	{
		BlockInput input1("input1");
		input1.allowedTypes.push_back("Bitmap1bit");
		input1.allowedTypes.push_back("Bitmap4bit");
		input1.allowedTypes.push_back("Bitmap8bit");
		input1.allowedTypes.push_back("Bitmap16bit");
		input1.allowedTypes.push_back("Bitmap24bit");
		input1.allowedTypes.push_back("Bitmap32bit");
		input1.setDescription("Domyslne wejscie");
		input1.setErrorCode(1);
		input1.setErrorDescription("Brak obiektu na wejsciu");
		aBlock->input.push_back(input1);

		BlockOutput output1("output1");
		output1.setOutputType("Bitmap8bit");
		output1.setDescription("Domyslne wyjscie");
		output1.setErrorCode(1);
		output1.setErrorDescription("Brak obiektu na wejsciu");
		aBlock->output.push_back(output1);

                BlockOutput output2("output2");
		output2.setOutputType("Bitmap8bit");
		output2.setDescription("Domyslne wyjscie");
		output2.setErrorCode(1);
		output2.setErrorDescription("Brak obiektu na wejsciu");
		aBlock->output.push_back(output2);

		return 2;
	}
	else
	{
		if(aBlock->input[0].getConnectedType().IsEmpty())
		{
			aBlock->input[0].setErrorCode(1);
			aBlock->input[0].setErrorDescription("Brak obiektu na wejsciu");
			aBlock->output[0].setErrorCode(1);
			aBlock->output[0].setErrorDescription("Brak obiektu na wejsciu");
			aBlock->output[0].setOutputType("Bitmap8bit");
                        aBlock->output[1].setErrorCode(1);
			aBlock->output[1].setErrorDescription("Brak obiektu na wejsciu");
			aBlock->output[1].setOutputType("Bitmap8bit");
			return 1;
		} 
		else
		{
			if(aBlock->input[0].getErrorCode() != 0 || aBlock->output[0].getErrorCode() != 0 || aBlock->output[1].getErrorCode() != 0)
			{
				aBlock->input[0].setErrorCode(0);
				aBlock->output[0].setErrorCode(0);
                                aBlock->output[1].setErrorCode(0);
				aBlock->input[0].setErrorDescription("");
				aBlock->output[0].setErrorDescription("");
                                aBlock->output[1].setErrorDescription("");
				return 1;
			}
			else 
				return 0;
		}
	}
}
//---------------------------------------------------------------------------
int __stdcall run(Block *aBlock)
{
	if(aBlock->input.size() != 1 || aBlock->input[0].getConnectedType().IsEmpty())
		return 1;

	Graphics::TBitmap* picture = new Graphics::TBitmap();
	AnsiString connectedType(aBlock->input[0].getConnectedType());
	
	if(connectedType == "Bitmap1bit")
		picture->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap1bit::getBitmap(aBlock->input[0].getObject()))));

	else	if(connectedType == "Bitmap4bit")
		picture->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap4bit::getBitmap(aBlock->input[0].getObject()))));

	else	if(connectedType == "Bitmap8bit")
		picture->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap8bit::getBitmap(aBlock->input[0].getObject()))));

	else	if(connectedType == "Bitmap16bit")
		picture->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap16bit::getBitmap(aBlock->input[0].getObject()))));

	else	if(connectedType == "Bitmap24bit")
		picture->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap24bit::getBitmap(aBlock->input[0].getObject()))));

	else	if(connectedType == "Bitmap32bit")
		picture->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap32bit::getBitmap(aBlock->input[0].getObject()))));

	if(picture->Width==picture->Height)
	{
		Graphics::TBitmap** pict = Fimage(picture);
		if(pict[0]==NULL || pict[1]==NULL)//na razie dzial tylko dla obrazow NxN
		{
                aBlock->output[0].setErrorCode(2);
                aBlock->output[0].setErrorDescription("Pusta bitmapa");
                picture->Free();
                return 2;
		}
	}
	else {
                aBlock->output[0].setErrorCode(2);
                aBlock->output[0].setErrorDescription("Bitmapa musi byc kwadratowa");
                picture->Free();
                return 2;
	}

	TypeConfig* copy1;
    TypeConfig* copy2;

    copy1 = IBitmap8bit::getNew();
    IBitmap8bit::setBitmap(copy1, *pict[0]);

    copy2 = IBitmap8bit::getNew();
    IBitmap8bit::setBitmap(copy2, *pict[1]);


	aBlock->output[0].setObject(*copy1);
        aBlock->output[1].setObject(*copy2);
	
	pict[0]->Free();
    pict[1]->Free();
    delete pict;
	delete copy1;
    delete copy2;

	return 0;
}
//---------------------------------------------------------------------------

