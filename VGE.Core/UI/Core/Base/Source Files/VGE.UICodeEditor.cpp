#include "VGE.UICodeEditor.h"
#include "VGE.UIManager.h"
#include "VGE.UIText.h"
#include "VGE.UIScrollBar.h"
#include "VGE.UITextArea.h"
#include "VGE.UIButton.h"
#include "VGE.UIPanel.h"
#include "VGE.UIWindow.h"
#include "VGE.UIListBox.h"
#include "VGE.UIComboBox.h"
#include "VGE.UIRadioButton.h"
#include "VGE.UICheckBox.h"
#include "VGE.UIProgressBar.h"
#include "VGE.UISlider.h"
#include "VGE.UITabControl.h"
#include "VGE.UITabPage.h"
#include "VGE.UITreeView.h"
#include "VGE.UITreeViewNode.h"

namespace VGE {
	UICodeEditor::UICodeEditor() : UIElement() {
		m_Type = UIElementType::CodeEditor;
		m_IsVisible = false;
		m_IsEnabled = true;
		m_IsDragging = false;
		m_IsScrolling = false;
		m_IsResizing = false;
		m_IsDraggingWindow = false;
		m_IsDraggingTab = false;
		m_IsDraggingNode = false;
		m_IsDraggingItem = false;
		m_IsDraggingThumb = false;
		m_IsDraggingSlider = false;
		m_IsDraggingScrollBar = false;
		m_IsDraggingSplitter = false;
		m_IsDraggingHandle = false;
		m_IsDraggingCorner = false;
		m_IsDraggingBorder = false;
		m_IsDraggingBackground = false;
		m_IsDraggingForeground = false;
		m_IsDraggingSelection = false;
		m_IsDraggingText = false;
		m_IsDraggingIcon = false;
		m_IsDraggingImage = false;
		m_IsDraggingColor = false;
		m_IsDraggingValue = false;
		m_IsDraggingProgress = false;
		m_IsDraggingPosition = false;
		m_IsDraggingSize = false;
		m_IsDraggingScale = false;
		m_IsDraggingRotation = false;
		m_IsDraggingAnchor = false;
		m_IsDraggingPivot = false;
		m_IsDraggingOrigin = false;
		m_IsDraggingDestination = false;
		m_IsDraggingSource = false;
		m_IsDraggingTarget = false;
		m_IsDraggingStart = false;
		m_IsDraggingEnd = false;
		m_IsDraggingCenter = false;
		m_IsDraggingHandle = false;
		m_IsDraggingCorner = false;
		m_IsDraggingBorder = false;
		m_IsDraggingBackground = false;
		m_IsDraggingForeground = false;
		m_IsDraggingSelection = false;
		m_IsDraggingText = false;
		m_IsDraggingIcon = false;
		m_IsDraggingImage = false;
		m_IsDraggingColor = false;
		m_IsDraggingValue = false;
		m_IsDraggingProgress = false;
		m_IsDraggingPosition = false;
		m_IsDraggingSize = false;
		m_IsDraggingScale = false;
		m_IsDraggingRotation = false;
		m_IsDraggingAnchor = false;
		m_IsDraggingPivot = false;
		m_IsDraggingOrigin = false;
		m_IsDraggingDestination = false;
		m_IsDraggingSource = false;
	};
}