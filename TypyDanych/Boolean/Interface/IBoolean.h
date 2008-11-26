#include <vector>
#include <System.hpp>
#include <exception>
using namespace std;

#ifndef __IBoolean_h__
#define __IBoolean_h__

#include "../../../Program/engine/TypeConfig.h"

class IBoolean
{
	public:
			static bool setValue(TypeConfig *type, bool value);
			static bool getValue(TypeConfig *type);
			static TypeConfig* getNew();
};


#endif
