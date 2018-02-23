// taikhoanDlg.cpp : À‘•ƒtƒ@ƒCƒ‹
//

#include "stdafx.h"
#include "login.h"
#include "taikhoanDlg.h"
#include "afxdialogex.h"
#include <afxdb.h>


// taikhoanDlg ƒ_ƒCƒAƒƒO

IMPLEMENT_DYNAMIC(taikhoanDlg, CDialog)

taikhoanDlg::taikhoanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TAIKHOAN, pParent)
{

}

taikhoanDlg::~taikhoanDlg()
{
}

void taikhoanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_THEM, control_them);
	DDX_Control(pDX, IDC_TAIKHOAN, control_taikhoan);
	DDX_Control(pDX, IDC_SODU, control_sodu);
	DDX_Control(pDX, IDC_TONG, control_tong);
	DDX_Control(pDX, IDC_NHAN, control_danhsachnhan);
	DDX_Control(pDX, IDC_TIENCHUYEN, control_tienchuyen);
	DDX_Control(pDX, IDC_CHUYEN, control_chuyen);
}
BOOL taikhoanDlg::OnInitDialog()
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
	int sum = 0;
	int i;
	CDatabase db;
	try {
		db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
		CRecordset rc(&db), rs(&db), rb(&db);
		CString sSQL;


		sSQL.Format(_T("SELECT name from bank1 where [user id]=%d ORDER BY id ASC "), user_id);
		rc.Open(CRecordset::forwardOnly, sSQL);
		CString ms, ml;
		while (!rc.IsEOF()) {
			rc.GetFieldValue((short)0, ms);
			control_taikhoan.AddString(ms);
			control_danhsachnhan.AddString(ms);
			rc.MoveNext();
		}
		rc.Close();





		CString sql;
		sql.Format(_T("SELECT sotien from bank1 where [user id]=%d order by id ASC"), user_id);
		rs.Open(CRecordset::forwardOnly, sql);
		while (!rs.IsEOF()) {
			rs.GetFieldValue((short)0, ml);
			i = _tstoi(ml);
			sum += i;
			rs.MoveNext();
		}
		rs.Close();
		CString sot;

		sot.Format(_T("SELECT sotien from bank1 WHERE id=0 and [user id] = %d"), user_id);
		rb.Open(CRecordset::forwardOnly, sot);

		rb.GetFieldValue((short)0, ml);
		rb.Close();

		control_sodu.SetWindowText(ml);

		ms.Format(_T("%d"), sum);
		control_tong.SetWindowText(ms);
	}
	catch (CDBException* pEx) {
		pEx->ReportError();
		pEx->Delete();
	}
	db.Close();

	

								// TODO: 初期化をここに追加します。
	control_taikhoan.SetCurSel(0);
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}


BEGIN_MESSAGE_MAP(taikhoanDlg, CDialog)
	ON_BN_CLICKED(IDC_THEM, &taikhoanDlg::OnClickedThem)
	ON_CBN_SELCHANGE(IDC_TAIKHOAN, &taikhoanDlg::OnSelchangeTaikhoan)


	ON_BN_CLICKED(IDC_CHUYEN, &taikhoanDlg::OnClickedChuyen)
END_MESSAGE_MAP()


// taikhoanDlg ƒƒbƒZ[ƒW ƒnƒ“ƒhƒ‰[


