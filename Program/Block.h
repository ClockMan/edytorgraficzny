#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __Block_h__
#define __Block_h__

#include "BlockConfig.h"
#include "BlockInput.h"
#include "BlockOutput.h"

namespace PIWO
{
	class BlockConfig;
	class BlockInput;
	class BlockOutput;
	class Block;
}

namespace PIWO
{
	class Block
	{
		private: PIWO::BlockConfig config;
		public: vector<PIWO::BlockInput> input;
		public: vector<PIWO::BlockOutput> output;

		public: PIWO::BlockConfig getConfig();
	};
}

#endif
