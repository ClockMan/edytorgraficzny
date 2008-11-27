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
* BlockConfig - Klasa przechowuj�ca dane w postaci hashmapy, u�ywana jako miejsce do przechowywania konfiguracji dowolnego bloczka.
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
				* Konsrutkor Kopiuj�cy
				*/
				BlockConfig(const BlockConfig &aCopy);

				BlockConfig(TStream &stream);
				/**
				* Destruktor
				*/
				~BlockConfig();

				/**
				* Dodaj� obiekt typu string (aTyp) na list� pod nazw� aName.
				* @param aName nazwa pod jak� obiekt ma widnie�c na li�cie
				* @param aValue dane jakie maj� zosta� wrzucone na list�
				* @return zwraca true je�li obiekt zosta� dodany
				*/
				bool addString(const AnsiString aName, const AnsiString aValue);
                /**
				* Dodaj� obiekt typu Boolean (aTyp) na list� pod nazw� aName.
				* @param aName nazwa pod jak� obiekt ma widnie�c na li�cie
				* @param aValue dane jakie maj� zosta� wrzucone na list�
				* @return zwraca true je�li obiekt zosta� dodany
				*/
				bool addBoolean(const AnsiString aName, bool aValue);
                /**
				* Dodaj� obiekt typu int (aTyp) na list� pod nazw� aName.
				* @param aName nazwa pod jak� obiekt ma widnie�c na li�cie
				* @param aValue dane jakie maj� zosta� wrzucone na list�
				* @return zwraca true je�li obiekt zosta� dodany
				*/
				bool addInt(const AnsiString aName, int aValue);
				/**
				* Dodaj� obiekt typu double (aTyp) na list� pod nazw� aName.
				* @param aName nazwa pod jak� obiekt ma widnie�c na li�cie
				* @param aValue dane jakie maj� zosta� wrzucone na list�
				* @return zwraca true je�li obiekt zosta� dodany
				*/
				bool addDouble(const AnsiString aName, double aValue);
                /**
				* Dodaj� obiekt typu TBitmap (aTyp) na list� pod nazw� aName.
				* @param aName nazwa pod jak� obiekt ma widnie�c na li�cie
				* @param aValue dane jakie maj� zosta� wrzucone na list�
				* @return zwraca true je�li obiekt zosta� dodany
				*/
				bool addBitmap(const AnsiString aName, Graphics::TBitmap &aValue);
                /**
				* Dodaj� obiekt typu TStream (aTyp) na list� pod nazw� aName.
				* @param aName nazwa pod jak� obiekt ma widnie�c na li�cie
				* @param aValue dane jakie maj� zosta� wrzucone na list�
				* @return zwraca true je�li obiekt zosta� dodany
				*/
				bool addStream(const AnsiString aName, TStream &aValue);
				/**
				* Zmienia obiekt typu string (aTyp) na lisci� pod nazw� aName.
				* @param aName nazwa pod jak� obiekt ma widnie�c na li�cie
				* @param aValue dane jakie maj� zosta� wrzucone na list�
				* @return zwraca true je�li obiekt zosta� dodany
				*/
				bool setString(const AnsiString aName, const AnsiString aValue);
                /**
				* Zmienia obiekt typu boolean (aTyp) na lisci� pod nazw� aName.
				* @param aName nazwa pod jak� obiekt ma widnie�c na li�cie
				* @param aValue dane jakie maj� zosta� wrzucone na list�
				* @return zwraca true je�li obiekt zosta� dodany
				*/
				bool setBoolean(const AnsiString aName, bool aValue);
                /**
				* Zmienia obiekt typu int (aTyp) na lisci� pod nazw� aName.
				* @param aName nazwa pod jak� obiekt ma widnie�c na li�cie
				* @param aValue dane jakie maj� zosta� wrzucone na list�
				* @return zwraca true je�li obiekt zosta� dodany
				*/
				bool setInt(const AnsiString aName, int aValue);
                /**
				* Zmienia obiekt typu double (aTyp) na lisci� pod nazw� aName.
				* @param aName nazwa pod jak� obiekt ma widnie�c na li�cie
				* @param aValue dane jakie maj� zosta� wrzucone na list�
				* @return zwraca true je�li obiekt zosta� dodany
				*/
				bool setDouble(const AnsiString aName, double aValue);
                /**
				* Zmienia obiekt typu TBitmap (aTyp) na lisci� pod nazw� aName.
				* @param aName nazwa pod jak� obiekt ma widnie�c na li�cie
				* @param aValue dane jakie maj� zosta� wrzucone na list�
				* @return zwraca true je�li obiekt zosta� dodany
				*/
				bool setBitmap(const AnsiString aName, Graphics::TBitmap &aValue);
                /**
				* Zmienia obiekt typu TStream (aTyp) na lisci� pod nazw� aName.
				* @param aName nazwa pod jak� obiekt ma widnie�c na li�cie
				* @param aValue dane jakie maj� zosta� wrzucone na list�
				* @return zwraca true je�li obiekt zosta� dodany
				*/
				bool setStream(const AnsiString aName, TStream &aValue);
				/**
				* Pobiera obiekt typu string z listy pod nazw� aName.
				* @param aName nazwa obiektu
				* @return warto�� danego obiektu
				*/
				AnsiString& getString(const AnsiString aName);
				/**
				* Pobiera obiekt typu boolean (aTyp) z listy pod nazw� aName.
				* @param aName nazwa obiektu
				* @return warto�� danego obiektu
				*/
				bool getBoolean(const AnsiString aName);
                /**
				* Pobiera obiekt typu int (aTyp) z listy pod nazw� aName.
				* @param aName nazwa obiektu
				* @return warto�� danego obiektu
				*/
				int getInt(const AnsiString aName);
				/**
				* Pobiera obiekt typu double (aTyp) z listy pod nazw� aName.
				* @param aName nazwa obiektu
				* @return warto�� danego obiektu
				*/
				double getDouble(const AnsiString aName);
				/**
				* Pobiera obiekt typu TBitmap (aTyp) z listy pod nazw� aName.
				* @param aName nazwa obiektu
				* @return warto�� danego obiektu
				*/
				Graphics::TBitmap& getBitmap(const AnsiString aName);
				/**
				* Pobiera obiekt typu Stream (aTyp) z listy pod nazw� aName.
				* @param aName nazwa obiektu
				* @return warto�� danego obiektu
				*/
				TStream& getStream(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw� aName jest typu String.
				* @param aName nazwa obiektu
				* @return ture - jezeli jest to ten sam typ false - je�eli nie.
				*/
				bool isString(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw� aName jest typu booleand.
				* @param aName nazwa obiektu
				* @return ture - jezeli jest to ten sam typ false - je�eli nie.
				*/
				bool isBoolean(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw� aName jest typu int.
				* @param aName nazwa obiektu
				* @return trure - jezeli jest to ten sam typ false - je�eli nie.
				*/
				bool isInt(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw� aName jest typu Double.
				* @param aName nazwa obiektu
				* @return true - jezeli jest to ten sam typ false - je�eli nie.
				*/
				bool isDouble(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw� aName jest typu TBitmap.
				* @param aName nazwa obiektu
				* @return true - jezeli jest to ten sam typ false - je�eli nie.
				*/
				bool isBitmap(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw� aName jest typu TStream.
				* @param aName nazwa obiektu
				* @return true - jezeli jest to ten sam typ false - je�eli nie.
				*/
				bool isStream(const AnsiString aName);
				/**
				* Zwraca typ danego obiekut.
				* @param aName nazwa obiektu
				* @return string okreslajacy typ.
				*/
				AnsiString& getType(const AnsiString aName);
				/**
				* Sprawdza czy obiekt pod nazw� aName istnieje.
				* @param aName nazwa obiektu
				* @return true - jezeli isntieje false - je�eli nie.
				*/
				bool isExist(const AnsiString aName);
				/**
				* Usuwa obiekt pod nazw� aName.
				* @param aName nazwa obiektu
				* @return true - jezeli zosta� usuni�ty false - je�eli nie.
				*/
				bool remove(const AnsiString aName);
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
				/*
				* Sprawdza czy ostatnio zosta�y dodkonane zmiany
				* @return true - je�li zosta� zmieniony
				*/
				bool isChanged();
				/**
				* czyszczenie listy
				*/
				void clear();
};

#endif
