// MoonPDFPropPage.cpp : CMoonPDFPropPage 属性页类的实现。

#include "stdafx.h"
#include "MoonPDF.h"
#include "MoonPDFPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMoonPDFPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CMoonPDFPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CMoonPDFPropPage, "MOONPDF.MoonPDFPropPage.1",
	0x3936d858, 0x49ff, 0x462e, 0x8b, 0xd8, 0x80, 0x37, 0x48, 0x64, 0xb2, 0xe3)

// CMoonPDFPropPage::CMoonPDFPropPageFactory::UpdateRegistry -
// 添加或移除 CMoonPDFPropPage 的系统注册表项

BOOL CMoonPDFPropPage::CMoonPDFPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MOONPDF_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CMoonPDFPropPage::CMoonPDFPropPage - 构造函数

CMoonPDFPropPage::CMoonPDFPropPage() :
	COlePropertyPage(IDD, IDS_MOONPDF_PPG_CAPTION)
{
}

// CMoonPDFPropPage::DoDataExchange - 在页和属性间移动数据

void CMoonPDFPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CMoonPDFPropPage 消息处理程序
