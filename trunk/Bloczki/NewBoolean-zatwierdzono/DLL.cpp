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
		output1.setOutputType("Boolean");
		output1.setDescription("Domyœlne wyjœcie");
		output1.setErrorCode(0);
		output1.setErrorDescription("");
		aBlock->output.push_back(output1);
		aBlock->getConfig()->addBoolean("data",false);
		return 2;
	}
	return 0;
}
//---------------------------------------------------------------------------
int __stdcall run(Block *aBlock)
{
	TypeConfig* copy=IBoolean::getNew();
	IBoolean::setValue(copy, aBlock->getConfig()->getBoolean("data"));
	aBlock->output[0].setObject(*copy);
	delete copy;
	return 0;
}
//---------------------------------------------------------------------------
