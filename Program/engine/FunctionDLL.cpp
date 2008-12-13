#include "FunctionDLL.h"

FunctionDLL::FunctionDLL(const AnsiString &fileDLL, const AnsiString &fileINI)
{
   DLLHandle=LoadLibrary(fileDLL.c_str());
   if (!DLLHandle) throw "B³¹d podczas za³adowania DLL";
   frun=(FunctionDLL_run)GetProcAddress(DLLHandle, "_run");
   fvalidate=(FunctionDLL_validate)GetProcAddress(DLLHandle, "_validate");
   fshowConfig=(FunctionDLL_showConfig)GetProcAddress(DLLHandle, "_showConfig");
   if ((!frun)||(!fvalidate)||(!fshowConfig))
   {
	   FreeLibrary(DLLHandle);
	   throw "To nie jest DLL'ka typu";
   }
   TIniFile *ini=new TIniFile(fileINI);
   name=ini->ReadString("INFO", "name", ExtractFileName(fileDLL).SetLength(ExtractFileName(fileDLL).Length()-ExtractFileExt(fileDLL).Length()));
   fullName=ini->ReadString("INFO", "fullname", name);
   description=ini->ReadString("INFO", "description","");
   int i=0;
   AnsiString c;
   while((c=ini->ReadString("CATEGORY", IntToStr(i),""))!="")
   {
	   category.push_back(c);
	   ++i;
   }
   delete ini;
   if (category.size()==0)
   {
	  category.push_back("DEFAULT FUNCTIONS");
   }
}

FunctionDLL::~FunctionDLL()
{
   FreeLibrary(DLLHandle);
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

