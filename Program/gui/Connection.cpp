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
   //sprawdzi� czy linie idealnie do siebie dochodz� i co najwa�niejsze czy czy docieraj� co celu
   //sprawdzamy ko�ce lini
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

  //ko�ce s� ok, teraz sprawdzamy po��czenia
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

void Connection::RightOutputToLeftInput(Position &in, Position &out)
{
  //TODO
}

void Connection::update(Line* object)
{
   //TODO
}

bool Connection::update()
{
   if ((input==NULL)||(output==NULL)||(inBlock==NULL)||(outBlock==NULL)) return false;
   //@TODO Obs�uge po��cze� z g�rnymi wej�ciami i dolnymi wyj�ciami, narazie wrzucamy �e takie po��czenie jest b��dne
   Position in=inBlock->getInputPosition(input);
   if (in.direction!=0&&in.direction!=2) return false;
   Position out=inBlock->getOutputPosition(output);
   if (out.direction!=0&&out.direction!=2) return false;

   //inicjujemy linie je�li ich niemamy, potrzebne jest ich 5
   if (lines.size()!=5)
   {
      	while(lines.size()>0)
		{
			delete lines[0];
			lines.erase(lines.begin());
		}

		for(int i=0;i<5;i++)
		{
			Line *line=new Line(fowner, false);
			lines.push_back(line);
		}
   }

   //teraz najgorsze, rzeba rozpatrzy� kt�ry model pod��czenia b�dzie najlepiej pasowa� i go zastosowa� pami�taj�c o tym �e u�ytkownik mo�e nam miesza� w tym po��czeniu przesuwaj�c linie etc.
   //ograniczenia:
   // - d�ugo�� lini wystaj�cej z bloczka nie mo�e by� mniejsza ni� 15px.
   // - szeroko�� ka�dej lini wynosi 3 px.
   // - je�li musimy "omin�� bloczek" to omijamy go na odleg�o�ci 25px. (w naszym pzrypadku dotyczy to g�ownie do�u i g�ry)
   // @TODO

   if (in.xy.x-out.xy.x>0)
   {
	  //po��czenie out -> in, gdzie bloczek docelowy jest na prawo od bloczka �r�owego
	  RightOutputToLeftInput(in, out);
   }
   //@TODO
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
   update((Line*)(Sender));
}

void Connection::OnConnectionSelectedRequest(TObject* Sender)
{
   if (!selected)
   {
	  setSelected(true);
	  if (OnConnectionSelected!=NULL) OnConnectionSelected(this);
   }
}


