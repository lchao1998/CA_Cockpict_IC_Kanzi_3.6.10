#include "sm_gauge.hpp"

namespace SharedMemory
{
    SM_POOL_IMPLEMENTATION(SharedMemoryPool_Gauge);

    SM_NUMBER_IMPLEMENTATION(uint16_t, gauge_ESP_VehicleSpeed, SharedMemoryPool_Gauge, 0U);
    SM_NUMBER_IMPLEMENTATION(uint16_t, gauge_EMS_EngineSpeed, SharedMemoryPool_Gauge, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, gauge_TCU_GearForDisplay, SharedMemoryPool_Gauge, 0U);
	SM_NUMBER_IMPLEMENTATION(uint8_t, gauge_Theme, SharedMemoryPool_Gauge, 0U);
	SM_NUMBER_IMPLEMENTATION(uint8_t, gauge_Translation, SharedMemoryPool_Gauge, 0U);
	SM_NUMBER_IMPLEMENTATION(uint8_t, gauge_SpecialEffects, SharedMemoryPool_Gauge, 0U);
}
