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
 * Klasa symbolizuje poszczególn¹ liniê u¿ywan¹ do tworzenia po³¹czeñ miedzy bloczkami.
 */
class Line : public TWinControl
{
	public:

		/**
		 *  W³aœciwoœæ - czy linia by³a przesówana przez u¿ytkownika
		 */
		 bool Resized;

		 bool Resize;

		 /**
		 *  W³aœciwoœæ - orientacja - true : pionowa, false : pozioma
		 */
		 bool Vertical;
		 TPoint oldPos;

		/**
		 * Konstruktor
		 * @param Owner kontrolka na której bêdzie rysowana linia
		 * @param vertical true - linia pionowa, false - linia pozioma
		 */
		__fastcall Line(TWinControl* Owner, bool vertical);
};
//---------------------------------------------------------------------------
#endif
