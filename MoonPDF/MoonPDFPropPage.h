#pragma once

// MoonPDFPropPage.h : CMoonPDFPropPage 属性页类的声明。


// CMoonPDFPropPage : 有关实现的信息，请参阅 MoonPDFPropPage.cpp。

class CMoonPDFPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMoonPDFPropPage)
	DECLARE_OLECREATE_EX(CMoonPDFPropPage)

// 构造函数
public:
	CMoonPDFPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_MOONPDF };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

