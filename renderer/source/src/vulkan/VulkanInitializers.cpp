#include <viking/vulkan/VulkanInitializers.hpp>

using namespace viking::vulkan;

bool VulkanInitializers::validate(VkResult result)
{
    return result == VK_SUCCESS;
}

VkApplicationInfo VulkanInitializers::applicationInfo(const char * app_name, uint32_t app_ver, const char * engine_name, uint32_t engine_ver, uint32_t api_version)
{
    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = app_name;
    app_info.applicationVersion = app_ver;
    app_info.pEngineName = engine_name;
    app_info.engineVersion = engine_ver;
    app_info.apiVersion = api_version;
    return app_info;
}

VkInstanceCreateInfo VulkanInitializers::instanceCreateInfo(VkApplicationInfo & app_info, std::vector<const char*>& instance_extensions, std::vector<const char*>& instance_layers)
{
    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledExtensionCount = (uint32_t)instance_extensions.size();
    create_info.ppEnabledExtensionNames = instance_extensions.data();
    create_info.enabledLayerCount = (uint32_t)instance_layers.size();
    create_info.ppEnabledLayerNames = instance_layers.data();
    return create_info;
}

VkDeviceCreateInfo viking::vulkan::VulkanInitializers::deviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>& queue_create_infos, const std::vector<const char*>& device_extensions, VkPhysicalDeviceFeatures & device_features)
{
	VkDeviceCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	create_info.pQueueCreateInfos = queue_create_infos.data();
	create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
	create_info.pEnabledFeatures = &device_features;
	create_info.enabledExtensionCount = (uint32_t)device_extensions.size();
	create_info.ppEnabledExtensionNames = device_extensions.data();
	return create_info;
}

VkCommandPoolCreateInfo viking::vulkan::VulkanInitializers::commandPoolCreateInfo(uint32_t queue_family_index, VkCommandPoolCreateFlags flags)
{
	VkCommandPoolCreateInfo pool_info = {};
	pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	pool_info.queueFamilyIndex = queue_family_index;
	pool_info.flags = flags;
	return pool_info;
}

VkSwapchainCreateInfoKHR viking::vulkan::VulkanInitializers::swapchainCreateInfoKHR(VkSurfaceFormatKHR surface_format, VkExtent2D extent, VkPresentModeKHR present_mode, uint32_t image_count, VkSurfaceKHR surface, VulkanQueueFamilyIndices indices, VulkanSwapChainConfiguration swap_chain_support)
{
	VkSwapchainCreateInfoKHR create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	create_info.imageFormat = surface_format.format;
	create_info.imageColorSpace = surface_format.colorSpace;
	create_info.imageExtent = extent;
	create_info.imageArrayLayers = 1;
	create_info.surface = surface;
	create_info.minImageCount = image_count;
	create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	create_info.presentMode = present_mode;
	create_info.clipped = VK_TRUE;
	create_info.oldSwapchain = VK_NULL_HANDLE;
	if (indices.graphics_indices != indices.present_indices)
	{
		create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		create_info.queueFamilyIndexCount = 2;
		create_info.pQueueFamilyIndices = std::vector<uint32_t>{ indices.graphics_indices, indices.present_indices }.data();
	}
	else
	{
		create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		create_info.queueFamilyIndexCount = 0;
		create_info.pQueueFamilyIndices = nullptr;
	}
	create_info.preTransform = swap_chain_support.capabilities.currentTransform;
	create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

	return create_info;
}

VkImageViewCreateInfo viking::vulkan::VulkanInitializers::imageViewCreate(VkImage image, VkFormat format, VkImageAspectFlags aspect_flags)
{
	VkImageViewCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	create_info.image = image;
	create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
	create_info.format = format;
	create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	create_info.subresourceRange.aspectMask = aspect_flags;
	create_info.subresourceRange.baseMipLevel = 0;
	create_info.subresourceRange.levelCount = 1;
	create_info.subresourceRange.baseArrayLayer = 0;
	create_info.subresourceRange.layerCount = 1;
	return create_info;
}

VkSemaphoreCreateInfo viking::vulkan::VulkanInitializers::semaphoreCreateInfo()
{
	VkSemaphoreCreateInfo semaphore_info = {};
	semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	return semaphore_info;
}

