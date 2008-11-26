#include "IDouble.h"

double IDouble::getValue(TypeConfig *type)
{
   if (type->getName()!="Double") return 0;
   return type->getDouble("float");
}

bool IDouble::setValue(TypeConfig *type, double value);
{
   if (type->getName()!="Double") return false;
   type->setDouble("float", value);
   return true;
}

TypeConfig* IDouble::getNew()
{
   TypeConfig *z=new TypeConfig("Double");
   z->addDouble("float",0);
   return z;
}
