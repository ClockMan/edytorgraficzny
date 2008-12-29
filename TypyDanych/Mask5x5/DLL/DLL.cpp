#include "DLL.h"
#pragma hdrstop
#pragma argsused
#pragma link "MEMMGR.LIB"


TFrame* __stdcall show(TWinControl* owner, TypeConfig* aData)
{
   if (!isValid(aData)) return NULL;
   TForm1 *x=new TForm1(owner);
   x->Parent=owner;
   for(int i=1;i<26;i++)
   {
		TPanel *pn=(TPanel*)(x->FindComponent("Panel"+IntToStr(i)));
		pn->Height=(int)(x->Height/5);
		pn->Width=(int)(x->Width/5);
		pn->Top=(((int)(i/5))*((int)(x->Height/5)));
		pn->Left=(((int)((i%5)-1))*((int)(x->Width/5)));
		pn->Caption=FloatToStr(aData->getDouble("d"+IntToStr((int)(i/5)+1)+"_"+IntToStr((i%5))));
		// 1  2  3  4  5
		// 6  7  8  9  10
		// 11 12 13 14 15
		// 16 17 18 19 20
		// 21 22 23 24 25
   }
   return x;
}

bool __stdcall isValid(TypeConfig* aData)
{
  if (aData->getName()!="Mask3x3") return false;
  for(int i2=1;i2<6;++i2)
  for(int i=1;i<6;++i)
  {
	if (!aData->isExist("d"+IntToStr(i)+"_"+IntToStr(i2))) return false;
	if (!aData->isDouble("d"+IntToStr(i)+"_"+IntToStr(i2))) return false;
  }
  return true;
}

AnsiString __stdcall getType()
{
	return "Mask5x5";
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
