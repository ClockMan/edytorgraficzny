#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;
#ifndef __TypeConfig_h__
#define __TypeConfig_h__

#include "BlockConfig.h"

/**
 * TypeConfig - Klasa reprezentujaca typ przesylany do bloku zdefiniowany przez uzytkownika.
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
		 * Konstruktor kopiujacy.
		 * @param kopia obiekt ktory zostanie skopiowany
		 */
		TypeConfig(const TypeConfig &kopia);
		/**
		 * Konstruktor
		 * @param stream - strumien z ktorego zostana odczytane dane.
		 */
		TypeConfig(TStream &stream);
		/**
		 * Destruktor
		 */
		~TypeConfig();
		/**
		 * Zapisuje listê obiektow do strumienia.
		 * @param aWhere strumien w ktorym zostana zapisane informacje.
		 * @return true - jezeli operacja sie powiodla false - jezeli nie.
		 */
		bool saveToStream(TStream &aWhere);
		/**
		 * Odczytuje infomracjê o obiektach na liscie z strumienia
		 * @param aName nazwa obiektu
		 * @return true - jezeli operacja sie powiodla false - jezeli nie.
		 */
		bool loadFromStream(TStream &aFrom);
		/**
		 * Pobiera nazwe.
		 * @return nazwa obiektu.
		 */
		AnsiString& getName();
};

#endif
