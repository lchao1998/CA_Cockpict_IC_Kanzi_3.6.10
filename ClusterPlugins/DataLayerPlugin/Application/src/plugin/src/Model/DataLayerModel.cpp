#include "DataLayerModel.hpp"
#include "sm_adas.hpp"
#include "sm_common.hpp"
#include "sm_gauge.hpp"
#include "sm_interaction_status.hpp"
#include "sm_telltale.hpp"
#include "sm_struct_define.h"
#include "sm_telltale.hpp"
#include "sm_tripcomputer.hpp"
#include "sm_warning.hpp"
#include "DataLayerCache.hpp"

#define CHECK_SHMVALUE_CHANGE(id, shm_id)\
if (shm_id.isModified())\
	DataLayerCache::getInstance().setSignalValue(id, shm_id.getValue());

DataLayerModel* DataLayerModel::m_instance = NULL;


bool DataLayerModel::init()
{
	checkPropertyName();
	createKanziProperty();

	m_bInit = true;
	return m_bInit;
}

void DataLayerModel::recvData()
{
	if (!m_bInit)
		return;
	checkDataChange();
	DataLayerCache::getInstance().updateSignalValue();
}
void DataLayerModel::make_property(DataIdentify id, bool defaultValue)
{
	DataLayerCache::getInstance().m_bSignalCells.push_back(SignalCell<bool>(g_dataCells[id], defaultValue));
}

void DataLayerModel::make_property(DataIdentify id, int defaultValue)
{
	DataLayerCache::getInstance().m_iSignalCells.push_back(SignalCell<int>(g_dataCells[id], defaultValue));

}

void DataLayerModel::make_property(DataIdentify id, unsigned int defaultValue)
{
	DataLayerCache::getInstance().m_iSignalCells.push_back(SignalCell<int>(g_dataCells[id], defaultValue));

}

void DataLayerModel::make_property(DataIdentify id, float defaultValue)
{
	DataLayerCache::getInstance().m_fSignalCells.push_back(SignalCell<float>(g_dataCells[id], defaultValue));

}

void DataLayerModel::make_property(DataIdentify id, string defaultValue)
{
	DataLayerCache::getInstance().m_sSignalCells.push_back(SignalCell<string>(g_dataCells[id], defaultValue));

}

void DataLayerModel::checkPropertyName()
{
	for (size_t i = 0; i < ID_MAX; i++)
	{
		DataCell& cell = g_dataCells[i];
		if (cell.shmName.empty())
		{
			cell.shmName = GetStringDataIdentify(cell.dataID);
		}

		if (cell.kanziProName.empty())
		{
			cell.kanziProName = GetStringDataIdentify(cell.dataID);
		}
	}
}

