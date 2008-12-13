#include "PluginContener.h"

bool PluginContener::addType(const AnsiString &fileDLL)
{
	try
	{
	  TypeDLL *tmp=new TypeDLL(fileDLL);
	  listOfType.push_back(tmp);
	  return true;
	}
	  catch (char* e)
	{
		return false;
	}
}

bool PluginContener::addFunction(const AnsiString &fileDLL, const AnsiString &fileINI)
{
	try
	{
	  FunctionDLL *tmp=new FunctionDLL(fileDLL, fileINI);
	  listOfFunction.push_back(tmp);
	  return true;
	} catch (char* e)
	{
		return false;
	}
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

