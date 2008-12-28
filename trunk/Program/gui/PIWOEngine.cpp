#include <vcl.h>
#pragma hdrstop
#include "PIWOEngine.h"
#include "BlockValidateInputElement.h"
#include "BlockValidateOutputElement.h"
#pragma package(smart_init)

__fastcall PIWOEngine::PIWOEngine(TComponent* Owner)
	: TPanel(Owner)
{
  plugins=NULL;
  area=new PIWOMAINCLASSTYPE(this);
  area->Parent=this;
  area->Align=alClient;
  area->BorderStyle=bsNone;
  area->OnClick=onThisClick;
  //DoubleBuffered=true;
  //area->DoubleBuffered=true;
  this->BorderStyle=bsNone;
  this->BevelOuter=bvLowered;
  this->BevelWidth=2;
  this->OnClick=onThisClick;
  selectedConnection=NULL;
  OnInformation=NULL;
  OnWarrning=NULL;
  OnError=NULL;
  selectedOutputBlock=NULL;
  selectedInputBlock=NULL;
  selectedInput=NULL;
  selectedOutput=NULL;
  Color=clMedGray;
  OnRunAllProgress=NULL;
  OnRunProgress=NULL;
  OnCompileProgress=NULL;
}


__fastcall PIWOEngine::~PIWOEngine()
{
  while(connections.size()>0)
  {
	  delete connections[0];
	  connections.erase(connections.begin());
  }

  while(blocks.size()>0)
  {
	  delete blocks[0];
	  blocks.erase(blocks.begin());
  }
  delete area;
}


bool PIWOEngine::AddBlock(const AnsiString &name)
{
   FunctionDLL *fun=plugins->getFunction(name);
   if (fun==NULL) return false;
   //szukamy numerku.
   int number=0;
   bool busy;
   do{
	++number;
	busy=false;
	for(unsigned int i=0;i<blocks.size();++i)
	{
		if (blocks[i]->nameOfBlock==name && blocks[i]->numberOfBlock==number) {
		  busy=true;
		  break;
		}
	}
   } while (busy);

   VisualBlock *newBlock=new VisualBlock(this->area);
   newBlock->Parent=this->area;
   newBlock->nameOfBlock=name;
   newBlock->numberOfBlock=number;
   newBlock->setTitle(name+" #"+IntToStr(number));
   newBlock->setConfigButtonGlyph(fun->picture);
   newBlock->Hint=fun->fullName;
   if (fun->description!="") newBlock->Hint+="\n"+fun->description;
   newBlock->Left=10;
   newBlock->Top=10;
   fun->validate(&(newBlock->block));
   newBlock->updateVisualComponents();
   newBlock->Visible=true;
   newBlock->OnConfigClick=OnVisualBlockConfigClick;
   newBlock->OnVisualInputSelected=OnVisualBlockInputSelected;
   newBlock->OnVisualOutputSelected=OnVisualBlockOutputSelected;
   newBlock->OnVInputHistory=OnVisualBlockInputHistoryClick;
   newBlock->OnVOutputHistory=OnVisualBlockOutputHistoryClick;
   newBlock->OnBlockMove=OnVisualBlockMove;
   newBlock->OnUnselect=OnVisualBlockUnselect;
   newBlock->OnSelect=OnVisualBlockSelect;
   newBlock->OnSelectAdd=OnVisualBlockSelectAdd;
   blocks.push_back(newBlock);
   if (OnInformation!=NULL) OnInformation(this, "Dodano blok: "+name+" #"+IntToStr(number));
   return true;
}

