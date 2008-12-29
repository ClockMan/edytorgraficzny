#include "BlockElement.h"

BlockElement::BlockElement(const AnsiString aName)
{
   object=NULL;
   name=aName;
}

BlockElement::BlockElement(const BlockElement &block)
{
   if (block.object!=NULL)
   object=new TypeConfig(*(block.object));
   else
   object=block.object;
   name=block.name;
   errorDescription=block.errorDescription;
   description=block.description;
   errorCode=block.errorCode;
}

BlockElement::~BlockElement()
{
	if (object) delete object;
}

AnsiString& BlockElement::getDescription()
{
   return description;
}

int BlockElement::getErrorCode()
{
	return errorCode;
}

AnsiString& BlockElement::getErrorDescription()
{
	return errorDescription;
}

AnsiString& BlockElement::getName()
{           
	return name;
}

TypeConfig* BlockElement::getObject()
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

void BlockElement::setObject(const TypeConfig &aData)
{
   if (object) delete object;
   object=new TypeConfig(aData);
}

void BlockElement::clearObject()
{
   if (object) delete object;
   object=NULL;
}
