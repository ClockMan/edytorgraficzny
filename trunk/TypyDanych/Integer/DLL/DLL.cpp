#include "DLL.h"
#pragma hdrstop
#pragma argsused
#pragma link "MEMMGR.LIB"


TForm* __stdcall show(TComponent* owner, TypeConfig* aData)
{
   if (!isValid(aData)) return NULL;
   TForm1 *x=new TForm1(owner);
   x->Panel1->Caption=IntToStr(aData->getInt("int"));
   return x;
}

bool __stdcall isValid(TypeConfig* aData)
{
  if (aData->getName()!="Integer") return false;
  if (!aData->isExist("int")) return false;
  if (!aData->isInt("int")) return false;
  return true;
}

AnsiString __stdcall getType()
{
	return "Integer";
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
