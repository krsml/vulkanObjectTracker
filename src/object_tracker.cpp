#include "object_tracker.h"
#include <unordered_map>
#include <string>
#include "simpleAndroidLog.h"

VkResult ObjectTracker::PostCallAllocateMemory(VkDevice device, const VkMemoryAllocateInfo *pAllocateInfo, const VkAllocationCallbacks *pAllocator, VkDeviceMemory *pMemory, VkResult result)
{
    if(result == VK_SUCCESS)
    {
        totalAllocSize+=pAllocateInfo->allocationSize;
        memorySizeMap[*pMemory] = pAllocateInfo->allocationSize;
    }
    return result;
};

void ObjectTracker::PreCallFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks *pAllocator)
{
    if (memory != VK_NULL_HANDLE)
    {
        totalAllocSize -= memorySizeMap[memory];
    }
}

VkResult ObjectTracker::PreCallQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR *pPresentInfo)
{
    numFrame++;
    if (numFrame >= tick)
    {
        numFrame = 0;
        std::string info = "Alloc Memory: " + std::to_string(totalAllocSize);
        LOGI("%s", info.c_str());
    }
    return VK_SUCCESS;
};


ObjectTracker objTracker;