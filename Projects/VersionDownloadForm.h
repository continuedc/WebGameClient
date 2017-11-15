//---------------------------------------------------------------------------

#ifndef VersionDownloadFormH
#define VersionDownloadFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Vcl.ComCtrls.hpp>

class MyThread :public TThread
{
public:
	 __fastcall MyThread()
	 :TThread(true)
	 {

	 }

	 void __fastcall Execute();
};

//---------------------------------------------------------------------------
class TForm5 : public TForm
{
__published:	// IDE-managed Components
	TIdHTTP *IdHTTP1;
	TProgressBar *ProgressBar1;
	void __fastcall IdHTTP1WorkBegin(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCountMax);
	void __fastcall IdHTTP1Work(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCount);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm5(TComponent* Owner);

	MyThread *downloadThread;

    void __fastcall stopDownloadIf();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm5 *Form5;
//---------------------------------------------------------------------------
#endif
