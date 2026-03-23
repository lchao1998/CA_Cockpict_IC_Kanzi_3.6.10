#include "sm_telltale.hpp"

namespace SharedMemory
{
    SM_POOL_IMPLEMENTATION(SharedMemoryPool_Telltale);

    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_EMS_CoolanTemperatureError, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_EMS_OilPressureSts, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_EMS_SVS, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_EMS_EngineFailureStatus, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_ESP_ABSFailStatus, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_SRS_WarningLampStatus, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_SRS_BuckleSwitchStatus, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_TCU_TransFailureStatus, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_EPB_FunctionLamp, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_BCM_BatteryStatus, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_BCM_DoorStatus, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_BCM_HighBeamStatus, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_BCM_LowBeamStatus, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_BCM_TurnIndicatorRight, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_BCM_TurnIndicatorLeft, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_BCM_RearFoglampStatus, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_BCM_FrontFoglampStatus, SharedMemoryPool_Telltale, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, telltale_BCM_PositionLampStatus, SharedMemoryPool_Telltale, 0U);
}
