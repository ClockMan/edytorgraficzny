#include "BlockConfig.h"

Item* BlockConfig::getItem(const AnsiString aName)
{
	for(int i=map.size()-1;i>=0;--i)
	{
	   if (map[i]->getName()==aName) return map[i];
	}
	throw "Niema takiego itemu na liœcie";
}

BlockConfig::BlockConfig()
{
	changed=false;
}

BlockConfig::BlockConfig(TStream &stream)
{
   if (!loadFromStream(stream)) throw "B³êdny format";
}

void BlockConfig::copyFrom(const BlockConfig &kopia)
{
   for(unsigned int i=0;i<kopia.map.size();++i)
	{
	   if (kopia.map[i]->getType()=="TBitmap") {
		  Graphics::TBitmap *d=new Graphics::TBitmap(*((Graphics::TBitmap*)kopia.map[i]->getObject()));
		  Item *it=new Item(kopia.map[i]->getName(), (void*)d, kopia.map[i]->getType());
		  map.push_back(it);
	   }
	   else
	   if (kopia.map[i]->getType()=="TStream") {
		  TMemoryStream *tmp=new TMemoryStream();
		  tmp->CopyFrom(((TStream*)kopia.map[i]->getObject()), 0);
		  Item *it=new Item(kopia.map[i]->getName(), (void*)tmp, kopia.map[i]->getType());
		  map.push_back(it);
	   }
	   else
	   if (kopia.map[i]->getType()=="AnsiString") {
		  AnsiString *na=new AnsiString(*((AnsiString*)(kopia.map[i]->getObject())));
		  Item *it=new Item(kopia.map[i]->getName(), (void*)na, kopia.map[i]->getType());
		  map.push_back(it);
	   }
	   else
	   if (kopia.map[i]->getType()=="Boolean") {
		 bool *tmp=new bool;
		 *tmp=*((bool*)(kopia.map[i]->getObject()));
		 Item *it=new Item(kopia.map[i]->getName(), (void*)tmp, kopia.map[i]->getType());
		 map.push_back(it);
	   }
	   else
	   if (kopia.map[i]->getType()=="Integer") {
		 int *tmp=new int;
		 *tmp=*((int*)(kopia.map[i]->getObject()));
		 Item *it=new Item(kopia.map[i]->getName(), (void*)tmp, kopia.map[i]->getType());
		 map.push_back(it);
	   }
	   else
	   if (kopia.map[i]->getType()=="Double") {
		 double *tmp=new double;
		 *tmp=*((double*)(kopia.map[i]->getObject()));
		 Item *it=new Item(kopia.map[i]->getName(), (void*)tmp, kopia.map[i]->getType());
		 map.push_back(it);
	   }
	}
}

BlockConfig::BlockConfig(const BlockConfig &kopia)
{
   copyFrom(kopia);
}

BlockConfig::~BlockConfig()
{
	clear();
}

void BlockConfig::clear()
{
	int i=map.size()-1;
	for(;i>=0;++i)
	{
	   if (map[i]->getType()=="TBitmap") {
		 delete (Graphics::TBitmap*)(map[i]->getObject());
	   }
	   else
	   if (map[i]->getType()=="TStream") {
		 delete (TMemoryStream*)(map[i]->getObject());
	   }
	   else
	   if (map[i]->getType()=="AnsiString") {
		 delete (AnsiString*)(map[i]->getObject());
	   }
	   else
	   if (map[i]->getType()=="Boolean") {
		 delete (bool*)(map[i]->getObject());
	   }
	   else
	   if (map[i]->getType()=="Integer") {
		 delete (int*)(map[i]->getObject());
	   }
	   else
	   if (map[i]->getType()=="Double") {
		 delete (double*)(map[i]->getObject());
	   }
	   delete (Item*)map[i];
	}
	map.clear();
}

bool BlockConfig::addString(const AnsiString aName, const AnsiString aValue)
{
  if (isExist(aName)) return false;
  AnsiString *d=new AnsiString(aValue);
  Item *it=new Item(aName, (void*)d, "AnsiString");
  map.push_back(it);
  changed=true;
  return true;
}

bool BlockConfig::addBoolean(const AnsiString aName, bool aValue)
{
  if (isExist(aName)) return false;
  bool *d=new bool;
  *d=aValue;
  Item *it=new Item(aName, (void*)d, "Boolean");
  map.push_back(it);
  changed=true;
  return true;
}

