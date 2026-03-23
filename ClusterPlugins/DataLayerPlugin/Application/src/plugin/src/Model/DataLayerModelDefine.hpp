/**
* @file         DataLayerModelDefine.hpp
* @brief        DataLayer Model Define class
* @details      Define the Model data here.
* @author       xu.qiang@zlingsmart.com
* @date         2022-5-23
* @version      v0.0.1
* @copyright    Copyright (c) 2022, zlingsmart Corporation.
**********************************************************************************
* @attention
*
* @par modity log:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2022/05/23  <td>v0.0.1   <td>          <td>Create
* </table>
*
**********************************************************************************
*/
#pragma once
#include "CommonDefine.hpp"
#include <boost/signals2.hpp>

/**
* @class SignalValue.
* @brief signal of value template.
*/
template<typename T>
class SignalValue : public boost::signals2::signal<void(T)>
{
public:
	SignalValue(T proDefaultValue) : m_bInitialized(true), m_tempValue(proDefaultValue), m_proValue(proDefaultValue) {}
	inline virtual T getValue() const { return m_proValue; };
	inline virtual void syncValue() { m_bInitialized = false; if (m_proValue != m_tempValue) { m_proValue = m_tempValue; (*this)(m_proValue); } }
	inline virtual void setTempValue(const T& value) { if (m_tempValue != value) m_tempValue = value; }
	inline bool bInitialized() { return m_bInitialized; }
private:
	// Property value. 
	T m_proValue;
	// Temporary value.
	T m_tempValue;
	// Whether initialized.
	bool m_bInitialized;
};

/**
* @enum SignalValue.
* @brief the data type(DT) of property data.
*/
enum DataType
{
	DT_Bool = 0,
	DT_Int,
	DT_Float,
	DT_String
};

/**
* @enum DataDirection.
* @brief the translate direction(DD) of property data .
*/
enum DataDirection
{
	DD_Memory_To_Plugin,
	DD_Plugin_To_Memory
};

/**
* @enum DataIdentify.
* @brief the identify (ID) of property data.
*/
enum DataIdentify
{
	ID_telltale_EMS_CoolanTemperatureError,
	ID_telltale_EMS_OilPressureSts,
	ID_telltale_EMS_SVS,
	ID_telltale_EMS_EngineFailureStatus,
	ID_telltale_ESP_ABSFailStatus,
	ID_telltale_SRS_WarningLampStatus,
	ID_telltale_SRS_BuckleSwitchStatus,
	ID_telltale_TCU_TransFailureStatus,
	ID_telltale_EPB_FunctionLamp,
	ID_telltale_BCM_BatteryStatus,
	ID_telltale_BCM_DoorStatus,
	ID_telltale_BCM_HighBeamStatus,
	ID_telltale_BCM_LowBeamStatus,
	ID_telltale_BCM_TurnIndicatorRight,
	ID_telltale_BCM_TurnIndicatorLeft,
	ID_telltale_BCM_RearFoglampStatus,
	ID_telltale_BCM_FrontFoglampStatus,
	ID_telltale_BCM_PositionLampStatus,

	ID_gauge_ESP_VehicleSpeed,
	ID_gauge_EMS_EngineSpeed,
	ID_gauge_TCU_GearForDisplay,
	ID_gauge_Theme,
	ID_gauge_Translation,
	ID_gauge_SpecialEffects,

	ID_tripcomputer_Odo,
	ID_tripcomputer_Dte,
	ID_tripcomputer_IP_FuelLevelPercent,
	ID_tripcomputer_AC_EnvironmentalTempVD,
	ID_tripcomputer_AC_EnvironmentalTemp,
	ID_tripcomputer_Vehicle_SYS_time_H,
	ID_tripcomputer_Vehicle_SYS_time_M,
	ID_tripcomputer_Vehicle_SYS_time_S,
	ID_tripcomputer_Vehicle_Running_time_H,
	ID_tripcomputer_Vehicle_Running_time_M,
	ID_tripcomputer_trip_Average_Speed,
	ID_tripcomputer_trip,

	ID_common_PEPS_PowerDistributionStatus,

