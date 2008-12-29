#include "DLL.h"
#pragma hdrstop
#pragma argsused
#pragma link "MEMMGR.LIB"


TFrame* __stdcall show(TWinControl* owner, TypeConfig* aData)
{
   if (!isValid(aData)) return NULL;
   TForm1 *x=new TForm1(owner);
   x->Parent=owner;
   for(int i=1;i<10;i++)
   {
		TPanel *pn=(TPanel*)(x->FindComponent("Panel"+IntToStr(i)));
		pn->Height=(int)(x->Height/3);
		pn->Width=(int)(x->Width/3);
		pn->Top=(((int)(i/3))*((int)(x->Height/3)));
		pn->Left=(((int)((i%3)-1))*((int)(x->Width/3)));
		pn->Caption=FloatToStr(aData->getDouble("d"+IntToStr((int)(i/3)+1)+"_"+IntToStr((i%3))));
		// 1 2 3
		// 4 5 6
		// 7 8 9 
   }
   return x;
}

bool __stdcall isValid(TypeConfig* aData)
{
  if (aData->getName()!="Mask3x3") return false;
  for(int i2=1;i2<4;++i2)
  for(int i=1;i<4;++i)
  {
	if (!aData->isExist("d"+IntToStr(i)+"_"+IntToStr(i2))) return false;
	if (!aData->isDouble("d"+IntToStr(i)+"_"+IntToStr(i2))) return false;
  }
  return true;
}

AnsiString __stdcall getType()
{
	return "Mask3x3";
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
