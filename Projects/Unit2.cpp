//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

#include "Unit1.h"
#include "Unit6.h"

#define IDC_NC 1002

#include <mshtml.h>

#include<Wininet.h>
#pragma comment(lib,"WinInet.lib")

BOOL AddNotificationIcon(HWND hwnd)
{
	//Application->MainFormOnTaskBar = false;
	//Form6->Hide();
	NOTIFYICONDATA nid = {sizeof(nid)};
	nid.hWnd = hwnd;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.uID = IDC_NC;
	nid.uCallbackMessage = WMAPP_NOTIFYCALLBACK;
    nid.hIcon = Application->Icon->Handle;
	Shell_NotifyIcon(NIM_ADD, &nid);

	// NOTIFYICON_VERSION_4 is prefered
    nid.uVersion = NOTIFYICON_VERSION_4;
    return Shell_NotifyIcon(NIM_SETVERSION, &nid);
}

BOOL DeleteNotificationIcon(HWND hwnd)
{
//Application->MainFormOnTaskBar = true;
	NOTIFYICONDATA nid = {sizeof(nid)};
	nid.hWnd = hwnd;
	nid.uID = IDC_NC;
    return Shell_NotifyIcon(NIM_DELETE, &nid);
}

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)   ,imMined(false) ,fulls(true)
{
	//int windowLong = (GetWindowLong(Handle, -16));
   //	SetWindowLong(Handle, -16, windowLong | 0x00080000 | 0x20000);

   Width = 1000;
		Height = 700;

		Center();

		UnicodeString titlePath = ChangeFileExt(ExtractFilePath(Application->ExeName),"Resource\\Title.png");
		Image1->Picture->LoadFromFile(titlePath);

        XuanfuPic = this->XuanfuImage->Picture;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{      if (Form1 != NULL)
		Form1->Close();
	   if (Form6 != NULL)
		   Form6->Close();
}

void __fastcall TForm2::bossKeyRevert()
{
	   this->Show();
	   Form6->Show();
	   DeleteNotificationIcon(Handle);
}

   void __fastcall  TForm2::WndProc(Messages::TMessage& Message) {
   if (Message.Msg == WM_GETDLGCODE) {
                Message.Result = Message.Result | DLGC_WANTARROWS;
			 }

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
		}
		else if (Message.Msg == WM_GETDLGCODE) {
                Message.Result = Message.Result | DLGC_WANTARROWS;
			 }
		else if (Message.Msg == WM_HOTKEY) {
			int uVirtKey = Message.LParamHi;
			 switch (uVirtKey) {
				case VK_F10:
					if (this->Visible) {
						 BossKeyImageHLClick(NULL);
					}
					else {
						bossKeyRevert();
                    }
					 break;
				case VK_F11:
					if (GridPanel1->Height ==0) {
						  GridPanel1->Height = 30;
					}
					else {
					  GridPanel1->Height = 0;
					  FullScreen();
					  fulls = true;
					}
					this->Refresh();
					FormResize(NULL);
					break;
				case VK_F5:
					 //this->WebBrowser1->Refresh();
					 break;
			 }
		 }
		else if (Message.Msg == WMAPP_NOTIFYCALLBACK) {
			if(Message.LParamLo == WM_LBUTTONDBLCLK)
			{
				bossKeyRevert();
			}
			else if (Message.LParamLo == WM_RBUTTONDOWN) {
				TPoint p;
				GetCursorPos(&p);
				PopupMenu1->Popup(p.x, p.y);
			}
		}
	}

//---------------------------------------------------------------------------

void __fastcall TForm2::FormResize(TObject *Sender)
{
 Image1->Left = 0;
 Image1->Top = 0;

 this->TitleBarBGImage->Width =  this->ClientRect.Width();

 GridPanel1->Left = 0;
		GridPanel1->Top = 0;
	GridPanel1->Width = this->ClientRect.Width();

    this->WSStateBG->Top = 0;
	this->WSStateBG->Left = this->ClientRect.Right - this->WSStateBG->Width;

	int w = 28;
	int ww = 1;

	this->CloseImage->Left =   this->ClientRect.Right - w;

	this->NormalImage->Left = this->ClientRect.Right - w * 2 - ww;

	this->MinImage->Left = this->ClientRect.Right - w * 3 - ww - 1;

	this->CloseImageHL->Left =   this->ClientRect.Right - w;

	this->NormalImageHL->Left = this->ClientRect.Right - w * 2 - ww;

	this->MinImageHL->Left = this->ClientRect.Right - w * 3 - ww - 1;

	float r = this->ClientRect.Right;
	r -= WSStateBG->Width;

	r -= this->FSImage->Width;
	this->FSImage->Left = r;
    this->FSImageHL->Left = r;

	r -= this->BossKeyImage->Width;
	this->BossKeyImage->Left = r;
	this->BossKeyImageHL->Left = r;

	r -= this->ClearCacheImage->Width;
	this->ClearCacheImage->Left = r;
    this->ClearCacheImageHL->Left = r;

	  r -= this->RefreshImage->Width;
	this->RefreshImage->Left = r;
    this->RefreshImageHL->Left = r;

	r -= this->XuanfuImage->Width;
	this->XuanfuImage->Left = r;
    this->XuanfuImageHL->Left = r;

		WebBrowser1->Left = this->ClientRect.Left;
		 WebBrowser1->Top = this->GridPanel1->Height;
		 WebBrowser1->Width = this->ClientRect.Width();
		 WebBrowser1->Height = this->ClientRect.Height() - this->GridPanel1->Height;

}
//---------------------------------------------------------------------------






