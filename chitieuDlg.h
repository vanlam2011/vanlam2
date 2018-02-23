#pragma once
#include "afxwin.h"
#include "afxdtctl.h"




// taikhoanDlg ƒ_ƒCƒAƒƒO

class chitieuDlg : public CDialog
{
	DECLARE_DYNAMIC(chitieuDlg)

public:
	chitieuDlg(CWnd* pParent = NULL);   // •W€ƒRƒ“ƒXƒgƒ‰ƒNƒ^[
	virtual ~chitieuDlg();


	// ƒ_ƒCƒAƒƒO ƒf[ƒ^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHITIEU };
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
	CComboBox control_mucchi;
	CEdit control_loai;
	CEdit control_sotien;
	CComboBox control_taikhoan;
	CDateTimeCtrl control_date;
public:
	//CloginDlg  login;
	CString sotien, khoanchi, mucchi, taikhoan,date;
	afx_msg void OnBnClickedOk();
	int user_id;
};

