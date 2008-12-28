#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockElement_h__
#define __BlockElement_h__
#include "TypeConfig.h"

/**
 * BlockElement - Klasa reprezentujaca wejscia/wyjscia miedzy blokami,
 * zawiera - nazwe, opis, stan - czy jest poprawnie podlaczony (errorCode)
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
		 * @param aName nazwa tworzonego wejscia/wyjœcia
		 */
		BlockElement(const AnsiString aName);
		/*
		 * Konstruktor
		 * @param aName nazwa tworzonego wejscia/wyjœcia
		 */
		BlockElement(const BlockElement &block);
		/*
		 * Destruktor
		 */
		~BlockElement();
		/*
		 * Pobiera opis.
		 * @return AnsiString opis wejscia/wyjœcia.
		 */
		AnsiString& getDescription();
		/*
		 * Pobiera kod bledu.
		 * @reurn int kod bledu.
		 */
		int getErrorCode();
		/*
		 * Pobiera Opis bledu
		 * @return AnsiString - Opis bledu.
		 */
		AnsiString& getErrorDescription();
		/*
		 * Pobiera nazwe obiektu.
		 * @return AnsiString nazwa obiektu.
		 */
		AnsiString& getName();
		/*
		 * Pobiera Konfiguracje bloku.
		 * @return TypeConfig konfiguracja bloku.
		 */
		TypeConfig* getObject();
		/*
		 * Ustawia opis.
		 * @param aDescription - ustawiany opis.
		 */
		void setDescription(const AnsiString aDescription);
		/*
		 * Ustawia opis bledu.
		 * @param aErrorDescription - ustawiany opis bledu.
		 */
		void setErrorDescription(const AnsiString aErrorDescription);
		/*
		 * Ustawia kod blad.
		 * @param aError - ustawiany opis.
		 */
		void setErrorCode(int aError);
		/*
		 * Ustawia obiekt.
		 * @param aData - ustawiany obiekt.
		 */
		void setObject(const TypeConfig &aData);
};


#endif
