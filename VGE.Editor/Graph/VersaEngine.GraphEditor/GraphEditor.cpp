#include "stdafx.h"
#include "VersaEngine.Editor.h" 
#include "GraphEditor.h"
#include "GraphEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGraphEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CGraphEditorView, CScrollView) // Changed base class to CScrollView
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSEWHEEL() // Added mouse wheel handler
    ON_WM_RBUTTONDOWN()

    ON_COMMAND(ID_CREATE_NODE, &CGraphEditorView::OnCreateNode) // Example command IDs
    ON_COMMAND(ID_DELETE_NODE, &CGraphEditorView::OnDeleteNode)
    // ... (Map other messages and commands as needed)
END_MESSAGE_MAP()

// CGraphEditorView construction/destruction

CGraphEditorView::CGraphEditorView()
{
    // TODO: Initialize your Graph object here (or pass it in the constructor)
}

CGraphEditorView::~CGraphEditorView()
{
}

BOOL CGraphEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CScrollView::PreCreateWindow(cs); // Changed base class to CScrollView
}

// CGraphEditorView drawing

void CGraphEditorView::OnDraw(CDC* pDC)
{
    CGraphEditorDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // Apply zoom and pan transformations to the device context
    pDC->SetMapMode(MM_ANISOTROPIC);
    pDC->SetWindowExt(100, 100); // Example initial extents, adjust as needed
    pDC->SetViewportExt((int)(100 * m_zoomFactor), (int)(100 * m_zoomFactor));
    pDC->SetWindowOrg(-m_scrollPos.x, -m_scrollPos.y);

    // Render connections
    for (Connection* connection : m_graph.Connections)
    {
        // TODO: Get screen coordinates for source and target pin positions
        CPoint sourcePos, targetPos;

        pDC->MoveTo(sourcePos);
        pDC->LineTo(targetPos);
    }

    // Render nodes
    for (Node* node : m_graph.Nodes)
    {
        CRect rect(node->Position.x, node->Position.y,
            node->Position.x + node->Size.x, node->Position.y + node->Size.y);
        pDC->FillSolidRect(rect, RGB(200, 200, 200)); // Example fill color
        pDC->Draw3dRect(rect, RGB(0, 0, 0), RGB(0, 0, 0)); // Example border color
        pDC->DrawText(CString(node->Name.c_str()), rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
}

// ... (CGraphEditorView printing - unchanged)

// CGraphEditorView message handlers

void CGraphEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Handle mouse click (node selection, connection start, etc.)
    CScrollView::OnLButtonDown(nFlags, point); // Changed base class to CScrollView
}

void CGraphEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Handle mouse release (node dragging end, connection end, etc.)
    CScrollView::OnLButtonUp(nFlags, point); // Changed base class to CScrollView
}

void CGraphEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Handle mouse move (node dragging, connection preview, etc.)
    CScrollView::OnMouseMove(nFlags, point); // Changed base class to CScrollView
}

BOOL CGraphEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
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

void CGraphEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
    ClientToScreen(&point); // Convert client coordinates to screen coordinates
    ShowContextMenu(point);
}

void CGraphEditorView::OnCreateNode()
{
    // TODO: Implement logic to create a new node at the mouse position
}

void CGraphEditorView::OnDeleteNode()
{
    if (m_selectedNode)
    {
        m_graph.RemoveNode(m_selectedNode);
        m_selectedNode = nullptr;
        Invalidate(); // Redraw the canvas
    }
}

// ... (Implement other message handlers and methods)