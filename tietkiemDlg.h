#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include <strsafe.h>
//#include "loginDlg.h"




// taikhoanDlg ƒ_ƒCƒAƒƒO

class tietkiemDlg : public CDialog
{
	DECLARE_DYNAMIC(tietkiemDlg)

public:
	tietkiemDlg(CWnd* pParent = NULL);   // •W€ƒRƒ“ƒXƒgƒ‰ƒNƒ^[
	virtual ~tietkiemDlg();


	// ƒ_ƒCƒAƒƒO ƒf[ƒ^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIETKIEM };
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
	CEdit control_tientieu;
	CEdit control_tiennhan;
	CEdit control_phantich;
	CComboBox control_thang;
	CButton control_tong;
	CButton control_no;
public:
	//CloginDlg login;
	afx_msg void OnSelchangeThang();
	afx_msg void OnClickedTongket();
	afx_msg void OnSelchangeNam();
private:
	CEdit control_hienthic;
	CEdit control_hienthichi;
	CEdit control_hienthino;
	CComboBox control_nam;
public:
	afx_msg void OnClickedNo();
	afx_msg void OnClickedchovay();
	int user_id;

};

