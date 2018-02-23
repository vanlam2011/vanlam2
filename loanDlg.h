#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
//#include "loginDlg.h"




// taikhoanDlg ƒ_ƒCƒAƒƒO

class loanDlg : public CDialog
{
	DECLARE_DYNAMIC(loanDlg)

public:
	loanDlg(CWnd* pParent = NULL);   // •W€ƒRƒ“ƒXƒgƒ‰ƒNƒ^[
	virtual ~loanDlg();


	// ƒ_ƒCƒAƒƒO ƒf[ƒ^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VAYMUON };
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
	CEdit control_name;
	CEdit control_sotien;
	int control_borrow;
	int control_shikin;
	CDateTimeCtrl control_ngay;
public:
	afx_msg void OnBnClickedOk();
private:
	CComboBox control_danhsachno;
	CEdit control_tienno;
	CEdit control_tientra;
public:
	afx_msg void OnSelchangeDanhsachno();
private:
	CEdit contol_loai;
	CButton control_xacnhan;
public:
	afx_msg void OnClickedXacnhan();
	int user_id;
};