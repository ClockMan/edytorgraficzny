#include "DLL.h"
#pragma hdrstop
#pragma argsused
#pragma link "MEMMGR.LIB"


TFrame* __stdcall show(TWinControl* owner, TypeConfig* aData)
{
   if (!isValid(aData)) return NULL;
   TForm1 *x=new TForm1(owner);
   x->Parent=owner;
   if (aData->getBoolean("bool"))
   {
	   x->Panel1->Color=clLime;
	   x->Panel1->Caption="TRUE";
   }
   else
   {
	   x->Panel1->Color=clRed;
	   x->Panel1->Caption="FALSE";
   }
   return x;
}

bool __stdcall isValid(TypeConfig* aData)
{
  if (aData->getName()!="Boolean") return false;
  if (!aData->isExist("bool")) return false;
  if (!aData->isBoolean("bool")) return false;
  return true;
}

AnsiString __stdcall getType()
{
	return "Boolean";
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