bool BlockConfig::addInt(const AnsiString aName, int aValue)
{
  if (isExist(aName)) return false;
  int *d=new int;
  *d=aValue;
  Item *it=new Item(aName, (void*)d, "Integer");
  map.push_back(it);
  changed=true;
  return true;
}

bool BlockConfig::addDouble(const AnsiString aName, double aValue)
{
  if (isExist(aName)) return false;
  double *d=new double;
  *d=aValue;
  Item *it=new Item(aName, (void*)d, "Double");
  map.push_back(it);
  changed=true;
  return true;
}

bool BlockConfig::addBitmap(const AnsiString aName, Graphics::TBitmap &aValue)
{
  if (isExist(aName)) return false;
  Graphics::TBitmap *d=new Graphics::TBitmap(aValue);
  Item *it=new Item(aName, (void*)d, "TBitmap");
  map.push_back(it);
  changed=true;
  return true;
}

bool BlockConfig::addStream(const AnsiString aName, TStream &aValue)
{
  if (isExist(aName)) return false;
  TStream *d=new TMemoryStream();
  d->CopyFrom(&aValue,0);
  Item *it=new Item(aName, (void*)d, "TStream");
  map.push_back(it);
  changed=true;
  return true;
}

bool BlockConfig::setString(const AnsiString aName, const AnsiString aValue)
{
  Item *it=getItem(aName);
  if (it->getType()!="AnsiString") return false;
  AnsiString *d=new AnsiString(aValue);
  delete (AnsiString*)(it->getObject());
  it->setObject((void*)d);
  changed=true;
  return true;
}

bool BlockConfig::setBoolean(const AnsiString aName, bool aValue)
{
  Item *it=getItem(aName);
  if (it->getType()!="Boolean") return false;
  bool *d=new bool;
  *d=aValue;
  delete (bool*)(it->getObject());
  it->setObject((void*)d);
  changed=true;
  return true;
}

bool BlockConfig::setInt(const AnsiString aName, int aValue)
{
  Item *it=getItem(aName);
  if (it->getType()!="Integer") return false;
  int *d=new int;
  *d=aValue;
  delete (int*)(it->getObject());
  it->setObject((void*)d);
  changed=true;
  return true;
}

bool BlockConfig::setDouble(const AnsiString aName, double aValue)
{
  Item *it=getItem(aName);
  if (it->getType()!="Double") return false;
  double *d=new double;
  *d=aValue;
  delete (double*)(it->getObject());
  it->setObject((void*)d);
  changed=true;
  return true;
}

bool BlockConfig::setBitmap(const AnsiString aName, Graphics::TBitmap &aValue)
{
  Item *it=getItem(aName);
  if (it->getType()!="TBitmap") return false;
  Graphics::TBitmap *d=new Graphics::TBitmap(aValue);
  delete (Graphics::TBitmap*)(it->getObject());
  it->setObject((void*)d);
  changed=true;
  return true;
}

bool BlockConfig::setStream(const AnsiString aName, TStream &aValue)
{
  Item *it=getItem(aName);
  if (it->getType()!="TStream") return false;
  TStream *d=new TMemoryStream();
  d->CopyFrom(&aValue,0);
  delete (TMemoryStream*)(it->getObject());
  it->setObject((void*)d);
  changed=true;
  return true;
}

AnsiString& BlockConfig::getString(const AnsiString aName)
{
  Item *it=getItem(aName);
  if (it->getType()!="AnsiString") throw "Otrzymano b³êdny typ danych";
  return *((AnsiString*)(it->getObject()));
}

bool BlockConfig::getBoolean(const AnsiString aName)
{
  Item *it=getItem(aName);
  if (it->getType()!="Boolean") throw "Otrzymano b³êdny typ danych";
  return *((bool*)(it->getObject()));
}

int BlockConfig::getInt(const AnsiString aName)
{
  Item *it=getItem(aName);
  if (it->getType()!="Integer") throw "Otrzymano b³êdny typ danych";
  return *((int*)(it->getObject()));
}

double BlockConfig::getDouble(const AnsiString aName)
{
  Item *it=getItem(aName);
  if (it->getType()!="Double") throw "Otrzymano b³êdny typ danych";
  return *((double*)(it->getObject()));
}

