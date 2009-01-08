#include "IMask3x3.h"

int IMask3x3::getValue(TypeConfig *type, int x, int y)
{
   if (type->getName()!="Mask3x3") return 0;
   return type->getInt("d"+IntToStr(y)+"_"+IntToStr(x));
}

bool IMask3x3::setValue(TypeConfig *type, int x, int y, int value)
{
   if (type->getName()!="Mask3x3") return false;
   type->setInt("d"+IntToStr(y)+"_"+IntToStr(x), value);
   return true;
}

TypeConfig* IMask3x3::getNew()
{
   TypeConfig *z=new TypeConfig("Mask3x3");
   z->addInt("d1_1",0);
   z->addInt("d1_2",0);
   z->addInt("d1_3",0);
   z->addInt("d2_1",0);
   z->addInt("d2_2",0);
   z->addInt("d2_3",0);
   z->addInt("d3_1",0);
   z->addInt("d3_2",0);
   z->addInt("d3_3",0);
   return z;
}