void PIWOEngine::validateBlock(VisualBlock *block, bool updateInputConnections)
{
  FunctionDLL *fun=plugins->getFunction(block->nameOfBlock);

  //zapami�ta� po��czenia przychodz�ce, wychodz�ce, kod b��du, opis, typ danych, wska�nik wej�cia, wyj�cia
  vector<BlockValidateInputElement*> inputHistory;
  vector<BlockValidateOutputElement*> outputHistory;

  if (updateInputConnections)
  {
	 for(unsigned int i=0;i<block->block.input.size();++i)
	 {
			BlockValidateInputElement *ih=new BlockValidateInputElement();
			ih->connection=NULL;
			//szukamy po��czenia
			for(unsigned int j=0;j<connections.size();++j)
			{
				if (connections[j]->inBlock==block&&connections[j]->input==&(block->block.input[i]))
				{
					ih->connection=connections[j];
					break;
				}
			}
			if (ih->connection!=NULL)
						{
							ih->input=&(block->block.input[i]);
							ih->errorDescription=block->block.input[i].getErrorDescription();
							ih->errorCode=block->block.input[i].getErrorCode();
							inputHistory.push_back(ih);
						} else delete ih;
	 }
  }

	 for(unsigned int i=0;i<block->block.output.size();++i)
	 {
		BlockValidateOutputElement *oh=new BlockValidateOutputElement();
		oh->output=&(block->block.output[i]);
		oh->errorDescription=block->block.output[i].getErrorDescription();
		oh->errorCode=block->block.output[i].getErrorCode();
		oh->type=block->block.output[i].getOutputType();
		for(unsigned int j=0;j<connections.size();++j)
		{
			if (connections[j]->outBlock==block&&connections[j]->output==&(block->block.output[i]))
			{
			   oh->connections.push_back(connections[j]);
			}
		}
		outputHistory.push_back(oh);
	 }

   int ret=fun->validate(&(block->block));
   //sprawdzi� czy jakie� po��czenia nie zosta�y "wyjebane"
   //i potem zaktualizowac je...
   
   if (updateInputConnections)
   {
	  while(inputHistory.size()>0)
	  {
		  //sprawdzic czy jest na nowej liscie
		  BlockInput* in=NULL;

		  for(unsigned int j=0;j<block->block.input.size();++j)
		  {
			  if (&(block->block.input[j])==inputHistory[0]->input)
			  {
				 in=&(block->block.input[j]);
				 break;
			  }
		  }

		 if (in!=NULL)
		 {
			//jest wej�cie
			//jest co� pod��czonego, je�li code, i error si� nie zgadzaj� to aktualizujemy
			//if (in->getErrorCode()!=inputHistory[0]->input->getErrorCode()||in->getErrorDescription()!=inputHistory[0]->input->getErrorDescription())
			{
				inputHistory[0]->connection->update();
			}
		 }
		 else
		 {
			 //niema wej�cia, wywalamy go razem z po��czeniami
			 for(unsigned int j=0;j<connections.size();++j)
			 {
				 if (connections[j]==inputHistory[0]->connection)
				 {
					delete connections[j];
					connections.erase(connections.begin()+j);
				 }
			 }
		 }

		 delete inputHistory[0];
		 inputHistory.erase(inputHistory.begin());
	  }
   }

   if (ret!=0) block->updateVisualComponents(); //aktualizujemy wy�wietlanie tylko gdy zmieni� si� kod.
   block->updateHistory();

   //aktualizacja wyj��, tu ju� b�dzie przejebane :P
   //sprawdzamy kt�re wyj�cia si� zmieni�y, i wrzucamy na wyj�cie je
   //1 - spisa� bloczki
   //2 - zaktualizowa� typ
   //3 - zvalidowa� bloczki
   //4 - zaktualizowac ponownie po��czenia
   //lecimy tylko do tych bloczk�w w kt�rych zmieni� si� typ
   vector<VisualBlock*> toCheck;
   while(outputHistory.size()>0)
   {
	  //sprawdzamy czy jest w spisie
	  BlockOutput* out=NULL;
		  for(unsigned int j=0;j<block->block.output.size();++j)
		  {
			  if (&(block->block.output[j])==outputHistory[0]->output)
			  {
				 out=&(block->block.output[j]);
				 break;
			  }
		  }

	   if (out!=NULL)
		 {
			//wyj�cie nie zosta�o usuni�te...
			if (out->getOutputType()!=outputHistory[0]->type)
			{
			   //typ si� zmieni�, pentla po po��czeniach
			   for(unsigned int g=0;g<outputHistory[0]->connections.size();++g)
			   {
					//sprawdzamy czy nowey typ jest na li�cie
					bool isTypeOnList=false;
					for(unsigned int i=0;i<outputHistory[0]->connections[g]->input->allowedTypes.size();++i)
					{
						if (outputHistory[0]->connections[g]->input->allowedTypes[i]==out->getOutputType()) {
						   isTypeOnList=true;
						   break;
						}
					}


					if (isTypeOnList)
					{
					  //typ jest na li�cie, aktualizujemy typ i dodajemy blok do validacji
					  outputHistory[0]->connections[g]->input->connect(out->getOutputType());
					  outputHistory[0]->connections[g]->update();
					}
					else
					{
					   //wi�c od��czamy blok i przeprowadzamy validatcje po��czenia i bloku
					   outputHistory[0]->connections[g]->input->disconnect();
					   outputHistory[0]->connections[g]->inBlock->updateVisualComponents();
					   outputHistory[0]->connections[g]->update();
					}

					bool isOnList=false;
					for(unsigned int k=0;k<toCheck.size();++k)
					{
						if (toCheck[k]==outputHistory[0]->connections[g]->inBlock) {
						   isOnList=true;
						   break;
						}
					}
					if (!isOnList) toCheck.push_back(outputHistory[0]->connections[g]->inBlock);
			   }
			}
			else
			{
				//typy s� takie same, sprawdzamy kody b��d�w tylko
				if (out->getErrorCode()!=outputHistory[0]->output->getErrorCode()||out->getErrorDescription()!=outputHistory[0]->output->getErrorDescription())
				{
				   //zmieni� si� kod b��du, aktualizujemy po��czenia
				   for(unsigned int g=0;g<outputHistory[0]->connections.size();++g)
				   {
					  outputHistory[0]->connections[g]->update();
				   }
				}
			}
		 }
		 else
		 {
			for(unsigned int k=0;k<outputHistory[0]->connections.size();++k)
			{
			 for(unsigned int j=0;j<connections.size();++j)
			 {
				 if (connections[j]==outputHistory[0]->connections[k])
				 {
					connections[j]->input->disconnect();
					toCheck.push_back(connections[j]->inBlock);
					delete connections[j];
					connections.erase(connections.begin()+j);
				 }
			 }
			}
		 }

		 delete outputHistory[0];
		 outputHistory.erase(outputHistory.begin());
   }

  for(unsigned int i=0;i<toCheck.size();++i)
  {
	validateBlock(toCheck[i], true);
  }
}

