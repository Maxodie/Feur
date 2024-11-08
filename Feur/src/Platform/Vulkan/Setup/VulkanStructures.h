#pragma once

typedef struct FE_VulkanQueueFamilyIndices
{
	FE_Optional(Uint32) graphicsFamily;
	FE_Optional(Uint32) presentFamily;
} FE_VulkanQueueFamilyIndices;

typedef struct FE_VulkanPysicalDevice
{
	VkPhysicalDevice GPU;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	VkPhysicalDeviceMemoryProperties memoryProperties;
	Bool supportDeviceLocalHostVisible;
	Uint32 graphicsQueueIndex;
	Uint32 presentQueueIndex;
	Uint32 transferQueueIndex;
} FE_VulkanPysicalDevice;

typedef struct FE_VulkanDebugger
{
	VkDebugUtilsMessengerEXT callback;
	Bool enableFullVulkanDebugMsg;
} FE_VulkanDebugger;

typedef struct FE_VulkanValidationLayer
{
	Bool enableValidationLayers;
	FE_List(const char* const) validationLayers;
} FE_VulkanValidationLayer;

typedef struct FE_VulkanPipeline
{
	VkPipeline handle;
	VkPipelineLayout layout;
} FE_VulkanPipeline;

typedef struct FE_VulkanInfo
{
	VkInstance instance;
	FE_VulkanDebugger debugger;
	FE_VulkanValidationLayer validationLayer;

	FE_VulkanPysicalDevice physicalDevice;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSurfaceKHR surface;

	FE_VulkanPipeline graphicsPipeline;

	//shaderc
	shaderc_compiler_t shaderCompiler;

	//temp
	VkSwapchainKHR swapChain;
	FE_List(VkImage) swapChainImages;
	FE_List(VkImageView) swapChainImageViews;

	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;



} FE_VulkanInfo;