#include "sm_adas.hpp"

namespace SharedMemory
{
    SM_POOL_IMPLEMENTATION(SharedMemoryPool_Adas);

    SM_NUMBER_IMPLEMENTATION(uint8_t, Adas_ACC_ACCMode, SharedMemoryPool_Adas, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, Adas_ACC_LaneChangeStatus, SharedMemoryPool_Adas, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, Adas_ACC_ACCTargetLngRange, SharedMemoryPool_Adas, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, Adas_ACC_ACCTargetType, SharedMemoryPool_Adas, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, Adas_ACC_VehicleAnimationStatus, SharedMemoryPool_Adas, 0U);
	SM_NUMBER_IMPLEMENTATION(uint8_t, Adas_ACC_Curve, SharedMemoryPool_Adas, 0U);
}
