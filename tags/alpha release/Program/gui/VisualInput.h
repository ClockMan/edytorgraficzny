#ifndef VisualInputH
#define VisualInputH

#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include "VisualInputOutput.h"
#include "../engine/BlockInput.h"
/**
 * Klasa symbolizuje wizualne wejscie bloku
 */
class PACKAGE VisualInput : public VisualInputOutput
{
     public:
    /**
     * Wskaznik do wejscia bloku
     */ 
	BlockInput* input;
	/**
	 * Konstruktor
	 * @param AOwner wskaznik do klasy bedacej wlascicielem dla tej
	 */
	__fastcall VisualInput(Classes::TComponent* AOwner);
};

#endif
