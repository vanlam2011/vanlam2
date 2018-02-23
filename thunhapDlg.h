#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
//#include "loginDlg.h"




// taikhoanDlg ƒ_ƒCƒAƒƒO

class thunhapDlg : public CDialog
{
	DECLARE_DYNAMIC(thunhapDlg)

public:
	thunhapDlg(CWnd* pParent = NULL);   // •W€ƒRƒ“ƒXƒgƒ‰ƒNƒ^[
	virtual ~thunhapDlg();


	// ƒ_ƒCƒAƒƒO ƒf[ƒ^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THUNHAP };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ƒTƒ|[ƒg

														// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	
	CComboBox control_taikhoan;
private:
	
	CEdit control_sotien;
	CComboBox control_loai;
public:
	//CloginDlg login;
	CString date, sotien;
	int i = 0;
	int user_id;
	afx_msg void OnBnClickedOk();
private:
	CDateTimeCtrl control_ngaythang;
};

