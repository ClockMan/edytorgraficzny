#include <vcl.h>
#pragma hdrstop
#include "Connection.h"
#pragma package(smart_init)

Connection::Connection(TWinControl* owner)
{
  fowner=owner;
  status=0;
  selected=false;
  input=NULL;
  output=NULL;
  inBlock=NULL;
  outBlock=NULL;
  OnConnectionSelected=NULL;
}

Connection::~Connection()
{
	while(lines.size()>0)
	{
		delete lines[0];
		lines.erase(lines.begin());   
	}
}

bool Connection::connectionOk(Position &in, Position &out)
{
   //sprawdziæ czy linie idealnie do siebie dochodz¹ i co najwa¿niejsze czy czy docieraj¹ co celu
   //sprawdzamy koñce lini
  TPoint first;
  TPoint last;
  switch (in.direction) {
	case 0 :
	case 1 : if (in.xy.x!=lines[4]->getPoint2().x||in.xy.y!=lines[4]->getPoint2().y) return false;
			last=lines[4]->getPoint1();
			break;
  default: return false;
  }

  switch (out.direction) {
	case 2 :
	case 3 : if (out.xy.x!=lines[0]->getPoint1().x||out.xy.y!=lines[0]->getPoint1().y) return false;
			last=lines[0]->getPoint2();
			break;
  default: return false;
  }

  //koñce s¹ ok, teraz sprawdzamy po³¹czenia
  int i=1;
  while((first.x!=last.x||first.y!=last.y)&&(i<4))
  {
	  if (lines[i]->Visible) {
		 if(lines[i]->getPoint1().x==first.x&&lines[i]->getPoint1().y==first.y)
		 {
		   first=lines[i]->getPoint2();
		 }
		 else
		 if(lines[i]->getPoint2().x==first.x&&lines[i]->getPoint2().y==first.y)
		 {
		   first=lines[i]->getPoint1();
		 }
		 else return false;
	  }
	  ++i;
  }
  return (first.x==last.x&&first.y==last.y);
}

bool Connection::connectionOk()
{
   if ((input==NULL)||(output==NULL)||(inBlock==NULL)||(outBlock==NULL)) return false;
   Position in=inBlock->getInputPosition(input);
   Position out=inBlock->getOutputPosition(output);
   if (lines.size()<5) return false;
   return connectionOk(in, out);
}

void Connection::redraw(Position &in, Position &out)
{
   //ustawiamy pocz¹tek i koniec, zostn¹ tylko 3 linie do modyfikacji
   TPoint p1, p2;
   int move=(abs(in.xy.x-out.xy.x)<20)?int(abs(in.xy.x-out.xy.x)/2):10;
   if (in.direction==0)
   {
	  p1.x=in.xy.x-move;
	  p1.y=in.xy.y;
   }

   if (in.direction==1)
   {
	  p1.x=in.xy.x;
	  p1.y=in.xy.y-10;
   }

   if (out.direction==3)
   {
	  p2.x=out.xy.x;
	  p2.y=out.xy.y+10;
   }

   if (out.direction==2)
   {
	  p2.x=out.xy.x+move;
	  p2.y=out.xy.y;
   }
   
   lines[0]->CanBeMoved=false;
   lines[4]->CanBeMoved=false;
   //problem znaleœæ linie poziom¹ która bêdzie w stanie po³¹czyæ wejœcie i wyjœcie., pozycja y niemo¿e przechodziæ ani przez blok A ni przez blok B
   int y;
   if (in.xy.x>out.xy.x)
   {
	  //jest ok nic nie przeszkadza
	  y=out.xy.y;
   }
   else
   {
	  //zawadzaj¹ obydwa bloki, y = 20px powyzej bloku A, 20 px ponizej bloku A
	  if (outBlock->Top-20<inBlock->Top-20 || outBlock->Top-20>inBlock->Top+inBlock->Height+20)
	  {
		 y=outBlock->Top-20;
	  } else
	  if ((outBlock->Top+outBlock->Height+20<inBlock->Top-20) || (outBlock->Top+outBlock->Height+20>inBlock->Top+inBlock->Height+20))
	  {
		 y=outBlock->Top+outBlock->Height+20;
	  } else
	  if ((inBlock->Top-20<outBlock->Top-20) || (inBlock->Top-20>outBlock->Top+outBlock->Height+20))
	  {
		 y=inBlock->Top-20;
	  } else
	  if ((inBlock->Top+inBlock->Height+20<outBlock->Top-20) || (inBlock->Top+inBlock->Height+20>outBlock->Top+outBlock->Height+20))
	  {
		 y=inBlock->Top+inBlock->Height+20;
	  }  else y=outBlock->Top-20;
   }

   y+=lines[2]->Resize;
   //znamy wysokoœc lini poziomej, rysujemy pionow¹ lew¹.
   lines[0]->setXY(out.xy.x, out.xy.y, p2.x+lines[1]->Resize, p2.y);
   lines[1]->setXY(p2.x+lines[1]->Resize, p2.y, p2.x+lines[1]->Resize, y);
   lines[3]->setXY(p1.x+lines[3]->Resize, p1.y, p1.x+lines[3]->Resize, y);
   lines[4]->setXY(in.xy.x, in.xy.y, p1.x+lines[3]->Resize, p1.y);
   lines[2]->setXY(p2.x+lines[1]->Resize, y, p1.x+lines[3]->Resize, y);
}

