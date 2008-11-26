#include "IMask3x3.h"

double IMask3x3::getValue(TypeConfig *type, int x, int y)
{
   if (type->getName()!="Mask3x3") return 0;
   return type->getDouble("d"+y+"_"+x);
}

bool IMask3x3::setValue(TypeConfig *type, int x, int y, double value)
{
   if (type->getName()!="Mask3x3") return false;
   type->setDouble("d"+y+"_"+x, value);
   return true;
}

TypeConfig* IMask3x3::getNew()
{
   TypeConfig *z=new TypeConfig("Mask3x3");
   z->addDouble("d1_1",0);
   z->addDouble("d1_2",0);
   z->addDouble("d1_3",0);
   z->addDouble("d2_1",0);
   z->addDouble("d2_2",0);
   z->addDouble("d2_3",0);
   z->addDouble("d3_1",0);
   z->addDouble("d3_2",0);
   z->addDouble("d3_3",0);
   return z;
}