void PIWOEngine::OnVisualBlockConfigClick(TObject* Sender)
{
   VisualBlock *block=(VisualBlock*)Sender;
   unsigned int rev=block->block.getConfig()->getRevision();
   FunctionDLL *fun=plugins->getFunction(block->nameOfBlock);
   if (!fun->showConfig(Application,&(block->block)))
   {
	  if (OnWarrning!=NULL) OnWarrning(this, "Blok: "+block->getTitle()+" nieposiada okna konfiguracji");
	  MessageBox(0,"Ten bloczek niema konfiguracji",("Konfiguracja bloczka: "+block->getTitle()).c_str(),MB_OK);
	  return;
   }
   if (rev!=block->block.getConfig()->getRevision())
   {
	 if (OnInformation!=NULL) OnInformation(this, "Zmodyfikowanao konfiguracje bloku: "+block->getTitle());
	 validateBlock(block);
   }
}

bool PIWOEngine::MakeConnection(VisualBlock* outputBlock, VisualOutput* output, VisualBlock* inputBlock, VisualInput* input)
{
	//sprawdzamy czy mo�na pod��czy�.

	bool canBe=false;
	for(unsigned int i=0;i<input->input->allowedTypes.size();++i)
	{
		if (output->output->getOutputType()==input->input->allowedTypes[i])
		{
			canBe=true;
			break;
		}
	}

	//zablokowanie cyklicznych po��cze�
	if (outputBlock==inputBlock) {
	   if (OnError!=NULL) OnError(this, "Po��czenia cyklycznie s� zabronione");
		return false;
	}

	vector<VisualBlock*> iwasThere;
	vector<VisualBlock*> toCheck;
	toCheck.push_back(inputBlock);
	while(toCheck.size()>0)
	{
		//sprawdzamy wszystkie po��czenia wychodz�ce z tego bloku, dodajemy je na liste
		for(unsigned int i=0;i<connections.size();++i)
		{
			if (connections[i]->outBlock==toCheck[0])
			{
				if (connections[i]->inBlock==outputBlock) {
				  //cykliczne
				  if (OnError!=NULL) OnError(this, "Po��czenia cyklycznie s� zabronione");
				  return false;
				}

				bool isOnList=false;
				for(unsigned int j=0;!isOnList&&j<toCheck.size();++j)
				{
				   if (toCheck[j]==connections[i]->inBlock) isOnList=true;
				}
				for(unsigned int j=0;!isOnList&&j<iwasThere.size();++j)
				{
				   if (iwasThere[j]==connections[i]->inBlock) isOnList=true;
				}

				if (!isOnList) toCheck.push_back(connections[i]->inBlock);
			}
		}

		iwasThere.push_back(toCheck[0]);
		toCheck.erase(toCheck.begin());
	}

	if (!canBe)
	{
		if (OnError!=NULL) OnError(this, "Po��czenie: "+outputBlock->getTitle()+"("+output->output->getDescription()+") -> "+inputBlock->getTitle()+"("+input->input->getDescription()+") niemo�e zosta� zrealizowane, pruba pod��czenia nieobs�ugiwanego typu danych");
		return false;
	}

	//ustawiamy po��czenie :P
	Connection* con=new Connection(this->area);
	con->input=input->input;
	con->inBlock=inputBlock;
	con->output=output->output;
	con->outBlock=outputBlock;
	con->OnConnectionSelected=OnConnectionSelect;
	input->input->connect(output->output->getOutputType());
	//aktualizacja bloku input
	con->draw();
	connections.push_back(con);
	validateBlock(inputBlock);
	con->update();
	return true;
}

