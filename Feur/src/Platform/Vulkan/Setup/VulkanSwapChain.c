#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanSwapChain.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include "Platform/Vulkan/Setup/VulkanDevice.h"

void FE_API VulkanCreateSwapChain(VulkanfeInfo* vkInfo)
{
    //get device swapchain data
    VulkanfeSwapChainSupportDetails swapChainSupport = VulkanQuerySwapChainSupport(vkInfo, vkInfo->physicalDevice);

    //select the best parameters
    VkSurfaceFormatKHR surfaceFormat = VulkanChooseSwapSurfaceFormat(&swapChainSupport.formats);
    VkPresentModeKHR presentMode = VulkanChooseSwapPresentMode(&swapChainSupport.presentModes);
    VkExtent2D extent = VulkanChooseSwapExtent(&swapChainSupport.capabilities);

    Uint32 imageCount = swapChainSupport.capabilities.minImageCount + 1;

    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)// if maxImageCount == 0 then imageCount is illimited
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    //create info
    VkSwapchainCreateInfoKHR createInfo = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = vkInfo->surface,
        .minImageCount = imageCount,
        .imageFormat = surfaceFormat.format,
        .imageColorSpace = surfaceFormat.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, //VK_IMAGE_USAGE_TRANSFER_DST_BIT 
        .preTransform = swapChainSupport.capabilities.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = presentMode,
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE
    };

    VulkanfeQueueFamilyIndices indices = VulkanFindQueueFamilies(vkInfo, vkInfo->physicalDevice);
    Uint32 queueFamilyIndices[] = { indices.graphicsFamily.value, indices.presentFamily.value };

    if (indices.graphicsFamily.value != indices.presentFamily.value) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optionnal
        createInfo.pQueueFamilyIndices = NULL; // Optionnal
    }

    VkResult result = vkCreateSwapchainKHR(vkInfo->device, &createInfo, NULL, &vkInfo->swapChain);
    FE_CORE_ASSERT(result == VK_SUCCESS, "failed to create swap chain!");

    FE_ListInit(vkInfo->swapChainImages);

    vkGetSwapchainImagesKHR(vkInfo->device, vkInfo->swapChain, &imageCount, NULL);
    FE_ListResize(vkInfo->swapChainImages, imageCount);
    vkGetSwapchainImagesKHR(vkInfo->device, vkInfo->swapChain, &imageCount, vkInfo->swapChainImages.data);

    vkInfo->swapChainImageFormat = surfaceFormat.format;
    vkInfo->swapChainExtent = extent;
}

VulkanfeSwapChainSupportDetails FE_API VulkanQuerySwapChainSupport(const struct VulkanfeInfo* vkInfo, VkPhysicalDevice device)
{
    //set details : capabilities, format and presentMode
    VulkanfeSwapChainSupportDetails details = { 0 };
    FE_ListInit(details.formats);
    FE_ListInit(details.presentModes);

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, vkInfo->surface, &details.capabilities);

    Uint32 formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, vkInfo->surface, &formatCount, NULL);

    if (formatCount != 0) {
        FE_ListResize(details.formats, formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, vkInfo->surface, &formatCount, details.formats.data);
    }

    Uint32 presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, vkInfo->surface, &presentModeCount, NULL);

    if (presentModeCount != 0) {
        FE_ListResize(details.presentModes, formatCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, vkInfo->surface, &presentModeCount, details.presentModes.data);
    }
    //

    return details;
}

VkSurfaceFormatKHR FE_API VulkanChooseSwapSurfaceFormat(const void* feListAvailableFormats)
{
    const FE_List(VkSurfaceFormatKHR)* availableFormats = feListAvailableFormats;
    for (SizeT i = 0; i < availableFormats->impl.count; i++)
    {
        if (availableFormats->data[i].format == VK_FORMAT_B8G8R8A8_SRGB && availableFormats->data[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormats->data[i];
        }
    }

    return availableFormats->data[0];
}

VkPresentModeKHR FE_API VulkanChooseSwapPresentMode(const void* feListAvailablePresentModes)
{
    const FE_List(VkPresentModeKHR)* availablePresentModes = feListAvailablePresentModes;
    for (SizeT i = 0; i < availablePresentModes->impl.count; i++)
    {
        if (availablePresentModes->data[i] == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentModes->data[i];
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D FE_API VulkanChooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities)
{
    if (capabilities->currentExtent.width != UINT32_MAX)
    {
        return capabilities->currentExtent;
    }
    else 
    {
        VkExtent2D actualExtent = { .width = GetApp()->windowData.w, .height = GetApp()->windowData.h };

        actualExtent.width = ILDA_clampi(actualExtent.width, capabilities->minImageExtent.width, capabilities->maxImageExtent.width);
        actualExtent.height = ILDA_clampi(actualExtent.height, capabilities->minImageExtent.height, capabilities->maxImageExtent.height);

        return actualExtent;
    }
}
