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
* Block - Klasa pojemnik przechowuj¹ca wejœcia i wyjscia bloku
* @author Piotr
* @date 2008.11.25
* @version 0.1
*/
class Block
{
		private:
				BlockConfig *config;
		public:
				/*
				* Lista wejœæ bloku.
				*/
				vector<BlockInput> input;
				/*
				* Lista wyjœæ bloku.
				*/
				vector<BlockOutput> output;
				/*
				* Konstruktor domyœlny.
				*/
				Block();
				/*
				* Konstruktor kopiuj¹cy
				*/
				Block(const Block &copy);
				/*
				* Destruktor
				*/
				~Block();
				/*
				* Zwraca wskaŸnik do uwstawieñ bloku.
				* @return BlockConfig* ustawienia bloku.
				*/
				BlockConfig* getConfig();
				/*
				* Ustawia w³aœciwoœci obiektu.
				* @param ob
				*/
				void setConfig(BlockConfig &ob);
};

#endif
