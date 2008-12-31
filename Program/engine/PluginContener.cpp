#include "PluginContener.h"

TypeDLL* PluginContener::addType(const AnsiString &fileDLL)
{
	try
	{
	  TypeDLL *tmp=new TypeDLL(fileDLL);
	  listOfType.push_back(tmp);
	  return tmp;
	}
	  catch (char* e)
	{
		return NULL;
	}
}

FunctionDLL* PluginContener::addFunction(const AnsiString &fileDLL)
{
	try
	{
	  FunctionDLL *tmp=new FunctionDLL(fileDLL);
	  listOfFunction.push_back(tmp);
	  return tmp;
	} catch (char* e)
	{
		return NULL;
	}
}

PluginContener::PluginContener()
{
	OnLoadingProgress=NULL;
	OnFunctionAddRequest=NULL;
}

PluginContener::~PluginContener()
{
	while(listOfType.size()>0)
	{
		TypeDLL* tmp=listOfType[listOfType.size()-1];
		listOfType.pop_back();
		delete tmp;
	}

	while(listOfFunction.size()>0)
	{
		FunctionDLL* tmp=listOfFunction[listOfFunction.size()-1];
		listOfFunction.pop_back();
		delete tmp;
	}
}

TypeDLL* PluginContener::getType(const AnsiString &type)
{
  for(int i=listOfType.size()-1;i>=0;--i)
  {
	  if (listOfType[i]->getType()==type) return listOfType[i];
  }
  return NULL;
}

FunctionDLL* PluginContener::getFunction(const AnsiString &names)
{
  for(int i=listOfFunction.size()-1;i>=0;--i)
  {
	  if (listOfFunction[i]->name==names) return listOfFunction[i];
  }
  return NULL;
}

void PluginContener::AddMenus(FunctionDLL *info, TMainMenu &menu, TImageList &images, int upId, int downId, int functionIcon, int folderIcon)
{
	TStringList *tmp=new TStringList();
	int index=functionIcon;
	if (info->picture!=NULL)
	{
	   Graphics::TBitmap *bmp=new Graphics::TBitmap();
	   bmp->Width=16;
	   bmp->Height=16;
	   TRect tmp2;
	   tmp2.Left=0;
	   tmp2.Right=16;
	   tmp2.Top=0;
	   tmp2.Bottom=16;
	   bmp->Canvas->StretchDraw(tmp2, info->picture);
	   index=images.AddMasked(bmp, clFuchsia);
	   delete bmp;
	}
	for(unsigned int i=0;i<info->category.size();i++)
	{
		tmp->Text=StringReplace(info->category[i],"|","\n",TReplaceFlags() << rfReplaceAll);
		if (tmp->Count==0||tmp->Strings[0].IsEmpty()) continue;
		//Wyszukiwanie maina, jak niema to dodajemy
		TMenuItem *x=&menu.Items[0];
		TMenuItem *y=NULL;
		for(int q=0;q<tmp->Count;q++)
		{
			for(int j=0;j<x->Count;j++)
			{
				if (x->Items[j]->GroupIndex==downId&&(x->Items[j]->Caption.AnsiCompare(tmp->Strings[q])==0))
				{
					y=x->Items[j];
					break;
				}
			}

			if (y==NULL)
			{
				//niema g³ownego menu, tworzymy go
				y=menu.CreateMenuItem();
				y->AutoCheck=false;
				y->Caption=tmp->Strings[q];
				y->GroupIndex=downId;
				y->Visible=true;
				y->ImageIndex=(q!=0)?folderIcon:-1;
				//znajdujemy miejsce gdzie go dodac
				int pos;
				for(pos=0;pos<x->Count;pos++)
					if ((x->Items[pos]->GroupIndex==downId&&tmp->Strings[q].AnsiCompare(x->Items[pos]->Caption)==-1)||(x->Items[pos]->GroupIndex==upId)) break;
				x->Insert(pos,y);
			}
			x=y;
			y=NULL;
		}
		//dodawanie koñcowego itemu, on te¿ musi byæ sortowany, niesprawdzamy czy nazwa taka ju¿ jest
    	int pos;
		for(pos=0;pos<x->Count;pos++)
		if ((x->Items[pos]->GroupIndex==upId&&info->fullName.AnsiCompare(x->Items[pos]->Caption)==-1)) break;

		y=menu.CreateMenuItem();
		y->AutoCheck=false;
		y->Caption=info->fullName;
		y->GroupIndex=upId;
		y->Visible=true;
		y->ImageIndex=index;
		y->Hint=info->description;
		y->OnClick=info->OnClick;
		x->Insert(pos,y);
	}
}

int PluginContener::SearchDirectory(std::vector<AnsiString> &refvecFiles,
					const AnsiString        &refcstrRootDirectory,
					const AnsiString        &refcstrExtension,
					bool                     bSearchSubdirectories)
{
  AnsiString strFilePath;
  AnsiString    strPattern;              // Pattern
  HANDLE          hFile;                   // Handle to file
  WIN32_FIND_DATA FileInformation;         // File information


  strPattern = refcstrRootDirectory + "\\*."+refcstrExtension;

  hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
  if(hFile != INVALID_HANDLE_VALUE)
  {
    do
	{
	  if(FileInformation.cFileName[0] != '.')
	  {
		strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

		if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
          if(bSearchSubdirectories)
          {
			int iRC = SearchDirectory(refvecFiles,
                                      strFilePath,
                                      refcstrExtension,
									  bSearchSubdirectories);
			if(iRC)
			  return iRC;
		  }
		}
        else
        {
			refvecFiles.push_back(strFilePath);
		}
      }
    } while(::FindNextFile(hFile, &FileInformation) == TRUE);

	// Close handle
    ::FindClose(hFile);

	DWORD dwError = ::GetLastError();
	if(dwError != ERROR_NO_MORE_FILES)
	  return dwError;
  }

  return 0;
}

void PluginContener::OnFunctionClick(void* Sender)
{
	if (OnFunctionAddRequest!=NULL) 
			OnFunctionAddRequest(Sender);
}

bool PluginContener::LoadData(AnsiString blockDir, AnsiString typesDir, TMainMenu &menu, TImageList &images, int upId, int downId, int functionIcon, int folderIcon)
{
	std::vector<AnsiString> types;
	SearchDirectory(types,typesDir,"dll");
	std::vector<AnsiString> functions;
	SearchDirectory(functions,blockDir,"dll");
	int max=types.size()+functions.size();
	unsigned int i,u=0;
	for(i=0;i<types.size();i++)
	{
	   TypeDLL *wsk=addType(types[i]);
	   if (wsk!=NULL)
	   {
		 if (OnLoadingProgress!=NULL)
				OnLoadingProgress(this, ++u, max, wsk->getType(),0);
	   }
	   else
	   {
		 if (OnLoadingProgress!=NULL)
		 OnLoadingProgress(this, ++u, max, ExtractFileName(types[i]), 2);
	   }
	}

	for(i=0;i<functions.size();i++)
	{
	   FunctionDLL *wsk=addFunction(functions[i]);
	   if (wsk!=NULL)
	   {
		 AddMenus(wsk, menu, images, upId, downId, functionIcon, folderIcon);
		 wsk->FunctionAddRequest=OnFunctionClick;
		 if (OnLoadingProgress!=NULL)
		 OnLoadingProgress(this, ++u, max, ExtractFileName(functions[i]), 1);
	   }
	   else
	   {
		 if (OnLoadingProgress!=NULL)
		 OnLoadingProgress(this, ++u, max, ExtractFileName(functions[i]), 3);
	   }
	}
   return true;	
}

