//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <mshtml.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TForm1 *Form1;

#include "Unit2.h"

#include "Unit3.h"

#include "Unit6.h"

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)         ,realone(false)
{
   ini = new TIniFile(ChangeFileExt(ExtractFilePath(Application->ExeName),"conf.ini"));
   homepageUrl = ini->ReadString("URL", "Homepage", "www.baidu.com");
   enterGameUrl = ini->ReadString("URL", "EnterGame", "blank");
lbuttondown = false;
WebBrowser1->Navigate(homepageUrl);
//WebBrowser1->Hide();
moved = false;

//int windowLong = ::GetWindowLong(this->Handle, -16);
// ::SetWindowLong(this->Handle, -16, windowLong | 0x00080000);

/*
int windowLong = (GetWindowLong(new HandleRef(this, this->SafeHandle()), -16));
::
SetWindowLong(new HandleRef(this, this->SafeHandle()), -16, windowLong | WS_SYSMENU);
*/
   //SetWindowLong(this->Handle, GWL_EXSTYLE,
   //	GetWindowLong(this->Handle, GWL_EXSTYLE) | WS_EX_LAYERED)  ;


   //this->SetParent(Form3);
   //this->BringToFront();
   //this->Hide();

   //SetWindowLong(this->Handle, GWL_EXSTYLE,
   //	GetWindowLong(this->Handle, GWL_EXSTYLE) | WS_CLIPCHILDREN)  ;

   //ShowMessage("客户端更新失败！无法获取最新版本信息。");

   UnicodeString titlePath = ChangeFileExt(ExtractFilePath(Application->ExeName),"Resource\\Login.png");
		Image1->Picture->LoadFromFile(titlePath);
}
//---------------------------------------------------------------------------







