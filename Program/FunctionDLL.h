#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __FunctionDLL_h__
#define __FunctionDLL_h__

#include "PluginContener.h"
#include "Block.h"

class FunctionDLL
{
		private:
				std::vector<PIWO::PluginContener*> listOfFunction;

		public:
				bool run(PIWO::Block aBlock);
				bool showConfig(PIWO::Block aBlock);
				int validate(PIWO::Block aBlock);
};

#endif
