
// LineView.cpp : implementation of the CLineView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Line.h"
#endif

#include "LineDoc.h"
#include "LineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLineView

IMPLEMENT_DYNCREATE(CLineView, CView)

BEGIN_MESSAGE_MAP(CLineView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CLineView construction/destruction

CLineView::CLineView() noexcept
{
	// TODO: add construction code here
	x = 0;
	y = 0;
}

CLineView::~CLineView()
{
}

BOOL CLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLineView drawing

void CLineView::OnDraw(CDC* /*pDC*/)
{
	CLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CLineView printing


void CLineView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLineView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLineView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLineView diagnostics

#ifdef _DEBUG
void CLineView::AssertValid() const
{
	CView::AssertValid();
}

void CLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLineDoc* CLineView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLineDoc)));
	return (CLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CLineView message handlers


void CLineView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	dc.MoveTo(x, y);
	dc.LineTo(point.x, point.y);
	x = point.x;
	y = point.y;
	CView::OnLButtonDown(nFlags, point);
}