void DataLayerModel::createKanziProperty()
{
	// TT
	make_property(ID_telltale_EMS_CoolanTemperatureError, telltale_EMS_CoolanTemperatureError.getValue());
	make_property(ID_telltale_EMS_OilPressureSts, telltale_EMS_OilPressureSts.getValue());
	make_property(ID_telltale_EMS_SVS, telltale_EMS_SVS.getValue());
	make_property(ID_telltale_EMS_EngineFailureStatus, telltale_EMS_EngineFailureStatus.getValue());
	make_property(ID_telltale_ESP_ABSFailStatus, telltale_ESP_ABSFailStatus.getValue());
	make_property(ID_telltale_SRS_WarningLampStatus, telltale_SRS_WarningLampStatus.getValue());
	make_property(ID_telltale_SRS_BuckleSwitchStatus, telltale_SRS_BuckleSwitchStatus.getValue());
	make_property(ID_telltale_TCU_TransFailureStatus, telltale_TCU_TransFailureStatus.getValue());
	make_property(ID_telltale_EPB_FunctionLamp, telltale_EPB_FunctionLamp.getValue());
	make_property(ID_telltale_BCM_BatteryStatus, telltale_BCM_BatteryStatus.getValue());
	make_property(ID_telltale_BCM_DoorStatus, telltale_BCM_DoorStatus.getValue());
	make_property(ID_telltale_BCM_HighBeamStatus, telltale_BCM_HighBeamStatus.getValue());
	make_property(ID_telltale_BCM_LowBeamStatus, telltale_BCM_LowBeamStatus.getValue());
	make_property(ID_telltale_BCM_TurnIndicatorRight, telltale_BCM_TurnIndicatorRight.getValue());
	make_property(ID_telltale_BCM_TurnIndicatorLeft, telltale_BCM_TurnIndicatorLeft.getValue());
	make_property(ID_telltale_BCM_RearFoglampStatus, telltale_BCM_RearFoglampStatus.getValue());
	make_property(ID_telltale_BCM_FrontFoglampStatus, telltale_BCM_FrontFoglampStatus.getValue());
	make_property(ID_telltale_BCM_PositionLampStatus, telltale_BCM_PositionLampStatus.getValue());

	// Gauge
	make_property(ID_gauge_ESP_VehicleSpeed, gauge_ESP_VehicleSpeed.getValue());
	make_property(ID_gauge_EMS_EngineSpeed, gauge_EMS_EngineSpeed.getValue());
	make_property(ID_gauge_TCU_GearForDisplay, gauge_TCU_GearForDisplay.getValue());
	make_property(ID_gauge_Theme, gauge_Theme.getValue());
	make_property(ID_gauge_Translation, gauge_Translation.getValue());
	make_property(ID_gauge_SpecialEffects, gauge_SpecialEffects.getValue());


	// Tripcomputer
	make_property(ID_tripcomputer_Odo, tripcomputer_Odo.getValue());
	make_property(ID_tripcomputer_Dte, tripcomputer_Dte.getValue());
	make_property(ID_tripcomputer_IP_FuelLevelPercent, tripcomputer_IP_FuelLevelPercent.getValue());
	make_property(ID_tripcomputer_AC_EnvironmentalTempVD, tripcomputer_AC_EnvironmentalTempVD.getValue());
	make_property(ID_tripcomputer_AC_EnvironmentalTemp, tripcomputer_AC_EnvironmentalTemp.getValue());
	make_property(ID_tripcomputer_Vehicle_SYS_time_H, tripcomputer_Vehicle_SYS_time_H.getValue());
	make_property(ID_tripcomputer_Vehicle_SYS_time_M, tripcomputer_Vehicle_SYS_time_M.getValue());
	make_property(ID_tripcomputer_Vehicle_SYS_time_S, tripcomputer_Vehicle_SYS_time_S.getValue());
	make_property(ID_tripcomputer_Vehicle_Running_time_H, tripcomputer_Vehicle_Running_time_H.getValue());
	make_property(ID_tripcomputer_Vehicle_Running_time_M, tripcomputer_Vehicle_Running_time_M.getValue());
	make_property(ID_tripcomputer_trip_Average_Speed, tripcomputer_trip_Average_Speed.getValue());
	make_property(ID_tripcomputer_trip, tripcomputer_trip.getValue());

	// Common
	make_property(ID_common_PEPS_PowerDistributionStatus, common_PEPS_PowerDistributionStatus.getValue());

	// Interaction
	make_property(ID_interaction_status_GW_MFS_Left_switch, interaction_status_GW_MFS_Left_switch.getValue());
	make_property(ID_interaction_status_GW_MFS_Right_switch, interaction_status_GW_MFS_Right_switch.getValue());
	make_property(ID_interaction_status_GW_MFS_UP_switch, interaction_status_GW_MFS_UP_switch.getValue());
	make_property(ID_interaction_status_GW_MFS_Down_switch, interaction_status_GW_MFS_Down_switch.getValue());
	make_property(ID_interaction_status_GW_MFS_OK_switch, interaction_status_GW_MFS_OK_switch.getValue());
	make_property(ID_interaction_status_Window_Status, interaction_status_Window_Status.getValue());
	make_property(ID_interaction_status_Menu_Status, interaction_status_Menu_Status.getValue());

	// Adas
	make_property(ID_Adas_ACC_ACCMode, Adas_ACC_ACCMode.getValue());
	make_property(ID_Adas_ACC_LaneChangeStatus, Adas_ACC_LaneChangeStatus.getValue());
	make_property(ID_Adas_ACC_ACCTargetLngRange, Adas_ACC_ACCTargetLngRange.getValue());
	make_property(ID_Adas_ACC_ACCTargetType, Adas_ACC_ACCTargetType.getValue());
	make_property(ID_Adas_ACC_VehicleAnimationStatus, Adas_ACC_VehicleAnimationStatus.getValue());
	make_property(ID_Adas_ACC_Curve, Adas_ACC_Curve.getValue());

	// Warning
	make_property(ID_warning_Showing_ID, warning_Showing_ID.getValue());
}

