#include "stdafx.h"
#include "loanDlg.h"
#include "login.h"
#include "afxdialogex.h"
#include <afxdb.h>



// taikhoanDlg ƒ_ƒCƒAƒƒO

IMPLEMENT_DYNAMIC(loanDlg, CDialog)

loanDlg::loanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_VAYMUON, pParent)
	, control_borrow(0)
	, control_shikin(1)
{

}

loanDlg::~loanDlg()
{
}

void loanDlg::DoDataExchange(CDataExchange* pDX)
{

	DDX_Control(pDX, IDC_NAME1, control_name);
	DDX_Control(pDX, IDC_SOTIEN, control_sotien);
	DDX_Control(pDX, IDC_NGAYVAYMUON, control_ngay);
	DDX_Check(pDX, IDC_VAY, control_borrow);
	DDX_Check(pDX, IDC_MUON, control_shikin);
	DDX_Control(pDX, IDC_DANHSACHNO, control_danhsachno);
	DDX_Control(pDX, IDC_SOTIEN1, control_tienno);
	DDX_Control(pDX, IDC_EDIT3, control_tientra);
	DDX_Control(pDX, IDC_LOAI, contol_loai);
	DDX_Control(pDX, IDC_XACNHAN, control_xacnhan);
}
BEGIN_MESSAGE_MAP(loanDlg, CDialog)

	ON_BN_CLICKED(IDOK, &loanDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_DANHSACHNO, &loanDlg::OnSelchangeDanhsachno)
	ON_BN_CLICKED(IDC_XACNHAN, &loanDlg::OnClickedXacnhan)
END_MESSAGE_MAP()
BOOL loanDlg::OnInitDialog()
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

	control_borrow = 0;
	control_shikin = 1;

	
		CDatabase db;
		db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
		CRecordset rc(&db);
		CString sSQL;


		sSQL.Format(_T("SELECT name from vaymuon where [user id]=%d  ORDER BY id ASC "), user_id);
		rc.Open(CRecordset::forwardOnly, sSQL);
		CString ms, ml;
		while (!rc.IsEOF()) {
			rc.GetFieldValue((short)0, ms);
			control_danhsachno.AddString(ms);
			
			rc.MoveNext();
		}
		rc.Close();
	
	


	return TRUE;
}

void loanDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	CTime time;
	CString name, tien,date , loai,ss;
	int sotien;


	DWORD dwResult = control_ngay.GetTime(time);
	date = time.Format(_T("%d,%m,%y"));


	control_name.GetWindowText(name);
	control_sotien.GetWindowText(tien);
	if (tien != ""&& name!="") {

		sotien = _tstoi(tien);
		if (control_borrow == 1) {
			loai.Format(_T("borrow"));
		}
		if (control_shikin) {
			loai.Format(_T("lend"));
		}
		int i=-1;
		CDatabase db;
		db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
		CString sql;
		sql.Format(_T("select max(id) from vaymuon"));
		CRecordset rd(&db);
		rd.Open(CRecordset::forwardOnly, sql);
		if (rd.IsEOF() != LB_ERR) {
			rd.GetFieldValue((short)0, ss);
			if (ss != "") {
				i = _tstoi(ss);
			}
		}
		i++;
		rd.Close();
		sql.Format(_T("INSERT into vaymuon([user id],id,name,sotien,date,loai) values(%d,%d,'%s',%d,'%s','%s')"), user_id, i, name, sotien, date, loai);
		db.ExecuteSQL(sql);
		db.Close();
	}
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialog::OnOK();
}


void loanDlg::OnSelchangeDanhsachno()
{
	CDatabase db;
	db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
	CRecordset rc(&db);
	CString sSQL;


	sSQL.Format(_T("SELECT loai from vaymuon where [user id]=%d and id=%d "), user_id,control_danhsachno.GetCurSel());
	rc.Open(CRecordset::forwardOnly, sSQL);
	CString ms;
	rc.GetFieldValue((short)0, ms);
	rc.Close();

	


	sSQL.Format(_T("SELECT sotien from vaymuon where [user id]=%d and id=%d"), user_id, control_danhsachno.GetCurSel());
	rc.Open(CRecordset::forwardOnly, sSQL);
	CString ml;
	rc.GetFieldValue((short)0, ml);
	rc.Close();

	db.Close();
	contol_loai.SetWindowText(ms);
	control_tienno.SetWindowText(ml);

	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void loanDlg::OnClickedXacnhan()
{
	UpdateData(TRUE);
	CString sotien, st1, loai;
	int st,st2;
	control_tientra.GetWindowText(sotien);
	st = _tstoi(sotien);

	CDatabase db;
	db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
	CRecordset rc(&db);
	CString sSQL;
	sSQL.Format(_T("SELECT sotien from vaymuon where [user id]=%d and id=%d"), user_id, control_danhsachno.GetCurSel());
	rc.Open(CRecordset::forwardOnly, sSQL);
	rc.GetFieldValue((short)0, st1);
	rc.Close();
	st2 = _tstoi(st1);

	sSQL.Format(_T("SELECT loai from vaymuon where [user id]=%d and id=%d"), user_id, control_danhsachno.GetCurSel());
	rc.Open(CRecordset::forwardOnly, sSQL);
	rc.GetFieldValue((short)0, loai);
	rc.Close();
	CString hienthi;

	if (st > st2) {
		if (loai == "borrow") {
			sSQL.Format(_T("update vaymuon set loai ='lend',sotien=%d where [user id]=%d and id=%d"),st-st2, user_id, control_danhsachno.GetCurSel());
			hienthi.Format(_T("lend"));
		}
		else {
			sSQL.Format(_T("update vaymuon set loai ='borrow' where [user id]=%d and id=%d"), user_id, control_danhsachno.GetCurSel());
			hienthi.Format(_T("borrow"));
		}
		sotien.Format(_T("%d"), st - st2);
		
	}
	else if (st < st2) {
		sSQL.Format(_T("update vaymuon set sotien=%d where [user id]=%d and id=%d"), st2-st,user_id, control_danhsachno.GetCurSel());
		hienthi += loai;
		sotien.Format(_T("%d"), st2-st);
	}
	db.ExecuteSQL(sSQL);
	if (st == st2) {
		sSQL.Format(_T("delete from vaymuon  where [user id]=%d and id=%d"), user_id, control_danhsachno.GetCurSel());
		db.ExecuteSQL(sSQL);
		for (int i = control_danhsachno.GetCurSel()+1; i <=control_danhsachno.GetCount()-1 ; i++)
		{
			sSQL.Format(_T("update vaymuon set id=%d where [user id]=%d and id=%d"), i - 1, user_id, i);
			db.ExecuteSQL(sSQL);
		}
		
	}
	control_tienno.SetWindowText(sotien);
	contol_loai.SetWindowText(hienthi);
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
