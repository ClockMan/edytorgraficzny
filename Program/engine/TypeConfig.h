#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __TypeConfig_h__
#define __TypeConfig_h__

#include "BlockConfig.h"

/**
* TypeConfig - Klasa reprezentuj¹ca typ przesy³any do bloku zdefiniowany przez u¿ytkownika.
* @author Piotr 
* @date 2008.11.25
* @version 0.1
*/
class TypeConfig: public BlockConfig
{
		protected:
				 AnsiString nazwa;
		public:
				/**
				* Konstruktor
				* @param aName - nazwa nowego typu.
				*/
				TypeConfig(const AnsiString aName);
				/**
				* Konstruktor kopiuj¹cy.
				*/
				TypeConfig(TypeConfig &kopia);
				/**
				* Konstruktor
				* @param stream - strumien z którego zostan¹ odczytane dane.
				*/
				TypeConfig(TStream &stream);
				/**
				* Destruktor
				*/
				~TypeConfig();
                /**
				* Zapisujê listê obiektów do strumienia.
				* @param aWhere strumien w którym zostan¹ zapisane informacje.
				* @return true - jezeli operacja siê powiod³a false - je¿eli nie.
				*/
				bool saveToStream(TStream &aWhere);
				/**
				* Odczytujê infomracjê o obiektach na liscie z strumienia
				* @param aName nazwa obiektu
				* @return true - jezeli operacja siê powiod³¹ false - je¿eli nie.
				*/
				bool loadFromStream(TStream &aFrom);
				/**
				* Pobiera nazwê.
				* @return AnsiString nazwa obiektu.
				*/
				AnsiString& getName();
};

#endif
