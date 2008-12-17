#include "FunctionDLL.h"

FunctionDLL::FunctionDLL(const AnsiString &fileDLL)
{
   FunctionAddRequest=NULL;
   DLLHandle=LoadLibrary(fileDLL.c_str());
   if (!DLLHandle) throw "B³¹d podczas za³adowania DLL";
   frun=(FunctionDLL_run)GetProcAddress(DLLHandle, "run");
   fvalidate=(FunctionDLL_validate)GetProcAddress(DLLHandle, "validate");
   fshowConfig=(FunctionDLL_showConfig)GetProcAddress(DLLHandle, "showConfig");
   if ((!frun)||(!fvalidate)||(!fshowConfig))
   {
	   FreeLibrary(DLLHandle);
	   throw "To nie jest DLL'ka typu";
   }
   AnsiString sname=ExtractFileName(fileDLL).SetLength(ExtractFileName(fileDLL).Length()-ExtractFileExt(fileDLL).Length());
   picture=NULL;

   if (FileExists(ExtractFileDir(fileDLL)+"\\"+sname+".bmp")) {
	picture=new Graphics::TBitmap();
	Graphics::TBitmap *tmp=new Graphics::TBitmap();
	tmp->LoadFromFile(ExtractFileDir(fileDLL)+"\\"+sname+".bmp");
	picture->Width=32;
	picture->Height=32;
	TRect tmp2;
	tmp2.Left=0;
	tmp2.Right=32;
	tmp2.Top=0;
	tmp2.Bottom=32;
	picture->Canvas->StretchDraw(tmp2, tmp);
	delete tmp;
   }

   if (FileExists(ExtractFileDir(fileDLL)+"\\"+sname+".ini")) {
	TIniFile *ini=new TIniFile(ExtractFileDir(fileDLL)+"\\"+sname+".ini");
	name=ini->ReadString("INFO", "name", sname);
	fullName=ini->ReadString("INFO", "fullname", name);
	description=ini->ReadString("INFO", "description","");
	int i=0;
	AnsiString c;
	while((c=ini->ReadString("CATEGORY", IntToStr(i),""))!="")
	{
	   category.push_back(c);
	   ++i;
	}
	AnsiString t=ini->ReadString("INFO", "image", "");
	if (t!=""&&FileExists(ExtractFileDir(fileDLL)+"\\"+t)) {
	if (picture!=NULL) delete picture;
	picture=new Graphics::TBitmap();
	Graphics::TBitmap *tmp=new Graphics::TBitmap();
	tmp->LoadFromFile(ExtractFileDir(fileDLL)+"\\"+t);
	picture->Width=32;
	picture->Height=32;
	TRect tmp2;
	tmp2.Left=0;
	tmp2.Right=32;
	tmp2.Top=0;
	tmp2.Bottom=32;
	picture->Canvas->StretchDraw(tmp2, tmp);
	delete tmp;
   }

	delete ini;
   }
   else
   {
	 name=ExtractFileName(fileDLL).SetLength(ExtractFileName(fileDLL).Length()-ExtractFileExt(fileDLL).Length());
	 fullName=name;
   }

   if (category.size()==0)
   {
	  category.push_back("Funkcje");
   }
}

FunctionDLL::~FunctionDLL()
{
   FreeLibrary(DLLHandle);
   if (picture!=NULL) delete picture;
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

void __fastcall FunctionDLL::OnClick(TObject *Sender)
{
  if (FunctionAddRequest!=NULL)
  		FunctionAddRequest(this);
}