void PIWOEngine::OnVisualBlockInputSelected(VisualInput* input,  TObject* Sender)
{
   //connection selecting
   Connection* con=getConnectionTo(input);
   if (con!=NULL)
   {
	 if (OnError!=NULL) OnError(this, "Po��czenie do tego wej�cia ju� istnieje "+con->outBlock->getTitle()+"("+con->output->getDescription()+") -> "+con->inBlock->getTitle()+"("+con->input->getDescription()+")");
	 return;
   }

	selectedInputBlock=(VisualBlock*)Sender;
	selectedInput=input;

   if (selectedOutputBlock!=NULL && selectedOutput!=NULL)
   {
	 if (MakeConnection(selectedOutputBlock,selectedOutput,selectedInputBlock,selectedInput))
	 {
		selectedOutputBlock=NULL;
		selectedInputBlock=NULL;
		selectedInput=NULL;
		selectedOutput=NULL;
	 }
   }
}

void PIWOEngine::OnVisualBlockOutputSelected(VisualOutput* output,  TObject* Sender)
{
	selectedOutputBlock=(VisualBlock*)Sender;
	selectedOutput=output;

   if (selectedInputBlock!=NULL && selectedInput!=NULL)
   {
	 if (MakeConnection(selectedOutputBlock,selectedOutput,selectedInputBlock,selectedInput))
	 {
		selectedOutputBlock=NULL;
		selectedInputBlock=NULL;
		selectedInput=NULL;
		selectedOutput=NULL;
	 }
   }
}

void PIWOEngine::OnVisualBlockInputHistoryClick(VisualInput* input, vectorBlockHistory* history)
{

}

void PIWOEngine::OnVisualBlockOutputHistoryClick(VisualOutput* output, vectorBlockHistory* history)
{

}

void PIWOEngine::OnVisualBlockMove(TObject* Sender, bool moveAll, int x, int y)
{
  //przes�wanie blok�w, jesli moveAll jest ustawione to przesuwamy all zaznaczone bloki, a jesli nie to tylko ten do ktorego dostalismy wska�nik (tzn dostajamy conneciton)
  if (moveAll)
  {
	for(unsigned int i=0;i<selectedBlocks.size();++i)
	{
	   if (selectedBlocks[i]!=Sender)
	   {
		 selectedBlocks[i]->Left+=x;
		 selectedBlocks[i]->Top+=y;
       }
    }
  }

  if (!moveAll)
  {
	  for(unsigned int i=0;i<connections.size();++i)
	  {
		 if (connections[i]->inBlock==Sender||connections[i]->outBlock==Sender) {
		   connections[i]->draw();
		 }
	  }
  }
  else
  {
	  for(unsigned int i=0;i<connections.size();++i)
	  {
		 if (connections[i]->inBlock==Sender||connections[i]->outBlock==Sender) {
		   connections[i]->draw();
		 }
	  }

	  for(unsigned int i=0;i<selectedBlocks.size();++i)
	  {
			for(unsigned int j=0;j<connections.size();++j)
			{
				if (connections[j]->inBlock==selectedBlocks[i]||connections[j]->outBlock==selectedBlocks[i]) {
					connections[j]->draw();
				}
			}
	  }
  }
}

