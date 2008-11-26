#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __PluginContener_h__
#define __PluginContener_h__

#include "TypeDLL.h"
#include "FunctionDLL.h"

class PluginContener
{
		private: vector<PIWO::TypeDLL> listOfType;
				 vector<PIWO::FunctionDLL> listOfFunction;

		public: bool addType(string aPath);
				bool addFunction(string aPath);
};

#endif
