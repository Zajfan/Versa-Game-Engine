// VersaEngine.EditorView.cpp : implementation of the CVersaEngineEditorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VersaEngine.Editor.h"
#endif

#include "VersaEngine.EditorDoc.h"
#include "VersaEngine.EditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CVersaEngineEditorView

IMPLEMENT_DYNCREATE(CVersaEngineEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CVersaEngineEditorView, CScrollView)
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CVersaEngineEditorView::OnFilePrintPreview)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_WM_LBUTTONDOWN() // Add left mouse button down message handler
    ON_WM_LBUTTONUP()   // Add left mouse button up message handler
    ON_WM_MOUSEMOVE()   // Add mouse move message handler
    ON_WM_MOUSEWHEEL()   // Add mouse wheel message handler
END_MESSAGE_MAP()

// CVersaEngineEditorView construction/destruction

CVersaEngineEditorView::CVersaEngineEditorView() noexcept
{
    // TODO: add construction code here
}

CVersaEngineEditorView::~CVersaEngineEditorView()
{
}

BOOL CVersaEngineEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

// CVersaEngineEditorView drawing

void CVersaEngineEditorView::OnDraw(CDC* pDC)
{
    CVersaEngineEditorDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // Apply zoom and pan transformations
    pDC->SetMapMode(MM_ANISOTROPIC);
    pDC->SetWindowExt(100, 100);
    pDC->SetViewportExt((int)(100 * m_zoomFactor), (int)(100 * m_zoomFactor));
    pDC->SetWindowOrg(-m_scrollPos.x, -m_scrollPos.y);

    // Render connections
    for (Connection* connection : m_graph.Connections)
    {
        CPoint sourcePoint = GetPinScreenCoordinates(connection->Source, connection->SourcePin);
        CPoint targetPoint = GetPinScreenCoordinates(connection->Target, connection->TargetPin);

        pDC->MoveTo(sourcePoint);
        pDC->LineTo(targetPoint);
    }

    // Render nodes
    for (Node* node : m_graph.Nodes)
    {
        CRect nodeRect(node->Position.x, node->Position.y,
            node->Position.x + node->Size.x, node->Position.y + node->Size.y);

        COLORREF nodeColor = RGB(node->Color.x * 255, node->Color.y * 255, node->Color.z * 255);
        CBrush nodeBrush(nodeColor);
        CPen nodePen(PS_SOLID, 2, RGB(0, 0, 0));

        CPen* oldPen = pDC->SelectObject(&nodePen);
        CBrush* oldBrush = pDC->SelectObject(&nodeBrush);

        switch (node->Shape)
        {
        case Node::NodeShape::Rectangle:
            pDC->Rectangle(nodeRect);
            break;
        case Node::NodeShape::RoundedRectangle:
            pDC->RoundRect(nodeRect, CPoint(10, 10));
            break;
        case Node::NodeShape::Circle:
            pDC->Ellipse(nodeRect);
            break;
        default:
            pDC->Rectangle(nodeRect);
            break;
        }

        pDC->SelectObject(oldPen);
        pDC->SelectObject(oldBrush);

        pDC->DrawText(CString(node->Name.c_str()), nodeRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        // (Optional) Draw icon if available
        // if (!node->Icon.empty()) { ... } 
    }
}

// ... (CVersaEngineEditorView printing)

// CVersaEngineEditorView message handlers

void CVersaEngineEditorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
    AFXPrintPreview(this);
#endif
}

BOOL CVersaEngineEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CVersaEngineEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CVersaEngineEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

void CVersaEngineEditorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CVersaEngineEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// Handlers for mouse interactions
void CVersaEngineEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Handle left mouse button down (e.g., select node, start connection)
    CScrollView::OnLButtonDown(nFlags, point);
}

void CVersaEngineEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Handle left mouse button up (e.g., end node drag, end connection)
    CScrollView::OnLButtonUp(nFlags, point);
}

void CVersaEngineEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Handle mouse move (e.g., drag node, draw connection preview)
    CScrollView::OnMouseMove(nFlags, point);
}

BOOL CVersaEngineEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    // Zoom in/out based on mouse wheel delta
    if (zDelta > 0)
    {
        m_zoomFactor *= 1.1f;
    }
    else
    {
        m_zoomFactor /= 1.1f;
    }

    Invalidate(); // Redraw the canvas
    return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

// ... (CVersaEngineEditorView diagnostics)
// CVersaEngineEditorView message handlers
