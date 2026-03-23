// *
// * sm_warning.cpp
// *
// *  Created on: Sep 22, 2020
// *      Author: imx8
// */


#include "sm_warning.hpp"

namespace SharedMemory
{
    SM_POOL_IMPLEMENTATION(SharedMemoryPool_Warning);

    SM_NUMBER_IMPLEMENTATION(uint8_t, warning_Showing_ID, SharedMemoryPool_Warning, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, warning_Flash_Flag, SharedMemoryPool_Warning, 0U);
}