VkRenderPassBeginInfo viking::vulkan::VulkanInitializers::renderPassBeginInfo(VkRenderPass render_pass, VkExtent2D swapchain_extent, std::array<VkClearValue, 2>& clear_values)
{
	VkRenderPassBeginInfo render_pass_info = {};
	render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	render_pass_info.renderPass = render_pass;
	render_pass_info.renderArea.offset = { 0, 0 };
	render_pass_info.renderArea.extent = swapchain_extent;
	render_pass_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
	render_pass_info.pClearValues = clear_values.data();
	return render_pass_info;
}

VkAttachmentDescription viking::vulkan::VulkanInitializers::attachmentDescription(VkFormat format, VkAttachmentStoreOp store_op, VkImageLayout final_layout)
{
	VkAttachmentDescription color_attachment = {};
	color_attachment.format = format;
	color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
	color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	color_attachment.storeOp = store_op;
	color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	color_attachment.finalLayout = final_layout;
	return color_attachment;
}

VkAttachmentReference viking::vulkan::VulkanInitializers::attachmentReference(VkImageLayout layout, uint32_t attachment)
{
	VkAttachmentReference color_attachment_refrence = {};
	color_attachment_refrence.attachment = attachment;
	color_attachment_refrence.layout = layout;
	return color_attachment_refrence;
}

VkFramebufferCreateInfo viking::vulkan::VulkanInitializers::framebufferCreateInfo(VkExtent2D & swap_chain_extent, std::vector<VkImageView>& attachments, VkRenderPass & render_pass)
{
	VkFramebufferCreateInfo framebuffer_info = {};
	framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebuffer_info.renderPass = render_pass;
	framebuffer_info.attachmentCount = static_cast<uint32_t>(attachments.size());
	framebuffer_info.pAttachments = attachments.data();
	framebuffer_info.width = swap_chain_extent.width;
	framebuffer_info.height = swap_chain_extent.height;
	framebuffer_info.layers = 1;
	return framebuffer_info;
}

VkSubpassDescription viking::vulkan::VulkanInitializers::subpassDescription(VkAttachmentReference & color_attachment_refrence, VkAttachmentReference & depth_attachment_ref)
{
	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &color_attachment_refrence;
	subpass.pDepthStencilAttachment = &depth_attachment_ref;
	return subpass;
}

VkSubpassDependency viking::vulkan::VulkanInitializers::subpassDependency()
{
	VkSubpassDependency subpass_dependency = {};
	subpass_dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	subpass_dependency.dstSubpass = 0;
	subpass_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subpass_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	subpass_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subpass_dependency.srcAccessMask = 0;
	return subpass_dependency;
}

VkRenderPassCreateInfo viking::vulkan::VulkanInitializers::renderPassCreateInfo(std::vector<VkAttachmentDescription>& attachments, VkSubpassDescription & subpass, VkSubpassDependency & subpass_dependency)
{
	VkRenderPassCreateInfo render_pass_info = {};
	render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	render_pass_info.attachmentCount = static_cast<uint32_t>(attachments.size());
	render_pass_info.pAttachments = attachments.data();
	render_pass_info.subpassCount = 1;
	render_pass_info.pSubpasses = &subpass;
	render_pass_info.dependencyCount = 1;
	render_pass_info.pDependencies = &subpass_dependency;
	return render_pass_info;
}

VkImageCreateInfo viking::vulkan::VulkanInitializers::imageCreateInfo(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, uint32_t mip_levels)
{
	VkImageCreateInfo image_info = {};
	image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	image_info.imageType = VK_IMAGE_TYPE_2D;
	image_info.extent.width = width;
	image_info.extent.height = height;
	image_info.extent.depth = 1;
	image_info.mipLevels = mip_levels;
	image_info.arrayLayers = 1;
	image_info.format = format;
	image_info.tiling = tiling;
	image_info.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
	image_info.usage = usage;
	image_info.samples = VK_SAMPLE_COUNT_1_BIT;
	image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	return image_info;
}

VkMemoryAllocateInfo viking::vulkan::VulkanInitializers::memoryAllocateInfo(VkDeviceSize size, uint32_t memory_type_index)
{
	VkMemoryAllocateInfo alloc_info = {};
	alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	alloc_info.allocationSize = size;
	alloc_info.memoryTypeIndex = memory_type_index;
	return alloc_info;
}

