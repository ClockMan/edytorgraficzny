#include "BlockOutput.h"

BlockOutput::BlockOutput(const AnsiString aName):BlockElement(aName)
{
}

BlockOutput::BlockOutput(const BlockOutput &kopia):BlockElement(kopia)
{
   outputType=kopia.outputType;
}

BlockOutput::~BlockOutput()
{
}

AnsiString& BlockOutput::getOutputType()
{
   return outputType;
}

bool BlockOutput::setOutputType(AnsiString aName)
{
   if (aName.IsEmpty()) return false;
   outputType=aName;
   return true;
}
