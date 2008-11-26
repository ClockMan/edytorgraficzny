#include "IMask5x5.h"

double IMask5x5::getValue(TypeConfig *type, int x, int y)
{
   if (type->getName()!="Mask5x5") return 0;
   return type->getDouble("d"+y+"_"+x);
}

bool IMask5x5::setValue(TypeConfig *type, int x, int y, double value)
{
   if (type->getName()!="Mask5x5") return false;
   type->setDouble("d"+y+"_"+x, value);
   return true;
}

TypeConfig* IMask5x5::getNew()
{
   TypeConfig *z=new TypeConfig("Mask5x5");
   for(int x=1;x<6;x++)
   {
	   for(int y=1;y<6;y++)
		z->addDouble("d"+y+"_"+x,0);
   }
   return z;
}
