//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "SHOW.h"
#include "../../../Program/engine/TypeConfig.h"

#pragma hdrstop
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

USELIB("..\..\Lib\memmgr.lib");

extern "C" __declspec(dllexport) TForm* show(TComponent* owner, TypeConfig* aData);
extern "C" __declspec(dllexport) bool isValid(TypeConfig* aData);

TForm* show(TComponent* owner, TypeConfig* aData)
{
   if (!isValid(aData)) return NULL;
   TForm1 *x=new TForm1(owner);
   x->Image1->Picture->Bitmap=&(aData->getBitmap("bitmapa"));
   return x;
}

bool isValid(TypeConfig* aData)
{
   //sprawdzanie typu danych
  if (aData->getName()!="Bitmap24bit") return false;
  if (!aData->isExist("bitmapa")) return false;
  if (!aData->isBitmap("bitmapa")) return false;
  Graphics::TBitmap *bmp=&(aData->getBitmap("bitmapa"));
  if (bmp->PixelFormat!=pf24bit) return false;
  return true;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
