#pragma once
#include <vector>
#include "ControlExample.h"

namespace Gallery
{
	class PageBase
	{
	public:
		void addExample(ControlExample&& example);
	};

}