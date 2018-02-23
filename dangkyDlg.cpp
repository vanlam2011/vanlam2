#include "stdafx.h"
#include "dangkyDlg.h"
#include "login.h"
#include "afxdialogex.h"
#include <afxdb.h>
#include "loginDlg.h"
extern CloginDlg login;


// taikhoanDlg ƒ_ƒCƒAƒƒO

IMPLEMENT_DYNAMIC(dangkyDlg, CDialog)

dangkyDlg::dangkyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DANGKY, pParent)
{

}

dangkyDlg::~dangkyDlg()
{
}

void dangkyDlg::DoDataExchange(CDataExchange* pDX)
{

	DDX_Control(pDX, IDC_USER, control_user);
	DDX_Control(pDX, IDC_PASS, control_pass);
	DDX_Control(pDX, IDC_MAIL, control_mail);
	DDX_Control(pDX, IDC_FIRSTNAME, control_fisrtname);
	DDX_Control(pDX, IDC_LASTNAME, control_lastname);
	DDX_Control(pDX, IDC_EMAIL, control_email);
}
BEGIN_MESSAGE_MAP(dangkyDlg, CDialog)

	ON_BN_CLICKED(IDOK, &dangkyDlg::OnBnClickedOk)
END_MESSAGE_MAP()
BOOL dangkyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定




	return TRUE;
}

void dangkyDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	CString phone, name, pass,mail,fname,lname;
	control_fisrtname.GetWindowText(fname);
	control_lastname.GetWindowText(lname);
	control_email.GetWindowText(mail);
	control_user.GetWindowText(name);
	control_pass.GetWindowText(pass);
	control_mail.GetWindowText(phone);
	if (name != "" && pass != "" && phone != ""&&fname!=""&&lname!=""&&mail!="") {
		char *str;
		
		str = (char*)memchr(mail, '@', mail.GetLength());
		if (str == "") {
			MessageBox(_T("メールアドレス入力してください"), _T("info"));
		}
		else {
			int n = 0;
			CDatabase db;
			db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
			CRecordset rd(&db);
			CString sql, sql1, ss;
			sql.Format(_T("select name from account1 where name = '%s'"),name);
			rd.Open(CRecordset::forwardOnly, sql);
			while (!rd.IsEOF()) {
				rd.GetFieldValue((short)0, ss);
				n++;
				rd.MoveNext();

			}
			rd.Close();
			if (n != 0) {
				MessageBox(_T("既に存在します"), _T("info"));
			}
			else {
				int i = -1;
				sql.Format(_T("select max(id) from account1"));

				rd.Open(CRecordset::forwardOnly, sql);
				if (rd.IsEOF() != LB_ERR) {
					rd.GetFieldValue((short)0, ss);
					if (ss != "") {
						i = _tstoi(ss);
					}
				}
				rd.Close();
				i++;
				sql1.Format(_T("INSERT into account1(id,user_name,last_name,email,name,mk,phone) values (%d,'%s','%s','%s','%s','%s','%s');"), i, fname, lname, mail, name, pass, phone);
				db.ExecuteSQL(sql1);
				db.Close();
				MessageBox(_T("sucess!!"), _T("info"));
				// TODO: ここにコントロール通知ハンドラー コードを追加します。
				CDialog::OnOK();
			}
		}

	}
	else {
		MessageBox(_T("全部入力してください"), _T("info"));
	}

}