void PIWOEngine::OnVisualBlockUnselect(TObject* Sender)
{
   //odznaczamy ten blok
   VisualBlock *block=(VisualBlock*)Sender;
   for(unsigned int i=0;i<selectedBlocks.size();++i)
   {
	   if (selectedBlocks[i]==block)
	   {
		  selectedBlocks.erase(selectedBlocks.begin()+i);
		  break;
	   }
   }
   if (OnInformation!=NULL) OnInformation(this, "Odznaczono blok: "+block->getTitle());
   block->setSelected(false);
}

void PIWOEngine::OnVisualBlockSelect(TObject* Sender)
{
   while(selectedBlocks.size()>0)
   {
	  if (selectedBlocks[0]!=Sender) {
	   if (OnInformation!=NULL) OnInformation(this, "Odznaczono blok: "+selectedBlocks[0]->getTitle());
	   selectedBlocks[0]->setSelected(false);
	  }
	  selectedBlocks.erase(selectedBlocks.begin());
   }

   for(unsigned int i=0;i<connections.size();++i)
   {
	   if (connections[i]->inBlock==Sender||connections[i]->outBlock==Sender)
			 connections[i]->BringToFront();
   }

   if (OnInformation!=NULL) OnInformation(this, "Zaznaczono blok: "+((VisualBlock*)Sender)->getTitle());
   selectedBlocks.push_back((VisualBlock*)Sender);
}

void PIWOEngine::OnVisualBlockSelectAdd(TObject* Sender)
{
   for(unsigned int i=0;i<selectedBlocks.size();++i)
   {
	  if (selectedBlocks[i]==Sender) return;
   }

   for(unsigned int i=0;i<connections.size();++i)
   {
	   if (connections[i]->inBlock==Sender||connections[i]->outBlock==Sender)
			 connections[i]->BringToFront();
   }

   if (OnInformation!=NULL) OnInformation(this, "Zaznaczono blok: "+((VisualBlock*)Sender)->getTitle());
   selectedBlocks.push_back((VisualBlock*)Sender);
}

void __fastcall PIWOEngine::onThisClick(TObject* Sender)
{
   UnselectAllBlocks();
   UnselectSelectedConnection();
}

void PIWOEngine::OnConnectionSelect(void* Sender)
{
   if (selectedConnection!=NULL)
   {
	  if (OnInformation!=NULL) OnInformation(this, "Odznaczono po��czenie: "+selectedConnection->outBlock->getTitle()+"("+selectedConnection->output->getDescription()+") -> "+selectedConnection->inBlock->getTitle()+"("+selectedConnection->input->getDescription()+")");
	  selectedConnection->setSelected(false);
   }
   selectedConnection=(Connection*)Sender;
   selectedConnection->BringToFront();
   if (OnInformation!=NULL) OnInformation(this, "Zaznaczono po��czenie: "+selectedConnection->outBlock->getTitle()+"("+selectedConnection->output->getDescription()+") -> "+selectedConnection->inBlock->getTitle()+"("+selectedConnection->input->getDescription()+")");
}

Connection* PIWOEngine::getConnectionTo(VisualInput* input)
{
   for(unsigned int i=0;i<connections.size();++i)
	   if (connections[i]->input==input->input) return connections[i];
   return NULL;
}

