#include "layer_factory.h"
#include <unordered_map>

class ObjectTracker : public layer_factory
{
public:
	ObjectTracker()
		: totalAllocSize(0){};

	VkResult PostCallAllocateMemory(VkDevice device, const VkMemoryAllocateInfo *pAllocateInfo, const VkAllocationCallbacks *pAllocator, VkDeviceMemory *pMemory, VkResult result)
	{
		if(result == VK_SUCCESS)
		{
			totalAllocSize+=pAllocateInfo->allocationSize;
			memorySizeMap[*pMemory] = pAllocateInfo->allocationSize;
		}
		return result;
	};

	void PreCallFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks *pAllocator)
	{
		if (memory != VK_NULL_HANDLE)
		{
			totalAllocSize -= memorySizeMap[memory];
		}
	}

private:
	size_t totalAllocSize;
	std::unordered_map<VkDeviceMemory, VkDeviceSize> memorySizeMap;
};