#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __FunctionDLL_h__
#define __FunctionDLL_h__

#include "Block.h"

class FunctionDLL
{
		public:
				int run(Block &aBlock);
				bool showConfig(Block &aBlock);
				int validate(Block &aBlock);
};

#endif