VkCommandBufferAllocateInfo viking::vulkan::VulkanInitializers::commandBufferAllocateInfo(VkCommandPool pool, uint32_t command_buffer_count)
{
	VkCommandBufferAllocateInfo alloc_info = {};
	alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	alloc_info.commandPool = pool;
	alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	alloc_info.commandBufferCount = command_buffer_count;
	return alloc_info;
}

VkCommandBufferBeginInfo viking::vulkan::VulkanInitializers::commandBufferBeginInfo(VkCommandBufferUsageFlags flag)
{
	VkCommandBufferBeginInfo begin_info = {};
	begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	begin_info.flags = flag;
	begin_info.pInheritanceInfo = nullptr;
	return begin_info;
}

VkImageMemoryBarrier viking::vulkan::VulkanInitializers::imageMemoryBarrier()
{
	VkImageMemoryBarrier image_memory_barrier{};
	image_memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	image_memory_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	image_memory_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	return image_memory_barrier;
}

VkImageMemoryBarrier viking::vulkan::VulkanInitializers::imageMemoryBarrier(VkImage & image, VkFormat & format, VkImageLayout & old_layout, VkImageLayout & new_layout)
{
	VkImageMemoryBarrier barrier = imageMemoryBarrier();
	barrier.oldLayout = old_layout;
	barrier.newLayout = new_layout;
	barrier.image = image;
	if (new_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
	{
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

		if (format != VK_FORMAT_UNDEFINED && VulkanCommon::hasStencilComponent(format))
		{
			barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
		}
	}
	else
	{
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	}
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	if (old_layout == VK_IMAGE_LAYOUT_PREINITIALIZED && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
	{
		barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	}
	else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
	{
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
	}
	else if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
	{
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	}
	else
	{
		// Error
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_FLAG_BITS_MAX_ENUM;
	}
	return barrier;
}

VkSubmitInfo viking::vulkan::VulkanInitializers::submitInfo(VkCommandBuffer & buffer)
{
	VkSubmitInfo submit_info = {};
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submit_info.commandBufferCount = 1;
	submit_info.pCommandBuffers = &buffer;
	return submit_info;
}

VkBufferCreateInfo viking::vulkan::VulkanInitializers::bufferCreateInfo(VkDeviceSize size, VkBufferUsageFlags usage)
{
	VkBufferCreateInfo buffer_info = {};
	buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buffer_info.size = size;
	buffer_info.usage = usage;
	buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	return buffer_info;
}

VkDescriptorPoolSize viking::vulkan::VulkanInitializers::descriptorPoolSize(VkDescriptorType type)
{
	VkDescriptorPoolSize pool_size = {};
	pool_size.type = type;
	pool_size.descriptorCount = 1;
	return pool_size;
}

VkDescriptorSetLayoutBinding viking::vulkan::VulkanInitializers::descriptorSetLayoutBinding(VkDescriptorType type, VkShaderStageFlags stage_flags, uint32_t binding)
{
	VkDescriptorSetLayoutBinding layout_bindings = {};
	layout_bindings.binding = binding;
	layout_bindings.descriptorType = type;
	layout_bindings.descriptorCount = 1;
	layout_bindings.stageFlags = stage_flags;
	return layout_bindings;
}

VkDescriptorPoolCreateInfo viking::vulkan::VulkanInitializers::descriptorPoolCreateInfo(std::vector<VkDescriptorPoolSize>& pool_sizes, uint32_t max_sets)
{
	VkDescriptorPoolCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	create_info.poolSizeCount = static_cast<uint32_t>(pool_sizes.size());
	create_info.pPoolSizes = pool_sizes.data();
	create_info.maxSets = max_sets;
	return create_info;
}

VkDescriptorSetLayoutCreateInfo viking::vulkan::VulkanInitializers::descriptorSetLayoutCreateInfo(std::vector<VkDescriptorSetLayoutBinding>& layout_bindings)
{
	VkDescriptorSetLayoutCreateInfo layout_info = {};
	layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layout_info.bindingCount = (uint32_t)layout_bindings.size();
	layout_info.pBindings = layout_bindings.data();
	return layout_info;
}

VkPipelineLayoutCreateInfo viking::vulkan::VulkanInitializers::pipelineLayoutCreateInfo(VkDescriptorSetLayout & descriptor_set_layout)
{
	VkPipelineLayoutCreateInfo pipeline_layout_info = {};
	pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipeline_layout_info.setLayoutCount = 1;
	pipeline_layout_info.pSetLayouts = &descriptor_set_layout;
	pipeline_layout_info.pushConstantRangeCount = 0;
	pipeline_layout_info.pPushConstantRanges = 0;
	return pipeline_layout_info;
}

VkDescriptorSetAllocateInfo viking::vulkan::VulkanInitializers::descriptorSetAllocateInfo(std::vector<VkDescriptorSetLayout>& layouts, VkDescriptorPool & pool)
{
	VkDescriptorSetAllocateInfo alloc_info = {};
	alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	alloc_info.descriptorPool = pool;
	alloc_info.descriptorSetCount = static_cast<uint32_t>(layouts.size());
	alloc_info.pSetLayouts = layouts.data();
	return alloc_info;
}

VkShaderModuleCreateInfo viking::vulkan::VulkanInitializers::shaderModuleCreateInfo(const std::vector<unsigned int>& code)
{
	VkShaderModuleCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	create_info.codeSize = code.size();
	create_info.pCode = reinterpret_cast<const uint32_t*>(code.data());
	return create_info;
}

VkShaderModuleCreateInfo viking::vulkan::VulkanInitializers::shaderModuleCreateInfo(const std::vector<char>& code)
{
	VkShaderModuleCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	create_info.codeSize = code.size();
	create_info.pCode = reinterpret_cast<const uint32_t*>(code.data());
	return create_info;
}

VkPipelineShaderStageCreateInfo viking::vulkan::VulkanInitializers::pipelineShaderStageCreateInfo(VkShaderModule & shader, const char * main, VkShaderStageFlagBits flag)
{
	VkPipelineShaderStageCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	info.stage = flag;
	info.module = shader;
	info.pName = main;
	return info;
}

VkComputePipelineCreateInfo viking::vulkan::VulkanInitializers::computePipelineCreateInfo(VkPipelineLayout & layout, VkPipelineShaderStageCreateInfo & shader_stage)
{
	VkComputePipelineCreateInfo create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
	create_info.layout = layout;
	create_info.stage = shader_stage;
	return create_info;
}

VkWriteDescriptorSet viking::vulkan::VulkanInitializers::writeDescriptorSet(VkDescriptorSet d_set, VkDescriptorBufferInfo & buffer_info, VkDescriptorType type, int binding)
{
	VkWriteDescriptorSet descriptor_write = {};
	descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptor_write.dstSet = d_set; // write to this descriptor set.
	descriptor_write.dstBinding = binding; // write to the first, and only binding.
	descriptor_write.dstArrayElement = 0;
	descriptor_write.descriptorType = type; // Type of buffer
	descriptor_write.descriptorCount = 1; // update a single descriptor.
	descriptor_write.pBufferInfo = &buffer_info;
	return descriptor_write;
}
VkWriteDescriptorSet viking::vulkan::VulkanInitializers::writeDescriptorSet(VkDescriptorSet d_set, VkDescriptorImageInfo& image_info, VkDescriptorType type, int binding)
{
	VkWriteDescriptorSet descriptor_write = {};
	descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptor_write.dstSet = d_set; // write to this descriptor set.
	descriptor_write.dstBinding = binding; // write to the first, and only binding.
	descriptor_write.dstArrayElement = 0;
	descriptor_write.descriptorType = type; // Type of buffer
	descriptor_write.descriptorCount = 1; // update a single descriptor.
	descriptor_write.pImageInfo = &image_info;
	return descriptor_write;
}

VkDescriptorBufferInfo viking::vulkan::VulkanInitializers::descriptorBufferInfo(VkBuffer buffer, uint32_t size, VkDeviceSize & offset)
{
	VkDescriptorBufferInfo buffer_info = {};
	buffer_info.buffer = buffer;
	buffer_info.offset = offset;
	buffer_info.range = size;
	return buffer_info;
}

VkFenceCreateInfo viking::vulkan::VulkanInitializers::createFenceInfo()
{
	VkFenceCreateInfo fenceCreateInfo = {};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.flags = 0;
	return fenceCreateInfo;
}

VkDeviceQueueCreateInfo viking::vulkan::VulkanInitializers::deviceQueueCreate(uint32_t queue_family_index, float queue_priority)
{
	VkDeviceQueueCreateInfo queue_create_info = {};
	queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_create_info.queueFamilyIndex = queue_family_index;
	queue_create_info.queueCount = 1;
	queue_create_info.pQueuePriorities = &queue_priority;
	return queue_create_info;
}
