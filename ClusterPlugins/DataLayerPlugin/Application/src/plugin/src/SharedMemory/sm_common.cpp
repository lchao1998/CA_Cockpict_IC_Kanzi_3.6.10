#include "sm_common.hpp"

namespace SharedMemory
{
    SM_POOL_IMPLEMENTATION(SharedMemoryPool_Common);

    SM_NUMBER_IMPLEMENTATION(uint8_t, common_PEPS_PowerDistributionStatus, SharedMemoryPool_Common, 0U);
}
