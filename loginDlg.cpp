
// loginDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "login.h"
#include "loginDlg.h"
#include "afxdialogex.h"
#include <afxdb.h>
#include "tietkiemDlg.h"
#include "chitieuDlg.h";
#include "loanDlg.h";
#include "taikhoanDlg.h"
#include "themDlg.h"
#include "thunhapDlg.h"

thunhapDlg thunhap;
tietkiemDlg tietkiem;
chitieuDlg chitieu;
loanDlg loan;
taikhoanDlg taikhoan;
themDlg them;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CloginDlg ダイアログ



CloginDlg::CloginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LOGIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CloginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NAME, control_ten);
	DDX_Control(pDX, IDC_PASS, control_pass);
	DDX_Control(pDX, IDC_BUTTON1, control_login);
	DDX_Control(pDX, IDC_BUTTON2, control_register);
	DDX_Control(pDX, IDC_EDIT1, control_thongbao);
}

BEGIN_MESSAGE_MAP(CloginDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CloginDlg::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CloginDlg::OnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON2, &CloginDlg::OnClickedButton2)
END_MESSAGE_MAP()


// CloginDlg メッセージ ハンドラー

BOOL CloginDlg::OnInitDialog()
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

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CloginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CloginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CloginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CloginDlg::OnClickedButton1()
{
	UpdateData(TRUE);
	CString str, str1, sql, user;
	control_ten.GetWindowText(str);
	control_pass.GetWindowText(str1);
	CDatabase db;
	try {
		db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
		CRecordset rd(&db);
		sql.Format(_T("select id from account1 where name='%s' and mk='%s'"), str, str1);
		rd.Open(CRecordset::forwardOnly, sql);
		rd.GetFieldValue((short)0, user);
		if (user != "") {
			user_id = _tstoi(user);
			
			this->ShowWindow(SW_HIDE);
			shouhi.user_id = user_id;

				// TODO: ここにコントロール通知ハンドラー コードを追加します。
			if (shouhi.DoModal() == IDOK) {

			}
			this->ShowWindow(SW_SHOW);
		}
		else
		{
			control_thongbao.SetWindowText(_T("アカウントが存在しないか、パスワードが間違っています"));
		}
		
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
	
}



void CloginDlg::OnClickedButton2()
{
	if (dangky.DoModal() == IDOK) {

	}
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
