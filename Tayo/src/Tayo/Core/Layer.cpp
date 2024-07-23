#include "typch.h"
#include "Layer.h"

namespace Tayo
{
	Layer::Layer(const std::string& name)
		:m_DebugName(name)
	{

	}

	Layer::~Layer()
	{

	}
	const std::string& Layer::GetName()const
	{ 
		return m_DebugName; 
	}
}