#include "Item.h"

AnsiString& Item::getName()
{
	return name;
}

void* Item::getObject()
{
	return pointer;
}

bool Item::setObject(void* aObject)
{
	if (aObject!=NULL)
	{
		pointer=aObject;
		return true;
	}
	return false;
}


AnsiString& Item::getType()
{
	return type;
}

Item::Item(const AnsiString aName, void* aObject, const AnsiString aType)
{
	if (aName.IsEmpty()) throw "Parametr aName jest pustym stringiem";
	if (aType.IsEmpty()) throw "Parametr aTyp jest pustym stringiem";
	if (aObject==NULL) throw "Parametr aObiekt jest NULL'em";
	name=aName;
	pointer=aObject;
	type=aType;
}

Item::Item(const Item &copy)
{
	name=copy.name;
	pointer=copy.pointer;
	type=copy.type;
}

