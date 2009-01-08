#include <vcl.h>
#pragma hdrstop
#include "VisualOutput.h"
#pragma package(smart_init)

__fastcall VisualOutput::VisualOutput(Classes::TComponent* AOwner)
	: VisualInputOutput(Owner)
{
	output=NULL;	
}