void __fastcall TForm1::CloseButtonImageClick(TObject *Sender)
{
	if (IDOK == Application->MessageBox(L"要退出蛮荒战神吗？", L"退出确认", MB_OKCANCEL +
		MB_ICONINFORMATION)) {
	this->Close();
	Form6->Close();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MinimizeButtonImageClick(TObject *Sender)
{
	Form6->WindowState = wsMinimized;
	//Form3->Hide();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::WebBrowser1DocumentComplete(TObject *ASender, IDispatch * const pDisp,
		  const OleVariant &URL)
{

	IHTMLDocument2* Doc;
	IHTMLElement*   Tmp;
	IHTMLBodyElement   *Body;
	IHTMLStyle *Sty;
	WebBrowser1-> Document-> QueryInterface(IID_IHTMLDocument2,(void**)&Doc);
	if(Doc==NULL)
		return;
	Doc->get_body(&Tmp);
	if(Tmp==NULL)
		goto end1;
	Tmp->get_style(&Sty);
	if(Sty==NULL)
		goto end2;
	VARIANT w,h;
	w.vt = VT_I4;
	h.vt = VT_I4;
	w.lVal =    (long)WebBrowser1->Width;
	h.lVal =    (long)WebBrowser1->Height;
	Sty->put_width(w);
	Sty->put_height(h);
	Sty->put_overflow(L"hidden");
	Sty->put_border(L"none");     //设置无边框
	Tmp->QueryInterface(IID_IHTMLBodyElement,   (void**)&Body);
	if(Body==NULL)
		goto end3;
	Body->put_scroll(L"no");   //设置无滚动条
	Body->Release();
end3:
	Sty->Release();
end2:
	Tmp->Release();
end1:
	Doc->Release();
}
//---------------------------------------------------------------------------





void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	TForm::OnMouseDown(Sender, Button, Shift, X, Y);
                     lbuttondown = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormMouseLeave(TObject *Sender)
{
	lbuttondown = false;
}
//---------------------------------------------------------------------------


		 #include <fstream>



void __fastcall TForm1::WebBrowser1BeforeNavigate2(TObject *ASender, IDispatch * const pDisp,
		  const OleVariant &URL, const OleVariant &Flags, const OleVariant &TargetFrameName,
          const OleVariant &PostData, const OleVariant &Headers,
		  WordBool &Cancel)
{
	std::wstring url((wchar_t*)URL);
	if (url.find(enterGameUrl.w_str()) != url.npos && Form2 != NULL)
	 {
		 Cancel = true;
			//this->Hide();
			Application->ShowMainForm = false;
            Form2->imMined = true;
            /*
			RECT rect2;
			::GetWindowRect(::FindWindow(_T("Shell_TrayWNd"),   NULL),   &rect2);

			RECT rt;
			SystemParametersInfo(SPI_GETWORKAREA,   0,   &rt,   0);    // 获得工作区大小
			Form2->Show();


			Form2->Left = rt.left;
			Form2->Top = rt.top;
			Form2->Width = (rt.right - rt.left);
			Form2->Height = rect2.top;
			*/
			Form2->Show();
            //Form2->Center();
			Form2->FullScreen();
			//Form2->Normal();
            //Form2->OnResize(NULL);


			//Form2->Show();
			//Form2->WindowState = wsMaximized;
			Form2->WebBrowser1->Navigate(URL);
			Form2->WebBrowser1->FullScreen = true;

			//Application->MainFormOnTaskBar = true;

			this->Hide();

			//Form1->WindowState = wsNormal;
            //Application->BringToFront();

			//this->Visible = false;
	}
//std::wfstream fs("out.txt", std::ofstream::out | std::ofstream::app);
//fs << (wchar_t*)URL << "\n";
//fs.close();
	   //ShowMessage((wchar_t*)URL);
}

void __fastcall  TForm1::WndProc(Messages::TMessage& Message) {
		TForm::WndProc(Message); // Inherited implementation
	}

//---------------------------------------------------------------------------

void __fastcall TForm1::paintto3()
{
     Graphics::TBitmap *bmp = new Graphics::TBitmap;
	bmp->PixelFormat = pf32bit;
	//bmp->Width = this->Image1->Picture->Bitmap->Width;
	//bmp->Height = this->Image1->Picture->Bitmap->Height;
	bmp->Width = 1065;
	bmp->Height = 671;
    for(int y=0; y<bmp->Height; y++)
	{
		RGBQUAD *pixel = (RGBQUAD*)bmp->ScanLine[y];
		for(int x=0; x<bmp->Width; x++,pixel++)
		{
		   pixel->rgbRed =  0;
		   pixel->rgbGreen =  0;
		   pixel->rgbBlue =  0;
			pixel->rgbReserved = 0;
		}
	}

	bmp->Canvas->Draw(0, 0, this->Image1->Picture->Graphic);

	//this->PaintTo(bmp->Canvas->Handle, 0, 0);

	//DWORD dwExStyle = GetWindowLong(Handle, GWL_EXSTYLE);
	//if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED) SetWindowLong(Handle, GWL_EXSTYLE, dwExStyle|WS_EX_LAYERED);

  // 关联BMP数据到窗体
	 BLENDFUNCTION blend={
		 AC_SRC_OVER,0,0xFF,AC_SRC_ALPHA
	 };
	 POINT ptWinPos = {Left,Top};
	 SIZE sizeWindow = {Width, Height};
	 POINT ptSrc = {0, 0};
	 bmp->Canvas->Lock();
	 if (Form3 != NULL && Form3->Handle != NULL)     {
           UpdateLayeredWindow(Form3->Handle, 0, &ptWinPos,
			 &sizeWindow, bmp->Canvas->Handle , &ptSrc, RGB(0,0,0), &blend, ULW_ALPHA);
	 }
	 bmp->Canvas->Unlock();
	delete bmp;

	//this->Paint();

	this->BringToFront();
	this->SetZOrder(true);
	if (Form3 != NULL)       {
		 Form3->Cascade();

	HRGN rgnRect1 = CreateRectRgn(0, 0, 1065, 671);
	   HRGN rgnRect2 = CreateRectRgn(
		this->WebBrowser1->Left,this->WebBrowser1->Top,
		this->WebBrowser1->Left + this->WebBrowser1->Width,
		this->WebBrowser1->Top + this->WebBrowser1->Height);
	HRGN rgnCloseButton = CreateEllipticRgn(
		this->CloseButtonImage->Left, this->CloseButtonImage->Top,
		this->CloseButtonImage->Left + this->CloseButtonImage->Width,
		this->CloseButtonImage->Top + this->CloseButtonImage->Height);
	HRGN rgnMinButton = CreateEllipticRgn(
		this->MinimizeButtonImage->Left, this->MinimizeButtonImage->Top,
		this->MinimizeButtonImage->Left + this->MinimizeButtonImage->Width,
		this->MinimizeButtonImage->Top + this->MinimizeButtonImage->Height);

	   CombineRgn(rgnRect1,rgnRect1,rgnRect2,RGN_XOR);
	   CombineRgn(rgnRect1,rgnRect1,rgnMinButton,RGN_XOR);
	   CombineRgn(rgnRect1,rgnRect1,rgnCloseButton,RGN_XOR);

	   SetWindowRgn(Form3->Handle, rgnRect1,TRUE);

	   //Form3->Hide();
	}

	//this->SetZOrder(true);
}

void __fastcall TForm1::FormShow(TObject *Sender)
{
	if (Form2 != NULL && Form2->imMined)     {
		  //Form2->Show();
	}
	if (Form3 != NULL) {
		Form3->Show();
	}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::CloseButtonImageMouseEnter(TObject *Sender)
{
	   this->CloseButtonImage->Hide();
	 this->CloseButtonImageHL->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CloseButtonImageHLMouseLeave(TObject *Sender)
{
		  this->CloseButtonImage->Show();
	 this->CloseButtonImageHL->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MinimizeButtonImageMouseEnter(TObject *Sender)
{
		 this->MinimizeButtonImage->Hide();
	 this->MinimizeButtonImageHL->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MinimizeButtonImageHLMouseLeave(TObject *Sender)
{
		  this->MinimizeButtonImage->Show();
	 this->MinimizeButtonImageHL->Hide();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormPaint(TObject *Sender)
{
		paintto3();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
if (Form3 != NULL) {
	 //this->Top = Form3->Top;
	// this->Left = Form3->Left;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormHide(TObject *Sender)
{
	  Form3->Hide();
}
//---------------------------------------------------------------------------

