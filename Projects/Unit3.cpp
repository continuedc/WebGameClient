//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

TForm1 *realForm1 = NULL;


TForm1 *form1_test;

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
DWORD dwExStyle = GetWindowLong(Handle, GWL_EXSTYLE);
	if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
		SetWindowLong(Handle, GWL_EXSTYLE, dwExStyle|WS_EX_LAYERED);

		this->Show();
		//this->SetParent(Form1);

		if (Form1 != NULL)
		Form1->Show();
			 //realForm1 = new TForm1(this);
			 //realForm1->realone = true;
			// realForm1->Show();

            this->SetZOrder(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormShow(TObject *Sender)
{       if (Form1 != NULL)
	   Form1->Show();
	   //ShowMessage(
	   //	"ml3");

}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
		//ShowMessage(
		//"ml");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormPaint(TObject *Sender)
{
		//ShowMessage(
		//"ml2");
}
//---------------------------------------------------------------------------



void __fastcall TForm3::FormActivate(TObject *Sender)
{
	   //::SetActiveWindow(Form1->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormResize(TObject *Sender)
{
	 //Form1->Width = this->Width;
     //Form1->Height = this->Height;
}
//---------------------------------------------------------------------------


void __fastcall TForm3::FormHide(TObject *Sender)
{      if (Form1 != NULL)
      Form1->Hide();
}
//---------------------------------------------------------------------------

