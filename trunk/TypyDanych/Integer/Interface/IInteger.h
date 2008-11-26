#include <vector>
#include <System.hpp>
#include <exception>
using namespace std;

#ifndef __IInteger_h__
#define __IInteger_h__

#include "../../../Program/engine/TypeConfig.h"

class IInteger
{
	public:
			static bool setValue(TypeConfig *type, int value);
			static int getValue(TypeConfig *type);
			static TypeConfig* getNew();
};


#endif