void taikhoanDlg::OnClickedThem()
{
	them.user_id = user_id;
	if (them.DoModal() == IDOK) {
		CDatabase db;
		db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
		CRecordset rc(&db),rs(&db);
		CString sSQL,sql,ss,ms;
		int s;
		sql.Format(_T("select max(id) from bank1 where [user id] = %d"), user_id);

		rc.Open(CRecordset::forwardOnly, sql);
		if (rc.IsEOF() != LB_ERR) {
			rc.GetFieldValue((short)0, ss);
			if (ss != "") {
				s = _tstoi(ss);
			}
		}
		rc.Close();
		s = s + 1;
		if ( s> control_taikhoan.GetCount()) {
			sSQL.Format(_T("select name from bank1 where name = '%s' and [user id]= %d"), them.str, user_id);
			rc.Open(CRecordset::forwardOnly, sSQL);
			while (!rc.IsEOF()) {
				rc.GetFieldValue((short)0, ms);
				control_taikhoan.AddString(ms);
				control_danhsachnhan.AddString(ms);
				rc.MoveNext();
			}

			rc.Close();
		}
		int sum=0,i;
		CString ml;
		sql.Format(_T("SELECT sotien from bank1 where [user id]= %d"),user_id);
		rs.Open(CRecordset::forwardOnly, sql);
		while (!rs.IsEOF()) {
			rs.GetFieldValue((short)0, ml);
			i = _tstoi(ml);
			sum += i;
			rs.MoveNext();
		}
		rs.Close();
		db.Close();



		ms.Format(_T("%d"), sum);
		control_tong.SetWindowText(ms);
		db.Close();
		
		sodu[b] = _tstoi(them.str1);
		b++;
			UpdateData(FALSE);
		}
		
	}
	// TODO: ‚±‚±‚ÉƒRƒ“ƒgƒ[ƒ‹’Ê’mƒnƒ“ƒhƒ‰[ ƒR[ƒh‚đ’Ç‰Á‚µ‚Ü‚·B



void taikhoanDlg::OnSelchangeTaikhoan()
{
	UpdateData(TRUE);
	CDatabase db;
	db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
	CRecordset rs(&db);
	CString sql, str;
	sql.Format(_T("SELECT sotien from bank1 WHERE id=%d  and [user id] = %d"), control_taikhoan.GetCurSel(),user_id);
	rs.Open(CRecordset::forwardOnly, sql);
	rs.GetFieldValue((short)0, str);
	rs.Close();
	db.Close();
	control_sodu.SetWindowText(str);
	UpdateData(FALSE);

	// TODO: ‚±‚±‚ÉƒRƒ“ƒgƒ[ƒ‹’Ê’mƒnƒ“ƒhƒ‰[ ƒR[ƒh‚đ’Ç‰Á‚µ‚Ü‚·B
}







void taikhoanDlg::OnClickedChuyen()
{
	UpdateData(TRUE);
	CString str, str1;
	int i, s;
	int st,tienchuyen,tiennhan;
	i = control_taikhoan.GetCurSel();
	s = control_danhsachnhan.GetCurSel();
	control_tienchuyen.GetWindowText(str);
	st = _tstoi(str);
	
	CDatabase db;
	try {
		db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
		CRecordset rd(&db), rc(&db);
		CString sSQL,sSQL1,sql,sql1,tc,tn;
		sql.Format(_T("select sotien from bank1 where [user id]= %d and id=%d"), user_id, control_taikhoan.GetCurSel());
		rd.Open(CRecordset::forwardOnly, sql);
		rd.GetFieldValue((short)0, tc);
		tienchuyen = _tstoi(tc);
		rd.Close();


		sql1.Format(_T("select sotien from bank1 where [user id]= %d and id=%d"), user_id, control_danhsachnhan.GetCurSel()); 
		rc.Open(CRecordset::forwardOnly, sql1);
		rc.GetFieldValue((short)0, tn);
		tiennhan = _tstoi(tn);
		rc.Close();

		if (st < tienchuyen && i != s) {
			tienchuyen -= st;
			tiennhan += st;


			sSQL.Format(_T("UPDATE bank1 SET sotien=%d WHERE id = %d and [user id] = %d"), tienchuyen, i, user_id);
			sSQL1.Format(_T("UPDATE bank1 SET sotien=%d WHERE id = %d and [user id] = %d"), tiennhan, s, user_id);
			db.ExecuteSQL(sSQL);
			db.ExecuteSQL(sSQL1);
		}
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
	db.Close();
	str.Format(_T(""));
	str1.Format(_T("%d"), tienchuyen);
	control_tienchuyen.SetWindowText(str);
	control_sodu.SetWindowText(str1);
	UpdateData(FALSE);

	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
