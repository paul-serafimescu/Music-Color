
// MusicColorView.cpp : implementation of the CMusicColorView class
//

#include "pch.h"
#include "framework.h"
#include "windows.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MusicColor.h"
#endif

#include "MusicColorDoc.h"
#include "MusicColorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MainFrm.h"


// CMusicColorView

IMPLEMENT_DYNCREATE(CMusicColorView, CView)

BEGIN_MESSAGE_MAP(CMusicColorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMusicColorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMusicColorView construction/destruction

CMusicColorView::CMusicColorView() noexcept
{
	// TODO: add construction code here

}

CMusicColorView::~CMusicColorView()
{
}

BOOL CMusicColorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMusicColorView drawing

void CMusicColorView::OnDraw(CDC* pDC)
{
	CMusicColorDoc* pDoc = GetDocument();
	CMainFrame* pwnd = ((CMainFrame*)(AfxGetApp()->m_pMainWnd));
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->isValid())
	{
		pwnd->FillFileName(pDoc->fileName);
		HDC hdc = pDC->GetSafeHdc();
		COLORREF cref;
		int picSize = pDoc->pictureSize();
		int xStart = 0, yStart = 0;
		for (int cnt = 0; cnt < pDoc->musicSheet.size(); cnt++)
		{
			convertColor(mixColor(pDoc->musicSheet[cnt]), cref);
			if (xStart + pDoc->musicSheet[cnt][0]  > picSize * TIMEBASE)
			{
				yStart += COLORSQSIZE;
				xStart = 0;
			}
			for (int y = 0; y < COLORSQSIZE; y++)
			{
				for (int x = 0; x < pDoc->musicSheet[cnt][0]; x++)
				{
					SetPixel(hdc, xStart + x, yStart + y, cref);
				}
			}
			xStart += pDoc->musicSheet[cnt][0];
		}
		
	}
}

// CMusicColorView printing


void CMusicColorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMusicColorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMusicColorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMusicColorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMusicColorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMusicColorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMusicColorView diagnostics

#ifdef _DEBUG
void CMusicColorView::AssertValid() const
{
	CView::AssertValid();
}

void CMusicColorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMusicColorDoc* CMusicColorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMusicColorDoc)));
	return (CMusicColorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMusicColorView message handlers
