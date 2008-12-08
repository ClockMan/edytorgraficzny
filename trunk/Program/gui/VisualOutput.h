#ifndef VisualOutputH
#define VisualOutputH

#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include "VisualInputOutput.h"
#include "../engine/BlockOutput.h"

class PACKAGE VisualOutput : public VisualInputOutput
{
     public:
	BlockOutput* output;
	__fastcall VisualOutput(Classes::TComponent* AOwner);
};

#endif