void __fastcall TForm2::FSImageClick(TObject *Sender)
{
              GridPanel1->Height = 0;
		  FormResize(NULL);
			//this->WindowState = wsMaximized;
            FullScreen();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RefreshImageClick(TObject *Sender)
{
	  this->WebBrowser1->Refresh();
}
//---------------------------------------------------------------------------




void __fastcall TForm2::XuanfuImageClick(TObject *Sender)
{
	   if (IDOK == Application->MessageBox(L"要离开当前游戏重新选择区服吗？", L"选服确认", MB_OKCANCEL +
		MB_ICONINFORMATION)) {
		   this->WebBrowser1->GoHome();
		   this->Hide();

		   Form1->Show();
		   Application->ShowMainForm = true;

		   Form2->imMined = false;
        }
}
//---------------------------------------------------------------------------


 void __fastcall TForm2::NormalImageClick(TObject *Sender)
 {
	   if (fulls){
		   Normal();
	   }
	   else {
		   FullScreen();
	   }
       fulls = !fulls;
 }

void __fastcall TForm2::CloseImageClick(TObject *Sender)
{
     this->Close();
	  Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::MinImageClick(TObject *Sender)
{
          Form6->WindowState =    wsMinimized;
	 //this->WindowState = wsMinimized;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CloseImageMouseEnter(TObject *Sender)
{
	 this->CloseImage->Hide();
	 this->CloseImageHL->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CloseImageHLMouseLeave(TObject *Sender)
{
	   this->CloseImage->Show();
	 this->CloseImageHL->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::MinImageMouseEnter(TObject *Sender)
{
		this->MinImage->Hide();
	 this->MinImageHL->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::MinImageHLMouseLeave(TObject *Sender)
{
		this->MinImage->Show();
	 this->MinImageHL->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::NormalImageMouseEnter(TObject *Sender)
{
	   this->NormalImage->Hide();
	 this->NormalImageHL->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::NormalImageHLMouseLeave(TObject *Sender)
{
		  this->NormalImage->Show();
	 this->NormalImageHL->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FSImageHLMouseLeave(TObject *Sender)
{
		 this->FSImage->Show();
	 this->FSImageHL->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FSImageMouseEnter(TObject *Sender)
{
		this->FSImage->Hide();
	 this->FSImageHL->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BossKeyImageMouseEnter(TObject *Sender)
{
	   this->BossKeyImage->Hide();
	 this->BossKeyImageHL->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BossKeyImageHLMouseLeave(TObject *Sender)
{
	 this->BossKeyImage->Show();
	 this->BossKeyImageHL->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ClearCacheImageMouseEnter(TObject *Sender)
{
		  this->ClearCacheImage->Hide();
	 this->ClearCacheImageHL->Show();
}
//---------------------------------------------------------------------------


void __fastcall TForm2::ClearCacheImageHLMouseLeave(TObject *Sender)
{
	   this->ClearCacheImage->Show();
	 this->ClearCacheImageHL->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RefreshImageMouseEnter(TObject *Sender)
{
		this->RefreshImage->Hide();
	 this->RefreshImageHL->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RefreshImageHLMouseLeave(TObject *Sender)
{
	   this->RefreshImage->Show();
	 this->RefreshImageHL->Hide();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TForm2::XuanfuImageHLMouseLeave(TObject *Sender)
{
	   this->XuanfuImage->Show();
	 this->XuanfuImageHL->Hide();
}
//---------------------------------------------------------------------------



void __fastcall TForm2::TitleBarBGImageMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	::ReleaseCapture();
    ::SendMessage(Handle, WM_NCLBUTTONDOWN, 0x2, 0);
}
//---------------------------------------------------------------------------


void __fastcall TForm2::BossKeyImageHLClick(TObject *Sender)
{
	 //
Form6->Hide();
this->Hide();

AddNotificationIcon(Handle);
}
//---------------------------------------------------------------------------

void ClearInternetCache()
{
	DWORD dwNeeded = 0;
	FindFirstUrlCacheEntry(NULL, NULL, &dwNeeded);

	if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
	unsigned char *buffer = new unsigned char[dwNeeded];
	try
	{
	LPINTERNET_CACHE_ENTRY_INFO lpicei =
	reinterpret_cast<LPINTERNET_CACHE_ENTRY_INFO>(buffer);
	HANDLE HFind = FindFirstUrlCacheEntry(NULL, lpicei, &dwNeeded);
	DeleteUrlCacheEntry(lpicei->lpszSourceUrlName);

	bool no_more_files = false;
	while (!no_more_files)
	{
	if (FindNextUrlCacheEntry(HFind, lpicei, &dwNeeded))
	{
        int isCookie = lpicei->CacheEntryType & COOKIE_CACHE_ENTRY;
	if (isCookie == 0) {
	   DeleteUrlCacheEntry(lpicei->lpszSourceUrlName);
	}
	}
	else switch (GetLastError())
	{
	case ERROR_INSUFFICIENT_BUFFER:
	{
	delete [] buffer;
	buffer = new unsigned char[dwNeeded];
	lpicei = reinterpret_cast<LPINTERNET_CACHE_ENTRY_INFO>(buffer);
	break;
	}
	default:
	{
	no_more_files = true;
	break;
	}
	}
	}
	FindCloseUrlCache(HFind);
	}
	catch (...)
	{
	delete [] buffer;
	}
	delete [] buffer;
	}

    ShowMessage("清理成功！");
}

void __fastcall TForm2::ClearCacheImageHLClick(TObject *Sender)
{
	ClearInternetCache();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormShow(TObject *Sender)
{
	  //Application->MainFormOnTaskBar = false;
      this->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::MenuItem2Click(TObject *Sender)
{
    this->Close();
}
//---------------------------------------------------------------------------



void __fastcall TForm2::MenuItem1Click(TObject *Sender)
{
     ClearInternetCache();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{
	 this->bossKeyID = GlobalAddAtom(L"MyHotKey") - 0xC000;
	 RegisterHotKey(Handle, this->bossKeyID, 0, VK_F10);


	 this->FSKeyID = GlobalAddAtom(L"MyHotKey2") - 0xC000;
	 RegisterHotKey(Handle, this->FSKeyID, 0, VK_F11);

	 //this->RefreshKeyID = GlobalAddAtom(L"MyHotKey3") - 0xC000;
	 //RegisterHotKey(Handle, this->RefreshKeyID, 0, VK_F5);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormDestroy(TObject *Sender)
{
     DeleteNotificationIcon(Handle);
}
//---------------------------------------------------------------------------


void __fastcall TForm2::XuanfuImageMouseLeave(TObject *Sender)
{
	 //TPicture *p = this->XuanfuImage->Picture;
 /*
TMemoryStream *s = new TMemoryStream();
s->Seek((__int64)0, (TSeekOrigin)soBeginning);
   XuanfuPic->SaveToStream(s) ;
   this->XuanfuImage->Picture->LoadFromStream(s);
   delete s;

 this->XuanfuImage->Refresh();
 */

 //this->XuanfuImage->Show();
  //	 this->XuanfuImageHL->Hide();
}

void __fastcall TForm2::XuanfuImageMouseEnter(TObject *Sender)
{
  /*
   TMemoryStream *s = new TMemoryStream();
   s->Seek((__int64)0, (TSeekOrigin)soBeginning);
   this->XuanfuImageHL->Picture->SaveToStream(s)  ;
   this->XuanfuImage->Picture->LoadFromStream(s);
     delete s;

  this->XuanfuImage->Refresh();
  */

   this->XuanfuImage->Hide();
	 this->XuanfuImageHL->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	   if (Key == VK_BACK) {
			//ShowMessage("fdsafs");
	   }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	if (Key == VK_BACK) {
			//ShowMessage("fdsafs");
	   }
}
//---------------------------------------------------------------------------

#include <vector>

unsigned stdkeys_arr[] = {VK_TAB, VK_RETURN, VK_BACK};
unsigned extkeys_arr[] =  {VK_DELETE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN};

std::vector<unsigned> StdKeys(stdkeys_arr, stdkeys_arr + 3);
std::vector<unsigned> ExtKeys(extkeys_arr, extkeys_arr + 5);
unsigned fExtended = 0x01000000;


bool inKeys(unsigned k, const std::vector<unsigned> &keys) {
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == k) {
			 return true;
		}
	}
	return false;
}

void __fastcall TForm2::ApplicationEvents1Message(tagMSG &Msg, bool &Handled)
{
	if (::IsChild(WebBrowser1->Handle, Msg.hwnd)) {
		 Handled = ::IsDialogMessageW(WebBrowser1->Handle, &Msg) == true;
		 if (Handled && !WebBrowser1->Busy) {
			  if (Msg.message >= WM_KEYFIRST && Msg.message <= WM_KEYLAST &&
				(inKeys(Msg.wParam, StdKeys) || GetKeyState(VK_CONTROL) < 0 ||
				(inKeys(Msg.wParam, ExtKeys) && (Msg.lParam & fExtended == fExtended)))) {
				  IOleInPlaceActiveObject *o;
				  this->WebBrowser1->Application->QueryInterface(IID_IOleInPlaceActiveObject, (void**)&o);
				  Handled = o->TranslateAcceleratorW(&Msg) == S_OK;
				  if (!Handled) {
					  Handled = true;
					  TranslateMessage(&Msg);
						DispatchMessage(&Msg);
				  }
			  }
		 }
	}
}
//---------------------------------------------------------------------------