	ID_interaction_status_GW_MFS_Left_switch,
	ID_interaction_status_GW_MFS_Right_switch,
	ID_interaction_status_GW_MFS_UP_switch,
	ID_interaction_status_GW_MFS_Down_switch,
	ID_interaction_status_GW_MFS_OK_switch,
	ID_interaction_status_Window_Status,
	ID_interaction_status_Menu_Status,

	ID_Adas_ACC_ACCMode,
	ID_Adas_ACC_LaneChangeStatus,
	ID_Adas_ACC_ACCTargetLngRange,
	ID_Adas_ACC_ACCTargetType,
	ID_Adas_ACC_VehicleAnimationStatus,
	ID_Adas_ACC_Curve,

	ID_warning_Showing_ID,


	ID_MAX,

};

#define DECL_ENUM_ELEMENT( element ) #element
#define BEGIN_MAP_ENUM( enum_name ) static char* g_##enum_name [] = 
#define END_MAP_ENUM( enum_name ); static char* GetString##enum_name(enum_name index) {return g_##enum_name [index]; }

/**
* @enum the gloable string array of property ids.
* @brief declare gloable string array of property ids.
*/
BEGIN_MAP_ENUM(DataIdentify)
{
	DECL_ENUM_ELEMENT(ID_telltale_EMS_CoolanTemperatureError),
	DECL_ENUM_ELEMENT(ID_telltale_EMS_OilPressureSts),
	DECL_ENUM_ELEMENT(ID_telltale_EMS_SVS),
	DECL_ENUM_ELEMENT(ID_telltale_EMS_EngineFailureStatus),
	DECL_ENUM_ELEMENT(ID_telltale_ESP_ABSFailStatus),
	DECL_ENUM_ELEMENT(ID_telltale_SRS_WarningLampStatus),
	DECL_ENUM_ELEMENT(ID_telltale_SRS_BuckleSwitchStatus),
	DECL_ENUM_ELEMENT(ID_telltale_TCU_TransFailureStatus),
	DECL_ENUM_ELEMENT(ID_telltale_EPB_FunctionLamp),
	DECL_ENUM_ELEMENT(ID_telltale_BCM_BatteryStatus),
	DECL_ENUM_ELEMENT(ID_telltale_BCM_DoorStatus),
	DECL_ENUM_ELEMENT(ID_telltale_BCM_HighBeamStatus),
	DECL_ENUM_ELEMENT(ID_telltale_BCM_LowBeamStatus),
	DECL_ENUM_ELEMENT(ID_telltale_BCM_TurnIndicatorRight),
	DECL_ENUM_ELEMENT(ID_telltale_BCM_TurnIndicatorLeft),
	DECL_ENUM_ELEMENT(ID_telltale_BCM_RearFoglampStatus),
	DECL_ENUM_ELEMENT(ID_telltale_BCM_FrontFoglampStatus),
	DECL_ENUM_ELEMENT(ID_telltale_BCM_PositionLampStatus),

	DECL_ENUM_ELEMENT(ID_gauge_ESP_VehicleSpeed),
	DECL_ENUM_ELEMENT(ID_gauge_EMS_EngineSpeed),
	DECL_ENUM_ELEMENT(ID_gauge_TCU_GearForDisplay),
	DECL_ENUM_ELEMENT(ID_gauge_Theme),
	DECL_ENUM_ELEMENT(ID_gauge_Translation),
	DECL_ENUM_ELEMENT(ID_gauge_SpecialEffects),

	DECL_ENUM_ELEMENT(ID_tripcomputer_Odo),
	DECL_ENUM_ELEMENT(ID_tripcomputer_Dte),
	DECL_ENUM_ELEMENT(ID_tripcomputer_IP_FuelLevelPercent),
	DECL_ENUM_ELEMENT(ID_tripcomputer_AC_EnvironmentalTempVD),
	DECL_ENUM_ELEMENT(ID_tripcomputer_AC_EnvironmentalTemp),
	DECL_ENUM_ELEMENT(ID_tripcomputer_Vehicle_SYS_time_H),
	DECL_ENUM_ELEMENT(ID_tripcomputer_Vehicle_SYS_time_M),
	DECL_ENUM_ELEMENT(ID_tripcomputer_Vehicle_SYS_time_S),
	DECL_ENUM_ELEMENT(ID_tripcomputer_Vehicle_Running_time_H),
	DECL_ENUM_ELEMENT(ID_tripcomputer_Vehicle_Running_time_M),
	DECL_ENUM_ELEMENT(ID_tripcomputer_trip_Average_Speed),
	DECL_ENUM_ELEMENT(ID_tripcomputer_trip),

	DECL_ENUM_ELEMENT(ID_common_PEPS_PowerDistributionStatus),

	DECL_ENUM_ELEMENT(ID_interaction_status_GW_MFS_Left_switch),
	DECL_ENUM_ELEMENT(ID_interaction_status_GW_MFS_Right_switch),
	DECL_ENUM_ELEMENT(ID_interaction_status_GW_MFS_UP_switch),
	DECL_ENUM_ELEMENT(ID_interaction_status_GW_MFS_Down_switch),
	DECL_ENUM_ELEMENT(ID_interaction_status_GW_MFS_OK_switch),
	DECL_ENUM_ELEMENT(ID_interaction_status_Window_Status),
	DECL_ENUM_ELEMENT(ID_interaction_status_Menu_Status),

	DECL_ENUM_ELEMENT(ID_Adas_ACC_ACCMode),
	DECL_ENUM_ELEMENT(ID_Adas_ACC_LaneChangeStatus),
	DECL_ENUM_ELEMENT(ID_Adas_ACC_ACCTargetLngRange),
	DECL_ENUM_ELEMENT(ID_Adas_ACC_ACCTargetType),
	DECL_ENUM_ELEMENT(ID_Adas_ACC_VehicleAnimationStatus),
	DECL_ENUM_ELEMENT(ID_Adas_ACC_Curve),

	DECL_ENUM_ELEMENT(ID_warning_Showing_ID),

}
END_MAP_ENUM(DataIdentify)

