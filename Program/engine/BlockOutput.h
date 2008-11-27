#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockOutput_h__
#define __BlockOutput_h__

#include "BlockElement.h"
/**
* BlockInput - Klasa pojemnik przechowuj�ca wej�cia i wyjscia bloku
* @author Piotr
* @date 2008.11.25
* @version 0.1
*/
class BlockOutput: public BlockElement
{
		private:
				AnsiString outputType;
		public:
			/**
			* Konstruktor
			* @param aName nazwa wyj�cia.
			*/
				BlockOutput(const AnsiString aName);
			/**
			* Konstruktor kopiuj�cy.
			* @param copy obiekt kt�ry zostanie skopiowany
			*/
				BlockOutput(const BlockOutput &copy);
			/**
			* Destruktor
			*/
				~BlockOutput();
			/**
			* Zwraca typ wyj�cia.
			* @return AnsiString typ wyj�cia
			*/
				AnsiString& getOutputType();
			/**
			* Ustawia typ wyj�cia.
			* @param aName typ wyj�cia.
			* @return poprawno�� wykonanej operacji
			*/
				bool setOutputType(AnsiString aName);
};

#endif
