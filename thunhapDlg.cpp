#include "stdafx.h"
#include "thunhapDlg.h"
#include "login.h"
#include "afxdialogex.h"
#include <afxdb.h>

// taikhoanDlg ƒ_ƒCƒAƒƒO

IMPLEMENT_DYNAMIC(thunhapDlg, CDialog)

thunhapDlg::thunhapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_THUNHAP, pParent)
{

}

thunhapDlg::~thunhapDlg()
{
}

void thunhapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAIKHOAN, control_taikhoan);
	DDX_Control(pDX, IDC_SOTIEN, control_sotien);
	DDX_Control(pDX, IDC_LUONG, control_loai);
	DDX_Control(pDX, IDC_NGAYTHANG, control_ngaythang);
}


BEGIN_MESSAGE_MAP(thunhapDlg, CDialog)

	ON_BN_CLICKED(IDOK, &thunhapDlg::OnBnClickedOk)
END_MESSAGE_MAP()



BOOL thunhapDlg::OnInitDialog()
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

	control_loai.AddString(_T("給与"));
	control_loai.AddString(_T("ボーナス"));

	int sum = 0;
	CDatabase db;
	db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
	CRecordset rc(&db);
	CString sSQL;


	sSQL.Format(_T("SELECT name from bank1 where [user id] = %d order by id ASC"),user_id);
	rc.Open(CRecordset::forwardOnly, sSQL);
	CString ms, ml;
	while (!rc.IsEOF()) {
		rc.GetFieldValue((short)0, ms);
		control_taikhoan.AddString(ms);

		rc.MoveNext();
	}
	rc.Close();
	db.Close();




	// TODO: 初期化をここに追加します。
	control_taikhoan.SetCurSel(0);
									// TODO: 初期化をここに追加します。



	control_loai.SetCurSel(0);

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}


void thunhapDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	CString thang, nam,ngay;
	int sotien1, thang1,nam1,ngay1,x, st;
	

	CString sql,sql1;
	CTime time;
	
	control_sotien.GetWindowText(sotien);
	if (sotien != "") {
		sotien1 = _tstoi(sotien);
		DWORD dwResult = control_ngaythang.GetTime(time);
		date = time.Format(_T("%d.%m.%y"));
		ngay = time.Format(_T("%d"));
		thang = time.Format(_T("%m"));
		nam = time.Format(_T("%y"));
		ngay1 = _tstoi(ngay);
		nam1 = _tstoi(nam);
		thang1 = _tstoi(thang);
		x = control_taikhoan.GetCurSel();
		CDatabase db;
		db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);

		CRecordset rs(&db);
		CString sql2, str;
		sql2.Format(_T("SELECT sotien from bank1 WHERE id=%d and [user id]= %d"), x,user_id);
		rs.Open(CRecordset::forwardOnly, sql2);
		rs.GetFieldValue((short)0, str);
		rs.Close();
		st = _tstoi(str);


		sql.Format(_T("INSERT into nhan1([user id],sotien,ngay,thang,nam) values(%d, %d,%d,%d,%d)"), user_id, sotien1,ngay1, thang1, nam1);
		sql1.Format(_T("UPDATE bank1 SET sotien=%d WHERE id = %d and [user id] = %d"), st + sotien1, x,user_id);
		db.ExecuteSQL(sql);
		db.ExecuteSQL(sql1);
		db.Close();
		i++;
	}
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialog::OnOK();
}
