// MoonPDFDialog.cpp : 实现文件
//

#include "../stdafx.h"
#include "../MoonPDF.h"
#include "MoonPDFDialog.h"
#include "afxdialogex.h"
#include "../common/StringHelper.h"

/**************************************************************全局变量定义**********************************/
CMoonPDFDialog *g_pMoonPdfDialog;//全局对话框对象
pdfapp_t g_app;//pdf app全局变量
HCURSOR arrowcurs, handcurs, waitcurs, caretcurs;//光标
BITMAPINFO *dibinf = NULL;//位图信息
fz_context *ctx = NULL;
HBRUSH bgbrush; //画刷
int justcopied = 0;

// CMoonPDFDialog 对话框

IMPLEMENT_DYNAMIC(CMoonPDFDialog, CDialogEx)

CMoonPDFDialog::CMoonPDFDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
	g_pMoonPdfDialog = this;
	m_bVisiableMenu = TRUE;
	m_bEnableScrollToZoom = TRUE;
	m_bEnableScrollToPage = TRUE;
	m_funcPdfCurrentPageIndexChanged = NULL;
	m_lCurrentPageIndex = 0L;
}

CMoonPDFDialog::~CMoonPDFDialog()
{
	//释放相关资源
	fz_context *ctx = g_app.ctx;
	pdfapp_close(&g_app);
	if (dibinf != NULL)
	{
		free(dibinf);
	}
	if (ctx != NULL)
	{
		fz_drop_context(ctx);
	}
}

void CMoonPDFDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMoonPDFDialog, CDialogEx)

	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

int CMoonPDFDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//初始化pdf环境
	ctx = fz_new_context(NULL, NULL, FZ_STORE_DEFAULT);
	if (!ctx)
	{
		MessageBoxA(NULL, "cannot initialise pdf context", "error", MB_OK);
		exit(1);
	}
	pdfapp_init(ctx, &g_app);

	//创建光标
	arrowcurs = LoadCursor(NULL, IDC_ARROW);
	handcurs = LoadCursor(NULL, IDC_HAND);
	waitcurs = LoadCursor(NULL, IDC_WAIT);
	caretcurs = LoadCursor(NULL, IDC_IBEAM);

	/* 创建背景颜色 */
	bgbrush = CreateSolidBrush(RGB(0x70, 0x70, 0x70));

	/* Init DIB info for buffer */
	dibinf = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 12);
	dibinf->bmiHeader.biSize = sizeof(dibinf->bmiHeader);
	dibinf->bmiHeader.biPlanes = 1;
	dibinf->bmiHeader.biBitCount = 32;
	dibinf->bmiHeader.biCompression = BI_RGB;
	dibinf->bmiHeader.biXPelsPerMeter = 2834;
	dibinf->bmiHeader.biYPelsPerMeter = 2834;
	dibinf->bmiHeader.biClrUsed = 0;
	dibinf->bmiHeader.biClrImportant = 0;
	dibinf->bmiHeader.biClrUsed = 0;


	SetCursor(arrowcurs);
	//测试打开
	//pdfapp_open(&g_app, "C:\\Users\\lengkristy\\Desktop\\0d6a0c09d6504308b45814d363f02e90.pdf", 0);

	return 0;
}

void CMoonPDFDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
					   //
	WinBlit();
}

void CMoonPDFDialog::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bVisiableMenu)
	{
		CreatePopMenu();
	}

	CDialogEx::OnRButtonDown(nFlags, point);
}

BOOL CMoonPDFDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	UINT uMsg = LOWORD(wParam);
	switch (uMsg)
	{
	case ID_RIGHT_MENU_ITEM_OPEN:
		OpenFileSlectWndAndOpenPdf();
		break;
	default:
		break;
	}
	return CDialogEx::OnCommand(wParam, lParam);
}

void CMoonPDFDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	//设置pdf显示区域的大小
	pdfapp_onresize(&g_app, cx, cy);
}

BOOL CMoonPDFDialog::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//根据鼠标滚动进行翻页，如果按住ctrl键，那么进行方法缩小
	static int oldx = 0;
	static int oldy = 0;
	if (zDelta <= 0)
	{
		HandleMouse(oldx, oldy, 5, 1);
		HandleMouse(oldx, oldy, 5, -1);
	}
	else
	{
		HandleMouse(oldx, oldy, 4, 1);
		HandleMouse(oldx, oldy, 4, -1);
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt); 
}

void CMoonPDFDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetFocus();
	HandleMouse(point.x, point.y, 3, 1);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMoonPDFDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HandleMouse(point.x, point.y, 0, 0);
	CDialogEx::OnMouseMove(nFlags, point);
}

void CMoonPDFDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	HandleMouse(point.x, point.y, 3, -1);
	CDialogEx::OnLButtonUp(nFlags, point);
}

/////////////////////////////////////////////外部函数//////////////////////////////////////////////////////
HWND CMoonPDFDialog::GetHWnd()
{
	return this->m_hWnd;
}

HDC CMoonPDFDialog::GetHdc()
{
	CDC* pORIDC = this->GetDC();
	HDC hdc = pORIDC->GetSafeHdc();
	return hdc;
}

//设置控件右键菜单显示隐藏
void CMoonPDFDialog::SetPopMenuVisiable(BOOL bVisiable)
{
	this->m_bVisiableMenu = bVisiable;
}

//打开pdf
void CMoonPDFDialog::OpenLocalPdf(CString pdfPath)
{
	//打开之前先关闭
	pdfapp_close(&g_app);
	string path = StringHelper::UnicodeToUTF8(pdfPath.GetBuffer());
	char cpath[1024] = { 0 };
	sprintf(cpath, "%s", path.c_str());
	pdfapp_open(&g_app, cpath, 1);
	pdfPath.ReleaseBuffer();
	//重绘窗体
	this->UpdateWindow();
	m_lCurrentPageIndex = g_app.pageno;
}

////////////////////////////////////////////////////////////private////////////////////////////////////////////////////////

//处理鼠标事件
void CMoonPDFDialog::HandleMouse(int x, int y, int btn, int state)
{
	int modifier = (GetAsyncKeyState(VK_SHIFT) < 0);
	modifier |= ((GetAsyncKeyState(VK_CONTROL) < 0) << 2);

	if (state != 0 && justcopied)
	{
		justcopied = 0;
		winrepaint(&g_app);
	}

	if (state == 1)
		SetCapture();
	if (state == -1)
		ReleaseCapture();
	//当modifier为4、5的时候会按住ctrl键滚动缩放，下面代码不允许滚动缩放
	if ((modifier == 4 || modifier == 5) && !this->m_bEnableScrollToZoom)
	{
		modifier = 0;
	}
	//当鼠标滚动或者按住shift键滚动的时候，pdf会翻页
	if (!(modifier == 4 || modifier == 5) && !this->m_bEnableScrollToPage)
	{
		return;
	}
	pdfapp_onmouse(&g_app, x, y, btn, modifier, state);

	//判断是否翻页了，如果pdf滚动翻页了，将新页码事件通知到外部
	if (this->m_lCurrentPageIndex != g_app.pageno)
	{
		this->m_lCurrentPageIndex = g_app.pageno;
		if (m_funcPdfCurrentPageIndexChanged != NULL)//回调通知外部事件
		{
			m_funcPdfCurrentPageIndexChanged(this->m_lCurrentPageIndex);
		}
	}
}

