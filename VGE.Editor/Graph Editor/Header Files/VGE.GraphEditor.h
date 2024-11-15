#pragma once
#ifndef VGE_GRAPH_EDITOR_H
#define VGE_GRAPH_EDITOR_H

#include "VGE.Editor.h"

namespace VGE
{
	class GraphEditor
	{
	public:
		GraphEditor();
		~GraphEditor();
		void Initialize();
		void Run();
		void Shutdown();
		Editor* GetEditor() { return m_Editor; }
		Core* GetCore() { return m_Editor->GetCore(); }
		Game* GetGame() { return m_Editor->GetGame(); }
		Graphics* GetGraphics() { return m_Editor->GetGraphics(); }
		Input* GetInput() { return m_Editor->GetInput(); }
		Physics* GetPhysics() { return m_Editor->GetPhysics(); }
		Resources* GetResources() { return m_Editor->GetResources(); }
		Scene* GetScene() { return m_Editor->GetScene(); }
		UI* GetUI() { return m_Editor->GetUI(); }
		Window* GetWindow() { return m_Editor->GetWindow(); }
	private:
		Editor* m_Editor;
	};
}

#endif // VGE_GRAPH_EDITOR_H
