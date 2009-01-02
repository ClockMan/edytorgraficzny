//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "subtraction.cpp"

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
#pragma link "MEMMGR.LIB"

#define INPUTS 2
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
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
		input1.setDescription("Domyœlne wejœcie 1");
		input1.setErrorCode(1);
		input1.setErrorDescription("Brak obiektu na wejœciu");
		aBlock->input.push_back(input1);

		BlockInput input2("input2");
		input2.allowedTypes.push_back("Bitmap1bit");
		input2.allowedTypes.push_back("Bitmap4bit");
		input2.allowedTypes.push_back("Bitmap8bit");
		input2.allowedTypes.push_back("Bitmap16bit");
		input2.allowedTypes.push_back("Bitmap24bit");
		input2.allowedTypes.push_back("Bitmap32bit");
		input2.setDescription("Domyœlne wejœcie 2");
		input2.setErrorCode(1);
		input2.setErrorDescription("Brak obiektu na wejœciu");
		aBlock->input.push_back(input2);

		BlockOutput output1("output1");
		output1.setOutputType("Bitmap24bit");
		output1.setDescription("Domyœlne wyjœcie");
		output1.setErrorCode(1);
		output1.setErrorDescription("Brak obiektu na wejœciu");
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
				aBlock->input[i].setErrorDescription("Brak obiektu na wejœciu");
				flag = true;
			}
		}
		if(flag)
		{
			aBlock->output[0].setErrorCode(1);
			aBlock->output[0].setErrorDescription("Brak obiektu na wejœciu");
			aBlock->output[0].setOutputType("Bitmap24bit");
			return 1;
		}
		else
		{
			flag = false;
			if (aBlock->output[0].getOutputType()!= aBlock->input[0].getConnectedType())
			{
				aBlock->output[0].setOutputType(aBlock->input[0].getConnectedType());
				aBlock->input[0].setErrorCode(0);
				aBlock->output[0].setErrorCode(0);
				aBlock->input[0].setErrorDescription("");
				aBlock->output[0].setErrorDescription("");
				return 1;
			}
			else
			{
				for(unsigned int i(0); i < aBlock->input.size(); i++)
				{
					if(aBlock->input[i].getErrorCode() != 0)
					{
						aBlock->input[i].setErrorCode(0);
						aBlock->input[i].setErrorDescription("");
						flag = true;
					}
				}
				if(aBlock->output[0].getErrorCode() != 0)
				{
					aBlock->output[0].setErrorCode(0);
					aBlock->output[0].setErrorDescription("");
					flag = true;
				}
				if(flag)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}

		}
	}
}
//---------------------------------------------------------------------------
int __stdcall run(Block *aBlock)
{
	if(aBlock->input.size() != INPUTS)
		return 1;
	for(unsigned int i(0); i < aBlock->input.size(); i++)
	{
		if(aBlock->input[i].getConnectedType().IsEmpty())
		{
			return 1;
		}
	}

	Graphics::TBitmap (*picture[INPUTS]);
	AnsiString connectedType;
	for(int i(0); i < INPUTS; i++)
	{
		connectedType = aBlock->input[i].getConnectedType();
		picture[i] = new Graphics::TBitmap();
		if(connectedType == "Bitmap1bit")
			picture[i]->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap1bit::getBitmap(aBlock->input[i].getObject()))));

		else if(connectedType == "Bitmap4bit")
			picture[i]->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap4bit::getBitmap(aBlock->input[i].getObject()))));

		else	if(connectedType == "Bitmap8bit")
			picture[i]->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap8bit::getBitmap(aBlock->input[i].getObject()))));

		else if(connectedType == "Bitmap16bit")
			picture[i]->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap16bit::getBitmap(aBlock->input[i].getObject()))));

		else	if(connectedType == "Bitmap24bit")
			picture[i]->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap24bit::getBitmap(aBlock->input[i].getObject()))));

		else	if(connectedType == "Bitmap32bit")
			picture[i]->Assign(const_cast<Graphics::TBitmap*>(&(IBitmap32bit::getBitmap(aBlock->input[i].getObject()))));
	}

	if(!Subtraction(picture[0], picture[1]))
	{
		aBlock->output[0].setErrorCode(2);
		aBlock->output[0].setErrorDescription("Pusta bitmapa");
		for(int i(0); i < INPUTS; i++)
		{
			picture[i]->Free();
		}
		return 2;
	}
    
	TypeConfig* copy;     
	AnsiString outputType;

	outputType = aBlock->input[0].getConnectedType();
	if(outputType == "Bitmap1bit")
	{
		copy = IBitmap1bit::getNew();
		IBitmap1bit::setBitmap(copy, *(picture[0]));
	}
	else if(outputType == "Bitmap4bit")
	{
		copy = IBitmap4bit::getNew();
		IBitmap4bit::setBitmap(copy, *(picture[0]));
	}
	else if(outputType == "Bitmap8bit")
	{
		copy = IBitmap8bit::getNew();
		IBitmap8bit::setBitmap(copy, *(picture[0]));
	}
	else if(outputType == "Bitmap16bit")
	{
		copy = IBitmap16bit::getNew();
		IBitmap16bit::setBitmap(copy, *(picture[0]));
	}
	else if(outputType == "Bitmap24bit")
	{
		copy = IBitmap24bit::getNew();
		IBitmap24bit::setBitmap(copy, *(picture[0]));
	}
	else if(outputType == "Bitmap32bit")
	{
		copy = IBitmap32bit::getNew();
		IBitmap32bit::setBitmap(copy, *(picture[0]));
	}

	aBlock->output[0].setObject(*copy);

	for(int i(0); i < INPUTS; i++)
	{
		picture[i]->Free();
	}
	delete copy;

	return 0;
}
//---------------------------------------------------------------------------
#undef INPUTS