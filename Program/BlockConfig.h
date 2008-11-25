#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockConfig_h__
#define __BlockConfig_h__

// #include "BlockElement.h"
// #include "Block.h"
#include "Item.h"

namespace PIWO
{
	class BlockElement;
	class Block;
	class Item;
	class BlockConfig;
}

namespace PIWO
{
	class BlockConfig
	{
		private: vector<item> map;
		private: bool changed;
		PIWO::BlockElement* object;
		PIWO::Block* config;

		public: bool addString(string aName, string aValue);

		public: bool addBoolean(string aName, bool aValue);

		public: bool addInt(string aName, int aValue);

		public: bool addDouble(string aName, double aValue);

		public: bool addBitmap(string aName, TBitmap aValue);

		public: bool addStream(string aName, TStream aValue);

		private: bool addItem(item aValue);

		public: bool setString(string aName, string aValue);

		public: bool setBoolean(string aName, bool aValue);

		public: bool setInt(string aName, int aValue);

		public: bool setDouble(string aName, double aValue);

		public: bool setBitmap(string aName, TBitmap aValue);

		public: bool setStream(string aName, TStream aValue);

		public: String getString(string aName);

		public: bool getBoolean(string aName);

		public: int getInt(string aName);

		public: double getDouble(string aName);

		public: TBitmap getBitmap(string aName);

		public: TStream getStream(string aName);

		private: PIWO::Item getItem(string aName);

		public: bool isString(string aName);

		public: bool isBoolean(string aName);

		public: bool isInt(string aName);

		public: bool isDouble(string aName);

		public: bool isBitmap(string aName);

		public: bool isStream(string aName);

		public: string getType(string aName);

		public: bool isExist(string aName);

		public: bool remove(string aName);

		public: bool saveToStream(TStream aWhere);

		public: bool loadFromStream(TStream aFrom);

		public: bool isChanged();
	};
}

#endif
