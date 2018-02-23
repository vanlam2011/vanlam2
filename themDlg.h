#pragma once
#include "afxwin.h"
#include "stdio.h"
//#include "loginDlg.h"




// themDlg ダイアログ

class themDlg : public CDialog
{
	DECLARE_DYNAMIC(themDlg)

public:
	themDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~themDlg();

	// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
private:
	CEdit control_ten;
	CEdit control_sodu;
	CButton control_xacnhan;
public:
	CString str;
	CString str1;
	//CloginDlg login;

	int user_id;
	afx_msg void OnBnClickedOk();
};
