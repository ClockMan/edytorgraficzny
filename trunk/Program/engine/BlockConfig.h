#include <System.hpp>
#include <Graphics.hpp>
#include <Controls.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockConfig_h__
#define __BlockConfig_h__

#include "Item.h"

/**
* BlockConfig - Klasa przechowuj¹ca dane w postaci hashmapy, u¿ywana jako miejsce do przechowywania konfiguracji dowolnego bloczka.
* @author Piotr Zegar
* @date 2008.11.25
* @version 1.1
*/
class BlockConfig
{
		protected:
				 vector<Item*> map;
				 bool changed;
				 Item* getItem(const AnsiString aName);
				 bool loadFromStream2(TStream &aFrom);
				 bool saveToStream2(TStream &aWhere);
				 void copyFrom(BlockConfig &kopia);
		public:
				/**
				* Konstruktor.
				*/
				BlockConfig();

				BlockConfig(BlockConfig &kopia);

				BlockConfig(TStream &stream);
				/**
				* Destruktor
				*/
				~BlockConfig();

				/**
				* Wrzuca obiekt typu string (aTyp) na listê pod nazw¹ aName.
				* @param aName nazwa pod jak¹ obiekt ma widnieœc na liœcie
				* @param aValue dane jakie maj¹ zostaæ wrzucone na listê
				* @return zwraca true jeœli obiekt zosta³ dodany
				*/
				bool addString(const AnsiString aName, const AnsiString aValue);

				bool addBoolean(const AnsiString aName, bool aValue);
				bool addInt(const AnsiString aName, int aValue);
				bool addDouble(const AnsiString aName, double aValue);
				bool addBitmap(const AnsiString aName, Graphics::TBitmap &aValue);
				bool addStream(const AnsiString aName, TStream &aValue);
				bool setString(const AnsiString aName, const AnsiString aValue);
				bool setBoolean(const AnsiString aName, bool aValue);
				bool setInt(const AnsiString aName, int aValue);
				bool setDouble(const AnsiString aName, double aValue);
				bool setBitmap(const AnsiString aName, Graphics::TBitmap &aValue);
				bool setStream(const AnsiString aName, TStream &aValue);
				AnsiString& getString(const AnsiString aName);
				bool getBoolean(const AnsiString aName);
				int getInt(const AnsiString aName);
				double getDouble(const AnsiString aName);
				Graphics::TBitmap& getBitmap(const AnsiString aName);
				TStream& getStream(const AnsiString aName);
				bool isString(const AnsiString aName);
				bool isBoolean(const AnsiString aName);
				bool isInt(const AnsiString aName);
				bool isDouble(const AnsiString aName);
				bool isBitmap(const AnsiString aName);
				bool isStream(const AnsiString aName);
				AnsiString& getType(const AnsiString aName);
				bool isExist(const AnsiString aName);
				bool remove(const AnsiString aName);
				bool saveToStream(TStream &aWhere);
				bool loadFromStream(TStream &aFrom);
				bool isChanged();
				void clear();
};

#endif
