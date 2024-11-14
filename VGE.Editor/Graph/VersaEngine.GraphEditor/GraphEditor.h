#pragma once

#include "Graph.h" // Include the Graph header

class CGraphEditorView : public CScrollView // Derive from CScrollView for scrolling and zooming
{
public:
    CGraphEditorView();
    virtual ~CGraphEditorView();

protected:
    DECLARE_DYNCREATE(CGraphEditorView)

    // Attributes
    Graph m_graph; // Reference to the Graph object

    Node* m_selectedNode = nullptr;
    bool m_isDraggingNode = false;
    CPoint m_dragOffset;
    float m_zoomFactor = 1.0f;

    // Operations
public:
    // ... (Other methods you might need)

    // Overrides
public:
    virtual void OnDraw(CDC* pDC);
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt); // For zooming

protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

    // Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    // Generated message map functions
protected:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point); // For context menu

    afx_msg void OnCreateNode();
    afx_msg void OnDeleteNode();
    // ... (Add other message handlers as needed)
    DECLARE_MESSAGE_MAP()
};