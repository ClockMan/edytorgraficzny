#include "Item.h"

AnsiString& Item::getName() {
	return name;
}

void* Item::getObject() {
	return wsk;
}

AnsiString& Item::getType() {
	return type;
}

Item::Item(AnsiString& aName, void* aObiekt, AnsiString& aTyp)
{
	if (aName.IsEmpty()) throw "Parametr aName jest pustym stringiem";
	if (aTyp.IsEmpty()) throw "Parametr aTyp jest pustym stringiem";
	if (aObiekt==NULL) throw "Parametr aObiekt jest NULL'em";
	name=aName;
	wsk=aObiekt;
	type=aTyp;
}

Item::Item(Item &kopia)
{
	name=kopia.name;
	wsk=kopia.wsk;
	type=kopia.type;
}

