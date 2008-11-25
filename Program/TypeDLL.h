#include <string>
#include <vector>
#include <exception>

using namespace std;

#ifndef __TypeDLL_h__
#define __TypeDLL_h__

#include "PluginContener.h"
#include "TypeConfig.h"
class TypeDLL
{
   private: string type;
			std::vector<PIWO::PluginContener*> listOfType;
   public: bool show(int aHandle, PIWO::TypeConfig aData);
   public: bool isValid(TypeConfig() aData);
};

#endif
