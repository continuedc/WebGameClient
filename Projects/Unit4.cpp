//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Unit1.h"
#include "Unit3.h"

TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormPaint(TObject *Sender)
{
	 if (realForm1 != NULL) {
        ShowMessage("ÖØ»Ø");
		realForm1->paintto3();
		Form3->Cascade();
	 }
}
//---------------------------------------------------------------------------
