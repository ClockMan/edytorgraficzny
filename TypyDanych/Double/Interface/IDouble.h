#include <vector>
#include <System.hpp>
#include <exception>
using namespace std;

#ifndef __IDouble_h__
#define __IDouble_h__

#include "../../../Program/engine/TypeConfig.h"

class IDouble
{
	public:
			static bool setValue(TypeConfig *type, double value);
			static double getValue(TypeConfig *type);
			static TypeConfig* getNew();
};


#endif
