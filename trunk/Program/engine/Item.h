#include <vector>
#include <System.hpp>
#include <exception>
using namespace std;

#ifndef __Item_h__
#define __Item_h__
/**
 * Item - Klasa pojemnik przechowujaca elementy dla listy BlockConfig/TypeConfig
 * UWAGA: Klasa nie zwalnia danych przesylanych jako wskaznik do konstruktora (aObiekt), osoba uzywajaca klasy sama musi to oprogramowac.
 * @author Piotr Zegar
 * @date 2008.11.25
 * @version 0.1
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
		 * Inicjuje pola prywatne nie pozwalajac na ich zmianne, konstruktor wywala wyjatek gdy parametry sa bledne
		 * @param aName Nazwa pod jaka beda przechowywane te dane, niemoze byc pusta
		 * @param aObiekt Obiekt ktory ma zostac powiazany z nazwa, niemoze byc NULL
		 * @param aType informacja o typie obiektu, nie uzywana wewnatrz klasy, nie moze byc puste
		 * @see Item(Item &kopia)
		 */
		Item(const AnsiString aName, void* aObject, const AnsiString aType);

		/**
		 * Konstruktor kopiujacy
		 * Kopiuje obiekt, wymagany dla vector
		 * @param kopia obiekt kopiowany
		 * @see Item(string aName, void* aObject, string aType)
		 */
		Item(Item &copy);

		/**
		 * Pobiera i zwraca nazwe podawana w konstruktorze, zwracana wartosc nie jest pustym stringiem
		 * @return nazwa
		 */
		AnsiString& getName();

		/**
		 * Pobiera i zwraca wskaznik do danych jakie przechowuje obiekt, zwracana wartosc nie ejst nullem
		 * @return wskaznik
		 */
		void* getObject();
		/**
		 * Ustawia nowy obiekt 
		 * @param aObiekt obiekt ktory zostanie dodany do listy.
		 * @return true/false w zaleznosci czy obiekt zostal pomyslnei zainicjalizowany
		 */

		bool setObject(void* aObject);

		/**
		 * Pobiera i zwraca nazwe typu danych jaka user powiazal z danymi i ta nazw¹, nigdy nie zwraca pustego stringu
		 * @return typ
		 */
		AnsiString& getType();

};


#endif
