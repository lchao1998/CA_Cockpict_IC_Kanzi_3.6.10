/**
* @file         sm_tripcompute.hpp
* @brief        shared memory of ipc link data
* @details      
* @author       xu.qiang@zlingsmart.com
* @date         2022-3-1
* @version      v0.0.1
* @copyright    Copyright (c) 2022, zlingsmart Corporation.
**********************************************************************************
* @attention 
* 
* @par modity log:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2022/03/01  <td>v0.0.1   <td>          <td>Create
* </table>
*
**********************************************************************************
*/
#pragma once
#include "sharedmemory.hpp"
#include "sm_struct_define.h"

using namespace SharedMemory;

namespace SharedMemory
{
    SM_POOL_DEFINITION(SharedMemoryPool_TripComputer);

    SM_NUMBER_DEFINITION(uint32_t, tripcomputer_Odo);
	SM_NUMBER_DEFINITION(uint32_t, tripcomputer_Dte);
    SM_NUMBER_DEFINITION(uint8_t, tripcomputer_IP_FuelLevelPercent);
    SM_NUMBER_DEFINITION(uint8_t, tripcomputer_AC_EnvironmentalTempVD);
    SM_NUMBER_DEFINITION(uint8_t, tripcomputer_AC_EnvironmentalTemp);
    SM_NUMBER_DEFINITION(uint8_t, tripcomputer_Vehicle_SYS_time_H);
    SM_NUMBER_DEFINITION(uint8_t, tripcomputer_Vehicle_SYS_time_M);
    SM_NUMBER_DEFINITION(uint8_t, tripcomputer_Vehicle_SYS_time_S);
    SM_NUMBER_DEFINITION(uint8_t, tripcomputer_Vehicle_Running_time_H);
    SM_NUMBER_DEFINITION(uint8_t, tripcomputer_Vehicle_Running_time_M);
    SM_NUMBER_DEFINITION(uint16_t, tripcomputer_trip_Average_Speed);
    SM_NUMBER_DEFINITION(uint16_t, tripcomputer_trip);
 }

