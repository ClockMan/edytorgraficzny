//---------------------------------------------------------------------------

#ifndef imageWindowH
#define imageWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TimgWindow : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel;
	TScrollBox *ScrollBoxPicture;
	TScrollBox *ScrollBoxPicsels;
	TLabel *LabelSizeText;
	TLabel *LabelSize;
	TLabel *LabelX;
	TLabel *LabelY;
	TEdit *EditX;
	TEdit *EditY;
	TImage *ImageSquare;
	TLabel *LabelR;
	TLabel *LabelG;
	TLabel *LabelB;
	TImage *ImagePicture;
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ImagePictureMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall EditXKeyPress(TObject *Sender, char &Key);
	void __fastcall EditXChange(TObject *Sender);
	void __fastcall EditYKeyPress(TObject *Sender, char &Key);
	void __fastcall EditYChange(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
private:	// User declarations
	TPoint *CursorPosition; 
	TPoint *CDown;
	void ChangeColor();
public:		// User declarations
	void PaintImage(Graphics::TBitmap* picture);
	void ClearImage();
	__fastcall TimgWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TimgWindow *imgWindow;
//---------------------------------------------------------------------------
#endif
