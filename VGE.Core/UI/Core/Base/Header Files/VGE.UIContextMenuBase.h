#pragma once
#ifndef VGE_UI_CONTEXT_MENU_BASE_H
#define VGE_UI_CONTEXT_MENU_BASE_H

#include "VGE.UIBase.h"

namespace VGE
{
	class UIContextMenuBase : public UIBase
	{
	public:
		UIContextMenuBase();
		virtual ~UIContextMenuBase();
		virtual void Initialize();
		virtual void Update();
		virtual void Render();
		virtual void Release();
		virtual void SetPosition(const Vector2& position);
		virtual void SetPosition(float x, float y);
		virtual void SetPositionX(float x);
		virtual void SetPositionY(float y);
		virtual void SetSize(const Vector2& size);
		virtual void SetSize(float width, float height);
		virtual void SetWidth(float width);
		virtual void SetHeight(float height);
		virtual void SetVisible(bool visible);
		virtual void AddItem(const std::string& text, const std::function<void()>& callback);
		virtual void AddItem(const std::string& text, const std::function<void()>& callback, const std::function<bool()>& condition);
		virtual void RemoveItem(const std::string& text);
		virtual void RemoveItem(const std::function<void()>& callback);
		virtual void ClearItems();
		virtual void SetItemEnabled(const std::string& text, bool enabled);
		virtual void SetItemEnabled(const std::function<void()>& callback, bool enabled);
		virtual void SetItemVisible(const std::string& text, bool visible);
		virtual void SetItemVisible(const std::function<void()>& callback, bool visible);
		virtual void SetItemText(const std::string& text, const std::string& newText);
		virtual void SetItemText(const std::function<void()>& callback, const std::string& newText);
		virtual void SetItemCallback(const std::string& text, const std::function<void()>& newCallback);
		virtual void SetItemCallback(const std::function<void()>& callback, const std::function<void()>& newCallback);
		virtual void SetItemCondition(const std::string& text, const std::function<bool()>& newCondition);
		virtual void SetItemCondition(const std::function<void()>& callback, const std::function<bool()>& newCondition);
		virtual void SetItemData(const std::string& text, void* data);
		virtual void SetItemData(const std::function<void()>& callback, void* data);
		virtual void* GetItemData(const std::string& text);
		virtual void* GetItemData(const std::function<void()>& callback);
		virtual void SetItemDataInt(const std::string& text, int data);
		virtual void SetItemDataInt(const std::function<void()>& callback, int data);

	protected:
		virtual void OnItemClicked(const std::function<void()>& callback);
		virtual void OnItemHovered(const std::function<void()>& callback);
		virtual void OnItemUnhovered(const std::function<void()>& callback);
		virtual void OnItemVisibleChanged(const std::function<void()>& callback);
		virtual void OnItemEnabledChanged(const std::function<void()>& callback);
		virtual void OnItemTextChanged(const std::function<void()>& callback);
		virtual void OnItemDataChanged(const std::function<void()>& callback);
		virtual void OnItemDataIntChanged(const std::function<void()>& callback);
		virtual void OnItemConditionChanged(const std::function<void()>& callback);
	};

}

#endif // VGE_UI_CONTEXT_MENU_BASE_H
