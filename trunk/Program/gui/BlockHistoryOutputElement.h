#ifndef BlockHistoryOutputElementH
#define BlockHistoryOutputElementH

#include "../engine/BlockOutput.h"
#include "../engine/TypeConfig.h"
/**
 * Klasa zawiera historie dla pojedynczego wyjscia bloku
 */
class BlockHistoryOutputElement
{
     private:
	TypeConfig* data;
     public:
    /**
     * Wyjscie bloku
     */ 
	BlockOutput* output;
	/**
	 * Ustawia obiekt
	 * @param d dane
	 */
	void setData(TypeConfig &d);
	/**
	 * Czysci obiekt
	 */
	void setNULL();
	/**
	 * Zwraca obiekt
	 * @return NULL lub TypeConfig*
	 */
	TypeConfig* getData();
	/**
	 * Konstruktor
	 */
	BlockHistoryOutputElement();
	/**
	 * Destruktor
	 */
	~BlockHistoryOutputElement();
};

#endif