bool PIWOEngine::DeleteBlock(const AnsiString &fullName)
{
	VisualBlock* toDelete=NULL;
	for(unsigned int i=0;i<blocks.size();++i)
	{
		if (blocks[i]->getTitle()==fullName) {
		   toDelete=blocks[i];
		   blocks.erase(blocks.begin()+i);
		   break;
		}
	}
	if (toDelete==NULL) return false;

    for(unsigned int j=0;j<connections.size();++j)
	{
		   if (connections[j]->inBlock==toDelete)
		   {
			  connections[j]->inBlock=NULL;
		   }
		   else
		   if (connections[j]->outBlock==toDelete)
		   {
			  connections[j]->outBlock=NULL;
		   }
	}

   vector<VisualBlock*> blocksToCheck;
   for(unsigned int j=0;j<connections.size();++j)
   {
	  //sprawdzamy wej�cia

	  if (connections[j]->inBlock!=NULL && connections[j]->outBlock==NULL)
	  {
		 connections[j]->input->disconnect();
		 bool isOnList=false;
		 for(unsigned int i=0;i<blocksToCheck.size();++i)
		 {
			 if (blocksToCheck[i]==connections[j]->inBlock)
			 {
				isOnList=true;
				break;
			 }
		 }
		 if (!isOnList) blocksToCheck.push_back(connections[j]->inBlock);
	  }
	  //sprawdzamy wyj�cia
	  if (connections[j]->outBlock!=NULL && connections[j]->inBlock==NULL)
	  {
		 bool isOnList=false;
		 for(unsigned int i=0;i<blocksToCheck.size();++i)
		 {
			 if (blocksToCheck[i]==connections[j]->outBlock)
			 {
				isOnList=true;
				break;
			 }
		 }
		 if (!isOnList) blocksToCheck.push_back(connections[j]->outBlock);
	  }

	  //usuwamy po��czenie
	  if (selectedConnection==connections[j]) selectedConnection=NULL;
	  delete connections[j];
	  connections.erase(connections.begin()+j);
	  --j;
   }

   //sprawdzamy co wywalone..
   for(unsigned int i=0;i<blocksToCheck.size();++i)
   {
	   validateBlock(blocksToCheck[i]);
   }
   return true;
}

bool PIWOEngine::DeleteSelectedBlocks()
{
   if (selectedBlocks.size()==0) return false;

   for(unsigned int i=0;i<selectedBlocks.size();++i)
   {
	   //zaznaczam po��czenia do usuni�cia
	   for(unsigned int j=0;j<connections.size();++j)
	   {
		   if (connections[j]->inBlock==selectedBlocks[i])
		   {
			  connections[j]->inBlock=NULL;
		   }
		   else
		   if (connections[j]->outBlock==selectedBlocks[i])
		   {
			  connections[j]->outBlock=NULL;
		   }
	   }
	   delete selectedBlocks[i];
   }
   selectedBlocks.clear();

   vector<VisualBlock*> blocksToCheck;
   for(unsigned int j=0;j<connections.size();++j)
   {
	  //sprawdzamy wej�cia

	  if (connections[j]->inBlock!=NULL && connections[j]->outBlock==NULL)
	  {
		 connections[j]->input->disconnect();
		 bool isOnList=false;
		 for(unsigned int i=0;i<blocksToCheck.size();++i)
		 {
			 if (blocksToCheck[i]==connections[j]->inBlock)
			 {
				isOnList=true;
				break;
			 }
		 }
		 if (!isOnList) blocksToCheck.push_back(connections[j]->inBlock);
	  }
	  //sprawdzamy wyj�cia
	  if (connections[j]->outBlock!=NULL && connections[j]->inBlock==NULL)
	  {
		 bool isOnList=false;
		 for(unsigned int i=0;i<blocksToCheck.size();++i)
		 {
			 if (blocksToCheck[i]==connections[j]->outBlock)
			 {
				isOnList=true;
				break;
			 }
		 }
		 if (!isOnList) blocksToCheck.push_back(connections[j]->outBlock);
	  }

	  //usuwamy po��czenie
	  if (selectedConnection==connections[j]) selectedConnection=NULL;
	  delete connections[j];
	  connections.erase(connections.begin()+j);
	  --j;
   }

   //sprawdzamy co wywalone..
   for(unsigned int i=0;i<blocksToCheck.size();++i)
   {
	   validateBlock(blocksToCheck[i]);
   }
   return true;
}

bool PIWOEngine::DeleteAllBlocks()
{
   if (blocks.size()==0) return false;
   while(connections.size()>0)
   {
	   delete connections[0];
	   connections.erase(connections.begin());
   }
   while(blocks.size()>0)
   {
	   delete blocks[0];
	   blocks.erase(blocks.begin());
   }
   return true;
}

void PIWOEngine::SelectAllBlocks()
{
  for(unsigned int i=0;i<blocks.size();++i)
  {
	if (!blocks[i]->isSelected())
	{
	   selectedBlocks.push_back(blocks[i]);
	   blocks[i]->setSelected(true);
	}
  }
}

