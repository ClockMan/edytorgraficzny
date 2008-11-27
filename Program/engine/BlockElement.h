#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockElement_h__
#define __BlockElement_h__

#include "TypeConfig.h"

/**
* BlockElement - Klasa reprezentuj¹ca wejscia/wyjscia miedzy blokami,
* zawiera - nazwê, opis, stan - czy jest poprawnie pod³¹czony (errorCode)
* @author Piotr
* @date 2008.11.25
* @version 0.1
*/

class BlockElement
{
		protected:
			AnsiString description;
			int errorCode;
			AnsiString errorDescription;
			TypeConfig *object;
			AnsiString name;

		public:
			/*
			* Konstruktor
			* @param aName nazwa tworzonego wejœcia/wyjœcia
			*/
			BlockElement(const AnsiString aName);
			/*
			* Konstruktor
			* @param aName nazwa tworzonego wejœcia/wyjœcia
			*/
			BlockElement(const BlockElement &block);
			/*
			* Destruktor
			*/
			~BlockElement();
			/*
			* Pobiera opis.
			* @return AnsiString opis wejœcia/wyjœcia.
			*/
			AnsiString& getDescription();
			/*
			* Pobiera kod b³êdu.
			* @reurn int kod b³êdu.
			*/
			int getErrorCode();
			/*
			* Pobiera Opis b³êdu
			* @return AnsiString - Opis b³êdu.
			*/
			AnsiString& geErrorDescription();
			/*
			* Pobiera nazwê obiektu.
			* @return AnsiString nazwa obiektu.
			*/
			AnsiString& getName();
			/*
			* Pobiera Konfiguracjê bloku.
			* @return TypeConfig konfiguracja bloku.
			*/
			TypeConfig* getObject();
			/*
			* Ustawia opis.
			* @param aDescription - ustawiany opis.
			*/
			void setDescription(const AnsiString aDescription);
            /*
			* Ustawia opis b³êdu.
			* @param aErrorDescription - ustawiany opis b³êdu.
			*/
			void setErrorDescription(const AnsiString aErrorDescription);
			/*
			* Ustawia kod b³¹d.
			* @param aError - ustawiany opis.
			*/
			void setErrorCode(int aError);
			/*
			* Ustawia obiekt.
			* @param aData - ustawiany obiekt.
			*/
			void setObject(TypeConfig &aData);
};


#endif
