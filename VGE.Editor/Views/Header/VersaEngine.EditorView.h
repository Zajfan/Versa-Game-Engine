// VersaEngine.EditorView.h : interface of the CVersaEngineEditorView class
//

#pragma once

#include "Graph.h" // Make sure to include your Graph.h header

class CVersaEngineEditorView : public CScrollView // Change to CScrollView for scrolling and zooming
{
protected: // create from serialization only
    CVersaEngineEditorView() noexcept;
    DECLARE_DYNCREATE(CVersaEngineEditorView)

    // Attributes
public:
    CVersaEngineEditorDoc* GetDocument() const;

    // Operations
public:

    // Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt); // Add mouse wheel handler for zooming

protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

    // Implementation
public:
    virtual ~CVersaEngineEditorView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // Generated message map functions
protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point); // Remove unused parameter warning
    DECLARE_MESSAGE_MAP()

private:
    Graph m_graph; // Add a Graph object to the view
    Node* m_selectedNode = nullptr; // Add a selected node pointer
    bool m_isDraggingNode = false;
    CPoint m_dragOffset;
    float m_zoomFactor = 1.0f; // Add a zoom factor

    CPoint GetPinScreenCoordinates(Node* node, Pin* pin); // Helper function to get pin screen coordinates
};

#ifndef _DEBUG  // debug version in VersaEngine.EditorView.cpp
inline CVersaEngineEditorDoc* CVersaEngineEditorView::GetDocument() const
{
    return reinterpret_cast<CVersaEngineEditorDoc*>(m_pDocument);
}
#endif