#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockOutput_h__
#define __BlockOutput_h__

#include "Block.h"
// #include "BlockElement.h"

namespace PIWO
{
	class Block;
	class BlockElement;
	class BlockOutput;
}

namespace PIWO
{
	class BlockOutput: public PIWO::BlockElement
	{
		private: string outputType;
		std::vector<PIWO::Block*> output;

		public: string getOutputType();

		public: bool setOutputType(string aName);
	};
}

#endif
