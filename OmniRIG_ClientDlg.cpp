// OmniRIG_ClientDlg.cpp : implementation file
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

#include "stdafx.h"
#include "afxctl.h"
#include "resource.h"
#include "OmniRIG_Client.h"
#include "OmniRIG_ClientDlg.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static LPCTSTR g_lpszRigStatus[] = {
	_T("Not Configured"),
	_T("Disabled"),
	_T("Port Busy"),
	_T("Not Responding"),
	_T("On Line")
};

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

struct StartUpCom {
    StartUpCom() { CoInitialize(NULL); }
    ~StartUpCom() { CoUninitialize(); }
} g_com_inst;

// COmniRIG_ClientDlg dialog

COmniRIG_ClientDlg::COmniRIG_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COmniRIG_ClientDlg::IDD, pParent)
{
	m_dwCookie = 0L;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	EnableAutomation();

	for(int nIndex = 0; nIndex < MAX_RADIO; nIndex++)
	{
		m_lReadable[nIndex] = 0L;
		m_lWriteable[nIndex] = 0L;
		m_lFreq[nIndex] = 0L;
		m_lFreqA[nIndex] = 0L;
		m_lFreqB[nIndex] = 0L;
	}
}

COmniRIG_ClientDlg::~COmniRIG_ClientDlg()
{
	if (m_dwCookie)
	{
		LPUNKNOWN pUnkSink = GetIDispatch(FALSE);
		AfxConnectionUnadvise(m_pOmniRig, __uuidof(IOmniRigXEvents), pUnkSink, FALSE, m_dwCookie);
		m_dwCookie = 0L;
	}
}

void COmniRIG_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_DIALOG_VISIBLE, m_btnDialogVisible);
	//DDX_Text(pDX, IDC_R1_FREQ, m_lFreq[0]);
	//DDX_Text(pDX, IDC_R2_FREQ, m_lFreq[1]);
	//DDX_Control(pDX, IDC_R1_FREQ, m_editFreq[0]);
	//DDX_Control(pDX, IDC_R2_FREQ, m_editFreq[1]);
	DDX_Text(pDX, IDC_R1_FREQ_A, m_lFreqA[0]);
	//DDX_Text(pDX, IDC_R2_FREQ_A, m_lFreqA[1]);
	DDX_Control(pDX, IDC_R1_FREQ_A, m_editFreqA[0]);
	//DDX_Control(pDX, IDC_R2_FREQ_A, m_editFreqA[1]);
	DDX_Text(pDX, IDC_R1_FREQ_B, m_lFreqB[0]);
	//DDX_Text(pDX, IDC_R2_FREQ_B, m_lFreqB[1]);
	DDX_Control(pDX, IDC_R1_FREQ_B, m_editFreqB[0]);
	//DDX_Control(pDX, IDC_R2_FREQ_B, m_editFreqB[1]);
	//DDX_Control(pDX, IDC_BTN_R1_FREQ, m_btnFreq[0]);
	//DDX_Control(pDX, IDC_BTN_R2_FREQ, m_btnFreq[1]);
	DDX_Control(pDX, IDC_BTN_R1_FREQ_A, m_btnFreqA[0]);
	DDX_Control(pDX, IDC_BTN_R2_FREQ_A, m_btnFreqA[1]);
	DDX_Control(pDX, IDC_BTN_R1_FREQ_B, m_btnFreqB[0]);
	//DDX_Control(pDX, IDC_BTN_R2_FREQ_B, m_btnFreqB[1]);
	DDX_Control(pDX, IDC_R1_MODE, m_cboxMode[0]);
	DDX_Control(pDX, IDC_R2_MODE, m_cboxMode[1]);
	DDX_Control(pDX, IDC_CHECK_R1_SPLIT, m_checkSplit[0]);
	DDX_Control(pDX, IDC_CHECK_R2_SPLIT, m_checkSplit[1]);
	DDX_Control(pDX, IDC_STATIC_R1_RIG, m_staticRig[0]);
	//DDX_Control(pDX, IDC_STATIC_R2_RIG, m_staticRig[1]);
	DDX_Control(pDX, IDC_STATIC_R1_STATUS, m_staticStatus[0]);
	//DDX_Control(pDX, IDC_STATIC_R2_STATUS, m_staticStatus[1]);
	DDX_Control(pDX, IDC_RADIO_R1_VFO_A, m_radioVfoA[0]);
	DDX_Control(pDX, IDC_RADIO_R2_VFO_A, m_radioVfoA[1]);
	DDX_Control(pDX, IDC_RADIO_R1_VFO_B, m_radioVfoB[0]);
	DDX_Control(pDX, IDC_RADIO_R2_VFO_B, m_radioVfoB[1]);
	//DDX_Control(pDX, IDC_SPIN_R1_FREQ, m_spinFreq[0]);
	//DDX_Control(pDX, IDC_SPIN_R2_FREQ, m_spinFreq[1]);
	DDX_Control(pDX, IDC_SPIN_R1_FREQ_A, m_spinFreqA[0]);
	//DDX_Control(pDX, IDC_SPIN_R2_FREQ_A, m_spinFreqA[1]);
	DDX_Control(pDX, IDC_SPIN_R1_FREQ_B, m_spinFreqB[0]);
	//DDX_Control(pDX, IDC_SPIN_R2_FREQ_B, m_spinFreqB[1]);
}

