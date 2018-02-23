#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
//#include "loginDlg.h"




// taikhoanDlg ƒ_ƒCƒAƒƒO

class dangkyDlg : public CDialog
{
	DECLARE_DYNAMIC(dangkyDlg)

public:
	dangkyDlg(CWnd* pParent = NULL);   // •W€ƒRƒ“ƒXƒgƒ‰ƒNƒ^[
	virtual ~dangkyDlg();


	// ƒ_ƒCƒAƒƒO ƒf[ƒ^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DANGKY };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ƒTƒ|[ƒg

														// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CEdit control_user;
	CEdit control_pass;
	CEdit control_mail;
public:
	afx_msg void OnBnClickedOk();
	CEdit control_fisrtname;
private:
	CEdit control_lastname;
	CEdit control_email;
};

