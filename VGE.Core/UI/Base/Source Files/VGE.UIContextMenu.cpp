#include "VGE.UIContextMenu.h"
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
	UIContextMenu::UIContextMenu() : UIElement() {
		m_Type = UIElementType::ContextMenu;
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
		m_IsDraggingBounds = false;
		m_IsDraggingPadding = false;
		m_IsDraggingMargin = false;
		m_IsDraggingSpacing = false;
		m_IsDraggingRadius = false;
		m_IsDraggingThickness = false;
		m_IsDraggingRadiusX = false;
		m_IsDraggingRadiusY = false;
		m_IsDraggingThicknessX = false;
		m_IsDraggingThicknessY = false;
		m_IsDraggingOffset = false;
		m_IsDraggingOffsetX = false;
		m_IsDraggingOffsetY = false;
		m_IsDraggingOffsetZ = false;
		m_IsDraggingSizeX = false;
		m_IsDraggingSizeY = false;
		m_IsDraggingSizeZ = false;
		m_IsDraggingScaleX = false;
		m_IsDraggingScaleY = false;
		m_IsDraggingScaleZ = false;
		m_IsDraggingRotationX = false;
	};
}