#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __PluginContener_h__
#define __PluginContener_h__

#include "TypeDLL.h"
#include "FunctionDLL.h"

namespace PIWO
{
	class TypeDLL;
	class FunctionDLL;
	class PluginContener;
}

namespace PIWO
{
	class PluginContener
	{
		private: vector<PIWO::TypeDLL> listOfType;
		private: vector<PIWO::FunctionDLL> listOfFunction;

		public: bool addType(string aPath);

		public: bool addFunction(string aPath);
	};
}

#endif