void PIWOEngine::InvertBlockSelection()
{
  vector<VisualBlock*> newSelections;
  for(unsigned int i=0;i<blocks.size();++i)
  {
	if (!blocks[i]->isSelected())
	{
	   newSelections.push_back(blocks[i]);
	   blocks[i]->setSelected(true);
	}
	else
	{
	   blocks[i]->setSelected(false);
    }
  }
  selectedBlocks=newSelections;
}

void PIWOEngine::UnselectAllBlocks()
{
   while(selectedBlocks.size()>0)
   {
	  selectedBlocks[0]->setSelected(false);
	  if (OnInformation!=NULL) OnInformation(this, "Odznaczono blok: "+selectedBlocks[0]->getTitle());
	  selectedBlocks.erase(selectedBlocks.begin());
   }
}

bool PIWOEngine::DeleteSelectedConnection()
{
   if (selectedConnection!=NULL)
   {
	  for(unsigned int i=0;i<connections.size();++i)
	  {
		if (connections[i]==selectedConnection)
		{
		   selectedConnection->input->disconnect();
		   VisualBlock* block=selectedConnection->inBlock;
		   delete connections[i];
		   connections.erase(connections.begin()+i);
		   validateBlock(block);
		   break;
		}
	  }
	  selectedConnection=NULL;
	  return true;
   } else return false;
}

bool PIWOEngine::DeleteAllConnections()
{
   if (connections.size()==0) return false;
   vector<VisualBlock*> list;
   while(connections.size()>0)
   {
	   bool isOnListToValidate=false;
	   for(unsigned int i=0;i<list.size();++i)
	   {
		  if (list[i]==connections[0]->inBlock)
		  {
			 isOnListToValidate=true;
			 break;
		  }
	   }

	   if (!isOnListToValidate) list.push_back(connections[0]->inBlock);
	   delete connections[0];
	   connections.erase(connections.begin());
   }
   selectedConnection=NULL;
   for(unsigned int i=0;i<list.size();++i)
   {
	   validateBlock(list[i]);
   }
   return true;
}

void PIWOEngine::UnselectSelectedConnection()
{
   if (selectedConnection!=NULL)
   {
	  selectedConnection->setSelected(false);
	  selectedConnection=NULL;
   }
}

void PIWOEngine::CancelCustomizationOnSelectedConnections()
{
   if (selectedConnection!=NULL)
   {
	  selectedConnection->setCustomizeFalse();
   }
}

void PIWOEngine::CancelCustomizationOnAllConnections()
{
	for(unsigned int i=0;i<connections.size();++i)
	{
	   connections[i]->setCustomizeFalse();
    }
}

bool PIWOEngine::run()
{
	//uruchamiamy wszystkie bloki, ale korzystamy z zasady :D
	// - niema �adnego b��du
	// - je�li jest wpis w histori to go u�ywamy.
	// - je�li niema wpisu w histori to oznacza to i� historia zostanie pomini�ta w wszystkich kolejnych blokach
}

bool PIWOEngine::runAll()
{
	//uruchamiamy wszystkie bloki, ale korzystamy z zasady :D
	// - niema �adnego b��du
	// - do histori tylko zapisujemy, usuwaj�c stare warto�ci.
	//przetwarzanie requencyjne od ko�ca (zawsze zaczynamy od blok�w nieposiadaj�cych wyj�cia lub z niedpo��czonym wyj�ciem)
	//sprawdzamy poprawno�c wynikowego typu - dll typ�w :(
}

bool PIWOEngine::compile()
{

}

