#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockOutput_h__
#define __BlockOutput_h__
#include "BlockElement.h"
/**
 * BlockInput - Klasa pojemnik przechowujaca wejscia i wyjscia bloku
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
		 * @param aName nazwa wyjscia.
		 */
		BlockOutput(const AnsiString aName);
		/**
		 * Konstruktor kopiujacy.
		 * @param copy obiekt ktory zostanie skopiowany
		 */
		BlockOutput(const BlockOutput &copy);
		/**
		 * Destruktor
		 */
		~BlockOutput();
		/**
		 * Zwraca typ wyjscia.
		 * @return AnsiString typ wyjscia
		 */
		AnsiString& getOutputType();
		/**
		 * Ustawia typ wyjscia.
		 * @param aName typ wyjscia.
		 * @return poprawnosc wykonanej operacji
		 */
		bool setOutputType(AnsiString aName);
};

#endif
