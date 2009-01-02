#include "IBoolean.h"

bool IBoolean::getValue(TypeConfig *type)
{
   if (type->getName()!="Boolean") return false;
   return type->getBoolean("bool");
}

bool IBoolean::setValue(TypeConfig *type, bool value)
{
   if (type->getName()!="Boolean") return false;
   type->setBoolean("bool", value);
   return true;
}

TypeConfig* IBoolean::getNew()
{
   TypeConfig *z=new TypeConfig("Boolean");
   z->addBoolean("bool",false);
   return z;
}
