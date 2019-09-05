// MoonPDFCtrl.cpp : CMoonPDFCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "MoonPDF.h"
#include "MoonPDFCtrl.h"
#include "MoonPDFPropPage.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMoonPDFCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CMoonPDFCtrl, COleControl)
	ON_MESSAGE(OCM_COMMAND, &CMoonPDFCtrl::OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CMoonPDFCtrl, COleControl)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "OpenLocalPdf", dispidOpenLocalPdf, OpenLocalPdf, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "SetPopMenuVisiable", dispidSetPopMenuVisiable, SetPopMenuVisiable, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "GetPdfPageCount", dispidGetPdfPageCount, GetPdfPageCount, VT_UI4, VTS_NONE)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "GotoPage", dispidGotoPage, GotoPage, VT_EMPTY, VTS_UI4)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "EnableScrollToZoom", dispidEnableScrollToZoom, EnableScrollToZoom, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "EnableScrollToPage", dispidEnableScrollToPage, EnableScrollToPage, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "GetCurrentPageIndex", dispidGetCurrentPageIndex, GetCurrentPageIndex, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "ExtractPageToSave", dispidExtractPageToSave, ExtractPageToSave, VT_I2, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "PdfZoomIn", dispidPdfZoomIn, PdfZoomIn, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "PdfZoomOut", dispidPdfZoomOut, PdfZoomOut, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "PdfClockwiseRotation", dispidPdfClockwiseRotation, PdfClockwiseRotation, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CMoonPDFCtrl, "PdfContrarotate", dispidPdfContrarotate, PdfContrarotate, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CMoonPDFCtrl, COleControl)
	EVENT_CUSTOM_ID("OnCurrentPageChanged", eventidOnCurrentPageChanged, OnCurrentPageChanged, VTS_I4)
END_EVENT_MAP()

// 属性页

// TODO: 根据需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CMoonPDFCtrl, 1)
	PROPPAGEID(CMoonPDFPropPage::guid)
END_PROPPAGEIDS(CMoonPDFCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CMoonPDFCtrl, "MOONPDF.MoonPDFCtrl.1",
	0x8c99f46d, 0x8421, 0x478e, 0x97, 0x87, 0x5d, 0x42, 0x4d, 0x21, 0x5a, 0x2f)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CMoonPDFCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DMoonPDF = { 0x50FEEB59, 0x40AA, 0x4376, { 0xA6, 0x25, 0xB7, 0xE1, 0xCE, 0xAD, 0xC4, 0xD8 } };
const IID IID_DMoonPDFEvents = { 0x91A28D6A, 0x936C, 0x4DEF, { 0x81, 0x2D, 0x2F, 0x6E, 0x83, 0x10, 0x86, 0x17 } };

// 控件类型信息

static const DWORD _dwMoonPDFOleMisc =
	OLEMISC_SIMPLEFRAME |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMoonPDFCtrl, IDS_MOONPDF, _dwMoonPDFOleMisc)

// CMoonPDFCtrl::CMoonPDFCtrlFactory::UpdateRegistry -
// 添加或移除 CMoonPDFCtrl 的系统注册表项

BOOL CMoonPDFCtrl::CMoonPDFCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegInsertable | afxRegApartmentThreading 改为 afxRegInsertable。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MOONPDF,
			IDB_MOONPDF,
			afxRegInsertable | afxRegApartmentThreading,
			_dwMoonPDFOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CMoonPDFCtrl::CMoonPDFCtrl - 构造函数

CMoonPDFCtrl::CMoonPDFCtrl()
{
	InitializeIIDs(&IID_DMoonPDF, &IID_DMoonPDFEvents);

	EnableSimpleFrame();
	// TODO:  在此初始化控件的实例数据。

	m_pMoonPDFDialog = NULL;
}

// CMoonPDFCtrl::~CMoonPDFCtrl - 析构函数

CMoonPDFCtrl::~CMoonPDFCtrl()
{
	// TODO:  在此清理控件的实例数据。

	//释放PDF对话框类
	if (m_pMoonPDFDialog != NULL)
	{
		delete m_pMoonPDFDialog;
	}
}

