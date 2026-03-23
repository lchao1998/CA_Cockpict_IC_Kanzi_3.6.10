#include "sm_tripcomputer.hpp"

namespace SharedMemory {
    SM_POOL_IMPLEMENTATION(SharedMemoryPool_TripComputer);

    SM_NUMBER_IMPLEMENTATION(uint32_t, tripcomputer_Odo, SharedMemoryPool_TripComputer, 0U);
	SM_NUMBER_IMPLEMENTATION(uint32_t, tripcomputer_Dte, SharedMemoryPool_TripComputer, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, tripcomputer_IP_FuelLevelPercent, SharedMemoryPool_TripComputer, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, tripcomputer_AC_EnvironmentalTempVD, SharedMemoryPool_TripComputer, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, tripcomputer_AC_EnvironmentalTemp, SharedMemoryPool_TripComputer, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, tripcomputer_Vehicle_SYS_time_H, SharedMemoryPool_TripComputer, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, tripcomputer_Vehicle_SYS_time_M, SharedMemoryPool_TripComputer, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, tripcomputer_Vehicle_SYS_time_S, SharedMemoryPool_TripComputer, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, tripcomputer_Vehicle_Running_time_H, SharedMemoryPool_TripComputer, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, tripcomputer_Vehicle_Running_time_M, SharedMemoryPool_TripComputer, 0U);
    SM_NUMBER_IMPLEMENTATION(uint16_t, tripcomputer_trip_Average_Speed, SharedMemoryPool_TripComputer, 0U);
    SM_NUMBER_IMPLEMENTATION(uint16_t, tripcomputer_trip, SharedMemoryPool_TripComputer, 0U);

}
