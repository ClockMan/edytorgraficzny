//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef SHOWH
#define SHOWH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TFrame
{
__published:	// IDE-managed Components
	TScrollBox *ScrollBox1;
	TImage *Image1;
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
