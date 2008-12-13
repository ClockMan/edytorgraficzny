#include "TypeDLL.h"

TypeDLL::TypeDLL(const AnsiString &fileDLL)
{
   DLLHandle=LoadLibrary(fileDLL.c_str());
   if (!DLLHandle) throw "B³¹d podczas za³adowania DLL";
   fshow=(TypeDLL_show)GetProcAddress(DLLHandle, "_show");
   fisValid=(TypeDLL_isValid)GetProcAddress(DLLHandle, "_isValid");
   fgetType=(TypeDLL_getType)GetProcAddress(DLLHandle, "_getType");
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

TForm* TypeDLL::show(TComponent* parent, TypeConfig* aData) {
	return fshow(parent, aData);
}

bool TypeDLL::isValid(TypeConfig *aData) {
	return fisValid(aData);
}

AnsiString& TypeDLL::getType()
{
  return fgetType();
}

