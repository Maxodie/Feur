#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanSwapChain.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include "Platform/Vulkan/Setup/VulkanDevice.h"

void VulkanInitSwapChain(FE_VulkanInfo* vkInfo)
{
    //get device swapchain data
    VulkanCreateSwapChainSupportByQuery(vkInfo);

    //select the best parameters
    VkSurfaceFormatKHR surfaceFormat = VulkanChooseSwapSurfaceFormat(&vkInfo->swapChain.details.formats);
    VkPresentModeKHR presentMode = VulkanChooseSwapPresentMode(&vkInfo->swapChain.details.presentModes);
    VkExtent2D extent = VulkanChooseSwapExtent(&vkInfo->swapChain.details.capabilities);

    vkInfo->swapChain.imageFormat = surfaceFormat.format;
    vkInfo->swapChain.details.selectedSurfaceFormat = surfaceFormat;
    vkInfo->swapChain.details.selectedPresentMode = presentMode;
    vkInfo->swapChain.extent = extent;

    VulkanCreateSwapChain(vkInfo);
    VulkanCreateSwapChainImages(vkInfo);
}

void VulkanCreateSwapChain(FE_VulkanInfo* vkInfo)
{
    Uint32 imageCount = vkInfo->swapChain.details.capabilities.minImageCount + 1;

    if (vkInfo->swapChain.details.capabilities.maxImageCount > 0 && imageCount > vkInfo->swapChain.details.capabilities.maxImageCount)// if maxImageCount == 0 then imageCount is illimited
    {
        imageCount = vkInfo->swapChain.details.capabilities.maxImageCount;
    }

    //create info
    VkSwapchainCreateInfoKHR createInfo = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = vkInfo->surface,
        .minImageCount = imageCount,
        .imageFormat = vkInfo->swapChain.imageFormat,
        .imageColorSpace = vkInfo->swapChain.details.selectedSurfaceFormat.colorSpace,
        .imageExtent = vkInfo->swapChain.extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, //VK_IMAGE_USAGE_TRANSFER_DST_BIT 
        .preTransform = vkInfo->swapChain.details.capabilities.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = vkInfo->swapChain.details.selectedPresentMode,
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE
    };


    Uint32 queueFamilyIndices[] = { vkInfo->queueFamilyIndices.graphicsFamily.value, vkInfo->queueFamilyIndices.presentFamily.value };

    if (vkInfo->queueFamilyIndices.graphicsFamily.value != vkInfo->queueFamilyIndices.presentFamily.value) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optionnal
        createInfo.pQueueFamilyIndices = VK_NULL_HANDLE; // Optionnal
    }

    VkResult result = vkCreateSwapchainKHR(vkInfo->logicalDevice, &createInfo, NULL, &vkInfo->swapChain.handle);
    FE_CORE_ASSERT(result == VK_SUCCESS, "failed to create swap chain! - %d", result);

    FE_CORE_LOG_SUCCESS("Vulkan swapchain created successfuly");
}

void VulkanCreateSwapChainImages(FE_VulkanInfo* vkInfo)
{
    FE_ListInit(vkInfo->swapChain.images);

    //cache and retrieving the swap chain data
    Uint32 imageCount;
    vkGetSwapchainImagesKHR(vkInfo->logicalDevice, vkInfo->swapChain.handle, &imageCount, NULL);
    FE_ListResize(vkInfo->swapChain.images, imageCount);
    vkInfo->imageBarriers = FE_MemoryGeneralAlloc(sizeof(VkImageMemoryBarrier) * vkInfo->swapChain.images.impl.count);
    vkGetSwapchainImagesKHR(vkInfo->logicalDevice, vkInfo->swapChain.handle, &imageCount, vkInfo->swapChain.images.data);

    //setup frames in flight
    vkInfo->swapChain.maxFramesInFlight = imageCount - 1;
    vkInfo->currentFrame = 0;
}

void VulkanDestroySwapChain(FE_VulkanInfo* vkInfo)
{
    vkDestroySwapchainKHR(vkInfo->logicalDevice, vkInfo->swapChain.handle, NULL);
}

