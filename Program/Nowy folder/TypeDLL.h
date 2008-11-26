#include <String.hpp>
#include <vector>
#include <exception>

using namespace std;

#ifndef __TypeDLL_h__
#define __TypeDLL_h__

#include "TypeConfig.h"

class TypeDLL
{
   private:
			AnsiString type;
   public:
			bool show(int aHandle, TypeConfig &aData);
			bool isValid(TypeConfig &aData);
};

#endif
