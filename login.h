
// login.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル



// CloginApp:
// このクラスの実装については、login.cpp を参照してください
//

class CloginApp : public CWinApp
{
public:
	CloginApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
public:
};

extern CloginApp theApp;
