#include <vcl.h>
#pragma hdrstop
#include "Connection.h"
#pragma package(smart_init)

Connection::Connection(TWinControl* owner)
{
  fowner=owner;
}

Connection::~Connection()
{
	for(int i=lines.size()-1;i>=0;--i)
	{
		delete lines[i];
	}
	lines.clear();
}


