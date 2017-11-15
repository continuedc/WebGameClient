//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm7 *Form7;
//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
	: TForm(Owner)
{

this->SetZOrder(false);
this->Cascade();
this->Cascade();
this->Cascade();
this->Cascade();
this->Cascade();
this->Enabled = false;
}
//---------------------------------------------------------------------------
