#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __PluginContener_h__
#define __PluginContener_h__
										//Sender, progress, max, info, code 0-ok typ danych, 1- ok funkcja, 2- nie typdanych, 3- nie funkcja
typedef void (__closure *PluginContener_OnProgress)(void*, int, int, AnsiString, int);

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
		int SearchDirectory(std::vector<AnsiString> &refvecFiles,
					const AnsiString        &refcstrRootDirectory,
					const AnsiString        &refcstrExtension,
					bool	   bSearchSubdirectories = true);
		void AddMenus(FunctionDLL *info, TMainMenu &menu, TImageList &images, int upId, int downId, int functionIcon, int folderIcon);
	public:
		PluginContener_OnProgress OnLoadingProgress;

		PluginContener();
		/**
		 * Destruktor
		 */
		~PluginContener();

		bool LoadData(AnsiString blockDir, AnsiString typesDir, TMainMenu &menu, TImageList &images, int upId, int downId, int functionIcon, int folderIcon);

		TypeDLL* addType(const AnsiString &fileDLL);

		FunctionDLL* addFunction(const AnsiString &fileDLL);

		TypeDLL* getType(const AnsiString &type);

		FunctionDLL* getFunction(const AnsiString &name);
};

#endif
