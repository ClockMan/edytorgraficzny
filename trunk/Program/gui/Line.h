#ifndef LineH
#define LineH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>

typedef void (__closure *Line_Function)(TObject*);

/**
 * @author Piotr Zegar
 * @date 2008.12.03
 * @version 0.1
 *
 * Klasa symbolizuje poszczeg�ln� lini� u�ywan� do tworzenia po��cze� miedzy bloczkami.
 */
class Line : public TWinControl
{
	private:
		bool moving;
		TPoint oldPos;

		__property OnMouseMove;
		__property OnMouseDown;
		__property OnMouseUp;
		__property Left;
		__property Top;
		__property Width;
		__property Height;

		void __fastcall LineMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall LineMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall LineMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	public:
		 Line_Function OnLineMove;
		 Line_Function OnConnectionSelectRequest;
		 Line_Function OnConnectionResetRequest;

		 __property Color;
		 
		/**
		 *  W�a�ciwo�� - czy linia by�a przes�wana przez u�ytkownika
		 */
		 int Resize;

		 /**
		 *  W�a�ciwo�� - orientacja - true : pionowa, false : pozioma
		 */
		 bool Vertical;

		 /**
		 *  W�a�ciwo�� - czy linia mo�e by� przenoszona
		 */
		 bool CanBeMoved;

		 bool setXY(int x1, int y1, int x2, int y2);
		 TPoint getPoint1();
		 TPoint getPoint2();
		/**
		 * Konstruktor
		 * @param Owner kontrolka na kt�rej b�dzie rysowana linia
		 * @param vertical true - linia pionowa, false - linia pozioma
		 */
		__fastcall Line(TWinControl* Owner, bool vertical);
};
//---------------------------------------------------------------------------
#endif
