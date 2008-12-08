#ifndef LineH
#define LineH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>

/**
 * @author Piotr Zegar
 * @date 2008.12.03
 * @version 0.1
 *
 * Klasa symbolizuje poszczeg�ln� lini� u�ywan� do tworzenia po��cze� miedzy bloczkami.
 */
class Line : public TWinControl
{
	public:

		/**
		 *  W�a�ciwo�� - czy linia by�a przes�wana przez u�ytkownika
		 */
		 bool Resized;

		 bool Resize;

		 /**
		 *  W�a�ciwo�� - orientacja - true : pionowa, false : pozioma
		 */
		 bool Vertical;
		 TPoint oldPos;

		/**
		 * Konstruktor
		 * @param Owner kontrolka na kt�rej b�dzie rysowana linia
		 * @param vertical true - linia pionowa, false - linia pozioma
		 */
		__fastcall Line(TWinControl* Owner, bool vertical);
};
//---------------------------------------------------------------------------
#endif
