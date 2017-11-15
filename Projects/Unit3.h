//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "Unit1.h"
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);

	void __fastcall WndProc(Messages::TMessage& Message) {
		TForm::WndProc(Message); // Inherited implementation
		if (Message.Msg == WM_NCHITTEST) {
			TWMNCHitTest& oMsg = reinterpret_cast<TWMNCHitTest&>(Message);
			TPoint oPoint(oMsg.XPos, oMsg.YPos); // Screen coordinates
			oPoint = ScreenToClient(oPoint); // Now in form-local coordinates
			// It's in the title bar (caption) if it's in a rectangle at the top of the form
			oMsg.Result = HTCAPTION;
		}
		else if (Message.Msg == WM_WINDOWPOSCHANGING) {
			 TWMWindowPosChanged &oMsg = reinterpret_cast<TWMWindowPosChanged&>(Message);
			 if ((oMsg.WindowPos->flags & SWP_NOMOVE) == 0) {
				  Form1->Top = oMsg.WindowPos->y;
			 Form1->Left = oMsg.WindowPos->x;
			 }
		}
	}
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
