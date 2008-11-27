#include <System.hpp>
#include <Graphics.hpp>
#include <Controls.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockConfig_h__
#define __BlockConfig_h__

#include "Item.h"

/**
* BlockConfig - Klasa przechowuj¹ca dane w postaci hashmapy, u¿ywana jako miejsce do przechowywania konfiguracji dowolnego bloczka.
* @author Piotr
* @date 2008.11.25
* @version 0.1
*/
class BlockConfig
{
		protected:
				 vector<Item*> map;
				 bool changed;
				 Item* getItem(const AnsiString aName);
				 bool loadFromStream2(TStream &aFrom);
				 bool saveToStream2(TStream &aWhere);
				 void copyFrom(const BlockConfig &aCopy);
		public:
				/**
				* Konstruktor.
				*/
				BlockConfig();
				/**
				* Konsrutkor Kopiuj¹cy
				*/
				BlockConfig(const BlockConfig &aCopy);

				BlockConfig(TStream &stream);
				/**
				* Destruktor
				*/
				~BlockConfig();

				/**
				* Dodajê obiekt typu string (aTyp) na listê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool addString(const AnsiString aName, const AnsiString aValue);
                /**
				* Dodajê obiekt typu Boolean (aTyp) na listê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool addBoolean(const AnsiString aName, bool aValue);
                /**
				* Dodajê obiekt typu int (aTyp) na listê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool addInt(const AnsiString aName, int aValue);
				/**
				* Dodajê obiekt typu double (aTyp) na listê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool addDouble(const AnsiString aName, double aValue);
                /**
				* Dodajê obiekt typu TBitmap (aTyp) na listê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool addBitmap(const AnsiString aName, Graphics::TBitmap &aValue);
                /**
				* Dodajê obiekt typu TStream (aTyp) na listê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool addStream(const AnsiString aName, TStream &aValue);
				/**
				* Zmienia obiekt typu string (aTyp) na lisciê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool setString(const AnsiString aName, const AnsiString aValue);
                /**
				* Zmienia obiekt typu boolean (aTyp) na lisciê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool setBoolean(const AnsiString aName, bool aValue);
                /**
				* Zmienia obiekt typu int (aTyp) na lisciê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool setInt(const AnsiString aName, int aValue);
                /**
				* Zmienia obiekt typu double (aTyp) na lisciê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool setDouble(const AnsiString aName, double aValue);
                /**
				* Zmienia obiekt typu TBitmap (aTyp) na lisciê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool setBitmap(const AnsiString aName, Graphics::TBitmap &aValue);
                /**
				* Zmienia obiekt typu TStream (aTyp) na lisciê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool setStream(const AnsiString aName, TStream &aValue);
				/**
				* Pobiera obiekt typu string z listy pod nazw¹ aName.
				* @param aName nazwa obiektu
				* @return wartoœæ danego obiektu
				*/
				AnsiString& getString(const AnsiString aName);
				/**
				* Pobiera obiekt typu boolean (aTyp) z listy pod nazw¹ aName.
				* @param aName nazwa obiektu
				* @return wartoœæ danego obiektu
				*/
				bool getBoolean(const AnsiString aName);
                /**
				* Pobiera obiekt typu int (aTyp) z listy pod nazw¹ aName.
				* @param aName nazwa obiektu
				* @return wartoœæ danego obiektu
				*/
				int getInt(const AnsiString aName);
				/**
				* Pobiera obiekt typu double (aTyp) z listy pod nazw¹ aName.
				* @param aName nazwa obiektu
				* @return wartoœæ danego obiektu
				*/
				double getDouble(const AnsiString aName);
				/**
				* Pobiera obiekt typu TBitmap (aTyp) z listy pod nazw¹ aName.
				* @param aName nazwa obiektu
				* @return wartoœæ danego obiektu
				*/
				Graphics::TBitmap& getBitmap(const AnsiString aName);
				/**
				* Pobiera obiekt typu Stream (aTyp) z listy pod nazw¹ aName.
				* @param aName nazwa obiektu
				* @return wartoœæ danego obiektu
				*/
				TStream& getStream(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw¹ aName jest typu String.
				* @param aName nazwa obiektu
				* @return ture - jezeli jest to ten sam typ false - je¿eli nie.
				*/
				bool isString(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw¹ aName jest typu booleand.
				* @param aName nazwa obiektu
				* @return ture - jezeli jest to ten sam typ false - je¿eli nie.
				*/
				bool isBoolean(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw¹ aName jest typu int.
				* @param aName nazwa obiektu
				* @return trure - jezeli jest to ten sam typ false - je¿eli nie.
				*/
				bool isInt(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw¹ aName jest typu Double.
				* @param aName nazwa obiektu
				* @return true - jezeli jest to ten sam typ false - je¿eli nie.
				*/
				bool isDouble(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw¹ aName jest typu TBitmap.
				* @param aName nazwa obiektu
				* @return true - jezeli jest to ten sam typ false - je¿eli nie.
				*/
				bool isBitmap(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw¹ aName jest typu TStream.
				* @param aName nazwa obiektu
				* @return true - jezeli jest to ten sam typ false - je¿eli nie.
				*/
				bool isStream(const AnsiString aName);
				/**
				* Zwraca typ danego obiekut.
				* @param aName nazwa obiektu
				* @return string okreslajacy typ.
				*/
				AnsiString& getType(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw¹ aName istnieje.
				* @param aName nazwa obiektu
				* @return true - jezeli isntieje false - je¿eli nie.
				*/
				bool isExist(const AnsiString aName);
				/**
				* Usuwa obiekt pod nazw¹ aName.
				* @param aName nazwa obiektu
				* @return true - jezeli zosta³ usuniêty false - je¿eli nie.
				*/
				bool remove(const AnsiString aName);
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
				/*
				* Sprawdza czy ostatnio zosta³y dodkonane zmiany
				* @return true - jeœli zosta³ zmieniony
				*/
				bool isChanged();
				/**
				* czyszczenie listy
				*/
				void clear();
};

#endif
