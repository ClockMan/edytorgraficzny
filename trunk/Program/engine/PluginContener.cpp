#include "PluginContener.h"

bool PluginContener::addType(const AnsiString &aPath, const AnsiString &type)
{
	if (getTypeDLL(type)!=NULL) return false;
	try
	{
	  TypeDLL *tmp=new TypeDLL(aPath, type);
	  listOfType.push_back(tmp);
	  return true;
	} catch (char* e)
	{
		return false;
	}
}

bool PluginContener::addFunction(const AnsiString &aPath, const AnsiString &name)
{
	if (getFunctionDLL(name)!=NULL) return false;
	try
	{
	  FunctionDLL *tmp=new FunctionDLL(aPath, name);
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

TypeDLL* PluginContener::getTypeDLL(const AnsiString &type)
{
  for(int i=listOfType.size()-1;i>=0;--i)
  {
	  if (listOfType[i]->getType()==type) return listOfType[i];
  }
  return NULL;
}

FunctionDLL* PluginContener::getFunctionDLL(const AnsiString &name)
{
  for(int i=listOfFunction.size()-1;i>=0;--i)
  {
	  if (listOfFunction[i]->getName()==name) return listOfFunction[i];
  }
  return NULL;
}

