#pragma once
#include "MoonPDFDialog.h"
// MoonPDFCtrl.h : CMoonPDFCtrl ActiveX 控件类的声明。


// CMoonPDFCtrl : 有关实现的信息，请参阅 MoonPDFCtrl.cpp。

class CMoonPDFCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMoonPDFCtrl)

// 构造函数
public:
	CMoonPDFCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CMoonPDFCtrl();

	DECLARE_OLECREATE_EX(CMoonPDFCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CMoonPDFCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMoonPDFCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CMoonPDFCtrl)		// 类型名称和杂项状态

	// 子类控件支持
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidGetCurrentPageIndex = 7L,
		eventidOnCurrentPageChanged = 1L,
		dispidEnableScrollToPage = 6L,
		dispidEnableScrollToZoom = 5L,
		dispidGotoPage = 4L,
		dispidGetPdfPageCount = 3L,
		dispidSetPopMenuVisiable = 2L,
		dispidOpenLocalPdf = 1L
	};

//成员变量
private:
	CMoonPDFDialog *m_pMoonPDFDialog;//PDF对话框类

private:
	void RegistCallbackEvent();//注册回调事件
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	//对外部接口，打开本地pdf文件
	void OpenLocalPdf(LPCTSTR pdfPathName);
	//设置控件右键菜单显示隐藏
	void SetPopMenuVisiable(VARIANT_BOOL bVisiable);
	//获取pdf页的数量
	LONG GetPdfPageCount();
	//跳转到具体的页
	void GotoPage(LONG number);
	//是否使能按住ctrl键滚动缩放
	void EnableScrollToZoom(VARIANT_BOOL bEnable);
	//是否使能滚动翻页
	void EnableScrollToPage(VARIANT_BOOL bEnable);
	//获取当前pdf页索引
	LONG GetCurrentPageIndex();

	//当前页发生改变事件
	void OnCurrentPageChanged(LONG lCurrentPageIndex)
	{
		FireEvent(eventidOnCurrentPageChanged, EVENT_PARAM(VTS_I4), lCurrentPageIndex);
	}
	
};

