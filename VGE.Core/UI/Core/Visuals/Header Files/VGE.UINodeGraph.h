#pragma once
#ifndef VGE_UINODEGRAPH_H
#define VGE_UINODEGRAPH_H

#include "VGE.UIBase.h"
#include "VGE.UINode.h"

namespace VGE
{
	class UINodeGraph : public UIBase
	{
	public:
		UINodeGraph();
		virtual ~UINodeGraph();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		void AddNode(UINode* node);
		void RemoveNode(UINode* node);
		void ClearNodes();
		const std::vector<UINode*>& GetNodes() const;
	private:
		std::vector<UINode*> m_Nodes;
	};
}

#endif // VGE_UINODEGRAPH_H
