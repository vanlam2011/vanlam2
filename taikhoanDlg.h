#pragma once
#include "afxwin.h"
#include "themDlg.h"



// taikhoanDlg ƒ_ƒCƒAƒƒO

class taikhoanDlg : public CDialog
{
	DECLARE_DYNAMIC(taikhoanDlg)

public:
	taikhoanDlg(CWnd* pParent = NULL);   // •W€ƒRƒ“ƒXƒgƒ‰ƒNƒ^[
	virtual ~taikhoanDlg();


	// ƒ_ƒCƒAƒƒO ƒf[ƒ^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAIKHOAN };
#endif

protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ƒTƒ|[ƒg

	DECLARE_MESSAGE_MAP()
private:
	CButton control_them;


public:
	//CloginDlg login;
	themDlg them;
	CComboBox control_taikhoan;
private:
	CEdit control_sodu;
	CEdit control_tong;
	int b = 0;
public:
	int sodu[30];
	afx_msg void OnClickedThem();
	afx_msg void OnSelchangeTaikhoan();


private:
	CComboBox control_danhsachnhan;
	CEdit control_tienchuyen;
	CButton control_chuyen;
public:
	afx_msg void OnClickedChuyen();
	int user_id;
};