void VulkanShutdownSwapChain(FE_VulkanInfo* vkInfo)
{

    FE_MemoryGeneralFree(vkInfo->imageBarriers);
    FE_ListClear(vkInfo->swapChain.images);
    VulkanDestroySwapChain(vkInfo);
    VulkanClearSwapChainSupport(vkInfo);
}

Bool VulkanCreateSwapChainSupportByQuery(FE_VulkanInfo* vkInfo)
{
    //Set details : capabilities, format and presentMode
    FE_ListInit(vkInfo->swapChain.details.formats);
    FE_ListInit(vkInfo->swapChain.details.presentModes);

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkInfo->physicalDevice.GPU, vkInfo->surface, &vkInfo->swapChain.details.capabilities);

    //Formats
    Uint32 formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(vkInfo->physicalDevice.GPU, vkInfo->surface, &formatCount, NULL);

    if (formatCount) {
        FE_ListResize(vkInfo->swapChain.details.formats, formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(vkInfo->physicalDevice.GPU, vkInfo->surface, &formatCount, vkInfo->swapChain.details.formats.data);
    }

    //Present modes
    Uint32 presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(vkInfo->physicalDevice.GPU, vkInfo->surface, &presentModeCount, NULL);

    if (presentModeCount) {
        FE_ListResize(vkInfo->swapChain.details.presentModes, formatCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(vkInfo->physicalDevice.GPU, vkInfo->surface, &presentModeCount, vkInfo->swapChain.details.presentModes.data);
    }

    return TRUE;
}

void VulkanClearSwapChainSupport(FE_VulkanInfo* vkInfo)
{
    FE_ListClear(vkInfo->swapChain.details.formats);
    FE_ListClear(vkInfo->swapChain.details.presentModes);
}

VkSurfaceFormatKHR VulkanChooseSwapSurfaceFormat(FE_ListParameterPtr(VkSurfaceFormatKHR) pAvailableFormats)
{
    const FE_List(VkSurfaceFormatKHR)* availableFormats = pAvailableFormats;
    for (SizeT i = 0; i < availableFormats->impl.count; i++)
    {
        if (availableFormats->data[i].format == VK_FORMAT_B8G8R8A8_SRGB && availableFormats->data[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormats->data[i];
        }
    }

    return availableFormats->data[0];
}

VkPresentModeKHR VulkanChooseSwapPresentMode(FE_ListParameterPtr(VkPresentModeKHR) pAvailablePresentModes)
{
    const FE_List(VkPresentModeKHR)* availablePresentModes = pAvailablePresentModes;
    for (SizeT i = 0; i < availablePresentModes->impl.count; i++)
    {
        if (availablePresentModes->data[i] == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentModes->data[i];
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanChooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities)
{
    if (capabilities->currentExtent.width != UINT32_MAX)
    {
        return capabilities->currentExtent;
    }
    else 
    {
        //VkExtent2D actualExtent = { .width = GetApp()->windowData.w, .height = GetApp()->windowData.h };
        VkExtent2D actualExtent = { .width = capabilities->currentExtent.width, .height = capabilities->currentExtent.height };

        actualExtent.width = ILDA_clamp(actualExtent.width, capabilities->minImageExtent.width, capabilities->maxImageExtent.width);
        actualExtent.height = ILDA_clamp(actualExtent.height, capabilities->minImageExtent.height, capabilities->maxImageExtent.height);

        return actualExtent;
    }
}

void VulkanResizeSwapChain(FE_VulkanInfo* vkInfo, Uint32 width, Uint32 height)
{
    VulkanDestroySwapChain(vkInfo);

    vkInfo->swapChain.extent.width = width < vkInfo->swapChain.details.capabilities.minImageExtent.width ? width : vkInfo->swapChain.details.capabilities.minImageExtent.width;
    vkInfo->swapChain.extent.height = height < vkInfo->swapChain.details.capabilities.minImageExtent.height ? width : vkInfo->swapChain.details.capabilities.minImageExtent.height;

    VulkanCreateSwapChain(vkInfo);
}
