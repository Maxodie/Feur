#pragma once

typedef struct FE_VulkanAllocatedBuffer {
	VkBuffer buffer;
	VmaAllocation allocation;
	VmaAllocationInfo info;
} FE_VulkanAllocatedBuffer;

typedef struct FE_VulkanDescriptor
{
	VkDescriptorSetLayout setLayout;
	VkDescriptorPool pool;
	VkDescriptorSet* sets;//static array
} FE_VulkanDescriptor;

typedef struct FE_VulkanUniformData
{
	FE_VulkanAllocatedBuffer* uniformBuffers;//static array
	void** uniformBuffersMapped;//static array
} FE_VulkanUniformData;

typedef struct FE_VulkanfeSwapChainSupportDetails 
{
	VkSurfaceCapabilitiesKHR capabilities;
	FE_List(VkSurfaceFormatKHR) formats;
	FE_List(VkPresentModeKHR) presentModes;
	VkPresentModeKHR selectedPresentMode;
	VkSurfaceFormatKHR selectedSurfaceFormat;
} FE_VulkanfeSwapChainSupportDetails;

typedef struct FE_VulkanSwapChain
{
	FE_VulkanfeSwapChainSupportDetails details;
	VkSwapchainKHR handle;

	FE_List(VkImage) images;
	FE_List(VkImageView) imageViews;
	VkFormat imageFormat;
	VkExtent2D extent;
	Uint32 maxFramesInFlight;
} FE_VulkanSwapChain;

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
	Uint32 graphicsQueueIndex;
	VkPhysicalDeviceMemoryProperties memoryProperties;
	Uint32 presentQueueIndex;
	Uint32 transferQueueIndex;
	Bool supportDeviceLocalHostVisible;
} FE_VulkanPysicalDevice;

typedef struct FE_VulkanValidationLayer
{
	Bool enableValidationLayers;
	FE_List(const char* const) validationLayers;
} FE_VulkanValidationLayer;

typedef struct FE_VulkanDebugger
{
	FE_VulkanValidationLayer validationLayer;
	VkDebugUtilsMessengerEXT callback;
	Bool enableFullVulkanDebugMsg;
} FE_VulkanDebugger;

typedef struct FE_VulkanPipeline
{
	VkPipeline handle;
	VkPipelineLayout layout;
} FE_VulkanPipeline;

typedef struct FE_VulkanInfo
{
	VkInstance instance;
	FE_VulkanDebugger debugger;

	FE_VulkanPysicalDevice physicalDevice;
	VkDevice logicalDevice;

	PFN_vkCmdEndRenderingKHR vkCmdEndRenderingKHR;
	PFN_vkCmdBeginRenderingKHR vkCmdBeginRenderingKHR;

	VkQueue graphicsQueue;
	VkQueue presentQueue;
	FE_VulkanQueueFamilyIndices queueFamilyIndices;
	VkSurfaceKHR surface;

	FE_VulkanSwapChain swapChain;
	Uint32 currentFrame;
	Uint32 imageIndex;

	VkSemaphore* imageAvailableSemaphores;//static array
	VkSemaphore imageGUIAvailableSemaphores;//static array
	VkSemaphore* queueCompleteSemaphores;//static array
	VkFence* inFlightFences;//static array

	FE_VulkanPipeline graphicsPipeline;
	FE_VulkanDescriptor descriptor;//must be same amount of descriptor ans drawIndexedIndirectCmd
	VkDrawIndexedIndirectCommand drawIndexedIndirectCmd;
	FE_VulkanAllocatedBuffer drawIndexedIndirectCmdBuffer;

	//shaderc
	shaderc_compiler_t shaderCompiler;

	VkCommandPool graphicsCommandPool;
	VkCommandBuffer* cmdBuffers;//static array
	VkImageMemoryBarrier* imageBarriers;//static array

	FE_VulkanAllocatedBuffer vertexBuffer;
	FE_VulkanAllocatedBuffer indexBuffer;
	FE_VulkanUniformData uniformData;

	RendererAPIData* apiData;

	VmaAllocator allocator;


} FE_VulkanInfo;