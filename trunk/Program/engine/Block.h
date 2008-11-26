#include <System.hpp>
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
				BlockConfig *config;
		public:
				//zastanawiams ie czy tu dac wskaznik do tych obiektow czy moze tak jak ejst teraz
				//bo i tak user to bedzie modyfikowal z poziomu dll'ki, imo wskaznik moze zaoszczedzic kopiowania
				//pomysl i zmien tak jak ci sie bedzie podobac
				vector<BlockInput> input;
				vector<BlockOutput> output;

				Block();
				Block(Block &copy);
				~Block();

				BlockConfig* getConfig();
				void setConfig(BlockConfig &ob);
};

#endif
