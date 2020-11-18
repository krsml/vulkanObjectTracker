#include "layer_factory.h"
#include <unordered_map>

class ObjectTracker : public layer_factory
{
public:
	ObjectTracker()
		: totalAllocSize(0)
		, numFrame(0)
		{
		};

	VkResult PostCallAllocateMemory(VkDevice device, const VkMemoryAllocateInfo *pAllocateInfo, const VkAllocationCallbacks *pAllocator, VkDeviceMemory *pMemory, VkResult result);

	void PreCallFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks *pAllocator);

	VkResult PreCallQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR *pPresentInfo);

private:
	size_t totalAllocSize;
	size_t numFrame;
	const size_t tick = 60;
	std::unordered_map<VkDeviceMemory, VkDeviceSize> memorySizeMap;
};