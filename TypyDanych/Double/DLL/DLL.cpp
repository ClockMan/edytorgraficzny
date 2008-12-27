#include "DLL.h"
#pragma hdrstop
#pragma argsused
#pragma link "MEMMGR.LIB"


TForm* __stdcall show(TComponent* owner, TypeConfig* aData)
{
   if (!isValid(aData)) return NULL;
   TForm1 *x=new TForm1(owner);
   x->Panel1->Caption=FormatFloat("0.000000000",aData->getDouble("float"));
   return x;
}

bool __stdcall isValid(TypeConfig* aData)
{
  if (aData->getName()!="Double") return false;
  if (!aData->isExist("float")) return false;
  if (!aData->isDouble("float")) return false;
  return true;
}

AnsiString __stdcall getType()
{
	return "Double";
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
