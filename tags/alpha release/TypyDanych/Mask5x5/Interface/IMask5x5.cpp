#include "IMask5x5.h"

int IMask5x5::getValue(TypeConfig *type, int x, int y)
{
   if (type->getName()!="Mask5x5") return 0;
   return type->getInt("d"+IntToStr(y)+"_"+IntToStr(x));
}

bool IMask5x5::setValue(TypeConfig *type, int x, int y, int value)
{
   if (type->getName()!="Mask5x5") return false;
   type->setInt("d"+IntToStr(y)+"_"+IntToStr(x), value);
   return true;
}

TypeConfig* IMask5x5::getNew()
{
   TypeConfig *z=new TypeConfig("Mask5x5");
   for(int x=1;x<6;x++)
   {
	   for(int y=1;y<6;y++)
		z->addInt("d"+IntToStr(y)+"_"+IntToStr(x),0);
   }
   return z;
}
