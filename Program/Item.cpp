#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Item.h"

string Item::getName() {
	return name;
}

void* Item::getObject() {
	return wsk;
}

string Item::getType() {
	return type;
}

Item::Item(string aName, void* aObiekt, string aTyp)
{
	if (aName.empty()) throw "Parametr aName jest pustym stringiem";
	if (aTyp.empty()) throw "Parametr aTyp jest pustym stringiem";
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

