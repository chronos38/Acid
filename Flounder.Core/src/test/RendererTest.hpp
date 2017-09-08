﻿#pragma once

#include "../renderer/irenderer.hpp"

namespace Flounder
{
	class renderertest :
		public IRenderer
	{
	private:
		shader *m_shader;
	public:
		renderertest();

		~renderertest();

		void Render(const Vector4 &clipPlane, const ICamera &camera) override;
	};
}