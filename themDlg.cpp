// themDlg.cpp : À‘•ƒtƒ@ƒCƒ‹
//

#include "stdafx.h"
#include "login.h"
#include "themDlg.h"
#include "afxdialogex.h"
#include "taikhoanDlg.h"
#include <afxdb.h>


// themDlg ƒ_ƒCƒAƒƒO

IMPLEMENT_DYNAMIC(themDlg, CDialog)

themDlg::themDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_THEM, pParent)
{

}

themDlg::~themDlg()
{
}

void themDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEN, control_ten);
	DDX_Control(pDX, IDC_SOTIEN, control_sodu);
}


BEGIN_MESSAGE_MAP(themDlg, CDialog)

	ON_BN_CLICKED(IDOK, &themDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// themDlg ƒƒbƒZ[ƒW ƒnƒ“ƒhƒ‰[



void themDlg::OnBnClickedOk()
{
	int i = -1;
	int n = 0;
	int usr_id;
	UpdateData(TRUE);
	int d;
	control_ten.GetWindowText(str);
	control_sodu.GetWindowText(str1);
	d = _tstoi(str1);
	CDatabase db;
	try {
		db.OpenEx(_T("DSN=shouhinsystem"), CDatabase::noOdbcDialog);
		CRecordset rd(&db);
		CRecordset rc(&db);
		CString sSQL, sql, ss, sql1, us_id;
		sql1.Format(_T("select [user id] from bank1 where name='%s'"), str);
		rd.Open(CRecordset::forwardOnly, sql1);
		while (!rd.IsEOF()) {
			rd.GetFieldValue((short)0, us_id);
				usr_id = _tstoi(us_id);
				if (usr_id == user_id) {
					n++;
			}
			rd.MoveNext();
		}
		rd.Close();
		if(n==0){
			sql.Format(_T("select max(id) from bank1 where [user id] = %d"), user_id);
	
			rc.Open(CRecordset::forwardOnly, sql);
			if (rc.IsEOF() != LB_ERR) {
				rc.GetFieldValue((short)0, ss);
				if (ss != "") {
					i = _tstoi(ss);
				}
			}
			i++;

			sSQL.Format(_T("insert into bank1([user id],id,name, sotien) values(%d,%d,'%s', %d);"), user_id, i, str, d);

			db.ExecuteSQL(sSQL);
			rc.Close();
		}
		else {
			MessageBox(_T("既に存在します"), _T("info"));
		}
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
	db.Close();
	
	UpdateData(FALSE);
	// TODO: ‚±‚±‚ÉƒRƒ“ƒgƒ[ƒ‹’Ê’mƒnƒ“ƒhƒ‰[ ƒR[ƒh‚đ’Ç‰Á‚µ‚Ü‚·B
	CDialog::OnOK();
}
