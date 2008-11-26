#include "IInteger.h"

int IInteger::getValue(TypeConfig *type)
{
   if (type->getName()!="Integer") return 0;
   return type->getInteger("int");
}

bool IInteger::setValue(TypeConfig *type, int value);
{
   if (type->getName()!="Integer") return false;
   type->setInteger("int", value);
   return true;
}

TypeConfig* IInteger::getNew()
{
   TypeConfig *z=new TypeConfig("Integer");
   z->addInteger("int",0);
   return z;
}
