/**
* @file         sm_struct_define.h
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
#ifndef SM_STRUCT_DEFINE_H
#define SM_STRUCT_DEFINE_H

#define SHARE_MEMORY_DEFAULT_SIZE (65535)

#define SM_POOL_DEFINITION(name) \
        extern SharedMemory::Pool name

#define SM_POOL_IMPLEMENTATION(name) \
        SharedMemory::Pool name(#name, SHARE_MEMORY_DEFAULT_SIZE);

#define SM_NUMBER_DEFINITION(type, name) \
        extern SharedMemory::AtomicNumber<type> name

#define SM_NUMBER_IMPLEMENTATION(type, name, pool, value) \
        SharedMemory::AtomicNumber<type> name(pool, #name, value)

/**
* @struct SM_Common
* @brief  define shared memory data
* @details in memory
*/
struct SM_Common
{
    uint8_t PEPS_PowerDistributionStatus;
};

/**
* @struct SM_Gauge
* @brief  define shared memory data
* @details in memory
*/
struct SM_Gauge
{
    uint16_t ESP_VehicleSpeed;
    uint16_t EMS_EngineSpeed;
    uint8_t TCU_GearForDisplay;
    uint8_t ESP_VehicleSpeedValid;
	uint8_t Theme;
	uint8_t Translation;
	uint8_t SpecialEffects;
};


/**
* @struct SM_Telltale
* @brief  define shared memory data
* @details in memory
*/
struct SM_Telltale
{
    uint8_t EMS_CoolanTemperatureError;
    uint8_t EMS_OilPressureSts;
    uint8_t EMS_SVS;
    uint8_t EMS_MIL;
    uint8_t ESP_ABSFailStatus;
    uint8_t SRS_WarningLampStatus;
    uint8_t SRS_BuckleSwitchStatus;
    uint8_t TCU_TransFailureStatus;
    uint8_t EPB_FunctionLamp;
    uint8_t BCM_BatteryStatus;
    uint8_t BCM_DoorStatus;
    uint8_t BCM_HighBeamStatus;
    uint8_t BCM_LowBeamStatus;
    uint8_t BCM_TurnIndicatorRight;
    uint8_t BCM_TurnIndicatorLeft;
    uint8_t BCM_RearFoglampStatus;
    uint8_t BCM_FrontFoglampStatus;
    uint8_t BCM_PositionLampStatus;
};

/**
* @struct SM_Chime
* @brief  define shared memory data
* @details in memory
*/
struct SM_Chime
{
    uint8_t SRS_DriverBuckleSwitchStatus;
    uint8_t SRS_PassengerBuckleSwitchStatus;
    uint8_t BCM_TurnIndicatorRight;
    uint8_t BCM_TurnIndicatorLeft;
};

/**
* @struct SM_TripComputer
* @brief  define shared memory data
* @details in memory
*/
struct SM_TripComputer
{
    uint32_t Odo;
	uint32_t Dte;
    uint8_t IP_FuelLevelPercent;
    uint8_t AC_EnvironmentalTempVD;
    uint8_t AC_EnvironmentalTemp;
    uint16_t Vehicle_Running_time;
};

/**
* @struct SM_Warning
* @brief  define shared memory data
* @details in memory
*/
struct SM_Warning
{
    uint8_t SRS_DriverBuckleSwitchStatus;
    uint8_t SRS_PassengerBuckleSwitchStatus;
    uint8_t EMS_MIL;
    uint8_t SRS_WarningLampStatus;
    uint8_t BCM_PassengerDoorStatus;
    uint8_t BCM_RightRearDoorStatus;
    uint8_t BCM_TrunkDoorStatus;
    uint8_t BCM_LeftRearDoorStatus;
    uint8_t BCM_DriverDoorStatus;
};

/**
* @struct SM_KeyBoard
* @brief  define shared memory data
* @details in memory
*/
struct SM_KeyBoard
{
    uint8_t GW_MFS_Left_switch;
    uint8_t GW_MFS_Right_switch;
    uint8_t GW_MFS_UP_switch;
    uint8_t GW_MFS_Down_switch;
    uint8_t GW_MFS_OK_switch;
};

/**
* @struct SM_KeyBoard
* @brief  define shared memory data
* @details in memory
*/
struct SM_ADAS
{
    uint8_t     ACC_ACCMode;
    uint8_t     ACC_LaneChangeStatus;
    uint16_t    ACC_ACCTargetLngRange;
    uint8_t     ACC_ACCTargetType;
    uint8_t     ACC_HostTargetDetection;
};

#endif // SM_STRUCT_DEFINE_H