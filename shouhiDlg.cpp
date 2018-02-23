#include "stdafx.h"
#include "afxwin.h"
#include "shouhiDlg.h"
#include "login.h"
#include <string>
#include <stdio.h>
#include <afxdb.h>

FILE *f;


IMPLEMENT_DYNAMIC(shouhiDlg, CDialog)

shouhiDlg::shouhiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SHOUHI, pParent)
{

}

shouhiDlg::~shouhiDlg()
{
}

void shouhiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_account, control_account);
	DDX_Control(pDX, IDC_THUNHAP, control_thunhap);
	DDX_Control(pDX, IDC_CHITIEU, control_chitieu);
	DDX_Control(pDX, IDC_TIETKIEM, control_tietkiem);
	DDX_Control(pDX, IDC_KHAC, control_khac);
	DDX_Control(pDX, IDC_HIENTHI, control_hienthi);
	DDX_Control(pDX, IDC_CHAO, control_chao);
}


BEGIN_MESSAGE_MAP(shouhiDlg, CDialog)

	ON_BN_CLICKED(IDC_account, &shouhiDlg::OnClickedAccount)
	ON_BN_CLICKED(IDC_THUNHAP, &shouhiDlg::OnClickedThunhap)
	ON_BN_CLICKED(IDC_CHITIEU, &shouhiDlg::OnClickedChitieu)
	ON_BN_CLICKED(IDC_TIETKIEM, &shouhiDlg::OnClickedTietkiem)
	ON_BN_CLICKED(IDC_KHAC, &shouhiDlg::OnClickedKhac)
END_MESSAGE_MAP()
BOOL shouhiDlg::OnInitDialog()
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
	CDatabase db;
	db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
	CRecordset rd(&db);
	CString name, hienthi, sql;
	sql.Format(_T("select last_name from account1 where id=%d"), user_id);
	rd.Open(CRecordset::forwardOnly, sql);
	rd.GetFieldValue((short)0, name);
	rd.Close();
	db.Close();
	hienthi.Format(_T("HELLO %s, HAVE A NICE DAY"), name);
	control_chao.SetWindowText(hienthi);
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}


void shouhiDlg::OnClickedAccount()
{
	taikhoan.user_id = user_id;
	if (taikhoan.DoModal() == IDOK) {

	}
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void shouhiDlg::OnClickedThunhap()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	thunhap.user_id = user_id;
	if (thunhap.DoModal() == IDOK) {
		if (thunhap.sotien != "") {
			CString str, str1,hienphu,str2;
			str2.Format(_T("     "));
			str1.Format(_T("\r\n"));
			str.Format(_T("					収入"));
			hienphu += str1+ thunhap.date+str2;
			hienphu += thunhap.sotien + str;
			hienthi.Insert(0, hienphu);
			control_hienthi.SetWindowText(hienthi);
			
		}
		
	}
}


void shouhiDlg::OnClickedChitieu()
{
	chitieu.user_id = user_id;
	if (chitieu.DoModal() == IDOK) {
		if (chitieu.sotien != "") {
			CString str, str1, hienphu, str2;
			str2.Format(_T("     "));
			str1.Format(_T("\r\n"));
			str.Format(_T("		消費"));
			hienphu += str1 + chitieu.date + str2+chitieu.mucchi+str2 +chitieu.khoanchi+str2+chitieu.taikhoan+str2;
			hienphu += chitieu.sotien + str;
			hienthi.Insert(0, hienphu);
			control_hienthi.SetWindowText(hienthi);
			
		}
		
	}
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void shouhiDlg::OnClickedTietkiem() {
	tietkiem.user_id = user_id;
	if (tietkiem.DoModal() == IDOK) {

	}
}
 void shouhiDlg::OnClickedKhac() {
	loan.user_id = user_id;
	if (loan.DoModal() == IDOK) {

	}
}
