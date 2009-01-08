#ifndef BlockValidateOutputElementH
#define BlockValidateOutputElementH

#include "../engine/BlockOutput.h"
#include "Connection.h"
#include <vector>
/**
 * Klasa ta jest pojemnikiem, dla metody validateBlock w PIWOEngine
 */
class BlockValidateOutputElement
{
	public:
	/**
	 * Wskaznik do wyjscia tego bloku
	 */
	BlockOutput* output;
	/**
	 * Typ danych na tym wyjsciu
	 */
	AnsiString type;
	/**
	 * Opis bledu na tym wyjsciu
	 */
	AnsiString errorDescription;
	/**
	 * Kod bledu na tym wyjsciu
	 */
	int errorCode;
	/**
	 * Wektor polaczen podlaczonych do tego wyjscia
	 */
	vector<Connection*> connections;
};
#endif                                       
