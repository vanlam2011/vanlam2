#pragma once
#include "afxwin.h"
#include "stdio.h"
//#include "loginDlg.h"




// themDlg �_�C�A���O

class themDlg : public CDialog
{
	DECLARE_DYNAMIC(themDlg)

public:
	themDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~themDlg();

	// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

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
