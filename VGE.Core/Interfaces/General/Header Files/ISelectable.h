#pragma once
#ifndef ISELECTABLE_H
#define ISELECTABLE_H

#include <string>

namespace vge
{
	class ISelectable
	{
	public:
		ISelectable();
		virtual ~ISelectable();
		virtual void Select();
		virtual void Deselect();
		virtual bool IsSelected();
	protected:
		bool m_Selected;
	};
}

#endif // ISELECTABLE_H