#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __TypeConfig_h__
#define __TypeConfig_h__

#include "BlockConfig.h"

/**
* TypeConfig - Klasa reprezentuj�ca typ przesy�any do bloku zdefiniowany przez u�ytkownika.
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
				* Konstruktor kopiuj�cy.
				*/
				TypeConfig(TypeConfig &kopia);
				/**
				* Konstruktor
				* @param stream - strumien z kt�rego zostan� odczytane dane.
				*/
				TypeConfig(TStream &stream);
				/**
				* Destruktor
				*/
				~TypeConfig();
                /**
				* Zapisuj� list� obiekt�w do strumienia.
				* @param aWhere strumien w kt�rym zostan� zapisane informacje.
				* @return true - jezeli operacja si� powiod�a false - je�eli nie.
				*/
				bool saveToStream(TStream &aWhere);
				/**
				* Odczytuj� infomracj� o obiektach na liscie z strumienia
				* @param aName nazwa obiektu
				* @return true - jezeli operacja si� powiod�� false - je�eli nie.
				*/
				bool loadFromStream(TStream &aFrom);
				/**
				* Pobiera nazw�.
				* @return AnsiString nazwa obiektu.
				*/
				AnsiString& getName();
};

#endif
