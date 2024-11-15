#pragma once
#ifndef VGE_ENGINE_H
#define VGE_ENGINE_H

#include "VGE.Core.h"
#include "VGE.Game.h"
#include "VGE.Graphics.h"
#include "VGE.Input.h"
#include "VGE.Physics.h"
#include "VGE.Resources.h"
#include "VGE.Scene.h"
#include "VGE.UI.h"
#include "VGE.Utils.h"
#include "VGE.Window.h"

namespace VGE
{
	class Engine
	{
	public:
		Engine();
		~Engine();
		void Initialize();
		void Run();
		void Shutdown();
		Core* GetCore() { return m_Core; }
		Game* GetGame() { return m_Game; }
		Graphics* GetGraphics() { return m_Graphics; }
		Input* GetInput() { return m_Input; }
		Physics* GetPhysics() { return m_Physics; }
		Resources* GetResources() { return m_Resources; }
		Scene* GetScene() { return m_Scene; }
		UI* GetUI() { return m_UI; }
		Window* GetWindow() { return m_Window; }
	private:
		Core* m_Core;
		Game* m_Game;
		Graphics* m_Graphics;
		Input* m_Input;
		Physics* m_Physics;
		Resources* m_Resources;
		Scene* m_Scene;
		UI* m_UI;
		Window* m_Window;
	};
}

#endif // VGE_ENGINE_H
