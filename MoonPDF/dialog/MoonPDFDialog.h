#pragma once
#include <afxdialogex.h>
#include <functional>
/*******************************************************************************************
 * 说明：用于加载pdf的对话框类，所有的pdf操作业务都由该类实现，pdf的相关实现是采用开源的
 *		 mupdf框架。
 * 作者：代浩然
 * 时间：2019-5-26 16:41
 ******************************************************************************************/
//回调事件的定义
typedef std::function<void(LONG)> PdfCurrentPageIndexChanged;//pdf当前显示页发生改变的回调函数定义

//PDF对话框类
class CMoonPDFDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMoonPDFDialog)

public:
	CMoonPDFDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMoonPDFDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public://事件
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
private:
	BOOL m_bVisiableMenu;//是否显示菜单
	BOOL m_bEnableScrollToZoom;//是否使能按住ctrl键滚动缩放
	BOOL m_bEnableScrollToPage;//是否使能滚动翻页
	PdfCurrentPageIndexChanged m_funcPdfCurrentPageIndexChanged;//pdf当前页发生改变
	LONG m_lCurrentPageIndex;//当前显示的页索引
private:
	//pdf绘制到界面上
	void WinBlit();
	//处理鼠标事件
	void HandleMouse(int x, int y, int btn, int state);
	//创建弹出菜单
	void CreatePopMenu();
	//打开文件选择框并且打开pdf文件
	void OpenFileSlectWndAndOpenPdf();
//外部函数
public:
	//获取窗体句柄
	HWND GetHWnd();
	//获取CDC
	HDC GetHdc();
	//打开本地pdf
	void OpenLocalPdf(CString pdfPath);
	//设置控件右键菜单显示隐藏
	void SetPopMenuVisiable(BOOL bVisiable);
	//获取pdf页的数量
	UINT GetPdfPageCount();
	//跳转到具体的页
	void GotoPage(UINT number);
	//是否使能按住ctrl键滚动缩放
	void EnableScrollToZoom(BOOL bEnable);
	//是否使能滚动翻页
	void EnableScrollToPage(BOOL bEnable);
	//获取当前pdf页索引
	LONG GetCurrentPageIndex();

public:
	//注册当前页改变事件
	void RegistCurrentPageChangeEvent(PdfCurrentPageIndexChanged funcPdfCurrentPageIndexChanged);
};
