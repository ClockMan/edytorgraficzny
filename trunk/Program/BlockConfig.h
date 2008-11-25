#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockConfig_h__
#define __BlockConfig_h__

#include "BlockElement.h"
#include "Block.h"
#include "Item.h"

class BlockConfig
{
		private: vector<Item> map;
				 bool changed;

				 bool addItem(item aValue);
				 PIWO::Item getItem(string aName);
		public:
				 bool addString(string aName, string aValue);
				 bool addBoolean(string aName, bool aValue);
				 bool addInt(string aName, int aValue);
				 bool addDouble(string aName, double aValue);
				 bool addBitmap(string aName, TBitmap aValue);
				 bool addStream(string aName, TStream aValue);
				 bool setString(string aName, string aValue);
				 bool setBoolean(string aName, bool aValue);
				 bool setInt(string aName, int aValue);
				 bool setDouble(string aName, double aValue);
				 bool setBitmap(string aName, TBitmap aValue);
				 bool setStream(string aName, TStream aValue);
				 String getString(string aName);
				 bool getBoolean(string aName);
				 int getInt(string aName);
				 double getDouble(string aName);
				 TBitmap getBitmap(string aName);
				 TStream getStream(string aName);
				 bool isString(string aName);
				 bool isBoolean(string aName);
				 bool isInt(string aName);
				 bool isDouble(string aName);
				 bool isBitmap(string aName);
				 bool isStream(string aName);
				 string getType(string aName);
				 bool isExist(string aName);
				 bool remove(string aName);
				 bool saveToStream(TStream aWhere);
				 bool loadFromStream(TStream aFrom);
				 bool isChanged();
};

#endif
