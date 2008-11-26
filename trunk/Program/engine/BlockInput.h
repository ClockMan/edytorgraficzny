#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockInput_h__
#define __BlockInput_h__

#include "BlockElement.h"
/**
* BlockInput - Klasa pojemnik przechowuj�ca wej�cia i wyjscia bloku
* @author Piotr
* @date 2008.11.25
* @version 0.1
*/
class BlockInput: public BlockElement
{
		public:
				AnsiString inputType;
		public:
		/**
		* Konstruktor
		* @param aName Nazwa wej�cia bloku
		*/
				BlockInput(const AnsiString aName);
		/**
		* Konstruktor kopiuj�cy
		*/
				BlockInput(BlockInput &kopia);
		 /**
		 * Destruktor
		 */
				~BlockInput();
		 /**
		 * lista dozwolonych typ�w kt�re mog� zosta� podane na wej�cie
		 */
				vector<AnsiString> allowedTypes;
		 /**
		 * Realizuj� po��czenia mi�dzy blokami.
		 * @param aName nazwa obiektu z kt�rym bedzi� po��czone wej�cie.
		 * @return bool poprawno�� przeprowadzonej operajci.
		 */
				bool connect(const AnsiString aName);
		 /**
		 * Pobiera typ po��czenia.
		 * @return nazwa typu po��czenia.
		 */
				AnsiString& getConnectedType();
		  /**
		  * roz��cza bloki
		  */
				void disconnect();
};

#endif
