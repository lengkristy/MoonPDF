#include "MoonPDFDialogTools.h"
#include "MoonPDFDialog.h"

/***********************************************************变量定义*******************************************/
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif
#define MIN(x,y) ((x) < (y) ? (x) : (y))
extern CMoonPDFDialog *g_pMoonPdfDialog;
extern HCURSOR arrowcurs, handcurs, waitcurs, caretcurs;
extern pdfapp_t g_app;//pdf app全局变量
static int justcopied = 0;
extern BITMAPINFO *dibinf;
static int timer_pending = 0;
static wchar_t wbuf[PATH_MAX];
static char filename[PATH_MAX];

/*
* Dialog boxes
*/

void winwarn(pdfapp_t *app, char *msg)
{
	//MessageBoxA(hwndframe, msg, "MuPDF: Warning", MB_ICONWARNING);
}

void winerror(pdfapp_t *app, char *msg)
{
	//MessageBoxA(hwndframe, msg, "MuPDF: Error", MB_ICONERROR);
	exit(1);
}

void wintitle(pdfapp_t *app, char *title)
{
	wchar_t wide[256], *dp;
	char *sp;
	int rune;

	dp = wide;
	sp = title;
	while (*sp && dp < wide + 255)
	{
		sp += fz_chartorune(&rune, sp);
		*dp++ = rune;
	}
	*dp = 0;

	SetWindowTextW(g_pMoonPdfDialog->GetHWnd(), wide);
}

void winresize(pdfapp_t *app, int w, int h)
{
	ShowWindow(g_pMoonPdfDialog->GetHWnd(), SW_SHOWDEFAULT);
	w += GetSystemMetrics(SM_CXFRAME) * 2;
	h += GetSystemMetrics(SM_CYFRAME) * 2;
	h += GetSystemMetrics(SM_CYCAPTION);
	SetWindowPos(g_pMoonPdfDialog->GetHWnd(), 0, 0, 0, w, h, SWP_NOZORDER | SWP_NOMOVE);
}

void winrepaint(pdfapp_t *app)
{
	InvalidateRect(g_pMoonPdfDialog->GetHWnd(), NULL, 0);
}

void winrepaintsearch(pdfapp_t *app)
{
	// TODO: invalidate only search area and
	// call only search redraw routine.
	InvalidateRect(g_pMoonPdfDialog->GetHWnd(), NULL, 0);
}

char *winpassword(pdfapp_t *app, char *filename)
{
	return NULL;
}

char *wintextinput(pdfapp_t *app, char *inittext, int retry)
{
	return NULL;
}

int winchoiceinput(pdfapp_t *app, int nopts, const char *opts[], int *nvals, const char *vals[])
{
	return 0;
}
void winopenuri(pdfapp_t *app, char *buf)
{
	//ShellExecuteA(hwndframe, "open", buf, 0, 0, SW_SHOWNORMAL);
}

void wincursor(pdfapp_t *app, int curs)
{
	if (curs == ARROW)
		SetCursor(arrowcurs);
	if (curs == HAND)
		SetCursor(handcurs);
	if (curs == WAIT)
		SetCursor(waitcurs);
	if (curs == CARET)
		SetCursor(caretcurs);
}

/*
* Event handling
*/

void windocopy(pdfapp_t *app)
{
	HGLOBAL handle;
	unsigned short *ucsbuf;

	if (!OpenClipboard(g_pMoonPdfDialog->GetHWnd()))
		return;
	EmptyClipboard();

	handle = GlobalAlloc(GMEM_MOVEABLE, 4096 * sizeof(unsigned short));
	if (!handle)
	{
		CloseClipboard();
		return;
	}

	ucsbuf = (unsigned short *)GlobalLock(handle);
	pdfapp_oncopy(&g_app, ucsbuf, 4096);
	GlobalUnlock(handle);

	SetClipboardData(CF_UNICODETEXT, handle);
	CloseClipboard();

	justcopied = 1;	/* keep inversion around for a while... */
}

