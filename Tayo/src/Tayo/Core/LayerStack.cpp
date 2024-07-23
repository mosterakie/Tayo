#include "typch.h"

#include "LayerStack.h"

namespace Tayo {
	LayerStack::LayerStack()
	{
		
	}

	LayerStack::~LayerStack()
	{
		for each (Layer * layer in m_Layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto iter = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (iter != m_Layers.end())
		{
			m_Layers.erase(iter);
			m_LayerInsertIndex--;
			layer->OnDetach();
		}
	}

	void LayerStack::PushOverLay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopOverLay(Layer* overlay)
	{
		auto iter = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (iter != m_Layers.end())
		{
			m_Layers.erase(iter);
			overlay->OnDetach();
		}
	}

}