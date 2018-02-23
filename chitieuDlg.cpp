#include "stdafx.h"
#include "chitieuDlg.h"
#include "login.h"
#include "afxdialogex.h"
#include <afxdb.h>



// taikhoanDlg ƒ_ƒCƒAƒƒO

IMPLEMENT_DYNAMIC(chitieuDlg, CDialog)

chitieuDlg::chitieuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CHITIEU, pParent)
{

}

chitieuDlg::~chitieuDlg()
{
}

void chitieuDlg::DoDataExchange(CDataExchange* pDX)
{

	DDX_Control(pDX, IDC_MUCCHI, control_mucchi);
	DDX_Control(pDX, IDC_KHOANCHI, control_loai);
	DDX_Control(pDX, IDC_SOTIEN, control_sotien);
	DDX_Control(pDX, IDC_TAIKHOAN, control_taikhoan);
	DDX_Control(pDX, IDC_NGAYTHANG, control_date);
}


BEGIN_MESSAGE_MAP(chitieuDlg, CDialog)

	
	ON_BN_CLICKED(IDOK, &chitieuDlg::OnBnClickedOk)
END_MESSAGE_MAP()



BOOL chitieuDlg::OnInitDialog()
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


	
	CDatabase db;
	db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
	CRecordset rc(&db);
	CString sSQL;


	sSQL.Format(_T("SELECT name from bank1 where [user id]=%d order by id ASC"),user_id);
	rc.Open(CRecordset::forwardOnly, sSQL);
	CString ms, ml;
	while (!rc.IsEOF()) {
		rc.GetFieldValue((short)0, ms);
		control_taikhoan.AddString(ms);

		rc.MoveNext();
	}
	rc.Close();
	db.Close();

	control_mucchi.AddString(_T("Transportation fee"));
	control_mucchi.AddString(_T("pocket money"));
	control_mucchi.AddString(_T("daily fee"));
	control_mucchi.AddString(_T("food expenses"));


	// TODO: 初期化をここに追加します。
	control_taikhoan.SetCurSel(0);
	control_mucchi.SetCurSel(0);
	// TODO: 初期化をここに追加します。



	

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void chitieuDlg::OnBnClickedOk()
{
CString st1;
	control_sotien.GetWindowText(sotien);
	if (sotien != "") {

		int sotien1, tk;
		sotien1 = _tstoi(sotien);
		control_loai.GetWindowText(khoanchi);
		CDatabase db;
		db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);

		CRecordset rs(&db),rc(&db);
		CString sql2, str,sql3;
		sql2.Format(_T("SELECT sotien from bank1 WHERE id=%d and [user id]= %d"), control_taikhoan.GetCurSel(),user_id);
		sql3.Format(_T("SELECT name from bank1 WHERE id=%d and [user id] =%d"), control_taikhoan.GetCurSel(),user_id);
		rs.Open(CRecordset::forwardOnly, sql2);
		rs.GetFieldValue((short)0, str);
		rs.Close();

		rc.Open(CRecordset::forwardOnly, sql3);
		rc.GetFieldValue((short)0, taikhoan);
		rc.Close();

		


		tk = _tstoi(str);
		if (sotien1 <= tk) {

			switch (control_mucchi.GetCurSel())
			{
			case 0:
				mucchi.Format(_T("Transportation fee")); break;
			case 1:
				mucchi.Format(_T("pocket money")); break;
			case 2:
				mucchi.Format(_T("daily fee")); break;
			case 3:
				mucchi.Format(_T("food expenses")); break;
			default:
				break;
			}

			CTime time;
			CString thang, nam,ngay;
			int  thang1, nam1,ngay1;

			DWORD dwResult = control_date.GetTime(time);
			date = time.Format(_T("%d.%m.%y"));
			ngay = time.Format(_T("%d"));
			thang = time.Format(_T("%m"));
			nam = time.Format(_T("%y"));
			nam1 = _tstoi(nam);
			thang1 = _tstoi(thang);
			ngay1 = _tstoi(ngay);


			CString s,s1;
			s.Format(_T("UPDATE bank1 SET sotien=%d WHERE id=%d and [user id]=%d"), tk - sotien1, control_taikhoan.GetCurSel(),user_id);
			s1.Format(_T("insert into chitieu1([user id],sotien,muchi,ngay,thang,nam) values (%d, %d,'%s',%d,%d,%d)"), user_id, sotien1, mucchi,ngay1,thang1, nam1);
			db.ExecuteSQL(s);
			db.ExecuteSQL(s1);
			sotien += st1;
		}
		db.Close();
		
		
	}
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialog::OnOK();
}
