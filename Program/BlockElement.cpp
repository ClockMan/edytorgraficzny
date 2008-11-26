#include "BlockElement.h"

BlockElement::BlockElement(const AnsiString aName)
{
   object=new BlockConfig();
   name=aName;
}

BlockElement::BlockElement(BlockElement &block)
{
   object=new BlockConfig(*(block.object));
   name=block.name;
   errorDescription=block.errorDescription;
   description=block.description;
   errorCode=block.errorCode;
}

BlockElement::~BlockElement()
{
	delete object;
}

AnsiString& BlockElement::getDescription()
{
   return description;
}

int BlockElement::getErrorCode()
{
	return errorCode;
}

AnsiString& BlockElement::geErrorDescription()
{
	return errorDescription;
}

AnsiString& BlockElement::getName()
{           
	return name;
}

BlockConfig* BlockElement::getObject()
{
	return object;
}

void BlockElement::setDescription(const AnsiString aDescription)
{
   description=aDescription;
}

void BlockElement::setErrorDescription(const AnsiString aErrorDescription)
{
   errorDescription=aErrorDescription;
}

void BlockElement::setErrorCode(int aError)
{
   errorCode=aError;
}

void BlockElement::setObject(BlockConfig &aData)
{
   delete object;
   object=new BlockConfig(aData);
}