Graphics::TBitmap& BlockConfig::getBitmap(const AnsiString aName)
{
  Item *it=getItem(aName);
  if (it->getType()!="TBitmap") throw "Otrzymano b³êdny typ danych";
  return *((Graphics::TBitmap*)(it->getObject()));
}

TStream& BlockConfig::getStream(const AnsiString aName)
{
  Item *it=getItem(aName);
  if (it->getType()!="TStream") throw "Otrzymano b³êdny typ danych";
  return *((TStream*)(it->getObject()));
}

bool BlockConfig::isString(const AnsiString aName)
{
  return getItem(aName)->getType()=="AnsiString";
}

bool BlockConfig::isBoolean(const AnsiString aName)
{
  return getItem(aName)->getType()=="Boolean";
}

bool BlockConfig::isInt(const AnsiString aName)
{
  return getItem(aName)->getType()=="Integer";
}

bool BlockConfig::isDouble(const AnsiString aName)
{
  return getItem(aName)->getType()=="Double";
}

bool BlockConfig::isBitmap(const AnsiString aName)
{
  return getItem(aName)->getType()=="TBitmap";
}

bool BlockConfig::isStream(const AnsiString aName)
{
  return getItem(aName)->getType()=="TStream";
}

AnsiString& BlockConfig::getType(const AnsiString aName)
{
  return getItem(aName)->getType();
}

bool BlockConfig::isExist(const AnsiString aName)
{
  try
  {
	 getItem(aName);
	 return true;
  }  catch(char* e)
  {
	 return false;
  }
}

bool BlockConfig::remove(const AnsiString aName)
{
  try
  {
	   Item *it=getItem(aName);

	   if (it->getType()=="TBitmap") {
		 delete (Graphics::TBitmap*)(it->getObject());
	   }
	   else
	   if (it->getType()=="TStream") {
		 delete (TMemoryStream*)(it->getObject());
	   }
	   else
	   if (it->getType()=="AnsiString") {
		 delete (AnsiString*)(it->getObject());
	   }
	   else
	   if (it->getType()=="Boolean") {
		 delete (bool*)(it->getObject());
	   }
	   else
	   if (it->getType()=="Integer") {
		 delete (int*)(it->getObject());
	   }
	   else
	   if (it->getType()=="Double") {
		 delete (double*)(it->getObject());
	   }

	   int i=map.size()-1;
	   for(;i>=0;--i)
	   {
		 if (map[i]==it)
		 {
			 if ((unsigned int)i!=map.size()-1) {
			   map[i]=map[map.size()-1];
			 }
			 map.pop_back();
			 delete it;
			 changed=true;
         }
	   }
	   return true;
  }  catch(Exception &e)
  {
	 return false;
  }
}

bool BlockConfig::saveToStream2(TStream &aWhere)
{
   unsigned long count=map.size();
   aWhere.Write(&count,sizeof(unsigned long));
   for(unsigned int i=0;i<map.size();++i)
   {
		count=map[i]->getType().Length();
		aWhere.Write(&count,sizeof(unsigned long));
		aWhere.Write(map[i]->getType().c_str(),count);

		count=map[i]->getName().Length();
		aWhere.Write(&count,sizeof(unsigned long));
		aWhere.Write(map[i]->getName().c_str(),count);

	   if (map[i]->getType()=="TBitmap") {
		 TMemoryStream *tmp=new TMemoryStream();
		 ((Graphics::TBitmap*)(map[i]->getObject()))->SaveToStream(tmp);
		 count=tmp->Size;
		 aWhere.Write(&count,sizeof(unsigned long));
		 aWhere.CopyFrom(tmp, 0);
		 delete tmp;
	   }
	   else
	   if (map[i]->getType()=="TStream") {
		 TMemoryStream *tmp=((TMemoryStream*)(map[i]->getObject()));
		 count=tmp->Size;
		 aWhere.Write(&count,sizeof(unsigned long));
		 aWhere.CopyFrom(tmp, 0);
	   }
	   else
	   if (map[i]->getType()=="AnsiString") {
		 count=((AnsiString*)map[i]->getObject())->Length();
		 aWhere.Write(&count,sizeof(unsigned long));
		 aWhere.Write(((AnsiString*)map[i]->getObject())->c_str(),count);
	   }
	   else
	   if (map[i]->getType()=="Boolean") {
		 aWhere.Write(((bool*)map[i]->getObject()),sizeof(bool));
	   }
	   else
	   if (map[i]->getType()=="Integer") {
		 aWhere.Write(((int*)map[i]->getObject()),sizeof(int));
	   }
	   else
	   if (map[i]->getType()=="Double") {
		 aWhere.Write(((double*)map[i]->getObject()),sizeof(double));
	   }
   }
   return true;
}

