#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockElement_h__
#define __BlockElement_h__

#include "TypeConfig.h"

/**
* BlockElement - Klasa reprezentuj�ca wejscia/wyjscia miedzy blokami,
* zawiera - nazw�, opis, stan - czy jest poprawnie pod��czony (errorCode)
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
			* @param aName nazwa tworzonego wej�cia/wyj�cia
			*/
			BlockElement(const AnsiString aName);
			/*
			* Konstruktor
			* @param aName nazwa tworzonego wej�cia/wyj�cia
			*/
			BlockElement(const BlockElement &block);
			/*
			* Destruktor
			*/
			~BlockElement();
			/*
			* Pobiera opis.
			* @return AnsiString opis wej�cia/wyj�cia.
			*/
			AnsiString& getDescription();
			/*
			* Pobiera kod b��du.
			* @reurn int kod b��du.
			*/
			int getErrorCode();
			/*
			* Pobiera Opis b��du
			* @return AnsiString - Opis b��du.
			*/
			AnsiString& geErrorDescription();
			/*
			* Pobiera nazw� obiektu.
			* @return AnsiString nazwa obiektu.
			*/
			AnsiString& getName();
			/*
			* Pobiera Konfiguracj� bloku.
			* @return TypeConfig konfiguracja bloku.
			*/
			TypeConfig* getObject();
			/*
			* Ustawia opis.
			* @param aDescription - ustawiany opis.
			*/
			void setDescription(const AnsiString aDescription);
            /*
			* Ustawia opis b��du.
			* @param aErrorDescription - ustawiany opis b��du.
			*/
			void setErrorDescription(const AnsiString aErrorDescription);
			/*
			* Ustawia kod b��d.
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
