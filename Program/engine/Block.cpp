#include "Block.h"

Block::Block()
{
	config=new BlockConfig();
}

Block::Block(const Block &copy)
{
	config=new BlockConfig(*copy.config);
	input=copy.input;
	output=copy.output;
}

Block::~Block()
{
    delete config;
}

BlockConfig* Block::getConfig()
{
	return config;
}

void Block::setConfig(BlockConfig &ob)
{
	delete config;
	config=new BlockConfig(ob);
}
