#include <vcl.h>
#pragma hdrstop
#include "BlockHistoryInputElement.h"
#pragma package(smart_init)

BlockHistoryInputElement::BlockHistoryInputElement()
{ 
	input=NULL;
	data=NULL;
}

BlockHistoryInputElement::BlockHistoryInputElement()
{ 
	if (data!=NULL) delete data;
}

void BlockHistoryInputElement::setData(TypeConfig &d)
{
	if (data!=NULL) delete data;
	data=new TypeConfig(d);
}

TypeConfig* BlockHistoryInputElement::getData()
{
	return data;
}
