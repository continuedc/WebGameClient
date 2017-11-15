//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VersionDownloadForm.h"

#include <inifiles.hpp>
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;

#include "Unit3.h"

//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)    ,downloadThread(NULL)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm5::IdHTTP1WorkBegin(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCountMax)

{
	ProgressBar1->Max=AWorkCountMax;
	ProgressBar1->Min=0;
	ProgressBar1->Position=0;
    this->Caption = "�����������°汾��¼��...";
}
//---------------------------------------------------------------------------
void __fastcall TForm5::IdHTTP1Work(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCount)

{
	ProgressBar1->Position = ProgressBar1->Position + AWorkCount;
}

//---------------------------------------------------------------------------
void __fastcall TForm5::FormCreate(TObject *Sender)
{
	downloadThread = new MyThread;
	downloadThread->Start();
    return;
}
//---------------------------------------------------------------------------


void __fastcall MyThread::Execute()
	 {
        //   return;
		System::UnicodeString inipath =
		ChangeFileExt(ExtractFilePath(Application->ExeName),"conf.ini");
		TIniFile *ini = new TIniFile(inipath);
		System::UnicodeString verUrl = ini->ReadString("URL", "VersionFile", "");
		System::UnicodeString updateServer = ini->ReadString("URL", "UpdaterServer", "");
		System::UnicodeString currentVer = ini->ReadString("Version", "Current", "");
		 delete ini;
		if (verUrl.Length() == 0 ||
			currentVer.Length() == 0 ||
			updateServer.Length() == 0) {
            return;
		}

		TStringStream *myStream = new TStringStream();
		try
		{
			Form5->IdHTTP1->Get(updateServer + "/" + verUrl,myStream);
		}
		catch(...)
		{

			//ShowMessage("�ͻ��˸���ʧ�ܣ��޷���ȡ���°汾��Ϣ��");
			myStream->Free();
			return;
		}

		myStream->Seek((__int64)0, (TSeekOrigin)soBeginning);
		UnicodeString content = myStream->ReadString(myStream->Size);
		//ShowMessage(content);
		myStream->Free();
		wchar_t * pNewLine = NULL;
		for (wchar_t *p = content.begin(); p != content.end(); ++p) {
			if (*p == L'\n') {
				pNewLine = p;
				break;
			}
		}
		if (pNewLine == NULL) {
			return;
		}

		UnicodeString verstr(content.begin(), pNewLine - content.begin());
		if (verstr == currentVer) {
			//ShowMessage("��ǰ�汾�Ѿ�������");
			return;
		}
		UnicodeString setupurl(pNewLine + 1, content.end() - pNewLine - 1);
		setupurl = updateServer + "/" + setupurl;
		//ShowMessage("��ǰ��¼���������µ�\n���ȷ���������°桾" + setupurl + "��");
		Form3->Hide();
		Form5->Show();

		TMemoryStream *myStream2 = new TMemoryStream();
		try
		{
			Form5->IdHTTP1->Get(setupurl,myStream2);
		}
		catch(...)
		{

			//ShowMessage("�ͻ��˸���ʧ�ܣ�");
			myStream2->Free();
			return;
		}
		//ShowMessage("���سɹ���");
		myStream2->SaveToFile(
		ChangeFileExt(ExtractFilePath(Application->ExeName),"lastest_setup.exe"));

		std::system(".\\reinstall.bat ");
	 }
void __fastcall TForm5::FormDestroy(TObject *Sender)
{       stopDownloadIf();
}
//---------------------------------------------------------------------------
void __fastcall TForm5::stopDownloadIf()
{
      Form5->IdHTTP1->Disconnect();
		Form5->IdHTTP1->FreeOnRelease();
	   if (downloadThread != NULL) {
	   //ShowMessage("sn");
				 downloadThread->Terminate();
				 downloadThread->WaitFor();
				 downloadThread = NULL;
				 return;
	   }
}
//---------------------------------------------------------------------------