/**
* @struct Data cell.
* @brief declare a cell of property data cell.
*/
struct DataCell
{
	DataIdentify dataID;
	string shmName;
	string kanziProName;
	DataDirection dataDirec;
	DataType dataType;
	int indeInShmStruct;
};

/**
* @struct Data cell Array define.
* @brief declare a cell array of property data cell.
*/
static DataCell g_dataCells[] = {
	{ ID_telltale_EMS_CoolanTemperatureError			, "" , "TT.CoolanTemperatureError"			, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_EMS_OilPressureSts					, "" , "TT.OilPressureSts"					, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_EMS_SVS								, "" , "TT.SVS"								, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_EMS_EngineFailureStatus				, "" , "TT.EngineFailureStatus"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_ESP_ABSFailStatus						, "" , "TT.ABSFailStatus"					, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_SRS_WarningLampStatus					, "" , "TT.WarningLampStatus"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_SRS_BuckleSwitchStatus				, "" , "TT.BuckleSwitchStatus"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_TCU_TransFailureStatus				, "" , "TT.TransFailureStatus"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_EPB_FunctionLamp						, "" , "TT.FunctionLamp"					, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_BCM_BatteryStatus						, "" , "TT.BatteryStatus"					, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_BCM_DoorStatus						, "" , "TT.DoorStatus"						, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_BCM_HighBeamStatus					, "" , "TT.HighBeamStatus"					, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_BCM_LowBeamStatus						, "" , "TT.LowBeamStatus"					, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_BCM_TurnIndicatorRight				, "" , "TT.TurnIndicatorRight"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_BCM_TurnIndicatorLeft					, "" , "TT.TurnIndicatorLeft"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_BCM_RearFoglampStatus					, "" , "TT.RearFoglampStatus"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_BCM_FrontFoglampStatus				, "" , "TT.FrontFoglampStatus"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_telltale_BCM_PositionLampStatus				, "" , "TT.PositionLampStatus"				, DD_Memory_To_Plugin , DT_Int, 0 },

	{ ID_gauge_ESP_VehicleSpeed							, "" , "Gauge.VehicleSpeed"					, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_gauge_EMS_EngineSpeed							, "" , "Gauge.EngineSpeed"					, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_gauge_TCU_GearForDisplay						, "" , "Gauge.GearForDisplay"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_gauge_Theme 								    , "" , "Gauge.Theme"					    , DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_gauge_Translation								, "" , "Gauge.Translation"					, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_gauge_SpecialEffects							, "" , "Gauge.SpecialEffects"				, DD_Memory_To_Plugin , DT_Int, 0 },

	{ ID_tripcomputer_Odo								, "" , "Trip.Odo"							, DD_Memory_To_Plugin , DT_Int, 0 },
    { ID_tripcomputer_Dte                               , "" , "Trip.Dte"                           , DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_tripcomputer_IP_FuelLevelPercent				, "" , "Trip.FuelLevelPercent"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_tripcomputer_AC_EnvironmentalTempVD			, "" , "Trip.EnvironmentalTempVD"			, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_tripcomputer_AC_EnvironmentalTemp				, "" , "Trip.EnvironmentalTemp"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_tripcomputer_Vehicle_SYS_time_H				, "" , "Trip.Vehicle_SYS_time_H"			, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_tripcomputer_Vehicle_SYS_time_M				, "" , "Trip.Vehicle_SYS_time_M"			, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_tripcomputer_Vehicle_SYS_time_S				, "" , "Trip.Vehicle_SYS_time_S"			, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_tripcomputer_Vehicle_Running_time_H			, "" , "Trip.Vehicle_Running_time_H"		, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_tripcomputer_Vehicle_Running_time_M			, "" , "Trip.Vehicle_Running_time_M"		, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_tripcomputer_trip_Average_Speed				, "" , "Trip.trip_Average_Speed"			, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_tripcomputer_trip								, "" , "Trip.trip"							, DD_Memory_To_Plugin , DT_Int, 0 },

	{ ID_common_PEPS_PowerDistributionStatus			, "" , "Common.PowerDistributionStatus"		, DD_Memory_To_Plugin , DT_Int, 0 },

	{ ID_interaction_status_GW_MFS_Left_switch			, "" , "Interaction.GW_MFS_Left_switch"		, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_interaction_status_GW_MFS_Right_switch			, "" , "Interaction.GW_MFS_Right_switch"	, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_interaction_status_GW_MFS_UP_switch			, "" , "Interaction.GW_MFS_UP_switch"		, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_interaction_status_GW_MFS_Down_switch			, "" , "Interaction.GW_MFS_Down_switch"		, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_interaction_status_GW_MFS_OK_switch			, "" , "Interaction.GW_MFS_OK_switch"		, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_interaction_status_Window_Status				, "" , "Interaction.Window_Status"			, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_interaction_status_Menu_Status					, "" , "Interaction.Menu_Status"			, DD_Memory_To_Plugin , DT_Int, 0 },

	{ ID_Adas_ACC_ACCMode								, "" , "Adas.ACCMode"						, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_Adas_ACC_LaneChangeStatus						, "" , "Adas.LaneChangeStatus"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_Adas_ACC_ACCTargetLngRange						, "" , "Adas.ACCTargetLngRange"				, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_Adas_ACC_ACCTargetType							, "" , "Adas.ACCTargetType"					, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_Adas_ACC_VehicleAnimationStatus				, "" , "Adas.VehicleAnimationStatus"		, DD_Memory_To_Plugin , DT_Int, 0 },
	{ ID_Adas_ACC_Curve									, "" , "Adas.Curve"							, DD_Memory_To_Plugin , DT_Int, 0 },

	{ ID_warning_Showing_ID								, "" , "Warning.Showing_ID"					, DD_Memory_To_Plugin , DT_Int, 0 },

};

/**
* @struct Signal cell .
* @brief declare a Signal cell for property data cell.
*/
template<typename T>
class SignalCell
{
public:
	explicit SignalCell(DataCell cell, T defaultValue)
		: m_signal(new SignalValue<T>(defaultValue))
		, m_dataCell(cell)
		, m_defaultValue(defaultValue)
	{
	}
	bool bSameGroupWithShm(const string& kanziName)
	{
		return (m_dataCell.shmName == kanziName);
	}
public:
	std::shared_ptr<SignalValue<T>> m_signal;
	DataCell m_dataCell;
	T  m_defaultValue;
};