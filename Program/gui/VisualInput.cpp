#include <vcl.h>
#pragma hdrstop
#include "VisualInput.h"
#pragma package(smart_init)

__fastcall VisualInput::VisualInput(Classes::TComponent* AOwner)
	: VisualInputOutput(Owner)
{
	input=NULL;	
}
