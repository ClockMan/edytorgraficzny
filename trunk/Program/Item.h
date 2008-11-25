#include <vector>
#include <System.hpp>
#include <exception>
using namespace std;

#ifndef __Item_h__
#define __Item_h__

/**
* Item - Klasa pojemnik przechowuj�ca elementy dla listy BlockConfig/TypeConfig
* UWAGA: Klasa nie zwalnia danych przesy�anych jako wska�nik do konstruktora (aObiekt), osoba u�ywaj�ca klasy sama musi to oprogramowa�.
* @author Piotr Zegar
* @date 2008.11.25
* @version 1.1
*/

class Item
{
		private:
				 AnsiString name;
				 void* wsk;
				 AnsiString type;
		public:
				/**
				* Konstruktor.
				* Inicjuje pola prywatne nie pozwalaj�c na ich zmiann�, konstruktor wywala wyj�tek gdy parametry s� b��dne
				* @param aName Nazwa pod jak� b�d� przechowywane te dane, niemo�e by� pusta
				* @param aObiekt Obiekt kt�ry ma zosta� powi�zany z nazw�, niemo�e by� NULL
				* @param aTyp informacja o typie obiektu, nie u�ywana wewn�trz klasy, nie mo�e by� puste
				* @see Item(Item &kopia)
				*/
				Item(const AnsiString aName, void* aObiekt, const AnsiString aTyp);

				/**
				* Konstruktor kopiuj�cy
				* Kopiuje obiekt, wymagany dla vector
				* @param kopia obiekt kopiowany
				* @see Item(string aName, void* aObiekt, string aTyp)
				*/
				Item(Item &kopia);

				/**
				* Pobiera i zwraca nazw� podawan� w konstruktorze, zwracana warto�c nie jest pustym stringiem
				* @return name
				*/
				AnsiString& getName();

				/**
				* Pobiera i zwraca wska�nik do danych jakie przechowuje obiekt, zwracana warto�c nie ejst nullem
				* @return wsk
				*/
				void* getObject();



				bool setObject(void* aObiekt);

				/**
				* Pobiera i zwraca nazw� typu danych jak� user powi�za� z danymi i t� nazw�, nigdy nie zwraca pustego stringu
				* @return type
				*/
				AnsiString& getType();

};


#endif
