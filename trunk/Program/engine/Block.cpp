#include "Block.h"

Block::Block()
{
	config=new BlockConfig();
}

Block::Block(Block &copy)
{
	config=new BlockConfig(*copy.config);
	//@TODO do napisania kopiowanie listy wejsc i wyjsc
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
