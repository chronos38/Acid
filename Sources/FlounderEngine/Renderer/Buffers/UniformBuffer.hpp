﻿#pragma once

#include "Renderer/Pipelines/Descriptor.hpp"
#include "Renderer/Pipelines/PipelineCreate.hpp"
#include "Renderer/Pipelines/ShaderProgram.hpp"
#include "Buffer.hpp"

namespace Flounder
{
	class F_EXPORT UniformBuffer :
		public Buffer,
		public Descriptor
	{
	private:
		VkDescriptorBufferInfo m_bufferInfo;
	public:
		UniformBuffer(const VkDeviceSize &size);

		~UniformBuffer();

		void Update(void *newData);

		void UpdateMap(const std::string &blockName, ShaderProgram *shaderProgram, const std::unordered_map<std::string, void *> &newDataMap);

		static DescriptorType CreateDescriptor(const uint32_t &binding, const VkShaderStageFlags &stage);

		VkWriteDescriptorSet GetWriteDescriptor(const uint32_t &binding, const DescriptorSet &descriptorSet) const override;
	};
}
