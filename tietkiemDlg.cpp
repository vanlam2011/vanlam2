#include "stdafx.h"
#include "tietkiemDlg.h"
#include "login.h"
#include "afxdialogex.h"
#include <afxdb.h>



// taikhoanDlg ƒ_ƒCƒAƒƒO

IMPLEMENT_DYNAMIC(tietkiemDlg, CDialog)

tietkiemDlg::tietkiemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TIETKIEM, pParent)
{

}

tietkiemDlg::~tietkiemDlg()
{
}

void tietkiemDlg::DoDataExchange(CDataExchange* pDX)
{



	DDX_Control(pDX, IDC_TIENTIEU, control_tientieu);
	DDX_Control(pDX, IDC_TIENNHAN, control_tiennhan);
	DDX_Control(pDX, IDC_PHANTICH, control_phantich);
	DDX_Control(pDX, IDC_THANG, control_thang);
	DDX_Control(pDX, IDC_TONGKET, control_tong);
	DDX_Control(pDX, IDC_N, control_no);
	DDX_Control(pDX, IDC_HIENTHICHITIEU, control_hienthic);
	DDX_Control(pDX, IDC_HIENTHITHUNHAP, control_hienthichi);
	DDX_Control(pDX, IDC_HIENTHINO, control_hienthino);
	DDX_Control(pDX, IDC_NAM, control_nam);
}
BEGIN_MESSAGE_MAP(tietkiemDlg, CDialog)


	ON_CBN_SELCHANGE(IDC_THANG, &tietkiemDlg::OnSelchangeThang)
	ON_BN_CLICKED(IDC_TONGKET, &tietkiemDlg::OnClickedTongket)
	ON_CBN_SELCHANGE(IDC_NAM, &tietkiemDlg::OnSelchangeNam)
	ON_BN_CLICKED(IDC_N, &tietkiemDlg::OnClickedNo)
	ON_BN_CLICKED(IDC_SHIKIN, &tietkiemDlg::OnClickedchovay)
