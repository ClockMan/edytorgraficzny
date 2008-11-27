#include <System.hpp>
#include <vector>
#include <exception>

using namespace std;

#ifndef __Block_h__
#define __Block_h__

#include "BlockConfig.h"
#include "BlockInput.h"
#include "BlockOutput.h"
/**
 * Block - Klasa pojemnik przechowujaca wejscia i wyjscia bloku
 * @author Piotr
 * @date 2008.11.25
 * @version 0.1
 */
class Block
{
	private:
		BlockConfig *config;
	public:
		/**
		 * Lista wejsc bloku.
		 */
		vector<BlockInput*> input;
		/**
		 * Lista wyjsc bloku.
		 */
		vector<BlockOutput*> output;
		/**
		 * Konstruktor domyslny.
		 */
		Block();
		/**
		 * Konstruktor kopiujacy
		 */
		Block(Block &copy);
		/**
		 * Destruktor
		 */
		~Block();
		/**
		 * Zwraca wskaznik do uwstawien bloku.
		 * @return BlockConfig* ustawienia bloku.
		 */
		BlockConfig* getConfig();
		/**
		 * Ustawia wlasciwoœci obiektu.
		 * @param ob
		 */
		void setConfig(BlockConfig &ob);
};

#endif