// CMoonPDFCtrl::OnDraw - 绘图函数

void CMoonPDFCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	DoSuperclassPaint(pdc, rcBounds);
	m_pMoonPDFDialog->MoveWindow(rcBounds, TRUE);//对话框显示到控件的rcBounds全范围。
}

// CMoonPDFCtrl::DoPropExchange - 持久性支持

void CMoonPDFCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}


// CMoonPDFCtrl::OnResetState - 将控件重置为默认状态

void CMoonPDFCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}


// CMoonPDFCtrl::AboutBox - 向用户显示“关于”框

void CMoonPDFCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_MOONPDF);
	dlgAbout.DoModal();
}


// CMoonPDFCtrl::PreCreateWindow - 修改 CreateWindowEx 的参数

BOOL CMoonPDFCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("STATIC");
	BOOL bRet = COleControl::PreCreateWindow(cs);
	cs.hMenu = NULL;
	return bRet;
}

// CMoonPDFCtrl::IsSubclassedControl - 这是一个子类控件

BOOL CMoonPDFCtrl::IsSubclassedControl()
{
	return TRUE;
}

// CMoonPDFCtrl::OnOcmCommand - 处理命令消息

LRESULT CMoonPDFCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
	WORD wNotifyCode = HIWORD(wParam);

	// TODO:  在此接通 wNotifyCode。

	return 0;
}


// CMoonPDFCtrl 消息处理程序


int CMoonPDFCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	//创建PDF对话框类
	m_pMoonPDFDialog = new CMoonPDFDialog();
	m_pMoonPDFDialog->Create(IDD_MAIN_DIALOG, this);
	m_pMoonPDFDialog->ShowWindow(SW_SHOW);

	//注册回调事件
	RegistCallbackEvent();
	return 0;
}

void CMoonPDFCtrl::RegistCallbackEvent()//注册回调事件
{
	PdfCurrentPageIndexChanged funcPdfCurrentPageIndexChanged = std::bind(&CMoonPDFCtrl::OnCurrentPageChanged, this, std::placeholders::_1);
	m_pMoonPDFDialog->RegistCurrentPageChangeEvent(funcPdfCurrentPageIndexChanged);
}


void CMoonPDFCtrl::OpenLocalPdf(LPCTSTR pdfPathName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	this->m_pMoonPDFDialog->OpenLocalPdf(pdfPathName);
}


void CMoonPDFCtrl::SetPopMenuVisiable(VARIANT_BOOL bVisiable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	this->m_pMoonPDFDialog->SetPopMenuVisiable(bVisiable);
}


LONG CMoonPDFCtrl::GetPdfPageCount()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	return this->m_pMoonPDFDialog->GetPdfPageCount();
}


void CMoonPDFCtrl::GotoPage(LONG number)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	this->m_pMoonPDFDialog->GotoPage(number);
}


void CMoonPDFCtrl::EnableScrollToZoom(VARIANT_BOOL bEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	this->m_pMoonPDFDialog->EnableScrollToZoom(bEnable);
}


void CMoonPDFCtrl::EnableScrollToPage(VARIANT_BOOL bEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	this->m_pMoonPDFDialog->EnableScrollToPage(bEnable);
}


LONG CMoonPDFCtrl::GetCurrentPageIndex()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	return this->m_pMoonPDFDialog->GetCurrentPageIndex();
}


SHORT CMoonPDFCtrl::ExtractPageToSave(LONG pageIndex, LPCTSTR newPdfPath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (this->m_pMoonPDFDialog->ExtractPageToSave(pageIndex, newPdfPath))
		return 0;
	else
		return -1;
}


void CMoonPDFCtrl::PdfZoomIn()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	this->m_pMoonPDFDialog->PdfZoomIn();
}


void CMoonPDFCtrl::PdfZoomOut()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	this->m_pMoonPDFDialog->PdfZoomOut();
}


void CMoonPDFCtrl::PdfClockwiseRotation()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	this->m_pMoonPDFDialog->PdfClockwiseRotation();
}


void CMoonPDFCtrl::PdfContrarotate()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	this->m_pMoonPDFDialog->PdfContrarotate();
}
