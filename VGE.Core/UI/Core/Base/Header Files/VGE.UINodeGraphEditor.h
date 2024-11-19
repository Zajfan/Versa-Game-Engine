#pragma once
#ifndef VGE_UINODEGRAPHEDITOR_H
#define VGE_UINODEGRAPHEDITOR_H

#include "VGE.UIBase.h"
#include "VGE.UINodeGraph.h"

namespace VGE
{
	class UINodeGraphEditor : public UIBase
	{
	public:
		UINodeGraphEditor();
		virtual ~UINodeGraphEditor();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		void SetNodeGraph(UINodeGraph* nodeGraph);
		UINodeGraph* GetNodeGraph() const;
	private:
		UINodeGraph* m_NodeGraph;
	};
}

#endif // VGE_UINODEGRAPHEDITOR_H
