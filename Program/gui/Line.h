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
class Line : protected TWinControl
{
	friend class Connection;
	
	protected:
		bool fresize;
		bool fresized;
		bool fvertical;
		TPoint oldPos;
	public:
		/**
		 * Konstruktor
		 * @param Owner kontrolka na której bêdzie rysowana linia
		 * @param vertical true - linia pionowa, false - linia pozioma
		 */
		__fastcall Line(TWinControl* Owner, bool vertical);
	__published:
		/**
		 *  W³aœciwoœæ - szerokoœæ/wysokoœæ lini
		 */
		__property Width;

		/**
		 *  W³aœciwoœæ - szerokoœæ/wysokoœæ lini
		 */
		__property Height;

		/**
		 *  W³aœciwoœæ - odleg³oœæ od górnej czeœci "p³aszczyzny"
		 */
		__property Top;

		/**
		 *  W³aœciwoœæ - odleg³oœæ od lewej czeœci "p³aszczyzny"
		 */
		__property Left;

		/**
		 *  W³aœciwoœæ - czy linia bêdzie widoczna true/false
		 */
		__property Visible;

		/**
		 *  W³aœciwoœæ - kolor linii
		 */
		__property Color  = {default=0x00000000};

		/**
		 *  W³aœciwoœæ - podpowiedŸ wyœwietlana po najechnaiu kursorem na linie
		 */
		__property Hint;

		/**
		 *  W³aœciwoœæ - czy linia by³a przesówana przez u¿ytkownika
		 */
		__property bool Resized = {read=fresized, default=false};

		/**
		 *  W³aœciwoœæ - orientacja - true : pionowa, false : pozioma
		 */
		__property bool Vertical = {read=fvertical, write=fvertical, default=false};

		/**
		 *  W³aœciwoœæ - funkcja wywo³ywana przy przesuwaniu kursora myszy nad lini¹
		 */
		__property OnMouseMove;

		/**
		 *  W³aœciwoœæ - funkcja wywo³ywana po puszczeniu klawisza myszy
		 */
		__property OnMouseUp;

		/**
		 *  W³aœciwoœæ - funkcja wywo³ywana po wciœniêciu klawisza myszy
		 */
		__property OnMouseDown;

		/**
		 *  W³aœciwoœæ - funkcja wywo³yana gdy kursor myszy wejdzie w przesteñ nad lini¹
		 */
		__property OnMouseEnter;

		/**
		 *  W³aœciwoœæ - funkcja wywo³ywana gdy kursor myszy opuœci przestrzeñ nad lini¹
		 */
		__property OnMouseLeave;

		/**
		 *  W³aœciwoœæ - funkcja wywo³ywana po klikniêciu myszy w liniê
		 */
		__property OnClick;

		/**
		 *  W³aœciwoœæ - funkcja wywo³ywana gdy klawisz zostanie naciœniety
		 */
		__property OnKeyPress;

		/**
		 *  W³aœciwoœæ - funkcja wywo³ywana gdy klawisz zostanie wciœniêty
		 */
		__property OnKeyDown;

		/**
		 *  W³aœciwoœæ - funkcja wywo³ywana gdy klawisz zostanie puszcony
		 */
		__property OnKeyUp;


};
//---------------------------------------------------------------------------
#endif
