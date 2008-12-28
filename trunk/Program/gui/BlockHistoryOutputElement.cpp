#include <vcl.h>
#pragma hdrstop
#include "BlockHistoryOutputElement.h"
#pragma package(smart_init)

BlockHistoryOutputElement::BlockHistoryOutputElement()
{ 
	output=NULL;
	data=NULL;
}

BlockHistoryOutputElement::~BlockHistoryOutputElement()
{ 
	if (data!=NULL) delete data;
}

void BlockHistoryOutputElement::setData(TypeConfig &d)
{
	if (data!=NULL) delete data;
	data=new TypeConfig(d);
}

TypeConfig* BlockHistoryOutputElement::getData()
{
	return data;
}

void BlockHistoryOutputElement::setNULL()
{
  if (data!=NULL) delete data;
  data=NULL;
}
