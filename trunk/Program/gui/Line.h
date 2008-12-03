#ifndef LineH
#define LineH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>

class TLine : protected TWinControl
{
	friend class Connection;
	
	protected:
		bool fresize;
		bool fresized;
		bool fvertical;
		TPoint oldPos;
	public:
		__fastcall TLine(TWinControl* Owner, bool vertical);
	__published:
		__property Width;
		__property Height;
		__property Top;
		__property Left;
		__property Visible;
		__property Color  = {default=0x00000000};
		__property Hint;
		__property bool Resized = {read=fresized, default=false};
		__property bool Vertical = {read=fvertical, write=fvertical, default=false};

		__property OnMouseMove;
		__property OnMouseUp;
		__property OnMouseDown;
		__property OnMouseEnter;
		__property OnMouseLeave;
		__property OnClick;
		__property OnKeyPress;
		__property OnKeyDown;
		__property OnKeyUp;


};
//---------------------------------------------------------------------------
#endif
