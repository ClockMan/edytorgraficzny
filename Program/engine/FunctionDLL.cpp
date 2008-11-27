#include "FunctionDLL.h"

FunctionDLL::FunctionDLL(const AnsiString &file, const AnsiString &sname)
{
   if (sname.IsEmpty()) throw "Nazwa musi byæ unikalna i nie pusta";
   DLLHandle=LoadLibrary(file.c_str());
   if (!DLLHandle) throw "B³¹d podczas za³adowania DLL";
   frun=(FunctionDLL_run)GetProcAddress(DLLHandle, "_run");
   fvalidate=(FunctionDLL_validate)GetProcAddress(DLLHandle, "_validate");
   fshowConfig=(FunctionDLL_showConfig)GetProcAddress(DLLHandle, "_showConfig");
   if ((!frun)||(!fvalidate)||(!fshowConfig))
   {
	   FreeLibrary(DLLHandle);
	   throw "To nie jest DLL'ka typu";
   }
   name=sname;
}

FunctionDLL::~FunctionDLL()
{
   FreeLibrary(DLLHandle);
}

AnsiString& FunctionDLL::getName()
{
	return name;
}

int FunctionDLL::run(Block *aBlock) {
	return frun(aBlock);
}

bool FunctionDLL::showConfig(TComponent *owner, Block *aBlock) {
	return fshowConfig(owner,aBlock);
}

int FunctionDLL::validate(Block *aBlock) {
	return fvalidate(aBlock);
}