//pdf绘制到界面上
void CMoonPDFDialog::WinBlit()
{
	if (!g_app.image)
	{
		return;
	}
	int image_w = fz_pixmap_width(g_app.ctx, g_app.image);
	int image_h = fz_pixmap_height(g_app.ctx, g_app.image);
	int image_n = fz_pixmap_components(g_app.ctx, g_app.image);
	unsigned char *samples = fz_pixmap_samples(g_app.ctx, g_app.image);
	int x0 = g_app.panx;
	int y0 = g_app.pany;
	int x1 = g_app.panx + image_w;
	int y1 = g_app.pany + image_h;
	RECT r;
	HBRUSH brush;

	if (g_app.image)
	{
		if (g_app.iscopying || justcopied)
		{
			pdfapp_invert(&g_app, g_app.selr);
			justcopied = 1;
		}

		pdfapp_inverthit(&g_app);

		dibinf->bmiHeader.biWidth = image_w;
		dibinf->bmiHeader.biHeight = -image_h;
		dibinf->bmiHeader.biSizeImage = image_h * 4;

		if (image_n == 2)
		{
			int i = image_w * image_h;
			unsigned char *color = (unsigned char*)malloc(i * 4);
			unsigned char *s = samples;
			unsigned char *d = color;
			for (; i > 0; i--)
			{
				d[2] = d[1] = d[0] = *s++;
				d[3] = *s++;
				d += 4;
			}
			SetDIBitsToDevice(this->GetHdc(),
				g_app.panx, g_app.pany, image_w, image_h,
				0, 0, 0, image_h, color,
				dibinf, DIB_RGB_COLORS);
			free(color);
		}
		if (image_n == 4)
		{
			SetDIBitsToDevice(this->GetHdc(),
				g_app.panx, g_app.pany, image_w, image_h,
				0, 0, 0, image_h, samples,
				dibinf, DIB_RGB_COLORS);
		}

		pdfapp_inverthit(&g_app);

		if (g_app.iscopying || justcopied)
		{
			pdfapp_invert(&g_app, g_app.selr);
			justcopied = 1;
		}
	}

	if (g_app.invert)
		brush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	else
		brush = bgbrush;

	/* Grey background */
	r.top = 0; r.bottom = g_app.winh;
	r.left = 0; r.right = x0;
	FillRect(this->GetHdc(), &r, brush);
	r.left = x1; r.right = g_app.winw;
	FillRect(this->GetHdc(), &r, brush);
	r.left = 0; r.right = g_app.winw;
	r.top = 0; r.bottom = y0;
	FillRect(this->GetHdc(), &r, brush);
	r.top = y1; r.bottom = g_app.winh;
	FillRect(this->GetHdc(), &r, brush);
}

//创建菜单
void CMoonPDFDialog::CreatePopMenu()
{
	//动态创建弹出菜单  
	CMenu menu;
	menu.CreatePopupMenu(); //创建一个弹出菜单
	menu.AppendMenuW(MF_BYCOMMAND | MF_STRING, ID_RIGHT_MENU_ITEM_OPEN, _T("打开（OPEN）")); //添加子菜单项  

	menu.AppendMenuW(MF_BYCOMMAND | MF_STRING, ID_RIGHT_MENU_ITEM_SAVE, _T("保存（SAVE）"));

	menu.AppendMenuW(MF_SEPARATOR);//分隔符

	CPoint point;//定义一个用于确定光标位置的位置

	GetCursorPos(&point);//获取当前光标的位置，以便使得菜单可以跟随光标 

	menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this); //加载弹出菜单 
}

//打开文件选择框并且打开pdf文件
void CMoonPDFDialog::OpenFileSlectWndAndOpenPdf()
{
	CString strFile = _T("");
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.pdf)|*.pdf|All Files (*.*)|*.*||"), NULL);
	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
	}
	if (strFile.IsEmpty())
	{
		return;
	}
	OpenLocalPdf(strFile);
}

//获取pdf页的数量
UINT CMoonPDFDialog::GetPdfPageCount()
{
	return g_app.pagecount;
}

//跳转到具体的页
void CMoonPDFDialog::GotoPage(UINT number)
{
	if (m_lCurrentPageIndex != number && number <= GetPdfPageCount() && 1 <= number)//当前页不等于跳转的页，并且要跳转的页大于等于1且小于等于总页数
	{
		pdfapp_gotopage(&g_app, number);//页面跳转
		if (m_funcPdfCurrentPageIndexChanged != NULL)//回调通知外部事件
		{
			m_funcPdfCurrentPageIndexChanged(number);
		}
	}
	
}

//是否使能按住ctrl键滚动缩放
void CMoonPDFDialog::EnableScrollToZoom(BOOL bEnable)
{
	m_bEnableScrollToZoom = bEnable;
}

//是否使能滚动翻页
void CMoonPDFDialog::EnableScrollToPage(BOOL bEnable)
{
	m_bEnableScrollToPage = bEnable;
}

//获取当前pdf页索引
LONG CMoonPDFDialog::GetCurrentPageIndex()
{
	return g_app.pageno;
}

