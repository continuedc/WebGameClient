//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <SHDocVw.hpp>
#include <Vcl.OleCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.AppEvnts.hpp>

UINT const WMAPP_NOTIFYCALLBACK = WM_APP + 1;

//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TImage *WSStateBG;
	TPanel *GridPanel1;
	TImage *FSImage;
	TImage *BossKeyImage;
	TImage *ClearCacheImage;
	TImage *RefreshImage;
	TImage *XuanfuImage;
	TImage *TitleBarBGImage;
	TImageList *ImageList1;
	TImage *CloseImage;
	TImage *MinImage;
	TImage *NormalImage;
	TImage *BossKeyImageHL;
	TImage *ClearCacheImageHL;
	TImage *CloseImageHL;
	TImage *FSImageHL;
	TImage *MinImageHL;
	TImage *NormalImageHL;
	TImage *RefreshImageHL;
	TImage *XuanfuImageHL;
	TPopupMenu *PopupMenu1;
	TMenuItem *MenuItem1;
	TMenuItem *MenuItem2;
	TMenuItem *N1;
	TWebBrowser *WebBrowser1;
	TApplicationEvents *ApplicationEvents1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FSImageClick(TObject *Sender);
	void __fastcall RefreshImageClick(TObject *Sender);
	void __fastcall XuanfuImageClick(TObject *Sender);
	void __fastcall CloseImageClick(TObject *Sender);
	void __fastcall MinImageClick(TObject *Sender);
    void __fastcall NormalImageClick(TObject *Sender);
	void __fastcall CloseImageMouseEnter(TObject *Sender);
	void __fastcall CloseImageHLMouseLeave(TObject *Sender);
	void __fastcall MinImageMouseEnter(TObject *Sender);
	void __fastcall MinImageHLMouseLeave(TObject *Sender);
	void __fastcall NormalImageMouseEnter(TObject *Sender);
	void __fastcall NormalImageHLMouseLeave(TObject *Sender);
	void __fastcall FSImageHLMouseLeave(TObject *Sender);
	void __fastcall FSImageMouseEnter(TObject *Sender);
	void __fastcall BossKeyImageMouseEnter(TObject *Sender);
	void __fastcall BossKeyImageHLMouseLeave(TObject *Sender);
	void __fastcall ClearCacheImageMouseEnter(TObject *Sender);
	void __fastcall ClearCacheImageHLMouseLeave(TObject *Sender);
	void __fastcall RefreshImageMouseEnter(TObject *Sender);
	void __fastcall RefreshImageHLMouseLeave(TObject *Sender);
	void __fastcall XuanfuImageMouseEnter(TObject *Sender);
	void __fastcall XuanfuImageHLMouseLeave(TObject *Sender);
	void __fastcall TitleBarBGImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall BossKeyImageHLClick(TObject *Sender);
	void __fastcall ClearCacheImageHLClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall MenuItem2Click(TObject *Sender);
	void __fastcall MenuItem1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall XuanfuImageMouseLeave(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);

private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);

	void __fastcall WndProc(Messages::TMessage& Message);

	bool imMined;

	bool fulls;

	int lastPosX, lastPosY;

	int bossKeyID;

	int FSKeyID;

	int RefreshKeyID;

	TPicture *XuanfuPic;

	void __fastcall bossKeyRevert();

	void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params)
	{
		TForm::CreateParams(Params);
		//Params.Style |= (WS_MINIMIZEBOX | WS_SYSMENU);
	}

	void __fastcall FullScreen()
	{
	lastPosX = Left;
		lastPosY = Top;

		RECT rect2;
		::GetWindowRect(::FindWindow(_T("Shell_TrayWNd"),   NULL),   &rect2);
		RECT rt;
		SystemParametersInfo(SPI_GETWORKAREA,   0,   &rt,   0);    // 获得工作区大小
		Left = rt.left;
		Top = rt.top;
		Width = (rt.right - rt.left);
		Height = rect2.top;
		OnResize(NULL);
	}

	void __fastcall Normal()
	{
	 	Width = 1000;
		Height = 700;
         RECT rect2;
		::GetWindowRect(::FindWindow(_T("Shell_TrayWNd"),   NULL),   &rect2);
		RECT rt;
		SystemParametersInfo(SPI_GETWORKAREA,   0,   &rt,   0);    // 获得工作区大小
		Left = lastPosX;
		Top = lastPosY;
		OnResize(NULL);
	}

	void __fastcall Center()
	{
        RECT rect2;
		::GetWindowRect(::FindWindow(_T("Shell_TrayWNd"),   NULL),   &rect2);
		RECT rt;
		SystemParametersInfo(SPI_GETWORKAREA,   0,   &rt,   0);    // 获得工作区大小
		lastPosX = (rt.right - rt.left) / 2 - Width / 2;
		lastPosY = (rt.bottom - rt.top) / 2 - Height / 2;

		Left = lastPosX;
		Top =   lastPosY;
	}
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