bool Connection::draw()
{
   if ((input==NULL)||(output==NULL)||(inBlock==NULL)||(outBlock==NULL)) return false;
   //@TODO Obs³uge po³¹czeñ z górnymi wejœciami i dolnymi wyjœciami, narazie wrzucamy ¿e takie po³¹czenie jest b³êdne
   Position in=inBlock->getInputPosition(input);
   if (in.direction!=0&&in.direction!=2) return false;
   Position out=outBlock->getOutputPosition(output);
   if (out.direction!=0&&out.direction!=2) return false;

   if (lines.size()==5)
   {
	  //update
	  if (connectionOk(in, out))
	  {
		 return true;
	  }
	  else
	  {
		redraw(in, out);
		return true;
	  }
   }
   else
   {
      	while(lines.size()>0)
		{
			delete lines[0];
			lines.erase(lines.begin());
		}

        for(int i=0;i<5;i++)
		{
			Line *line=new Line(fowner, false);
			line->Parent=fowner;
			line->OnConnectionSelectRequest=OnConnectionSelectedRequest;
			line->OnLineMove=OnLineMove;
			line->OnConnectionResetRequest=OnConnectionResetRequest;
			lines.push_back(line);
		}
		redraw(in, out);
		return true;
   }
}

bool Connection::update()
{
   //update danych w zale¿noœci od wejœæ - opis, kolor
   //generujemy nowy status
   if (input->getErrorCode()>1||output->getErrorCode()>1)
	status=2;
	else
   if (input->getErrorCode()==1||output->getErrorCode()==1)
	status=1;
	else
	status=0;

	AnsiString str;
	// komentarz:
	typeOfConnection=output->getOutputType();
	str+=outBlock->getTitle()+" - "+output->getDescription()+": "+output->getOutputType();
	if (output->getErrorCode()!=0) {
		if (output->getErrorDescription().IsEmpty())
		  str+=" (Error:"+IntToStr(output->getErrorCode())+")";
		else
		  str+=" ("+output->getErrorDescription()+")";
	}
	str+="\n -> \n";
	str+=inBlock->getTitle()+" - "+input->getDescription()+": [";
	bool is=false;
	for(unsigned int i=0;i<input->allowedTypes.size();++i)
	{
	  str+=input->allowedTypes[i];
	  if (i<input->allowedTypes.size()-1) str+=",";
	  if (input->allowedTypes[i]==output->getOutputType()) is=true;
	}
	str+="]";
	if (!is) status=2;

	if (input->getErrorCode()!=0) {
		if (input->getErrorDescription()!="")
		  str+=" (Error:"+IntToStr(input->getErrorCode())+")";
		else
		  str+=" ("+input->getErrorDescription()+")";
	}

    if (selected)
	  {
		 for(unsigned int i=0;i<lines.size();i++)
		 {
			 if (status==2) lines[i]->Color=ConnectionErrorSelectedColor;else
			 if (status==1) lines[i]->Color=ConnectionWarrningSelectedColor;else
			 lines[i]->Color=ConnectionOkSelectedColor;
		 }
	  }
	  else
	  {
		 for(unsigned int i=0;i<lines.size();i++)
		 {
			 if (status==2) lines[i]->Color=ConnectionErrorNormalColor;else
			 if (status==1) lines[i]->Color=ConnectionWarrningNormalColor;else
			 lines[i]->Color=ConnectionOkNormalColor;
		 }
	  }

   for(unsigned int i=0;i<lines.size();i++)
   {
		lines[i]->Hint=str;
   }
   return true;
}

void Connection::BringToFront()
{
   for(unsigned int i=0;i<lines.size();i++)
   {
	  lines[i]->BringToFront();
   }
}

void Connection::setSelected(bool s)
{
   if (s!=selected)
   {
	  if (s)
	  {
		 for(unsigned int i=0;i<lines.size();i++)
		 {
			 if (status==2) lines[i]->Color=ConnectionErrorSelectedColor;else
			 if (status==1) lines[i]->Color=ConnectionWarrningSelectedColor;else
			 lines[i]->Color=ConnectionOkSelectedColor;
		 }
	  }
	  else
	  {
		 for(unsigned int i=0;i<lines.size();i++)
		 {
			 if (status==2) lines[i]->Color=ConnectionErrorNormalColor;else
			 if (status==1) lines[i]->Color=ConnectionWarrningNormalColor;else
			 lines[i]->Color=ConnectionOkNormalColor;
		 }
	  }
	  selected=s;
   }
}

void Connection::OnLineMove(TObject* Sender)
{
   draw();
}

void Connection::OnConnectionSelectedRequest(TObject* Sender)
{
   BringToFront();
   if (!selected)
   {
	  setSelected(true);
	  if (OnConnectionSelected!=NULL) OnConnectionSelected(this);
   }
}

void Connection::OnConnectionResetRequest(TObject* Sender)
{
   for(unsigned int i=0;i<lines.size();i++)
   {
		lines[i]->Resize=0;
   }
   draw();
}


bool Connection::getCustomizeState()
{
   for(unsigned int i=0;i<lines.size();i++)
   {
	   if (lines[i]->Resize!=0) return true;
   }
   return false;
}

void Connection::setCustomizeFalse()
{
   for(unsigned int i=0;i<lines.size();i++)
   {
		lines[i]->Resize=0;
   }
   draw();
}


