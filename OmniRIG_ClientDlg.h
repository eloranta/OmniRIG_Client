// OmniRIG_ClientDlg.h : header file
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; version 2 of the License.
// 
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
// Contact: olecam@f5mzn.org

#pragma once

#import "C:\Program Files\Afreet\OmniRig\OmniRig.exe"
using namespace OmniRig;

#include "afxwin.h"
#include "afxcmn.h"

#define MAX_RADIO	2
#define RIG1		1
#define RIG2		2
#define VFO_A		0
#define VFO_B		1

class CMyClickableStatic : public CStatic
{
public:
	int m_group = 0;
	int m_digitIndex = 0;
	class COmniRIG_ClientDlg* m_pParentDlg = nullptr;
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

class CMyComboBox : public CComboBox
{
public:
	void SetCurItem(DWORD dwItem)
	{
		int nSize = GetCount();
		for(int nIndex = 0; nIndex < nSize; nIndex++)
		{
			if (GetItemData(nIndex) == dwItem)
			{
				SetCurSel(nIndex);
				return;
			}
		}
	};

	DWORD GetCurItem()
	{
		int nIndex = GetCurSel();
		return (DWORD) GetItemData(nIndex);
	};
};

// COmniRIG_ClientDlg dialog
class COmniRIG_ClientDlg : public CDialog
{
// Construction
public:
	COmniRIG_ClientDlg(CWnd* pParent = NULL);	// standard constructor
	~COmniRIG_ClientDlg();

// Dialog Data
	enum { IDD = IDD_OMNIRIG_CLIENT_DIALOG };

	void ChangeDigit(int group, int index, int delta);
	void UpdateDigitDisplay(int group);


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support



// Implementation
protected:
	HICON m_hIcon;
	DWORD m_dwCookie;
	IOmniRigXPtr m_pOmniRig;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
	afx_msg HRESULT VisibleChange();
	afx_msg HRESULT RigTypeChange(long RigNumber);
	afx_msg HRESULT StatusChange(long RigNumber);
	afx_msg HRESULT ParamsChange(long RigNumber, long Params);
	afx_msg HRESULT CustomReply(long RigNumber, const _variant_t & Command, const _variant_t & Reply);
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedDialogVisible();
	afx_msg void OnBnClickedBtnR1Freq();
	afx_msg void OnBnClickedBtnR2Freq();
	afx_msg void OnBnClickedBtnR1FreqA();
	afx_msg void OnBnClickedBtnR2FreqA();
	afx_msg void OnBnClickedBtnR1FreqB();
	afx_msg void OnBnClickedBtnR2FreqB();
	afx_msg void OnCbnSelchangeR1Mode();
	afx_msg void OnCbnSelchangeR2Mode();
	afx_msg void OnBnClickedCheckR1Split();
	afx_msg void OnBnClickedCheckR2Split();
	afx_msg void OnBnClickedRadioR1VfoA();
	afx_msg void OnBnClickedRadioR1VfoB();
	afx_msg void OnBnClickedRadioR2VfoA();
	afx_msg void OnBnClickedRadioR2VfoB();
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

protected:
	CEdit* m_pEditFreq[MAX_RADIO];
	CEdit* m_pEditFreqA[MAX_RADIO];
	CEdit* m_pEditFreqB[MAX_RADIO];
	void SetFreq(long RigNumber, long Frequency);
	void SetFreqA(long RigNumber, long Frequency);
	void SetFreqB(long RigNumber, long Frequency);
	void SetVfo(long RigNumber, int nVfo);
	void SetMode(long RigNumber, RigParamX Mode);
	void SetSplit(long RigNumber, BOOL bIsSplit);
	
private:
	CButton m_btnDialogVisible;
	unsigned long m_lReadable[MAX_RADIO];
	unsigned long m_lWriteable[MAX_RADIO];
	long m_lFreq[MAX_RADIO];
	CEdit m_editFreq[MAX_RADIO];
	long m_lFreqA[MAX_RADIO];
	CEdit m_editFreqA[MAX_RADIO];
	long m_lFreqB[MAX_RADIO];
	CEdit m_editFreqB[MAX_RADIO];
	CSpinButtonCtrl m_spinFreq[MAX_RADIO];
	CSpinButtonCtrl m_spinFreqA[MAX_RADIO];
	CSpinButtonCtrl m_spinFreqB[MAX_RADIO];
	CButton m_btnFreq[MAX_RADIO];
	CButton m_btnFreqA[MAX_RADIO];
	CButton m_btnFreqB[MAX_RADIO];
	CMyComboBox m_cboxMode[MAX_RADIO];
	CButton m_checkSplit[MAX_RADIO];
	CStatic m_staticRig[MAX_RADIO];
	CStatic m_staticStatus[MAX_RADIO];
	CButton m_radioVfoA[MAX_RADIO];
	CButton m_radioVfoB[MAX_RADIO];
	CBrush m_brushBg;
	CBrush m_brushOnAir;
	CFont m_font;
	CMyClickableStatic m_digitA[8];
	CStatic d1;
	CStatic d2;
	CStatic d11;
	CStatic d21;
	CMyClickableStatic m_digitB[8];
	CString m_rigType;
	CString m_rigStatus;
	bool m_txOn = false;
public:
	afx_msg void OnBnClickedButton1_8();
	afx_msg void OnBnClickedButton3_5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButton50();
};
