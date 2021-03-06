
// loginDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#include "shouhiDlg.h"
#include "dangkyDlg.h"

// CloginDlg ダイアログ
class CloginDlg : public CDialog
{
// コンストラクション
public:
	CloginDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CEdit control_ten;
	CEdit control_pass;
	CButton control_login;
	CButton control_register;
public:
	dangkyDlg dangky;
	int user_id;
	shouhiDlg shouhi;
	afx_msg void OnClickedButton1();
	
private:
	CEdit control_thongbao;
public:
	afx_msg void OnClickedButton2();
};