BEGIN_MESSAGE_MAP(COmniRIG_ClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DIALOG_VISIBLE, &COmniRIG_ClientDlg::OnBnClickedDialogVisible)
	//ON_BN_CLICKED(IDC_BTN_R1_FREQ, &COmniRIG_ClientDlg::OnBnClickedBtnR1Freq)
	//ON_BN_CLICKED(IDC_BTN_R2_FREQ, &COmniRIG_ClientDlg::OnBnClickedBtnR2Freq)
	ON_BN_CLICKED(IDC_BTN_R1_FREQ_A, &COmniRIG_ClientDlg::OnBnClickedBtnR1FreqA)
	ON_BN_CLICKED(IDC_BTN_R2_FREQ_A, &COmniRIG_ClientDlg::OnBnClickedBtnR2FreqA)
	ON_BN_CLICKED(IDC_BTN_R1_FREQ_B, &COmniRIG_ClientDlg::OnBnClickedBtnR1FreqB)
	//ON_BN_CLICKED(IDC_BTN_R2_FREQ_B, &COmniRIG_ClientDlg::OnBnClickedBtnR2FreqB)
	ON_CBN_SELCHANGE(IDC_R1_MODE, &COmniRIG_ClientDlg::OnCbnSelchangeR1Mode)
	ON_CBN_SELCHANGE(IDC_R2_MODE, &COmniRIG_ClientDlg::OnCbnSelchangeR2Mode)
	ON_BN_CLICKED(IDC_CHECK_R1_SPLIT, &COmniRIG_ClientDlg::OnBnClickedCheckR1Split)
	ON_BN_CLICKED(IDC_CHECK_R2_SPLIT, &COmniRIG_ClientDlg::OnBnClickedCheckR2Split)
	ON_BN_CLICKED(IDC_RADIO_R1_VFO_A, &COmniRIG_ClientDlg::OnBnClickedRadioR1VfoA)
	ON_BN_CLICKED(IDC_RADIO_R1_VFO_B, &COmniRIG_ClientDlg::OnBnClickedRadioR1VfoB)
	ON_BN_CLICKED(IDC_RADIO_R2_VFO_A, &COmniRIG_ClientDlg::OnBnClickedRadioR2VfoA)
	ON_BN_CLICKED(IDC_RADIO_R2_VFO_B, &COmniRIG_ClientDlg::OnBnClickedRadioR2VfoB)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(COmniRIG_ClientDlg, CCmdTarget)
	DISP_FUNCTION_ID(COmniRIG_ClientDlg, "VisibleChange", 0x1, VisibleChange, VT_EMPTY, /*VTS_BSTR VTS_BSTR VTS_BSTR*/VTS_NONE)
	DISP_FUNCTION_ID(COmniRIG_ClientDlg, "RigTypeChange", 0x2, RigTypeChange, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(COmniRIG_ClientDlg, "StatusChange",  0x3, StatusChange, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(COmniRIG_ClientDlg, "ParamsChange",  0x4, ParamsChange, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(COmniRIG_ClientDlg, "CustomReply",   0x5, CustomReply, VT_EMPTY, VTS_I4 VTS_VARIANT VTS_VARIANT)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(COmniRIG_ClientDlg, CCmdTarget)
    INTERFACE_PART(COmniRIG_ClientDlg, __uuidof(IOmniRigXEvents), Dispatch)
END_INTERFACE_MAP()

// COmniRIG_ClientDlg message handlers

BOOL COmniRIG_ClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	for(int nIndex = 0; nIndex < MAX_RADIO; nIndex++)
	{
		//m_spinFreq[nIndex].SetRange32(0, 0x7FFFFFFF);
		m_spinFreqA[0].SetRange32(0, 0x7FFFFFFF);
		m_spinFreqB[0].SetRange32(0, 0x7FFFFFFF);
	}

	try 
	{
		// Connect to OmniRif if it is running
		HRESULT hr = m_pOmniRig.GetActiveObject("OmniRig.OmniRigX");
		if (FAILED(hr)) 
			_com_issue_error(hr);
	}
	catch (_com_error& e)
	{
		UNUSED(e);

		// Start a new instance of OnmiRig
		HRESULT hr = m_pOmniRig.CreateInstance("OmniRig.OmniRigX", NULL, CLSCTX_LOCAL_SERVER);
		if (FAILED(hr)) 
		{
			//_com_issue_error(hr);
			MessageBox(_T("Application will exit.\nReason: could not connect to OmniRig."), _T("Fatal Error"), MB_OK|MB_ICONERROR);
			exit(EXIT_FAILURE);
		}
	}

	LPUNKNOWN pUnkSink = GetIDispatch(FALSE);
	VERIFY(AfxConnectionAdvise(m_pOmniRig, __uuidof(IOmniRigXEvents), pUnkSink, FALSE, &m_dwCookie));

	VisibleChange();

	for (int nRigNumber = 1; nRigNumber <= MAX_RADIO; nRigNumber++)
	{
		RigTypeChange(nRigNumber);
		StatusChange(nRigNumber);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COmniRIG_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COmniRIG_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COmniRIG_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT COmniRIG_ClientDlg::VisibleChange()
{
	BOOL bIsVisible = m_pOmniRig->GetDialogVisible();
	//m_btnDialogVisible.SetCheck(bIsVisible ? BST_CHECKED : BST_UNCHECKED);
	return 0L;
}

HRESULT COmniRIG_ClientDlg::RigTypeChange(long RigNumber)
{
	TRACE("IOmniRigXEvents: RigTypeChange (RigNumber=%ld)\n", RigNumber);

	IRigXPtr pRig = (RigNumber == 1) ? m_pOmniRig->Rig1 : m_pOmniRig->Rig2;
	int nRigIndex = RigNumber - 1;
	m_lReadable[nRigIndex] = pRig->GetReadableParams();
	m_lWriteable[nRigIndex] = pRig->GetWriteableParams();

	//m_editFreq[nRigIndex].EnableWindow(m_lReadable[nRigIndex] & PM_FREQ);
	m_editFreqA[0].EnableWindow(m_lReadable[0] & PM_FREQA);
	m_editFreqB[0].EnableWindow(m_lReadable[0] & PM_FREQB);

	//m_spinFreq[nRigIndex].EnableWindow(m_lReadable[nRigIndex] & PM_FREQ);
	m_spinFreqA[0].EnableWindow(m_lReadable[0] & PM_FREQA);
	m_spinFreqB[0].EnableWindow(m_lReadable[0] & PM_FREQB);

	//m_btnFreq[nRigIndex].EnableWindow(m_lWriteable[nRigIndex] & PM_FREQ);
	m_btnFreqA[nRigIndex].EnableWindow(m_lWriteable[nRigIndex] & PM_FREQA);
	//m_btnFreqB[nRigIndex].EnableWindow(m_lWriteable[nRigIndex] & PM_FREQB);

	int nZIndex;
	m_cboxMode[nRigIndex].ResetContent();
	if (m_lReadable[nRigIndex] & PM_CW_U)
	{
		nZIndex = m_cboxMode[nRigIndex].AddString(_TEXT("CW"));
		m_cboxMode[nRigIndex].SetItemData(nZIndex, PM_CW_U);
	}
	if (m_lReadable[nRigIndex] & PM_CW_L)
	{
		nZIndex = m_cboxMode[nRigIndex].AddString(_TEXT("CW-R"));
		m_cboxMode[nRigIndex].SetItemData(nZIndex, PM_CW_L);
	}
	if (m_lReadable[nRigIndex] & PM_SSB_U)
	{
		nZIndex = m_cboxMode[nRigIndex].AddString(_TEXT("USB"));
		m_cboxMode[nRigIndex].SetItemData(nZIndex, PM_SSB_U);
	}
	if (m_lReadable[nRigIndex] & PM_SSB_L)
	{
		nZIndex = m_cboxMode[nRigIndex].AddString(_TEXT("LSB"));
		m_cboxMode[nRigIndex].SetItemData(nZIndex, PM_SSB_L);
	}
	if (m_lReadable[nRigIndex] & PM_DIG_U)
	{
		nZIndex = m_cboxMode[nRigIndex].AddString(_TEXT("FSK-R"));
		m_cboxMode[nRigIndex].SetItemData(nZIndex, PM_DIG_U);
	}
	if (m_lReadable[nRigIndex] & PM_DIG_L)
	{
		nZIndex = m_cboxMode[nRigIndex].AddString(_TEXT("FSK"));
		m_cboxMode[nRigIndex].SetItemData(nZIndex, PM_DIG_L);
	}
	if (m_lReadable[nRigIndex] & PM_AM)
	{
		nZIndex = m_cboxMode[nRigIndex].AddString(_TEXT("AM"));
		m_cboxMode[nRigIndex].SetItemData(nZIndex, PM_AM);
	}
	if (m_lReadable[nRigIndex] & PM_FM)
	{
		nZIndex = m_cboxMode[nRigIndex].AddString(_TEXT("FM"));
		m_cboxMode[nRigIndex].SetItemData(nZIndex, PM_FM);
	}
	m_cboxMode[nRigIndex].EnableWindow(m_cboxMode[nRigIndex].GetCount());

	m_radioVfoA[nRigIndex].EnableWindow(m_lReadable[nRigIndex] & (PM_VFOAA|PM_VFOAB|PM_VFOA));
	m_radioVfoB[nRigIndex].EnableWindow(m_lReadable[nRigIndex] & (PM_VFOBA|PM_VFOBB|PM_VFOB));

	m_checkSplit[nRigIndex].EnableWindow(m_lReadable[nRigIndex] & PM_SPLITON);

	ParamsChange(RigNumber, PM_FREQ);
	ParamsChange(RigNumber, PM_FREQA);
	ParamsChange(RigNumber, PM_FREQB);
	ParamsChange(RigNumber, PM_FREQB);
	ParamsChange(RigNumber, PM_CW_U);
	ParamsChange(RigNumber, PM_SPLITON);
	ParamsChange(RigNumber, PM_VFOAA);

	m_staticRig[0].SetWindowText(pRig->GetRigType());
	
	return 0L;
}

HRESULT COmniRIG_ClientDlg::StatusChange(long RigNumber)
{
	TRACE("IOmniRigXEvents: StatusChange (RigNumber=%ld)\n", RigNumber);

	int nRigIndex = RigNumber - 1;
	IRigXPtr pRig = (RigNumber == 1) ? m_pOmniRig->Rig1 : m_pOmniRig->Rig2;
	LPCTSTR lpszStatus = g_lpszRigStatus[pRig->GetStatus()];
	m_staticStatus[0].SetWindowText(lpszStatus);

	return 0L;
}

HRESULT COmniRIG_ClientDlg::ParamsChange(long RigNumber, long Params)
{
	TRACE("IOmniRigXEvents: ParamsChange (RigNumber=%ld, Params=%ld)\n", RigNumber, Params);
	
	if (RigNumber < 1 || RigNumber > MAX_RADIO)
		return 0L;

	int nRigIndex = RigNumber - 1;

	IRigXPtr pRig = (RigNumber == 1) ? m_pOmniRig->Rig1 : m_pOmniRig->Rig2;

	if (Params & PM_FREQ)
		m_lFreq[nRigIndex] = pRig->GetFreq();
	if (Params & PM_FREQA)
	{
		m_lFreqA[0] = pRig->GetFreqA();
		
		CString freq;
		freq.Format(_T("%08ld"), pRig->GetFreqA());
		CString *digit = new CString;

		for (int i = 0; i < 8; i++)
		{
			if (freq == "00000000")
				break;
			*digit = freq[i];
			const wchar_t* s = digit->GetString();
			SetDlgItemText(IDCSTATIC7 - i, s);
		}	
	}
	if (Params & PM_FREQB)
		m_lFreqB[nRigIndex] = pRig->GetFreqB();
	if (Params & (PM_CW_U|PM_CW_L|PM_SSB_U|PM_SSB_L|PM_DIG_U|PM_DIG_L|PM_AM|PM_FM))
		m_cboxMode[nRigIndex].SetCurItem(pRig->GetMode());
	if (Params & (PM_SPLITON|PM_SPLITOFF|PM_VFOAB|PM_VFOBA))
		m_checkSplit[nRigIndex].SetCheck((pRig->GetSplit() == PM_SPLITON) ? BST_CHECKED : BST_UNCHECKED);
	if (Params & (PM_VFOAA|PM_VFOAB|PM_VFOA|PM_VFOBA|PM_VFOBB|PM_VFOB))
	{
		int nVfo = pRig->GetVfo();		
		m_radioVfoA[nRigIndex].SetCheck((nVfo & (PM_VFOAA|PM_VFOAB|PM_VFOA)) ? BST_CHECKED : BST_UNCHECKED);
		m_radioVfoB[nRigIndex].SetCheck((nVfo & (PM_VFOBA|PM_VFOBB|PM_VFOB)) ? BST_CHECKED : BST_UNCHECKED);
	}

	UpdateData(0);
	
	return 0;
}

HRESULT COmniRIG_ClientDlg::CustomReply(long RigNumber, const _variant_t & Command, const _variant_t & Reply)
{
	CString strCommand, strReply;

	if (Command.vt == VT_BSTR)
		strCommand = Command.bstrVal;
	else
		strCommand = "???";
	if (Reply.vt == VT_BSTR)
		strReply = Reply.bstrVal;
	else
		strReply = "???";

	TRACE("IOmniRigXEvents: CustomReply (RigNumber=%ld, Command='%s', Reply='%s')\n", RigNumber, Command, Reply);
	return 0;
}

void COmniRIG_ClientDlg::SetFreq(long RigNumber, long lFrequency)
{
	IRigXPtr pRig = (RigNumber == 1) ? m_pOmniRig->Rig1 : m_pOmniRig->Rig2;
	int nRigIndex = RigNumber - 1;

	UpdateData(TRUE);
	pRig->PutFreq(lFrequency);
}

void COmniRIG_ClientDlg::SetFreqA(long RigNumber, long lFrequency)
{
	IRigXPtr pRig = (RigNumber == 1) ? m_pOmniRig->Rig1 : m_pOmniRig->Rig2;
	int nRigIndex = RigNumber - 1;

	UpdateData(TRUE);
	pRig->PutFreqA(lFrequency);
}

void COmniRIG_ClientDlg::SetFreqB(long RigNumber, long lFrequency)
{
	IRigXPtr pRig = (RigNumber == 1) ? m_pOmniRig->Rig1 : m_pOmniRig->Rig2;
	int nRigIndex = RigNumber - 1;

	UpdateData(TRUE);
	pRig->PutFreqB(lFrequency);
}

void COmniRIG_ClientDlg::SetVfo(long RigNumber, int nVfo)
{
	IRigXPtr pRig = (RigNumber == 1) ? m_pOmniRig->Rig1 : m_pOmniRig->Rig2;
	int nRigIndex = RigNumber - 1;

	if (m_lWriteable[0] & (PM_VFOA|PM_VFOB))
	{
		pRig->PutVfo((nVfo == VFO_A) ? PM_VFOA : PM_VFOB);
	}
	else if (m_lWriteable[nRigIndex] & (PM_VFOAA|PM_VFOAB|PM_VFOBA|PM_VFOBB))
	{
		if (nVfo == VFO_A)
			pRig->PutVfo((pRig->GetSplit() == PM_SPLITON) ? PM_VFOAB : PM_VFOAA);
		else
			pRig->PutVfo((pRig->GetSplit() == PM_SPLITON) ? PM_VFOBA : PM_VFOBB);
	}
	else
		ASSERT(FALSE);
}

void COmniRIG_ClientDlg::SetMode(long RigNumber, RigParamX Mode)
{
	IRigXPtr pRig = (RigNumber == 1) ? m_pOmniRig->Rig1 : m_pOmniRig->Rig2;
	pRig->PutMode(Mode);
}

void COmniRIG_ClientDlg::SetSplit(long RigNumber, BOOL bIsSplit)
{
	IRigXPtr pRig = (RigNumber == 1) ? m_pOmniRig->Rig1 : m_pOmniRig->Rig2;
	int nRigIndex = RigNumber - 1;

	if (m_lWriteable[nRigIndex] & PM_SPLITON)
	{
		pRig->PutSplit(bIsSplit ? PM_SPLITON : PM_SPLITOFF);
	}
	else if (m_lWriteable[nRigIndex] & (PM_VFOAA|PM_VFOAB|PM_VFOBA|PM_VFOBB))
	{
		RigParamX vfo = pRig->GetVfo();
		if (bIsSplit)
			pRig->PutVfo((vfo & (PM_VFOAA|PM_VFOAB)) ? PM_VFOBA : PM_VFOAB);
		else
			pRig->PutVfo((vfo & (PM_VFOAA|PM_VFOAB)) ? PM_VFOBB : PM_VFOAA);
	}
	else
		ASSERT(FALSE);
}

void COmniRIG_ClientDlg::OnBnClickedDialogVisible()
{
	BOOL bIsVisible = (m_btnDialogVisible.GetCheck() == BST_CHECKED);
	m_pOmniRig->PutDialogVisible(bIsVisible);
}

void COmniRIG_ClientDlg::OnBnClickedBtnR1Freq()
{
	UpdateData(TRUE);
	SetFreq(RIG1, m_lFreq[0]);
}

void COmniRIG_ClientDlg::OnBnClickedBtnR2Freq()
{
	UpdateData(TRUE);
	SetFreq(RIG2, m_lFreq[1]);
}

void COmniRIG_ClientDlg::OnBnClickedBtnR1FreqA()
{
	UpdateData(TRUE);
	SetFreqA(RIG1, m_lFreqA[0]);
}

void COmniRIG_ClientDlg::OnBnClickedBtnR2FreqA()
{
	//UpdateData(TRUE);
	//SetFreqA(RIG2, m_lFreqA[1]);
}

void COmniRIG_ClientDlg::OnBnClickedBtnR1FreqB()
{
	UpdateData(TRUE);
	SetFreqB(RIG1, m_lFreqB[0]);
}

void COmniRIG_ClientDlg::OnBnClickedBtnR2FreqB()
{
	//UpdateData(TRUE);
	//SetFreqB(RIG2, m_lFreq[1]);
}

void COmniRIG_ClientDlg::OnBnClickedRadioR1VfoA()
{
	SetVfo(RIG1, VFO_A);
}

void COmniRIG_ClientDlg::OnBnClickedRadioR1VfoB()
{
	SetVfo(RIG1, VFO_B);
}

void COmniRIG_ClientDlg::OnBnClickedRadioR2VfoA()
{
	SetVfo(RIG2, VFO_A);
}

void COmniRIG_ClientDlg::OnBnClickedRadioR2VfoB()
{
	SetVfo(RIG2, VFO_B);
}

void COmniRIG_ClientDlg::OnCbnSelchangeR1Mode()
{
	RigParamX mode = (RigParamX) m_cboxMode[0].GetCurItem();
	SetMode(RIG1, mode);
}

void COmniRIG_ClientDlg::OnCbnSelchangeR2Mode()
{
	RigParamX mode = (RigParamX) m_cboxMode[1].GetCurItem();
	SetMode(RIG2, mode);
}

void COmniRIG_ClientDlg::OnBnClickedCheckR1Split()
{
	BOOL bSplitToggle = (m_checkSplit[0].GetCheck() == BST_CHECKED);
	SetSplit(RIG1, bSplitToggle);
}

void COmniRIG_ClientDlg::OnBnClickedCheckR2Split()
{
	BOOL bSplitToggle = (m_checkSplit[1].GetCheck() == BST_CHECKED);
	SetSplit(RIG2, bSplitToggle);
}