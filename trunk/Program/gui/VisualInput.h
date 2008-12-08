#ifndef VisualInputH
#define VisualInputH

#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include "VisualInputOutput.h"
#include "../engine/BlockInput.h"

class PACKAGE VisualInput : public VisualInputOutput
{
     public:
	BlockInput* input;
	__fastcall VisualInput(Classes::TComponent* AOwner);
};

#endif
