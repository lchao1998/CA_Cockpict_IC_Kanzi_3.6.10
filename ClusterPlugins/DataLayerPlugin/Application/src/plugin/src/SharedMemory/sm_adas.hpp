/**
* @file         sm_adas.hpp
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
    SM_POOL_DEFINITION(SharedMemoryPool_Adas);

    SM_NUMBER_DEFINITION(uint8_t,   Adas_ACC_ACCMode); // 0x0=OFF mode；0x1=Passive mode；0x2 =StandBy mode；0x3 = Active Control mode；0x4 = Brake Only mode；0x5= Override；0x6 = Stand Wait mode；0x7 = Failure mode
    SM_NUMBER_DEFINITION(uint8_t,   Adas_ACC_LaneChangeStatus);  // 0x0=Has not changed；0x1=changing；0x2=end change；0x3=Unknow
    SM_NUMBER_DEFINITION(uint8_t,   Adas_ACC_ACCTargetLngRange); // 0x0: no display 0x01: 30m ,0x02 : 80m 0x03: 180m
    SM_NUMBER_DEFINITION(uint8_t,   Adas_ACC_ACCTargetType); // 0x0=no display；0x1=sedan；0x2=motorcycle；0x3=pedestrian；0x4=Bicycle；0x5=Bus；0x7=truck；0x8~0xE=reserved；0xF=other
    SM_NUMBER_DEFINITION(uint8_t,   Adas_ACC_VehicleAnimationStatus); // 0:stop 1:running 2:turn right 3:turn left 
	SM_NUMBER_DEFINITION(uint8_t,   Adas_ACC_Curve);//0:default;1:left;2:right
}

