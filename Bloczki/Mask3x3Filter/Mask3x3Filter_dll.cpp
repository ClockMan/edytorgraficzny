//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "Mask3x3Filter.h"

#include "../../TypyDanych/Bitmap1bit/Interface/IBitmap1bit.h"
#include "../../TypyDanych/Bitmap4bit/Interface/IBitmap4bit.h"
#include "../../TypyDanych/Bitmap8bit/Interface/IBitmap8bit.h"
#include "../../TypyDanych/Bitmap16bit/Interface/IBitmap16bit.h"
#include "../../TypyDanych/Bitmap24bit/Interface/IBitmap24bit.h"
#include "../../TypyDanych/Bitmap32bit/Interface/IBitmap32bit.h"

#include "../../TypyDanych/Mask3x3/Interface/IMask3x3.h"
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
		input1.setDescription("Domy�lne wej�cie - obraz");
		input1.setErrorCode(1);
		input1.setErrorDescription("Brak obiektu na wej�ciu");
		aBlock->input.push_back(input1);

		BlockInput input2("input2");
		input2.allowedTypes.push_back("Mask3x3");
		input2.setDescription("Domy�lne wej�cie - maska 3x3");
		input2.setErrorCode(1);
		input2.setErrorDescription("Brak obiektu na wej�ciu");
		aBlock->input.push_back(input2);

		BlockOutput output1("output1");
		output1.setOutputType("Bitmap24bit");
		output1.setDescription("Domy�lne wyj�cie");
		output1.setErrorCode(1);
		output1.setErrorDescription("Brak obiektu na wej�ciu");
		aBlock->output.push_back(output1);
		return 2;
	}
	else
	{
		bool flag = false;
		for(unsigned int i(0); i < aBlock->input.size(); i++)
		{
			if(aBlock->input[i].getConnectedType().IsEmpty())
			{
				aBlock->input[i].setErrorCode(1);
				aBlock->input[i].setErrorDescription("Brak obiektu na wej�ciu");
				flag = true;
			}
			else if(aBlock->input[i].getErrorCode() != 0)
			{
				aBlock->input[i].setErrorCode(0);
				aBlock->input[i].setErrorDescription("");
			}
		}
		if(flag)
		{
			aBlock->output[0].setErrorCode(1);
			aBlock->output[0].setErrorDescription("Brak obiektu na wej�ciu"); 
			aBlock->output[0].setOutputType("Bitmap24bit");
			return 1;
		}
		else
		{
			if (aBlock->output[0].getOutputType()!= aBlock->input[0].getConnectedType())
			{
				aBlock->output[0].setOutputType(aBlock->input[0].getConnectedType());
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
			{
				return 0;
			}
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

	else    if(connectedType == "Bitmap4bit")
		picture->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap4bit::getBitmap(aBlock->input[0].getObject()))));

	else	if(connectedType == "Bitmap8bit")
		picture->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap8bit::getBitmap(aBlock->input[0].getObject()))));

	else    if(connectedType == "Bitmap16bit")
		picture->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap16bit::getBitmap(aBlock->input[0].getObject()))));

	else	if(connectedType == "Bitmap24bit")
		picture->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap24bit::getBitmap(aBlock->input[0].getObject()))));

	else	if(connectedType == "Bitmap32bit")
		picture->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap32bit::getBitmap(aBlock->input[0].getObject()))));

		
	TypeConfig* tmp=IMask3x3::getNew();
	tmp = aBlock->input[1].getObject();
	short *mask = new short[9];
	mask[0]=IMask3x3::getValue(tmp,1,1);
	mask[1]=IMask3x3::getValue(tmp,1,2);
	mask[2]=IMask3x3::getValue(tmp,1,3);
	mask[3]=IMask3x3::getValue(tmp,2,1);
	mask[4]=IMask3x3::getValue(tmp,2,2);
	mask[5]=IMask3x3::getValue(tmp,2,3);
	mask[6]=IMask3x3::getValue(tmp,3,1);
	mask[7]=IMask3x3::getValue(tmp,3,2);
	mask[8]=IMask3x3::getValue(tmp,3,3);

	if(!MaskFilter(picture, mask))
	{
		aBlock->output[0].setErrorCode(2);
		aBlock->output[0].setErrorDescription("Pusta bitmapa");
		picture->Free();
		return 2;
	}
	TypeConfig* copy;

	if(connectedType == "Bitmap1bit")
	{
		copy = IBitmap1bit::getNew();
		IBitmap1bit::setBitmap(copy, *picture);
	}
	else if(connectedType == "Bitmap4bit")
	{
		copy = IBitmap4bit::getNew();
		IBitmap4bit::setBitmap(copy, *picture);
	}
	else if(connectedType == "Bitmap8bit")
	{
		copy = IBitmap8bit::getNew();
		IBitmap8bit::setBitmap(copy, *picture);
	}
	else if(connectedType == "Bitmap16bit")
	{
		copy = IBitmap16bit::getNew();
		IBitmap16bit::setBitmap(copy, *picture);
	}
	else if(connectedType == "Bitmap24bit")
	{
		copy = IBitmap24bit::getNew();
		IBitmap24bit::setBitmap(copy, *picture);
	}
	else if(connectedType == "Bitmap32bit")
	{
		copy = IBitmap32bit::getNew();
		IBitmap32bit::setBitmap(copy, *picture);
	}

	aBlock->output[0].setObject(*copy);
	
	picture->Free();
	delete copy;
    delete mask;
	delete tmp;

	return 0;
}
//---------------------------------------------------------------------------
