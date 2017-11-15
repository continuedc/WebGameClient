//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SHDocVw_OCX.h"
#include <SHDocVw.hpp>
#include <Vcl.OleCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <sstream>
#include <inifiles.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TWebBrowser *WebBrowser1;
	TImage *Image1;
	TImage *CloseButtonImage;
	TImage *MinimizeButtonImage;
	TImage *CloseButtonImageHL;
	TImage *MinimizeButtonImageHL;
	TButton *Button1;
	TImageList *ImageList1;
	TImage *MinimizeButtonImageHL2;
	void __fastcall CloseButtonImageClick(TObject *Sender);
	void __fastcall MinimizeButtonImageClick(TObject *Sender);
	void __fastcall WebBrowser1DocumentComplete(TObject *ASender, IDispatch * const pDisp,
		  const OleVariant &URL);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormMouseLeave(TObject *Sender);
	void __fastcall WebBrowser1BeforeNavigate2(TObject *ASender, IDispatch * const pDisp,
          const OleVariant &URL, const OleVariant &Flags, const OleVariant &TargetFrameName,
          const OleVariant &PostData, const OleVariant &Headers,
          WordBool &Cancel);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CloseButtonImageMouseEnter(TObject *Sender);
	void __fastcall CloseButtonImageHLMouseLeave(TObject *Sender);
	void __fastcall MinimizeButtonImageMouseEnter(TObject *Sender);
	void __fastcall MinimizeButtonImageHLMouseLeave(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
private:	// User declarations

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

	void __fastcall paintto3();

	bool realone;

	bool lbuttondown;
	bool moved;

	TPoint lastPoint;

	TIniFile *ini;

	System::UnicodeString homepageUrl;
	System::UnicodeString enterGameUrl;

	void __fastcall WndProc(Messages::TMessage& Message);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

extern TForm1 *realForm1;
//---------------------------------------------------------------------------
#endif
