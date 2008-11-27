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
* Block - Klasa pojemnik przechowuj�ca wej�cia i wyjscia bloku
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
				* Lista wej�� bloku.
				*/
				vector<BlockInput> input;
				/*
				* Lista wyj�� bloku.
				*/
				vector<BlockOutput> output;
				/*
				* Konstruktor domy�lny.
				*/
				Block();
				/*
				* Konstruktor kopiuj�cy
				*/
				Block(const Block &copy);
				/*
				* Destruktor
				*/
				~Block();
				/*
				* Zwraca wska�nik do uwstawie� bloku.
				* @return BlockConfig* ustawienia bloku.
				*/
				BlockConfig* getConfig();
				/*
				* Ustawia w�a�ciwo�ci obiektu.
				* @param ob
				*/
				void setConfig(BlockConfig &ob);
};

#endif
