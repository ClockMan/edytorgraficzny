//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "DLL.h"
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
		output1.setOutputType("Mask3x3");
		output1.setDescription("Domyœlne wyjœcie");
		output1.setErrorCode(0);
		output1.setErrorDescription("");
		aBlock->output.push_back(output1);
		aBlock->getConfig()->addInt("d1_1",0);
		aBlock->getConfig()->addInt("d1_2",0);
		aBlock->getConfig()->addInt("d1_3",0);
		aBlock->getConfig()->addInt("d2_1",0);
		aBlock->getConfig()->addInt("d2_2",0);
		aBlock->getConfig()->addInt("d2_3",0);
		aBlock->getConfig()->addInt("d3_1",0);
		aBlock->getConfig()->addInt("d3_2",0);
		aBlock->getConfig()->addInt("d3_3",0);
		return 2;
	}
	return 0;
}
//---------------------------------------------------------------------------
int __stdcall run(Block *aBlock)
{
	TypeConfig* copy=IMask3x3::getNew();
	IMask3x3::setValue(copy, 1, 1,aBlock->getConfig()->getInt("d1_1"));
	IMask3x3::setValue(copy, 1, 2,aBlock->getConfig()->getInt("d1_2"));
	IMask3x3::setValue(copy, 1, 3,aBlock->getConfig()->getInt("d1_3"));
	IMask3x3::setValue(copy, 2, 1,aBlock->getConfig()->getInt("d2_1"));
	IMask3x3::setValue(copy, 2, 2,aBlock->getConfig()->getInt("d2_2"));
	IMask3x3::setValue(copy, 2, 3,aBlock->getConfig()->getInt("d2_3"));
	IMask3x3::setValue(copy, 3, 1,aBlock->getConfig()->getInt("d3_1"));
	IMask3x3::setValue(copy, 3, 2,aBlock->getConfig()->getInt("d3_2"));
	IMask3x3::setValue(copy, 3, 3,aBlock->getConfig()->getInt("d3_3"));
	aBlock->output[0].setObject(*copy);
	delete copy;
	return 0;
}
//---------------------------------------------------------------------------