void DataLayerModel::checkDataChange()
{
	if (!m_bInit)
		return;

	// TT
	CHECK_SHMVALUE_CHANGE(ID_telltale_EMS_CoolanTemperatureError, telltale_EMS_CoolanTemperatureError);
	CHECK_SHMVALUE_CHANGE(ID_telltale_EMS_OilPressureSts, telltale_EMS_OilPressureSts);
	CHECK_SHMVALUE_CHANGE(ID_telltale_EMS_SVS, telltale_EMS_SVS);
	CHECK_SHMVALUE_CHANGE(ID_telltale_EMS_EngineFailureStatus, telltale_EMS_EngineFailureStatus);
	CHECK_SHMVALUE_CHANGE(ID_telltale_ESP_ABSFailStatus, telltale_ESP_ABSFailStatus);
	CHECK_SHMVALUE_CHANGE(ID_telltale_SRS_WarningLampStatus, telltale_SRS_WarningLampStatus);
	CHECK_SHMVALUE_CHANGE(ID_telltale_SRS_BuckleSwitchStatus, telltale_SRS_BuckleSwitchStatus);
	CHECK_SHMVALUE_CHANGE(ID_telltale_TCU_TransFailureStatus, telltale_TCU_TransFailureStatus);
	CHECK_SHMVALUE_CHANGE(ID_telltale_EPB_FunctionLamp, telltale_EPB_FunctionLamp);
	CHECK_SHMVALUE_CHANGE(ID_telltale_BCM_BatteryStatus, telltale_BCM_BatteryStatus);
	CHECK_SHMVALUE_CHANGE(ID_telltale_BCM_DoorStatus, telltale_BCM_DoorStatus);
	CHECK_SHMVALUE_CHANGE(ID_telltale_BCM_HighBeamStatus, telltale_BCM_HighBeamStatus);
	CHECK_SHMVALUE_CHANGE(ID_telltale_BCM_LowBeamStatus, telltale_BCM_LowBeamStatus);
	CHECK_SHMVALUE_CHANGE(ID_telltale_BCM_TurnIndicatorRight, telltale_BCM_TurnIndicatorRight);
	CHECK_SHMVALUE_CHANGE(ID_telltale_BCM_TurnIndicatorLeft, telltale_BCM_TurnIndicatorLeft);
	CHECK_SHMVALUE_CHANGE(ID_telltale_BCM_RearFoglampStatus, telltale_BCM_RearFoglampStatus);
	CHECK_SHMVALUE_CHANGE(ID_telltale_BCM_FrontFoglampStatus, telltale_BCM_FrontFoglampStatus);
	CHECK_SHMVALUE_CHANGE(ID_telltale_BCM_PositionLampStatus, telltale_BCM_PositionLampStatus);

	// Gauge
	CHECK_SHMVALUE_CHANGE(ID_gauge_ESP_VehicleSpeed, gauge_ESP_VehicleSpeed);
	CHECK_SHMVALUE_CHANGE(ID_gauge_EMS_EngineSpeed, gauge_EMS_EngineSpeed);
	CHECK_SHMVALUE_CHANGE(ID_gauge_TCU_GearForDisplay, gauge_TCU_GearForDisplay);
	CHECK_SHMVALUE_CHANGE(ID_gauge_Theme, gauge_Theme);
	CHECK_SHMVALUE_CHANGE(ID_gauge_Translation, gauge_Translation);
	CHECK_SHMVALUE_CHANGE(ID_gauge_SpecialEffects, gauge_SpecialEffects);

	// Tripcomputer
	CHECK_SHMVALUE_CHANGE(ID_tripcomputer_Odo, tripcomputer_Odo);
	CHECK_SHMVALUE_CHANGE(ID_tripcomputer_Dte, tripcomputer_Dte);
	CHECK_SHMVALUE_CHANGE(ID_tripcomputer_IP_FuelLevelPercent, tripcomputer_IP_FuelLevelPercent);
	CHECK_SHMVALUE_CHANGE(ID_tripcomputer_AC_EnvironmentalTempVD, tripcomputer_AC_EnvironmentalTempVD);
	CHECK_SHMVALUE_CHANGE(ID_tripcomputer_AC_EnvironmentalTemp, tripcomputer_AC_EnvironmentalTemp);
	CHECK_SHMVALUE_CHANGE(ID_tripcomputer_Vehicle_SYS_time_H, tripcomputer_Vehicle_SYS_time_H);
	CHECK_SHMVALUE_CHANGE(ID_tripcomputer_Vehicle_SYS_time_M, tripcomputer_Vehicle_SYS_time_M);
	CHECK_SHMVALUE_CHANGE(ID_tripcomputer_Vehicle_SYS_time_S, tripcomputer_Vehicle_SYS_time_S);
	CHECK_SHMVALUE_CHANGE(ID_tripcomputer_Vehicle_Running_time_H, tripcomputer_Vehicle_Running_time_H);
	CHECK_SHMVALUE_CHANGE(ID_tripcomputer_Vehicle_Running_time_M, tripcomputer_Vehicle_Running_time_M);
	CHECK_SHMVALUE_CHANGE(ID_tripcomputer_trip_Average_Speed, tripcomputer_trip_Average_Speed);
	CHECK_SHMVALUE_CHANGE(ID_tripcomputer_trip, tripcomputer_trip);

	// Common
	CHECK_SHMVALUE_CHANGE(ID_common_PEPS_PowerDistributionStatus, common_PEPS_PowerDistributionStatus);

	// Interaction
	CHECK_SHMVALUE_CHANGE(ID_interaction_status_GW_MFS_Left_switch, interaction_status_GW_MFS_Left_switch);
	CHECK_SHMVALUE_CHANGE(ID_interaction_status_GW_MFS_Right_switch, interaction_status_GW_MFS_Right_switch);
	CHECK_SHMVALUE_CHANGE(ID_interaction_status_GW_MFS_UP_switch, interaction_status_GW_MFS_UP_switch);
	CHECK_SHMVALUE_CHANGE(ID_interaction_status_GW_MFS_Down_switch, interaction_status_GW_MFS_Down_switch);
	CHECK_SHMVALUE_CHANGE(ID_interaction_status_GW_MFS_OK_switch, interaction_status_GW_MFS_OK_switch);
	CHECK_SHMVALUE_CHANGE(ID_interaction_status_Window_Status, interaction_status_Window_Status);
	CHECK_SHMVALUE_CHANGE(ID_interaction_status_Menu_Status, interaction_status_Menu_Status);

	// Adas
	CHECK_SHMVALUE_CHANGE(ID_Adas_ACC_ACCMode, Adas_ACC_ACCMode);
	CHECK_SHMVALUE_CHANGE(ID_Adas_ACC_LaneChangeStatus, Adas_ACC_LaneChangeStatus);
	CHECK_SHMVALUE_CHANGE(ID_Adas_ACC_ACCTargetLngRange, Adas_ACC_ACCTargetLngRange);
	CHECK_SHMVALUE_CHANGE(ID_Adas_ACC_ACCTargetType, Adas_ACC_ACCTargetType);
	CHECK_SHMVALUE_CHANGE(ID_Adas_ACC_VehicleAnimationStatus, Adas_ACC_VehicleAnimationStatus);
	CHECK_SHMVALUE_CHANGE(ID_Adas_ACC_Curve, Adas_ACC_Curve);

	// Warning
	CHECK_SHMVALUE_CHANGE(ID_warning_Showing_ID, warning_Showing_ID);
}