bool PIWOEngine::runBlock(VisualBlock* block, bool fastRun, bool *useHistory)
{
	/*
		Algorytm:
		* za�o�enie: aby bloczek by� przetworzony musi by� przynajmniej jedno wej�cie z kodem 0 gdy bloczek posiada wej�cia i przynajmniej jedno wyj�cie z kodem 0 gdy bloczek posiada wyj�cia.
		* za�o�enie: wej�cia do kt�rych pod��czony typ nie spe�nia wymaga� jest uznawane jako wej�cie z kodem 1 i nie pod��czonym blokiem. [zaktualizowa� w wyswietlaniu bloku i po��czenia, aby nie widzia� blok po��czenia]
		* za�o�enie: uruchamiamy wszystkie bloki jakie si� da.
		- uruchamiamy bloki od kt�rych jeste�my zale�ni (requencyjnie) - je�li nie zosta�y jeszcze uruchomione):
			- sprawdzamy czy blok by� ju� uruchomiony, je�li nie to uruchamiamy
			- pobieramy dane z wyj�� bloku, je�li dane s� r�wne NULL to znaczy �e blok nie zosta� uruchomiony - przerywamy
			- kopiujemy dane na wej�cie
		- sprawdzamy czy bloczke mo�e by� uruchomiony, ma conajmniej jedno poprawne wej�cie i jedno poprawne wyj�cie [o ile ma], jak nie to wywalamy warrning
		- je�li fastRun jest ustawione na true i useHistory=true i mamy dane w histori to je uzywamy, je�li niemamy danych w histori to upewniamy si� �e histora niemo�e zosta� u�yta.
		- uruchamiamy blok
		- sprawdzamy kod b��du
		- sprawdzamy dane wyj�ciowe bloczka
		- ustawiamy dane na wyj�ciach o ile s� poprawne, jak nie to nie ustawiamy
		- przeprowadzamy validacje bloczka
		- zwracamy true
    */

	//sprawdzamy dane wejsciowe.
	for(unsigned int i=0;i<block->block.input.size();++i)
	{
		if (!block->block.input[i].getConnectedType().IsEmpty())
		{
		   //znajdujemy po��czenie odpowiedizalne za to wej�cie
		   Connection *con=NULL;
		   for(unsigned int j=0;j<connections.size();++j)
		   {
			   if (connections[j]->input==&block->block.input[i])
			   {
				  con=connections[j];
				  break;
			   }
		   }

		   if (con!=NULL)
		   {
			  //jest po��czenie, sprawdzamy czy na danym bloku s� dane
			  TypeConfig *data=con->output->getObject();
			  if (data!=NULL)
			  {
				  //mamy dane wi�c je kopiujemy.
				  block->block.input[i].setObject(*data);
			  }
			  else
			  {
				  //niema danych :(
				  //sprawdzamy czy blok by� uruchamiany
				  if (con->outBlock->runned) {
					  //by� uruchamiany, trudno, wywalamy warrning i przerywamy wykonywanie
					  if (OnWarrning!=NULL) {
						 OnWarrning(this, "Brak wymaganych danych na wej�ciu do bloku: "+block->getTitle());
					  }
					  block->setStatusColor(clYellow);
					  return false;
				  }
				  else
				  {
					  //uruchamiamy blok :D
					  if (!runBlock(con->outBlock, fastRun, useHistory))
					  {
						  //blok nie zosta� uruchomiony, ale pech
						  if (OnWarrning!=NULL) {
							OnWarrning(this, "Blok nadrz�dny "+con->outBlock->getTitle()+" dla "+block->getTitle()+" nie zosta� uruchomiony - brak wymaganych danych wej�ciowych");
						  }
						  block->setStatusColor(clYellow);
						  return false;
					  }
					  else
					  {
						  //a jednak si� uruchomi�, ale fux :d, sprawdzamy czy mamy te dane
                          TypeConfig *data=con->output->getObject();
						  if (data!=NULL)
						  {
								//mamy dane wi�c je kopiujemy.
								block->block.input[i].setObject(*data);
						  }
						  else
						  {
							  //by� uruchamiany, trudno, wywalamy warrning i przerywamy wykonywanie
							 if (OnWarrning!=NULL) {
								OnWarrning(this, "Brak wymaganych danych na wej�ciu do bloku: "+block->getTitle());
							 }
							 block->setStatusColor(clYellow);
							 return false;
						  }
					  }
				  }
              }
		   }
		   else
		   {
			  //niema po��czenia ? jakim cudem
			  if (OnWarrning!=NULL) {
				 OnWarrning(this, "Brak wymaganych danych na wej�ciu do bloku (nie znale�iono po��czenia): "+block->getTitle());
			  }
			  block->setStatusColor(clYellow);
			  return false;
           }
		}
	}

	//Mamy ju� dane wej�ciowe (fuxem)
	//nieb�de tu sprawdza� danych wyj�ciowych :d
	//teraz sprawdzimy historie i uruchomimy bloczek D:
}
