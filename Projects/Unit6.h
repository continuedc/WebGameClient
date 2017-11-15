//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "Unit2.h"
#include "Unit1.h"

//---------------------------------------------------------------------------
class TForm6 : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TForm6(TComponent* Owner);

	void __fastcall  WndProc(Messages::TMessage& Message)
	{
		  TForm::WndProc(Message);

		if (Message.Msg == WM_KEYUP) {
			  if (Message.WParam == VK_F5) {
				   if (Form2 != NULL && Form2->Visible == true) {
					   Form2->WebBrowser1->Refresh();
				   }

				   if (Form1 != NULL && Form1->Visible == true) {
					   Form1->WebBrowser1->Refresh();
				   }
			  }
		}
    }
};
//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
