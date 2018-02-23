#pragma once
#pragma warning(suppress : 4996)
#include "afxwin.h"
#include "taikhoanDlg.h"
#include "thunhapDlg.h"
#include "chitieuDlg.h"
#include "tietkiemDlg.h"
#include "loanDlg.h"
class shouhiDlg : public CDialog
{
	DECLARE_DYNAMIC(shouhiDlg)

public:
	shouhiDlg(CWnd* pParent = NULL);   // •W€ƒRƒ“ƒXƒgƒ‰ƒNƒ^[
	virtual ~shouhiDlg();


	// ƒ_ƒCƒAƒƒO ƒf[ƒ^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOUHI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ƒTƒ|[ƒg
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CButton control_account;
	CButton control_thunhap;
	CButton control_chitieu;
	CButton control_tietkiem;
	CButton control_khac;
	CEdit control_hienthi;
public:
	CString hienthi;
	taikhoanDlg taikhoan;
	thunhapDlg thunhap;
	chitieuDlg chitieu;
	tietkiemDlg tietkiem;
	loanDlg loan;
	int user_id;
	afx_msg void OnClickedAccount();
	afx_msg void OnClickedThunhap();
	afx_msg void OnClickedChitieu();
	afx_msg void OnClickedTietkiem();
	afx_msg void OnClickedKhac();
private:
	CEdit control_chao;
};

