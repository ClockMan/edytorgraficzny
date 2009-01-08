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
}
//---------------------------------------------------------------------------

void TimgWindow::PaintImage(Graphics::TBitmap* picture)
{
		if (image!=NULL) delete image;
		image=new Graphics::TBitmap();
		image->Assign(picture);
		ImagePicture->Picture->Bitmap=image;
		ImagePicture->Canvas->Draw(0, 0, picture);
		LabelSize->Caption = IntToStr(image->Width)+ " × " + IntToStr(image->Height);
		ChangeColor();

	ScrollBoxPicture->BorderStyle = bsSingle;
}
//---------------------------------------------------------------------------

void TimgWindow::ClearImage()
{
	delete image;
	ImagePicture->Picture->Bitmap=NULL;
	image=NULL;
	LabelSize->Caption = "- × -";
    
	EditX->Text = "0";
	EditY->Text = "0";

	ImagePicture->ClientWidth = 1; ImagePicture->ClientHeight = 1;
	ImagePicture->Canvas->Rectangle(-1, -1, ImagePicture->ClientWidth + 2, ImagePicture->ClientHeight + 2);

	LabelR->Caption = "R ";
	LabelG->Caption = "G ";
	LabelB->Caption = "B ";
	ScrollBoxPicture->BorderStyle = bsNone;
}
//---------------------------------------------------------------------------

void __fastcall TimgWindow::ImagePictureMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
	if(Shift.Contains(ssLeft))
	{
		ScrollBoxPicture->HorzScrollBar->Position = PictureCDown->x - ((ImagePicture->Left + X) - CDown->x);    
		ScrollBoxPicture->VertScrollBar->Position = PictureCDown->y - ((ImagePicture->Top + Y) - CDown->y);
	}
	else if(!Shift.ToInt())
	{
		EditX->Text = (String)X;
		EditY->Text = (String)Y;
	}
}
//---------------------------------------------------------------------------

void __fastcall TimgWindow::FormCreate(TObject *Sender)
{
	CursorPosition = new TPoint; //mo¿na je przecie normalnie zadeklarowaæ, i siê stwo¿y, no ale niech zostanie z new
	CDown = new TPoint;
	PictureCDown = new TPoint;
	CursorPosition->x = 0;
	CursorPosition->y = 0;     
	CDown->x = 0;
	CDown->y = 0;
	PictureCDown->x = 0;
	PictureCDown->y = 0;
	ScrollBoxPicture->DoubleBuffered = true;
	ScrollBoxPicsels->DoubleBuffered = true;
	Panel->DoubleBuffered = true;
	DoubleBuffered =true;
	ClearImage();
}
//---------------------------------------------------------------------------

void __fastcall TimgWindow::FormDestroy(TObject *Sender)
{
	delete CursorPosition;
	delete CDown;
	delete PictureCDown;
	if (image) 	delete image;
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

	LabelR->Caption = "R " + (String)GetRValue(ImageSquare->Canvas->Brush->Color);
	LabelG->Caption = "G " + (String)GetGValue(ImageSquare->Canvas->Brush->Color);
	LabelB->Caption = "B " + (String)GetGValue(ImageSquare->Canvas->Brush->Color);
}
//---------------------------------------------------------------------------

void __fastcall TimgWindow::FormResize(TObject *Sender)
{
	ScrollBoxPicture->Width = ClientWidth - 105;
	ScrollBoxPicture->Height = ClientHeight - 15;
	ScrollBoxPicsels->Height = ClientHeight - 15;
}
//---------------------------------------------------------------------------

void __fastcall TimgWindow::ImagePictureMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	PictureCDown->x = ScrollBoxPicture->HorzScrollBar->Position;
	PictureCDown->y = ScrollBoxPicture->VertScrollBar->Position;
	CDown->x = ImagePicture->Left + X;
	CDown->y = ImagePicture->Top + Y;
}
//---------------------------------------------------------------------------

void __fastcall TimgWindow::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action=caHide;
}
//---------------------------------------------------------------------------
void __fastcall TimgWindow::CreateParams(Controls::TCreateParams &Params)
{
   TCustomForm::CreateParams(Params);
   Params.ExStyle=Params.ExStyle | WS_EX_APPWINDOW;
   Params.WndParent = GetDesktopWindow();
}