END_MESSAGE_MAP()
BOOL tietkiemDlg::OnInitDialog()
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
	CRecordset rc(&db),rb(&db);
	CString sSQL,sql1,tieu,thu,tong;
	int tieu1, thu1;
	int sum1 = 0, sum2 = 0;
	sSQL.Format(_T("select sotien from chitieu1 where [user id] = %d"),user_id);
	rc.Open(CRecordset::forwardOnly, sSQL);
	while (!rc.IsEOF()) {
		rc.GetFieldValue((short)0, tieu);
		tieu1 = _tstoi(tieu);
		sum1 += tieu1;
		rc.MoveNext();
	}
	rc.Close();
	sql1.Format(_T("select sotien from nhan1 where [user id] = %d"),user_id);
	rb.Open(CRecordset::forwardOnly, sql1);
	while (!rb.IsEOF()) {
		rb.GetFieldValue((short)0, thu);
		thu1 = _tstoi(thu);
		sum2 += thu1;
		rb.MoveNext();
	}
	rb.Close();


	CString tu, te, to;
	tu.Format(_T("%d"), sum2);
	te.Format(_T("%d"), sum1);
	tong.Format(_T("%d"), sum2 - sum1);
	control_tientieu.SetWindowText(te);
	control_tiennhan.SetWindowText(tu);
	control_phantich.SetWindowText(tong);
	control_thang.AddString(_T(""));
	for (int i = 1; i <= 12; i++) {
		CString s;
		s.Format(_T("%d"), i);
		control_thang.AddString(s);
	}

	control_nam.AddString(_T("2017"));
	control_nam.AddString(_T("2018"));
	control_nam.AddString(_T("2019"));

	control_thang.SetCurSel(0);
	control_nam.SetCurSel(0);


	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void tietkiemDlg::OnSelchangeThang()
{
	UpdateData(TRUE);
	int thang;
	int nam; 
	nam = control_nam.GetCurSel();
	nam += 17;
	thang = control_thang.GetCurSel();
	CDatabase db;
	CString xuongdong,space;
	xuongdong.Format(_T("\r\n"));
	space.Format(_T("   "));
	db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
	CRecordset rc(&db), rb(&db);
	CString sSQL, sql1, tieu, thu, tong,chitieu,thunhap,xet,xet1;
	int tieu1, thu1;
	int sum1 = 0, sum2 = 0;
	sSQL.Format(_T("select sotien from chitieu1 where [user id] = %d and thang = %d and nam = %d order by ngay ASC"), user_id,thang,nam);
	rc.Open(CRecordset::forwardOnly, sSQL);
	while (!rc.IsEOF()) {
		rc.GetFieldValue((short)0, tieu);
		tieu1 = _tstoi(tieu);
		sum1 += tieu1;
		rc.MoveNext();
	}
	rc.Close();


	sSQL.Format(_T("select ngay, sotien, muchi from chitieu1 where [user id] = %d and thang = %d and nam = %d order by ngay ASC"), user_id, thang, nam);
	rc.Open(CRecordset::forwardOnly, sSQL);
	short nF = rc.GetODBCFieldCount();
	while (!rc.IsEOF()) {
		for (short index = 0; index < nF; index++) {
			rc.GetFieldValue(index, xet);
			chitieu += xet;
			chitieu += space;
		}
		chitieu += xuongdong;
		rc.MoveNext();
	}
	rc.Close();


	sql1.Format(_T("select sotien from nhan1 where [user id] = %d and thang = %d and nam = %d"), user_id,thang,nam);
	rb.Open(CRecordset::forwardOnly, sql1);
	while (!rb.IsEOF()) {
		rb.GetFieldValue((short)0, thu);
		thu1 = _tstoi(thu);
		sum2 += thu1;
		rb.MoveNext();
	}
	rb.Close();


	sql1.Format(_T("select ngay, sotien from nhan1 where [user id] = %d and thang = %d and nam = %d"), user_id, thang,nam);
	rb.Open(CRecordset::forwardOnly, sql1);
	short nF1= rb.GetODBCFieldCount();
	while (!rb.IsEOF()) {
		for (short index = 0; index < nF1; index++) {
			rb.GetFieldValue(index, xet1);
			thunhap += xet1;
			thunhap += space;
		}
		thunhap += xuongdong;
		rb.MoveNext();
		
	}
	rb.Close();



	CString tu, te, to;
	tu.Format(_T("%d"), sum2);
	te.Format(_T("%d"), sum1);
	tong.Format(_T("%d"), sum2 - sum1);
	control_hienthic.SetWindowText(chitieu);
	control_hienthichi.SetWindowText(thunhap);
	control_tientieu.SetWindowText(te);
	control_tiennhan.SetWindowText(tu);
	control_phantich.SetWindowText(tong);

	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void tietkiemDlg::OnClickedTongket()
{
	UpdateData(TRUE);
	CDatabase db;
	db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
	CRecordset rc(&db), rb(&db);
	CString sSQL, sql1, tieu, thu, tong;
	int tieu1, thu1;
	int sum1 = 0, sum2 = 0;
	sSQL.Format(_T("select sotien from chitieu1 where [user id] = %d"), user_id);
	rc.Open(CRecordset::forwardOnly, sSQL);
	while (!rc.IsEOF()) {
		rc.GetFieldValue((short)0, tieu);
		tieu1 = _tstoi(tieu);
		sum1 += tieu1;
		rc.MoveNext();
	}
	rc.Close();
	sql1.Format(_T("select sotien from nhan1 where [user id] = %d"), user_id);
	rb.Open(CRecordset::forwardOnly, sql1);
	while (!rb.IsEOF()) {
		rb.GetFieldValue((short)0, thu);
		thu1 = _tstoi(thu);
		sum2 += thu1;
		rb.MoveNext();
	}
	rb.Close();


	CString tu, te, to;
	tu.Format(_T("%d"), sum2);
	te.Format(_T("%d"), sum1);
	tong.Format(_T("%d"), sum2 - sum1);
	control_hienthic.SetWindowText(_T(""));
	control_hienthichi.SetWindowText(_T(""));
	control_tientieu.SetWindowText(te);
	control_tiennhan.SetWindowText(tu);
	control_phantich.SetWindowText(tong);

	// TODO: ここにコントロール通知ハンドラー コードを追加します。.
}
void tietkiemDlg::OnSelchangeNam() {
	UpdateData(TRUE);
	int nam;
	nam = control_nam.GetCurSel();
	nam += 17;
	CDatabase db;
	db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
	CRecordset rc(&db), rb(&db);
	CString sSQL, sql1, tieu, thu, tong;
	int tieu1, thu1;
	int sum1 = 0, sum2 = 0;
	sSQL.Format(_T("select sotien from chitieu1 where [user id] = %d and nam = %d"), user_id,nam);
	rc.Open(CRecordset::forwardOnly, sSQL);
	while (!rc.IsEOF()) {
		rc.GetFieldValue((short)0, tieu);
		tieu1 = _tstoi(tieu);
		sum1 += tieu1;
		rc.MoveNext();
	}
	rc.Close();
	sql1.Format(_T("select sotien from nhan1 where [user id] = %d and nam = %d"), user_id,nam);
	rb.Open(CRecordset::forwardOnly, sql1);
	while (!rb.IsEOF()) {
		rb.GetFieldValue((short)0, thu);
		thu1 = _tstoi(thu);
		sum2 += thu1;
		rb.MoveNext();
	}
	rb.Close();

	control_thang.SetCurSel(0);
	CString tu, te, to;
	tu.Format(_T("%d"), sum2);
	te.Format(_T("%d"), sum1);
	tong.Format(_T("%d"), sum2 - sum1);
	control_hienthic.SetWindowText(_T(""));
	control_hienthichi.SetWindowText(_T(""));
	control_tientieu.SetWindowText(te);
	control_tiennhan.SetWindowText(tu);
	control_phantich.SetWindowText(tong);

	// TODO: ここにコントロール通知ハンドラー コードを追加します。.
}



void tietkiemDlg::OnClickedNo()
{
	UpdateData(TRUE);
	CString xuongdong, space;
	xuongdong.Format(_T("\r\n"));
	space.Format(_T("  "));

	CDatabase db;
	db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
	CRecordset rc(&db);
	CString hienthi, no,sql1;
	

	sql1.Format(_T("select date,name,sotien from vaymuon where [user id] = %d and loai ='borrow'"), user_id);
	rc.Open(CRecordset::forwardOnly, sql1);
	short nF = rc.GetODBCFieldCount();
	while (!rc.IsEOF()) {
		for (short index = 0; index < nF; index++) {
			rc.GetFieldValue(index, no);
			hienthi += no;
			hienthi += space;
		}
		hienthi += xuongdong;
		rc.MoveNext();

	}
	rc.Close();
	db.Close();
	control_hienthino.SetWindowText(hienthi);
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}

void tietkiemDlg::OnClickedchovay() {
	UpdateData(TRUE);
	CString xuongdong, space, cham;
	xuongdong.Format(_T("\r\n"));
	space.Format(_T("  "));
	cham.Format(_T("."));

	CDatabase db;
	db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
	CRecordset rc(&db);
	CString  hienthi, no, sql1;

	sql1.Format(_T("select date,name,sotien from vaymuon where [user id] = %d and loai ='lend'"), user_id);
	rc.Open(CRecordset::forwardOnly, sql1);
	short nF = rc.GetODBCFieldCount();
	while (!rc.IsEOF()) {
		for (short index = 0; index < nF; index++) {
			rc.GetFieldValue(index, no);
			hienthi += no;
			hienthi += space;
		}
		hienthi += xuongdong;
		rc.MoveNext();

	}
	rc.Close();
	db.Close();
	control_hienthino.SetWindowText(hienthi);
}
