//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "imageWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TimgWindow *imgWindow;
//---------------------------------------------------------------------------

__fastcall TimgWindow::TimgWindow(TComponent* Owner)
	: TForm(Owner)
{
	CursorPosition = new TPoint;   
	CDown = new TPoint;
}
//---------------------------------------------------------------------------

void TimgWindow::PaintImage(Graphics::TBitmap* picture)
{
		ImagePicture->Picture->Graphic = picture;
		ImagePicture->ClientWidth = ImagePicture->Picture->Width;
		ImagePicture->ClientHeight = ImagePicture->Picture->Height;

		ImagePicture->Canvas->Draw(0, 0, picture);
		LabelSize->Caption = (String)ImagePicture->ClientWidth + " × " + (String)ImagePicture->ClientHeight;
}
//---------------------------------------------------------------------------

void TimgWindow::ClearImage()
{
	ImagePicture->Canvas->Rectangle(-1, -1, ImagePicture->ClientWidth + 2, ImagePicture->ClientHeight + 2);
}
//---------------------------------------------------------------------------

void __fastcall TimgWindow::ImagePictureMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
	if(!Shift.ToInt())
	{
		EditX->Text = (String)X;
		EditY->Text = (String)Y;
	}
}
//---------------------------------------------------------------------------

void __fastcall TimgWindow::FormCreate(TObject *Sender)
{
	CursorPosition->x = 0;
	CursorPosition->y = 0;     
	CDown->x = 0;
	CDown->y = 0;
}
//---------------------------------------------------------------------------

   void __fastcall TimgWindow::FormDestroy(TObject *Sender)
{
	delete CursorPosition;
	delete CDown;
}
//---------------------------------------------------------------------------

void __fastcall TimgWindow::EditXKeyPress(TObject *Sender, char &Key)
{
	if('0'<=Key && Key<='9' || Key==8)
	{
		EditX->ReadOnly = false;
	}
	else
	{
		EditX->ReadOnly = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TimgWindow::EditXChange(TObject *Sender)
{
	if(!EditX->Text.IsEmpty())
	{
		try {
			CursorPosition->x = EditX->Text.ToInt();
			ChangeColor();
		} catch (EConvertError &ece) {
			EditX->Text = (String)CursorPosition->x;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TimgWindow::EditYKeyPress(TObject *Sender, char &Key)
{
	if('0'<=Key && Key<='9' || Key==8)
	{
		EditY->ReadOnly = false;
	}
	else
	{
		EditY->ReadOnly = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TimgWindow::EditYChange(TObject *Sender)
{
	if(!EditX->Text.IsEmpty())
	{
		try {
			CursorPosition->y = EditY->Text.ToInt();
			ChangeColor();
		} catch (EConvertError &ece) {
			EditY->Text = (String)CursorPosition->y;
		}
	}
}
//---------------------------------------------------------------------------

void TimgWindow::ChangeColor()
{
	ImageSquare->Canvas->Brush->Color = ImagePicture->Canvas->Pixels[CursorPosition->x][CursorPosition->y];
	ImageSquare->Canvas->Rectangle(0, 0, ImageSquare->ClientWidth - 1, ImageSquare->ClientHeight - 1);

	LabelR->Caption = "R "+(String)GetRValue(ImageSquare->Canvas->Brush->Color);
	LabelG->Caption = "G "+(String)GetGValue(ImageSquare->Canvas->Brush->Color);
	LabelB->Caption = "B "+(String)GetGValue(ImageSquare->Canvas->Brush->Color);
}
//---------------------------------------------------------------------------
void __fastcall TimgWindow::FormResize(TObject *Sender)
{
	ScrollBoxPicture->Width = ClientWidth - 105;
	ScrollBoxPicture->Height = ClientHeight - 15;
	ScrollBoxPicsels->Height = ClientHeight - 15;
}
//---------------------------------------------------------------------------