void windrawrect(pdfapp_t *app, int x0, int y0, int x1, int y1)
{
	RECT r;
	r.left = x0;
	r.top = y0;
	r.right = x1;
	r.bottom = y1;
	FillRect(g_pMoonPdfDialog->GetHdc(), &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
}

void windrawstring(pdfapp_t *app, int x, int y, char *s)
{
	HFONT font = (HFONT)GetStockObject(ANSI_FIXED_FONT);
	SelectObject(g_pMoonPdfDialog->GetHdc(), font);
	TextOutA(g_pMoonPdfDialog->GetHdc(), x, y - 12, s, (int)strlen(s));
}

static void
do_close(pdfapp_t *app)
{
	fz_context *ctx = app->ctx;
	pdfapp_close(app);
	free(dibinf);
	fz_drop_context(ctx);
}

void winclose(pdfapp_t *app)
{
	if (pdfapp_preclose(app))
	{
		do_close(app);
		exit(0);
	}
}

void winfullscreen(pdfapp_t *app, int state)
{
	static WINDOWPLACEMENT savedplace;
	static int isfullscreen = 0;
	if (state && !isfullscreen)
	{
		GetWindowPlacement(g_pMoonPdfDialog->GetHWnd(), &savedplace);
		SetWindowLong(g_pMoonPdfDialog->GetHWnd(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
		SetWindowPos(g_pMoonPdfDialog->GetHWnd(), NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowWindow(g_pMoonPdfDialog->GetHWnd(), SW_SHOWMAXIMIZED);
		isfullscreen = 1;
	}
	if (!state && isfullscreen)
	{
		SetWindowLong(g_pMoonPdfDialog->GetHWnd(), GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(g_pMoonPdfDialog->GetHWnd(), NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
		SetWindowPlacement(g_pMoonPdfDialog->GetHWnd(), &savedplace);
		isfullscreen = 0;
	}
}

int winsavequery(pdfapp_t *app)
{
	switch (MessageBoxA(g_pMoonPdfDialog->GetHWnd(), "File has unsaved changes. Do you want to save", "MuPDF", MB_YESNOCANCEL))
	{
	case IDYES: return SAVE;
	case IDNO: return DISCARD;
	default: return CANCEL;
	}
}

int winquery(pdfapp_t *app, const char *query)
{
	switch (MessageBoxA(g_pMoonPdfDialog->GetHWnd(), query, "MuPDF", MB_YESNOCANCEL))
	{
	case IDYES: return QUERY_YES;
	case IDNO:
	default: return QUERY_NO;
	}
}

int wingetcertpath(char *buf, int len)
{
	return 0;
}

int wingetsavepath(pdfapp_t *app, char *buf, int len)
{
	wchar_t twbuf[PATH_MAX];
	OPENFILENAME ofn;

	wcscpy(twbuf, wbuf);
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_pMoonPdfDialog->GetHWnd();
	ofn.lpstrFile = twbuf;
	ofn.nMaxFile = PATH_MAX;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = L"MuPDF: Save PDF file";
	ofn.lpstrFilter = L"PDF Documents (*.pdf)\0*.pdf\0All Files\0*\0\0";
	ofn.Flags = OFN_HIDEREADONLY;
	if (GetSaveFileName(&ofn))
	{
		int code = WideCharToMultiByte(CP_UTF8, 0, twbuf, -1, buf, MIN(PATH_MAX, len), NULL, NULL);
		if (code == 0)
		{
			winerror(&g_app, "cannot convert filename to utf-8");
			return 0;
		}

		wcscpy(wbuf, twbuf);
		strcpy(filename, buf);
		return 1;
	}
	else
	{
		return 0;
	}
}

void winalert(pdfapp_t *app, pdf_alert_event *alert)
{
	int buttons = MB_OK;
	int icon = MB_ICONWARNING;
	int pressed = PDF_ALERT_BUTTON_NONE;

	switch (alert->icon_type)
	{
	case PDF_ALERT_ICON_ERROR:
		icon = MB_ICONERROR;
		break;
	case PDF_ALERT_ICON_WARNING:
		icon = MB_ICONWARNING;
		break;
	case PDF_ALERT_ICON_QUESTION:
		icon = MB_ICONQUESTION;
		break;
	case PDF_ALERT_ICON_STATUS:
		icon = MB_ICONINFORMATION;
		break;
	}

	switch (alert->button_group_type)
	{
	case PDF_ALERT_BUTTON_GROUP_OK:
		buttons = MB_OK;
		break;
	case PDF_ALERT_BUTTON_GROUP_OK_CANCEL:
		buttons = MB_OKCANCEL;
		break;
	case PDF_ALERT_BUTTON_GROUP_YES_NO:
		buttons = MB_YESNO;
		break;
	case PDF_ALERT_BUTTON_GROUP_YES_NO_CANCEL:
		buttons = MB_YESNOCANCEL;
		break;
	}

	pressed = MessageBoxA(g_pMoonPdfDialog->GetHWnd(), alert->message, alert->title, icon | buttons);

	switch (pressed)
	{
	case IDOK:
		alert->button_pressed = PDF_ALERT_BUTTON_OK;
		break;
	case IDCANCEL:
		alert->button_pressed = PDF_ALERT_BUTTON_CANCEL;
		break;
	case IDNO:
		alert->button_pressed = PDF_ALERT_BUTTON_NO;
		break;
	case IDYES:
		alert->button_pressed = PDF_ALERT_BUTTON_YES;
	}
}


void winprint(pdfapp_t *app)
{
	MessageBoxA(g_pMoonPdfDialog->GetHWnd(), "The MuPDF library supports printing, but this application currently does not", "Print document", MB_ICONWARNING);
}

#define OUR_TIMER_ID 1

void winadvancetimer(pdfapp_t *app, float delay)
{
	timer_pending = 1;
	SetTimer(g_pMoonPdfDialog->GetHWnd(), OUR_TIMER_ID, (unsigned int)(1000 * delay), NULL);
}

void winreplacefile(char *source, char *target)
{
	wchar_t wsource[PATH_MAX];
	wchar_t wtarget[PATH_MAX];

	int sz = MultiByteToWideChar(CP_UTF8, 0, source, -1, wsource, PATH_MAX);
	if (sz == 0)
	{
		winerror(&g_app, "cannot convert filename to Unicode");
		return;
	}

	sz = MultiByteToWideChar(CP_UTF8, 0, target, -1, wtarget, PATH_MAX);
	if (sz == 0)
	{
		winerror(&g_app, "cannot convert filename to Unicode");
		return;
	}

#if (_WIN32_WINNT >= 0x0500)
	ReplaceFile(wtarget, wsource, NULL, REPLACEFILE_IGNORE_MERGE_ERRORS, NULL, NULL);
#else
	DeleteFile(wtarget);
	MoveFile(wsource, wtarget);
#endif
}

void wincopyfile(char *source, char *target)
{
	wchar_t wsource[PATH_MAX];
	wchar_t wtarget[PATH_MAX];

	int sz = MultiByteToWideChar(CP_UTF8, 0, source, -1, wsource, PATH_MAX);
	if (sz == 0)
	{
		winerror(&g_app, "cannot convert filename to Unicode");
		return;
	}

	sz = MultiByteToWideChar(CP_UTF8, 0, target, -1, wtarget, PATH_MAX);
	if (sz == 0)
	{
		winerror(&g_app, "cannot convert filename to Unicode");
		return;
	}

	CopyFile(wsource, wtarget, FALSE);
}

void winreloadpage(pdfapp_t *app)
{
	SendMessage(g_pMoonPdfDialog->GetHWnd(), WM_APP, 0, 0);
}

