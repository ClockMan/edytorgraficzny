#include <vector>
#include <System.hpp>
#include <exception>
using namespace std;

#ifndef __IMask3x3_h__
#define __IMask3x3_h__

#include "../../../Program/engine/TypeConfig.h"

class IMask3x3
{
	public:
			static bool setValue(TypeConfig *type, int x, int y, int value);
			static int getValue(TypeConfig *type, int x, int y);
			static TypeConfig* getNew();
};


#endif
