#ifndef VisualInputOutputH
#define VisualInputOutputH

#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>

typedef void ( __closure *VisualFunction )(TObject*);

/**
 * Klasa symbolizujaca wizualnie wejscia i wyjscia do bloku
 */
class PACKAGE VisualInputOutput : public TPanel
{
private:
	void __fastcall MouseEnterF(TObject *Sender);
	void __fastcall MouseLeaveF(TObject *Sender);
	void __fastcall MouseDownF(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	protected:
public:
	/**
	 * Event
	 */
	VisualFunction OnShowHistory;
	/**
	 * Konstruktor
	 * @param AOwner wskaznik do klasy bedacej wlascicielem dla tej
	 */
	__fastcall VisualInputOutput(Classes::TComponent* AOwner);
};

#endif
