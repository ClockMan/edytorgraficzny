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
		 * @param Owner kontrolka na kt�rej b�dzie rysowana linia
		 * @param vertical true - linia pionowa, false - linia pozioma
		 */
		__fastcall Line(TWinControl* Owner, bool vertical);
	__published:
		/**
		 *  W�a�ciwo�� - szeroko��/wysoko�� lini
		 */
		__property Width;

		/**
		 *  W�a�ciwo�� - szeroko��/wysoko�� lini
		 */
		__property Height;

		/**
		 *  W�a�ciwo�� - odleg�o�� od g�rnej cze�ci "p�aszczyzny"
		 */
		__property Top;

		/**
		 *  W�a�ciwo�� - odleg�o�� od lewej cze�ci "p�aszczyzny"
		 */
		__property Left;

		/**
		 *  W�a�ciwo�� - czy linia b�dzie widoczna true/false
		 */
		__property Visible;

		/**
		 *  W�a�ciwo�� - kolor linii
		 */
		__property Color  = {default=0x00000000};

		/**
		 *  W�a�ciwo�� - podpowied� wy�wietlana po najechnaiu kursorem na linie
		 */
		__property Hint;

		/**
		 *  W�a�ciwo�� - czy linia by�a przes�wana przez u�ytkownika
		 */
		__property bool Resized = {read=fresized, default=false};

		/**
		 *  W�a�ciwo�� - orientacja - true : pionowa, false : pozioma
		 */
		__property bool Vertical = {read=fvertical, write=fvertical, default=false};

		/**
		 *  W�a�ciwo�� - funkcja wywo�ywana przy przesuwaniu kursora myszy nad lini�
		 */
		__property OnMouseMove;

		/**
		 *  W�a�ciwo�� - funkcja wywo�ywana po puszczeniu klawisza myszy
		 */
		__property OnMouseUp;

		/**
		 *  W�a�ciwo�� - funkcja wywo�ywana po wci�ni�ciu klawisza myszy
		 */
		__property OnMouseDown;

		/**
		 *  W�a�ciwo�� - funkcja wywo�yana gdy kursor myszy wejdzie w przeste� nad lini�
		 */
		__property OnMouseEnter;

		/**
		 *  W�a�ciwo�� - funkcja wywo�ywana gdy kursor myszy opu�ci przestrze� nad lini�
		 */
		__property OnMouseLeave;

		/**
		 *  W�a�ciwo�� - funkcja wywo�ywana po klikni�ciu myszy w lini�
		 */
		__property OnClick;

		/**
		 *  W�a�ciwo�� - funkcja wywo�ywana gdy klawisz zostanie naci�niety
		 */
		__property OnKeyPress;

		/**
		 *  W�a�ciwo�� - funkcja wywo�ywana gdy klawisz zostanie wci�ni�ty
		 */
		__property OnKeyDown;

		/**
		 *  W�a�ciwo�� - funkcja wywo�ywana gdy klawisz zostanie puszcony
		 */
		__property OnKeyUp;


};
//---------------------------------------------------------------------------
#endif
