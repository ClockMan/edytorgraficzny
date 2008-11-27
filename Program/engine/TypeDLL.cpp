#include "TypeDLL.h"

TypeDLL::TypeDLL(const AnsiString &file, const AnsiString &stype)
{
   if (stype.IsEmpty()) throw "Nazwa musi byæ unikalna i nie pusta"; 
   DLLHandle=LoadLibrary(file.c_str());
   if (!DLLHandle) throw "B³¹d podczas za³adowania DLL";
   fshow=(TypeDLL_show)GetProcAddress(DLLHandle, "_show");
   fisValid=(TypeDLL_isValid)GetProcAddress(DLLHandle, "_isValid");
   if ((!fshow)||(!fisValid))
   {
	   FreeLibrary(DLLHandle);
	   throw "To nie jest DLL'ka typu";
   }
   type=stype;
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
  return type;
}

