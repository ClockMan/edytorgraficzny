#ifndef VisualOutputH
#define VisualOutputH

#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include "VisualInputOutput.h"
#include "../engine/BlockOutput.h"

/**
 * Klasa symbolizujaca wizualne wyjscia z bloku
 */
class PACKAGE VisualOutput : public VisualInputOutput
{
     public:
    /**
     * Wskaznik do wyjscia
     */ 
	BlockOutput* output;
	/**
	 * Konstruktor
	 * @param AOwner wskaznik do klasy bedacej wlascicielem dla tej
	 */
	__fastcall VisualOutput(Classes::TComponent* AOwner);
};

#endif
