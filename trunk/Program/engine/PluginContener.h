#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __PluginContener_h__
#define __PluginContener_h__

#include "TypeDLL.h"
#include "FunctionDLL.h"
/**
 * Item - Klasa pojemnik przechowujaca pluginy
 * @author Piotr
 * @date 2008.11.25
 * @version 0.1
 */
class PluginContener
{
	private:
		vector<TypeDLL*> listOfType;
		vector<FunctionDLL*> listOfFunction;
	public:
		/**
		 * Destruktor
		 */
		~PluginContener();

		TypeDLL* addType(const AnsiString &fileDLL);

		FunctionDLL* addFunction(const AnsiString &fileDLL);

		TypeDLL* getType(const AnsiString &type);

		FunctionDLL* getFunction(const AnsiString &name);
};

#endif
