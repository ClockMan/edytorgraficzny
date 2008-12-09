#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "TypeConfig.h"

TypeConfig::TypeConfig(const AnsiString aName)
{
	if(aName.IsEmpty())
    	throw "Nazwa nie mo¿e byæ pusta";
   nazwa=aName;
}

TypeConfig::TypeConfig(TStream &stream)
{
   if (!loadFromStream(stream)) throw "B³êdny format";
}

TypeConfig::TypeConfig(const TypeConfig &kopia):BlockConfig(kopia)
{
   nazwa=kopia.nazwa;
}

TypeConfig::~TypeConfig()
{
   //clear();
}

bool TypeConfig::saveToStream(TStream &aWhere)
{
   char id;
   id='T';
   aWhere.Write(&id, 1);
   id='C';
   aWhere.Write(&id, 1);

   unsigned long count=nazwa.Length();
   aWhere.Write(&count,sizeof(unsigned long));
   aWhere.Write(nazwa.c_str(),count);

   return saveToStream2(aWhere);
}

bool TypeConfig::loadFromStream(TStream &aFrom)
{
   clear();
   char id1,id2;
   aFrom.Read(&id1, 1);aFrom.Read(&id2, 1);
   if ((id1!='T')||(id2!='C')) return false;

   unsigned long itmp;
   aFrom.Read(&itmp, sizeof(unsigned long));
   char *typ1=new char[itmp+1];
   aFrom.Read(typ1, itmp);
   typ1[itmp]='\0';
   AnsiString *typ=new AnsiString(typ1);
   nazwa=*typ;
   delete typ1;
   return loadFromStream2(aFrom);
}

const AnsiString& TypeConfig::getName()
{
   return nazwa;
}
