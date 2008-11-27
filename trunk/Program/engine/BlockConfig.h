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
 * BlockConfig - Klasa przechowujaca dane w postaci hashmapy, uzywana jako miejsce do przechowywania konfiguracji dowolnego bloczka.
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
		 * Konsrutkor Kopiujacy
		 * @param aCopy obiekt ktory zostanie skopiowany
		 */
		BlockConfig(const BlockConfig &aCopy);

		BlockConfig(TStream &stream);
		/**
		 * Destruktor
		 */
		~BlockConfig();

		/**
		 * Dodaje obiekt typu string (aTyp) na listê pod nazwa aName.
		 * @param aName nazwa pod jaka obiekt ma widniesc na liœcie
		 * @param aValue dane jakie maja zostac wrzucone na liste
		 * @return zwraca true jesli obiekt zostal dodany
		 */
		bool addString(const AnsiString aName, const AnsiString aValue);
		/**
		 * Dodaje obiekt typu Boolean (aTyp) na listê pod nazwa aName.
		 * @param aName nazwa pod jaka obiekt ma widniesc na liœcie
		 * @param aValue dane jakie maja zostac wrzucone na liste
		 * @return zwraca true jesli obiekt zostal dodany
		 */
		bool addBoolean(const AnsiString aName, bool aValue);
		/**
		 * Dodaje obiekt typu int (aTyp) na listê pod nazwa aName.
		 * @param aName nazwa pod jaka obiekt ma widniesc na liœcie
		 * @param aValue dane jakie maja zostac wrzucone na liste
		 * @return zwraca true jesli obiekt zostal dodany
		 */
		bool addInt(const AnsiString aName, int aValue);
		/**
		 * Dodaje obiekt typu double (aTyp) na listê pod nazwa aName.
		 * @param aName nazwa pod jaka obiekt ma widniesc na liœcie
		 * @param aValue dane jakie maja zostac wrzucone na liste
		 * @return zwraca true jesli obiekt zostal dodany
		 */
		bool addDouble(const AnsiString aName, double aValue);
		/**
		 * Dodaje obiekt typu TBitmap (aTyp) na listê pod nazwa aName.
		 * @param aName nazwa pod jaka obiekt ma widniesc na liœcie
		 * @param aValue dane jakie maja zostac wrzucone na liste
		 * @return zwraca true jesli obiekt zostal dodany
		 */
		bool addBitmap(const AnsiString aName, Graphics::TBitmap &aValue);
		/**
		 * Dodaje obiekt typu TStream (aTyp) na listê pod nazwa aName.
		 * @param aName nazwa pod jaka obiekt ma widniesc na liœcie
		 * @param aValue dane jakie maja zostac wrzucone na liste
		 * @return zwraca true jesli obiekt zostal dodany
		 */
		bool addStream(const AnsiString aName, TStream &aValue);
		/**
		 * Zmienia obiekt typu string (aTyp) na liscie pod nazwa aName.
		 * @param aName nazwa pod jaka obiekt ma widniesc na liœcie
		 * @param aValue dane jakie maja zostac wrzucone na liste
		 * @return zwraca true jesli obiekt zostal dodany
		 */
		bool setString(const AnsiString aName, const AnsiString aValue);
		/**
		 * Zmienia obiekt typu boolean (aTyp) na liscie pod nazwa aName.
		 * @param aName nazwa pod jaka obiekt ma widniesc na liœcie
		 * @param aValue dane jakie maja zostac wrzucone na liste
		 * @return zwraca true jesli obiekt zostal dodany
		 */
		bool setBoolean(const AnsiString aName, bool aValue);
		/**
		 * Zmienia obiekt typu int (aTyp) na liscie pod nazwa aName.
		 * @param aName nazwa pod jaka obiekt ma widniesc na liœcie
		 * @param aValue dane jakie maja zostac wrzucone na liste
		 * @return zwraca true jesli obiekt zostal dodany
		 */
		bool setInt(const AnsiString aName, int aValue);
		/**
		 * Zmienia obiekt typu double (aTyp) na liscie pod nazwa aName.
		 * @param aName nazwa pod jaka obiekt ma widniesc na liœcie
		 * @param aValue dane jakie maja zostac wrzucone na liste
		 * @return zwraca true jesli obiekt zostal dodany
		 */
		bool setDouble(const AnsiString aName, double aValue);
		/**
		 * Zmienia obiekt typu TBitmap (aTyp) na liscie pod nazwa aName.
		 * @param aName nazwa pod jaka obiekt ma widniesc na liœcie
		 * @param aValue dane jakie maja zostac wrzucone na liste
		 * @return zwraca true jesli obiekt zostal dodany
		 */
		bool setBitmap(const AnsiString aName, Graphics::TBitmap &aValue);
		/**
		 * Zmienia obiekt typu TStream (aTyp) na liscie pod nazwa aName.
		 * @param aName nazwa pod jaka obiekt ma widniesc na liœcie
		 * @param aValue dane jakie maja zostac wrzucone na liste
		 * @return zwraca true jesli obiekt zostal dodany
		 */
		bool setStream(const AnsiString aName, TStream &aValue);
		/**
		 * Pobiera obiekt typu string z listy pod nazwa aName.
		 * @param aName nazwa obiektu
		 * @return wartosc danego obiektu
		 */
		AnsiString& getString(const AnsiString aName);
		/**
		 * Pobiera obiekt typu boolean (aTyp) z listy pod nazwa aName.
		 * @param aName nazwa obiektu
		 * @return wartosc danego obiektu
		 */
		bool getBoolean(const AnsiString aName);
		/**
		 * Pobiera obiekt typu int (aTyp) z listy pod nazwa aName.
		 * @param aName nazwa obiektu
		 * @return wartosc danego obiektu
		 */
		int getInt(const AnsiString aName);
		/**
		 * Pobiera obiekt typu double (aTyp) z listy pod nazwa aName.
		 * @param aName nazwa obiektu
		 * @return wartosc danego obiektu
		 */
		double getDouble(const AnsiString aName);
		/**
		 * Pobiera obiekt typu TBitmap (aTyp) z listy pod nazwa aName.
		 * @param aName nazwa obiektu
		 * @return wartosc danego obiektu
		 */
		Graphics::TBitmap& getBitmap(const AnsiString aName);
		/**
		 * Pobiera obiekt typu Stream (aTyp) z listy pod nazwa aName.
		 * @param aName nazwa obiektu
		 * @return wartosc danego obiektu
		 */
		TStream& getStream(const AnsiString aName);
		/**
		 * Sprawdza czy obiekt pod nazwa aName jest typu String.
		 * @param aName nazwa obiektu
		 * @return ture - jezeli jest to ten sam typ false - jezeli nie.
		 */
		bool isString(const AnsiString aName);
		/**
		 * Sprawdza czy obiekt pod nazwa aName jest typu booleand.
		 * @param aName nazwa obiektu
		 * @return ture - jezeli jest to ten sam typ false - jezeli nie.
		 */
		bool isBoolean(const AnsiString aName);
		/**
		 * Sprawdza czy obiekt pod nazwa aName jest typu int.
		 * @param aName nazwa obiektu
		 * @return trure - jezeli jest to ten sam typ false - jezeli nie.
		 */
		bool isInt(const AnsiString aName);
		/**
		 * Sprawdza czy obiekt pod nazwa aName jest typu Double.
		 * @param aName nazwa obiektu
		 * @return true - jezeli jest to ten sam typ false - jezeli nie.
		 */
		bool isDouble(const AnsiString aName);
		/**
		 * Sprawdza czy obiekt pod nazwa aName jest typu TBitmap.
		 * @param aName nazwa obiektu
		 * @return true - jezeli jest to ten sam typ false - jezeli nie.
		 */
		bool isBitmap(const AnsiString aName);
		/**
		 * Sprawdza czy obiekt pod nazwa aName jest typu TStream.
		 * @param aName nazwa obiektu
		 * @return true - jezeli jest to ten sam typ false - jezeli nie.
		 */
		bool isStream(const AnsiString aName);
		/**
		 * Zwraca typ danego obiekut.
		 * @param aName nazwa obiektu
		 * @return string okreslajacy typ.
		 */
		AnsiString& getType(const AnsiString aName);
		/**
		 * Sprawdza czy obiekt pod nazwa aName istnieje.
		 * @param aName nazwa obiektu
		 * @return true - jezeli isntieje false - jezeli nie.
		 */
		bool isExist(const AnsiString aName);
		/**
		 * Usuwa obiekt pod nazwa aName.
		 * @param aName nazwa obiektu
		 * @return true - jezeli zostal usuniety false - jezeli nie.
		 */
		bool remove(const AnsiString aName);
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
		/*
		 * Sprawdza czy ostatnio zostaly dodkonane zmiany
		 * @return true - jesli zostal zmieniony
		 */
		bool isChanged();
		/**
		 * czyszczenie listy
		 */
		void clear();
};

#endif
