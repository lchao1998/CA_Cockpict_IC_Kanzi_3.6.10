/**
* @file         sm_common.hpp
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
    SM_POOL_DEFINITION(SharedMemoryPool_Common);

    SM_NUMBER_DEFINITION(uint8_t, common_PEPS_PowerDistributionStatus);
}

