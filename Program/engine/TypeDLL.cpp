#include "TypeDLL.h"

TypeDLL::TypeDLL(const AnsiString &fileDLL)
{
   DLLHandle=LoadLibrary(fileDLL.c_str());
   if (!DLLHandle) throw "B³¹d podczas za³adowania DLL";
   fshow=(TypeDLL_show)GetProcAddress(DLLHandle, "show");
   fisValid=(TypeDLL_isValid)GetProcAddress(DLLHandle, "isValid");
   fgetType=(TypeDLL_getType)GetProcAddress(DLLHandle, "getType");
   if ((!fshow)||(!fisValid)||(!fgetType))
   {
	   FreeLibrary(DLLHandle);
	   throw "To nie jest DLL'ka typu";
   }
}

TypeDLL::~TypeDLL()
{
   FreeLibrary(DLLHandle);
}

TFrame* TypeDLL::show(TWinControl* parent, TypeConfig* aData) {
	return fshow(parent, aData);
}

bool TypeDLL::isValid(TypeConfig *aData) {
	return fisValid(aData);
}

AnsiString TypeDLL::getType()
{
  return fgetType();
}

