#ifndef VisualInputOutputH
#define VisualInputOutputH

#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>

typedef void ( __closure *VisualFunction )(TObject*);

class PACKAGE VisualInputOutput : public TPanel
{
private:
	void __fastcall MouseEnterF(TObject *Sender);
	void __fastcall MouseLeaveF(TObject *Sender);
	void __fastcall MouseDownF(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	protected:
public:
	VisualFunction OnShowHistory;
	__fastcall VisualInputOutput(Classes::TComponent* AOwner);
};

#endif
