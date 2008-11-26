#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockOutput_h__
#define __BlockOutput_h__

#include "BlockElement.h"

class BlockOutput: public BlockElement
{
		private:
				AnsiString outputType;
		public:
				BlockOutput(const AnsiString aName);
				BlockOutput(BlockOutput &kopia);
				~BlockOutput();

				AnsiString& getOutputType();
				bool setOutputType(AnsiString aName);
};

#endif
