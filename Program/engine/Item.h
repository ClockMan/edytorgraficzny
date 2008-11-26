#include <vector>
#include <System.hpp>
#include <exception>
using namespace std;

#ifndef __Item_h__
#define __Item_h__

/**
* Item - Klasa pojemnik przechowuj¹ca elementy dla listy BlockConfig/TypeConfig
* UWAGA: Klasa nie zwalnia danych przesy³anych jako wskaŸnik do konstruktora (aObiekt), osoba u¿ywaj¹ca klasy sama musi to oprogramowaæ.
* @author Piotr Zegar
* @date 2008.11.25
* @version 1.1
*/

class Item
{
	private:
		AnsiString name;
		void* pointer;
		AnsiString type;
	public:
		/**
		 * Konstruktor.
		 * Inicjuje pola prywatne nie pozwalaj¹c na ich zmiannê, konstruktor wywala wyj¹tek gdy parametry s¹ b³êdne
		 * @param aName Nazwa pod jak¹ bêd¹ przechowywane te dane, niemo¿e byæ pusta
		 * @param aObiekt Obiekt który ma zostaæ powi¹zany z nazw¹, niemo¿e byæ NULL
		 * @param aType informacja o typie obiektu, nie u¿ywana wewn¹trz klasy, nie mo¿e byæ puste
		 * @see Item(Item &kopia)
		 */
		Item(const AnsiString aName, void* aObject, const AnsiString aType);

		/**
		 * Konstruktor kopiuj¹cy
		 * Kopiuje obiekt, wymagany dla vector
		 * @param kopia obiekt kopiowany
		 * @see Item(string aName, void* aObject, string aType)
		 */
		Item(Item &copy);

		/**
		 * Pobiera i zwraca nazwê podawan¹ w konstruktorze, zwracana wartoœc nie jest pustym stringiem
		 * @return name
		 */
		AnsiString& getName();

		/**
		 * Pobiera i zwraca wskaŸnik do danych jakie przechowuje obiekt, zwracana wartoœc nie ejst nullem
		 * @return wsk
		 */
		void* getObject();
		/**
		 * Ustawia nowy obiekt 
		 * @param aObiekt obiekt który zostanie dodany do listy.
		 * @return true/false w zaleznosci czy obiekt zosta³ pomyœlnei zainicjalizowany
		 */

		bool setObject(void* aObiekt);

		/**
		 * Pobiera i zwraca nazwê typu danych jak¹ user powi¹za³ z danymi i t¹ nazw¹, nigdy nie zwraca pustego stringu
		 * @return type
		 */
		AnsiString& getType();

};


#endif
