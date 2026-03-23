/**
* @file         sm_interaction_status.hpp
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
    SM_POOL_DEFINITION(SharedMemoryPool_InteractionStatus);


    SM_NUMBER_DEFINITION(uint8_t, interaction_status_GW_MFS_Left_switch);
    SM_NUMBER_DEFINITION(uint8_t, interaction_status_GW_MFS_Right_switch);
    SM_NUMBER_DEFINITION(uint8_t, interaction_status_GW_MFS_UP_switch);
    SM_NUMBER_DEFINITION(uint8_t, interaction_status_GW_MFS_Down_switch);
    SM_NUMBER_DEFINITION(uint8_t, interaction_status_GW_MFS_OK_switch);
    SM_NUMBER_DEFINITION(uint8_t, interaction_status_Window_Status); // show window index: manu-0, adas-1 navi-2
    SM_NUMBER_DEFINITION(uint8_t, interaction_status_Menu_Status); // show menu index: sub menu 1, sub menu 2, sub menu 3,default is 1

}

