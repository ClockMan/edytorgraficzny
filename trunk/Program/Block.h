#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __Block_h__
#define __Block_h__

#include "BlockConfig.h"
#include "BlockInput.h"
#include "BlockOutput.h"

class Block
{
		private:
				PIWO::BlockConfig config;
		public:
				vector<PIWO::BlockInput*> input;
				vector<PIWO::BlockOutput*> output;
				PIWO::BlockConfig* getConfig();
};

#endif