/**
* 说明：提取pdf页面，然后另存为新的文件
* 参数：
*    pageIndex：提取的页索引
*	  newPdfPath：保存文件的路径
*/
BOOL CMoonPDFDialog::ExtractPageToSave(UINT pageIndex, CString newPdfPath)
{
	pdf_write_options opts = { 0 };
	pdf_document *doc_des = NULL;
	pdf_graft_map *graft_map;
	pdf_parse_write_options(ctx, &opts, "");
	fz_try(ctx)
	{
		doc_des = pdf_create_document(ctx);
	}
	fz_catch(ctx)
	{
		return FALSE;
	}
	if (pageIndex > this->GetPdfPageCount() || pageIndex < 1)
	{
		return FALSE;
	}
	graft_map = pdf_new_graft_map(ctx, doc_des);
	fz_try(ctx)
	{
		this->PageMerge(&g_app, doc_des, pageIndex, -1, graft_map);
	}
	fz_always(ctx)
	{
		pdf_drop_graft_map(ctx, graft_map);
	}
	fz_catch(ctx)
	{
		pdf_drop_document(ctx, doc_des);
		return FALSE;
	}
	fz_try(ctx)
	{
		string path = StringHelper::UnicodeToUTF8(newPdfPath.GetBuffer());
		pdf_save_document(ctx, doc_des, path.c_str(), &opts);
		newPdfPath.ReleaseBuffer();
	}
	fz_always(ctx)
	{
		pdf_drop_document(ctx, doc_des);
	}
	fz_catch(ctx)
	{
		return FALSE;
	}
	return TRUE;
}

/**
* 按比例放大pdf
*/
void CMoonPDFDialog::PdfZoomIn()
{
	pdfapp_zoom_in(&g_app);
}

/**
* 按比例缩小pdf
*/
void CMoonPDFDialog::PdfZoomOut()
{
	pdfapp_zoom_out(&g_app);
}

/**
* 顺时针旋转90度
*/
void CMoonPDFDialog::PdfClockwiseRotation()
{
	pdf_clockwise_rotation(&g_app);
}

/**
* 逆时针旋转90度
*/
void CMoonPDFDialog::PdfContrarotate()
{
	pdf_contrarotate(&g_app);
}

//合并页
void CMoonPDFDialog::PageMerge(pdfapp_t * app, pdf_document *doc_des, int page_from, int page_to, pdf_graft_map *graft_map)
{
	pdf_obj *page_ref;
	pdf_obj *page_dict = NULL;
	pdf_obj *obj;
	pdf_obj *ref = NULL;
	int i;

	/* Copy as few key/value pairs as we can. Do not include items that reference other pages. */
	static pdf_obj * const copy_list[] = {
		PDF_NAME(Contents),
		PDF_NAME(Resources),
		PDF_NAME(MediaBox),
		PDF_NAME(CropBox),
		PDF_NAME(BleedBox),
		PDF_NAME(TrimBox),
		PDF_NAME(ArtBox),
		PDF_NAME(Rotate),
		PDF_NAME(UserUnit)
	};

	fz_var(ref);
	fz_var(page_dict);

	fz_try(app->ctx)
	{
		page_ref = pdf_lookup_page_obj(app->ctx, (pdf_document*)app->doc, page_from - 1);
		pdf_flatten_inheritable_page_items(app->ctx, page_ref);

		/* Make a new page object dictionary to hold the items we copy from the source page. */
		page_dict = pdf_new_dict(app->ctx, doc_des, 4);

		pdf_dict_put(app->ctx, page_dict, PDF_NAME(Type), PDF_NAME(Page));

		for (i = 0; i < nelem(copy_list); i++)
		{
			obj = pdf_dict_get(app->ctx, page_ref, copy_list[i]);
			if (obj != NULL)
				pdf_dict_put_drop(app->ctx, page_dict, copy_list[i], pdf_graft_mapped_object(app->ctx, graft_map, obj));
		}

		/* Add the page object to the destination document. */
		ref = pdf_add_object(app->ctx, doc_des, page_dict);

		/* Insert it into the page tree. */
		pdf_insert_page(app->ctx, doc_des, page_to - 1, ref);
	}
	fz_always(app->ctx)
	{
		pdf_drop_obj(app->ctx, page_dict);
		pdf_drop_obj(app->ctx, ref);
	}
	fz_catch(app->ctx)
	{
		fz_rethrow(app->ctx);
	}
}

/////////////////////////////////////////////////////////外部事件注册/////////////////////////////////////////////
//注册当前页改变事件
void CMoonPDFDialog::RegistCurrentPageChangeEvent(PdfCurrentPageIndexChanged funcPdfCurrentPageIndexChanged)
{
	this->m_funcPdfCurrentPageIndexChanged = funcPdfCurrentPageIndexChanged;
}