bool BlockConfig::saveToStream(TStream &aWhere)
{
   char id;
   id='B';
   aWhere.Write(&id, 1);
   id='C';
   aWhere.Write(&id, 1);
   return saveToStream2(aWhere);
}

bool BlockConfig::loadFromStream2(TStream &aFrom)
{
   unsigned long count;
   aFrom.Read(&count, sizeof(unsigned long));
   for(unsigned int i=0;i<count;++i)
   {
	  unsigned long itmp;
	  aFrom.Read(&itmp, sizeof(unsigned long));
	  char *typ1=new char[itmp+1];
	  aFrom.Read(typ1, itmp);
	  typ1[itmp]='\0';
	  AnsiString *typ=new AnsiString(typ1);
	  delete typ1;

	  aFrom.Read(&itmp, sizeof(unsigned long));
	  typ1=new char[itmp+1];
	  aFrom.Read(typ1, itmp);
	  typ1[itmp]='\0';
	  AnsiString *name=new AnsiString(typ1);
	  delete typ1;

	   if ((*typ)=="TBitmap") {
		  unsigned long siz;
		  aFrom.Read(&siz, sizeof(unsigned long));
		  TMemoryStream *tmp=new TMemoryStream();
		  if (siz!=0) tmp->CopyFrom(&aFrom, siz);
		  Graphics::TBitmap *d=new Graphics::TBitmap();
		  d->LoadFromStream(tmp);
		  Item *it=new Item(*name, (void*)d, *typ);
		  map.push_back(it);
		  delete tmp;
		  delete it;//bug
	   }
	   else
	   if ((*typ)=="TStream") {
		  unsigned long siz;
		  aFrom.Read(&siz, sizeof(unsigned long));
		  TMemoryStream *tmp=new TMemoryStream();
		  if (siz!=0) tmp->CopyFrom(&aFrom, siz);
		  Item *it=new Item(*name, (void*)tmp, *typ);
		  map.push_back(it);
		  delete tmp;//bug
		  delete it;//bug
	   }
	   else
	   if ((*typ)=="AnsiString") {
		  unsigned long siz;
		  aFrom.Read(&siz, sizeof(unsigned long));
		  char *yp1=new char[siz+1];
		  aFrom.Read(yp1, siz);
		  yp1[siz]='\0';
		  AnsiString *na=new AnsiString(yp1);
		  Item *it=new Item(*name, (void*)na, *typ);
		  map.push_back(it);
		  delete yp1;
		  delete na;//bug
		  delete it;//bug
	   }
	   else
	   if ((*typ)=="Boolean") {
		 bool *tmp=new bool;
		 aFrom.Read(tmp, sizeof(bool));
		 Item *it=new Item(*name, (void*)tmp, *typ);
		 map.push_back(it);
		 delete tmp;
		 delete it;//bug
	   }
	   else
	   if ((*typ)=="Integer") {
		 int *tmp=new int;
		 aFrom.Read(tmp, sizeof(int));
		 Item *it=new Item(*name, (void*)tmp, *typ);
		 map.push_back(it);
		 delete it;//bug
	   }
	   else
	   if ((*typ)=="Double") {
		 double *tmp=new double;
		 aFrom.Read(tmp, sizeof(double));
		 Item *it=new Item(*name, (void*)tmp, *typ);
		 map.push_back(it);
		 delete it;//bug
	   }
	   delete name;
	   delete typ;
   }
   return true;
}

bool BlockConfig::loadFromStream(TStream &aFrom)
{
   clear();
   char id1,id2;
   aFrom.Read(&id1, 1);
   aFrom.Read(&id2, 1);
   if ((id1!='B')||(id2!='C')) return false;
   return loadFromStream2(aFrom);
}

bool BlockConfig::isChanged()
{
	return changed;
}
