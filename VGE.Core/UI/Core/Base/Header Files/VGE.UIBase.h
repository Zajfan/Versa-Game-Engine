#pragma once
#ifndef VGE_UI_BASE_H
#define VGE_UI_BASE_H

#include "VGE.Core.h"

namespace VGE
{
	class VGE_API UIBase
	{
	public:
		UIBase();
		virtual ~UIBase();
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
	protected:
		Vector2 m_Position;
		Vector2 m_Size;
		bool m_Visible;
	};
}

#endif // VGE_UI_BASE_H