#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __Block_h__
#define __Block_h__
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
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
		TForm *blockWindow;
		/*
		 * Lista wejsc bloku.
		 */
		vector<BlockInput> input;
		/*
		 * Lista wyjsc bloku.
		 */
		vector<BlockOutput> output;
		/*
		 * Konstruktor domyslny.
		 */
		Block();
		/*
		 * Konstruktor kopiujacy
		 * @param copy obiekt ktory zostanie skopiowany
		 */
		Block(const Block &copy);
		/*
		 * Destruktor
		 */
		~Block();
		/*
		 * Zwraca wskaznik do uwstawien bloku.
		 * @return ustawienia bloku.
		 */
		BlockConfig* getConfig();
		/*
		 * Ustawia wlasciwosci obiektu.
		 * @param ob wlasciowsci obiektu.
		 */
		void setConfig(const BlockConfig &ob);
};

#endif
