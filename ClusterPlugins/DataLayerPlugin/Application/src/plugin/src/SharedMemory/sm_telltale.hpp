/**
* @file         sm_telltale.hpp
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
    SM_POOL_DEFINITION(SharedMemoryPool_Telltale);

    SM_NUMBER_DEFINITION(uint8_t, telltale_EMS_CoolanTemperatureError);
    SM_NUMBER_DEFINITION(uint8_t, telltale_EMS_OilPressureSts);
    SM_NUMBER_DEFINITION(uint8_t, telltale_EMS_SVS);
    SM_NUMBER_DEFINITION(uint8_t, telltale_EMS_EngineFailureStatus);
    SM_NUMBER_DEFINITION(uint8_t, telltale_ESP_ABSFailStatus);
    SM_NUMBER_DEFINITION(uint8_t, telltale_SRS_WarningLampStatus);
    SM_NUMBER_DEFINITION(uint8_t, telltale_SRS_BuckleSwitchStatus);
    SM_NUMBER_DEFINITION(uint8_t, telltale_TCU_TransFailureStatus);
    SM_NUMBER_DEFINITION(uint8_t, telltale_EPB_FunctionLamp);
    SM_NUMBER_DEFINITION(uint8_t, telltale_BCM_BatteryStatus);
    SM_NUMBER_DEFINITION(uint8_t, telltale_BCM_DoorStatus);
    SM_NUMBER_DEFINITION(uint8_t, telltale_BCM_HighBeamStatus);
    SM_NUMBER_DEFINITION(uint8_t, telltale_BCM_LowBeamStatus);
    SM_NUMBER_DEFINITION(uint8_t, telltale_BCM_TurnIndicatorRight);
    SM_NUMBER_DEFINITION(uint8_t, telltale_BCM_TurnIndicatorLeft);
    SM_NUMBER_DEFINITION(uint8_t, telltale_BCM_RearFoglampStatus);
    SM_NUMBER_DEFINITION(uint8_t, telltale_BCM_FrontFoglampStatus);
    SM_NUMBER_DEFINITION(uint8_t, telltale_BCM_PositionLampStatus);
}

