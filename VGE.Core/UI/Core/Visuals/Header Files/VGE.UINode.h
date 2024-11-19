#pragma once
#ifndef VGE_UINODE_H
#define VGE_UINODE_H

#include "VGE.UIBase.h"

namespace VGE
{
	class UINode : public UIBase
	{
	public:
		UINode();
		virtual ~UINode();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
	};
}

#endif // VGE_UINODE_H
