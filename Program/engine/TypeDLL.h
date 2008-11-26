#include <System.hpp>
#include <vector>
#include <exception>
#include <vcl.h>
using namespace std;

#ifndef __TypeDLL_h__
#define __TypeDLL_h__

#include "TypeConfig.h"

/**
*  Interfejs pozwalaj¹cy na ³¹dowanie i u¿ywanie biblioteki typu
*/
typedef TForm* ( *TypeDLL_show )(TComponent*, TypeConfig*);
typedef bool ( *TypeDLL_isValid )(TypeConfig*);

class TypeDLL
{
   private:
			AnsiString type;
			HANDLE DLLHandle;
			TypeDLL_show fshow;
			TypeDLL_isValid fisValid;
   public:
			TypeDLL(const AnsiString file, const AnsiString stype);
			~TypeDLL();
			TForm* show(TComponent* parent, TypeConfig* aData);
			bool isValid(TypeConfig *aData);
			AnsiString& getType();

};

#endif
