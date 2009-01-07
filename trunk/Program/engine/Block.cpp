#include "Block.h"

Block::Block()
{
	config=new BlockConfig();
	blockWindow=NULL;
	title="";
}

Block::Block(const Block &copy)
{
	config=new BlockConfig(*copy.config);
	input=copy.input;
	output=copy.output;
	blockWindow=NULL;
	title=copy.title;
}

Block::~Block()
{
    try{
    if (blockWindow!=NULL) delete blockWindow;
    } catch(...)
    {
      //nic tu :d
    }
    delete config;
}

BlockConfig* Block::getConfig()
{
	return config;
}

void Block::setConfig(const BlockConfig &ob)
{
	delete config;
	config=new BlockConfig(ob);
}
