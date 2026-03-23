#include "sm_interaction_status.hpp"

namespace SharedMemory
{
    SM_POOL_IMPLEMENTATION(SharedMemoryPool_InteractionStatus);

    SM_NUMBER_IMPLEMENTATION(uint8_t, interaction_status_GW_MFS_Left_switch, SharedMemoryPool_InteractionStatus, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, interaction_status_GW_MFS_Right_switch, SharedMemoryPool_InteractionStatus, 1U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, interaction_status_GW_MFS_UP_switch, SharedMemoryPool_InteractionStatus, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, interaction_status_GW_MFS_Down_switch, SharedMemoryPool_InteractionStatus, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, interaction_status_GW_MFS_OK_switch, SharedMemoryPool_InteractionStatus, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, interaction_status_Window_Status, SharedMemoryPool_InteractionStatus, 0U);
    SM_NUMBER_IMPLEMENTATION(uint8_t, interaction_status_Menu_Status, SharedMemoryPool_InteractionStatus, 1U);
}
