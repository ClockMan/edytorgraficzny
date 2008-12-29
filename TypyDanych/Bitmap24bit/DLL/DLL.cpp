#include "DLL.h"
#pragma hdrstop
#pragma argsused
#pragma link "MEMMGR.LIB"


TFrame* __stdcall show(TWinControl* owner,  TypeConfig* aData)
{
   if (!isValid(aData)) return NULL;
   TForm1 *x=new TForm1(owner);
   x->Parent=owner;
   x->Image1->Picture->Bitmap=const_cast<Graphics::TBitmap*>(&(aData->getBitmap("bitmapa")));
   return x;
}

bool __stdcall isValid(TypeConfig* aData)
{
  if (aData->getName()!="Bitmap24bit") return false;
  if (!aData->isExist("bitmapa")) return false;
  if (!aData->isBitmap("bitmapa")) return false;
  Graphics::TBitmap *bmp=const_cast<Graphics::TBitmap*>(&(aData->getBitmap("bitmapa")));
  if (bmp->PixelFormat!=pf24bit) return false;
  return true;
}

AnsiString __stdcall getType()
{
	return "Bitmap24bit";
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
