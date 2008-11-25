#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __FunctionDLL_h__
#define __FunctionDLL_h__

#include "PluginContener.h"
#include "Block.h"

namespace PIWO
{
	class PluginContener;
	class Block;
	class FunctionDLL;
}

namespace PIWO
{
	class FunctionDLL
	{
		std::vector<PIWO::PluginContener*> listOfFunction;

		public: bool run(PIWO::Block aBlock);

		public: bool showConfig(PIWO::Block aBlock);

		public: int validate(PIWO::Block aBlock);
	};
}

#endif
