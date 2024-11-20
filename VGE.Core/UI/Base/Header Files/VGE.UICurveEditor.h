#pragma once
#ifndef VGE_UICURVEEDITOR_H
#define VGE_UICURVEEDITOR_H

#include "VGE.UIBase.h"
#include "VGE.UICurve.h"

namespace VGE
{
	class UICurveEditor : public UIBase
	{
	public:
		UICurveEditor();
		virtual ~UICurveEditor();
		virtual void Update() override;
		virtual void Render() override;
		void SetCurve(UICurve* curve);
		UICurve* GetCurve() const;
		void SetCurveColor(const glm::vec4& color);
		const glm::vec4& GetCurveColor() const;
		void SetCurveWidth(float width);
		float GetCurveWidth() const;
		void SetCurveResolution(int resolution);
		int GetCurveResolution() const;
		void SetCurveVisible(bool visible);
		bool IsCurveVisible() const;
		void SetGridColor(const glm::vec4& color);
		const glm::vec4& GetGridColor() const;
		void SetGridSize(float size);
		float GetGridSize() const;
		void SetGridVisible(bool visible);
		bool IsGridVisible() const;
		void SetGridSnap(bool snap);
		bool IsGridSnap() const;
		void SetGridSnapSize(float size);
		float GetGridSnapSize() const;
		void SetGridSnapColor(const glm::vec4& color);
		const glm::vec4& GetGridSnapColor() const;
		void SetGridSnapWidth(float width);
		float GetGridSnapWidth() const;
		void SetGridSnapResolution(int resolution);
		int GetGridSnapResolution() const;
		void SetGridSnapVisible(bool visible);
		bool IsGridSnapVisible() const;
		void SetGridSnapType(UICurveEditorGridSnapType type);
		UICurveEditorGridSnapType GetGridSnapType() const;
		void SetGridSnapTypeVisible(bool visible);
		bool IsGridSnapTypeVisible() const;
		void SetGridSnapTypeColor(const glm::vec4& color);
		const glm::vec4& GetGridSnapTypeColor() const;
		void SetGridSnapTypeWidth(float width);
		float GetGridSnapTypeWidth() const;
		void SetGridSnapTypeResolution(int resolution);
		int GetGridSnapTypeResolution() const;
		void SetGridSnapTypeOffset(float offset);
		float GetGridSnapTypeOffset() const;
		void SetGridSnapTypeSize(float size);
		float GetGridSnapTypeSize() const;
		void SetGridSnapTypeTextSize(float size);
		float GetGridSnapTypeTextSize() const;
		void SetGridSnapTypeTextVisible(bool visible);
		bool IsGridSnapTypeTextVisible() const;
		void SetGridSnapTypeTextOffset(float offset);
		float GetGridSnapTypeTextOffset() const;
		void SetGridSnapTypeTextResolution(int resolution);
		int GetGridSnapTypeTextResolution() const;

	private:
		UICurve* m_curve;
		glm::vec4 m_curveColor;
		float m_curveWidth;
		int m_curveResolution;
		bool m_curveVisible;
		glm::vec4 m_gridColor;
		float m_gridSize;
		bool m_gridVisible;
		bool m_gridSnap;
		float m_gridSnapSize;
		glm::vec4 m_gridSnapColor;
		float m_gridSnapWidth;
		int m_gridSnapResolution;
		bool m_gridSnapVisible;
		UICurveEditorGridSnapType m_gridSnapType;
		bool m_gridSnapTypeVisible;
		glm::vec4 m_gridSnapTypeColor;
		float m_gridSnapTypeWidth;
		int m_gridSnapTypeResolution;
		float m_gridSnapTypeOffset;
		float m_gridSnapTypeSize;
		float m_gridSnapTypeTextSize;
		bool m_gridSnapTypeTextVisible;
		float m_gridSnapTypeTextOffset;
		int m_gridSnapTypeTextResolution;
	};

}

#endif // VGE_UICURVEEDITOR_H