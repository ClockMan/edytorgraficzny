#ifndef LineH
#define LineH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>

typedef bool (__closure *Line_FunctionMove)(TObject*, int);
typedef bool (__closure *Line_FunctionSelected )(TObject*);

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

		void __fastcall LineMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall LineMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall LineMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	public:
		 Line_FunctionMove OnLineMove;
		 Line_FunctionSelected OnConnectionSelectRequest;
		 
		/**
		 *  W�a�ciwo�� - czy linia by�a przes�wana przez u�ytkownika
		 */
		 bool Resized;

		 /**
		 *  W�a�ciwo�� - orientacja - true : pionowa, false : pozioma
		 */
		 bool Vertical;

		 /**
		 *  W�a�ciwo�� - czy linia mo�e by� przenoszona
		 */
		 bool CanBeMoved;

		/**
		 * Konstruktor
		 * @param Owner kontrolka na kt�rej b�dzie rysowana linia
		 * @param vertical true - linia pionowa, false - linia pozioma
		 */
		__fastcall Line(TWinControl* Owner, bool vertical);
};
//---------------------------------------------------------------------------
#endif
