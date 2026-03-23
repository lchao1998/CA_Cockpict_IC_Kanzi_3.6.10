#include "SimulateData.hpp"
#include <kanzi/kanzi.hpp>
#include <random>
#include <thread>
#ifdef WIN32
#include <windows.h>
#endif



static int i = 0;
static bool flag = false;
static bool startflag = false;


void SimulateData::simulate(DataLayerPlugin* plugin)
{
	if (plugin == NULL)
	{
		return;
	}

	auto tmp = std::chrono::steady_clock::now();
	if ((tmp - m_begin_01).count() / (1000*1000) > 50)
	{
		//kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("SimulateData count : {}...", (tmp - m_begin).count() / (1000 * 1000)));
		m_begin_01 = tmp;
		m_datalayerPlugin = plugin;

		simulate_VehicleSpeed();
	}

	if ((tmp - m_begin_05).count() / (1000*1000) > 500)
	{
		m_begin_05 = tmp;

		simulate_EngineSpeed();
	}

	if ((tmp - m_begin_1).count() / (1000*1000) > 1000)
	{
		m_begin_1 = tmp;

		simulate_ODO();
	}

	if ((tmp - m_begin_3).count() / (1000 * 1000) > 3000)
	{
		m_begin_3 = tmp;

		simulate_Adas();
	}

	if ((tmp - m_begin_5).count() / (1000 * 1000) > 5000)
	{
		m_begin_5 = tmp;
	
		simulate_GearForDisplay();
		simulate_TurnIndicator();
		simulate_Interaction();
		simulate_Warning();
	}

	if (((tmp - start).count() / (1000 * 1000) > 500) && (i < 16))
	{
		start = tmp;

		simulate_TT();
	}

	if ((tmp - m_begin_10).count() / (1000 * 1000) > 10000)
	{
		m_begin_10 = tmp;

		i = 0;
		flag = !flag;

		simulate_SysTime();
	}

	if ((tmp - m_begin_15).count() / (1000 * 1000) > 15000)
	{
		m_begin_15 = tmp;

		simulate_Theme();
	}

}

void SimulateData::simulate_ODO()
{
	static int odo = 0;
	odo++;
	m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Trip.Odo"), odo);
	m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Trip.Dte"), 500 - odo);
	//kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("SimulateData odo : {} ...", odo));
}

void SimulateData::simulate_GearForDisplay()
{
	static int gear = 0;
	m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.GearForDisplay"), gear);
	kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("SimulateData gear : {} ...", gear));
	gear++;
	if (gear > 3)
	{
		gear = 0;
	}
}

void SimulateData::simulate_VehicleSpeed()
{
	static int speed = 0;
	m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.VehicleSpeed"), speed);
	kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("SimulateData gear : {} ...", speed));
	speed += 1;
	if (speed >= 240 )
	{
		speed = 0;
	}
}

void SimulateData::simulate_EngineSpeed()
{
	static int tacheSpeed = 0;
	m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.EngineSpeed"),tacheSpeed);
	kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("SimulateData EngineSpeed : {} ...", tacheSpeed));
	tacheSpeed += 100;
	if (tacheSpeed > 5500)
	{
		tacheSpeed = 0;
	}
}

void SimulateData::simulate_TurnIndicator()
{
	static int turnStatus = 0;
	if (turnStatus == 0)
	{
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.TurnIndicatorLeft"), 1);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.TurnIndicatorRight"), 0);
	}
	else if(turnStatus == 1)
	{
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.TurnIndicatorLeft"), 0);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.TurnIndicatorRight"), 0);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Adas.Curve"), 1);
		kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("Adas.Curve : 1"));
	}
	else if (turnStatus == 2)
	{
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.TurnIndicatorLeft"), 0);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.TurnIndicatorRight"), 0);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Adas.Curve"), 0);
		kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("Adas.Curve : 0"));
	}
	else if (turnStatus == 3)
	{
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.TurnIndicatorLeft"), 0);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.TurnIndicatorRight"), 0);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Adas.Curve"), 2);
		kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("Adas.Curve : 2"));
	}
	else if (turnStatus == 4)
	{
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.TurnIndicatorLeft"), 0);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.TurnIndicatorRight"), 1);
	}

	turnStatus++;
	if (turnStatus > 4)
	{
		turnStatus = 0;
	}


}

void SimulateData::simulate_Warning()
{
	////获取引擎中的节点，通过代码改变节点的属性

	//Application warning;
	//ScreenSharedPtr screen = warning.getScreen();
	//Node2DSharedPtr  image = screen->lookupNode<Node2D>("image");
	//image->setRenderTransformation(SRTValue2D(Vector2(1, 1), 0, Vector2(580, 0)));
	

	static int waringID = 0;
	m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Warning.Showing_ID"), waringID);
	kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("SimulateData Warning id : {} ...", waringID));
	waringID++;
	if (waringID > 10)
	{
		waringID = 0;
	}
}

void SimulateData::simulate_SysTime()
{
	static int h = 11;
	static int m = 21;

	m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Trip.Vehicle_SYS_time_H"), h);
	m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Trip.Vehicle_SYS_time_M"), m);

	m += 1;

	if (h > 24)
	{
		h = 0;
	}

	if (m > 59)
	{
		m = 0;
		h += 1;
	}
}

void SimulateData::simulate_TT()
{
	//static int index = 0; 
	//index++;
	//if (index > 10000)
	//{
	//	index = 0;
	//}
	//static default_random_engine ae,be,ce,de;
	//static uniform_int_distribution<unsigned> ua(0, 9+ index);
	//static uniform_int_distribution<unsigned> ub(10, 20 + index);
	//static uniform_int_distribution<unsigned> uc(4, 33 + index);
	//static uniform_int_distribution<unsigned> ud(1, 50 + index);
	//int a, b, c, d;
	//a = ua(ae) % 2;
	//b = ub(be) % 2;
	//c = uc(ce) % 2;
	//d = ud(de) % 2;

	//kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("SimulateData simulate_TT id : a : {} b: {} c: {} d: {} ...", a,b,c,d));

	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.SVS"), a);
	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.BuckleSwitchStatus"), c);
	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.FrontFoglampStatus"), a);
	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.RearFoglampStatus"), d);
	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.HighBeamStatus"), d);
	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.LowBeamStatus"), a);
	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.PositionLampStatus"), b);

	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.EngineFailureStatus"), d);
 //   m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.CoolanTemperatureError"), a);
	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.OilPressureSts"), b);
	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.ABSFailStatus"), a);
	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.WarningLampStatus"), a);
	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.TransFailureStatus"), b);
	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.FunctionLamp"), c);

	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.BatteryStatus"), d);
	//m_datalayerPlugin->setProperty(DynamicPropertyType<int>("TT.DoorStatus"), d);


	string TT[] = { "TT.SVS","TT.BuckleSwitchStatus","TT.FrontFoglampStatus","TT.RearFoglampStatus","TT.HighBeamStatus","TT.LowBeamStatus","TT.PositionLampStatus" ,
					"TT.EngineFailureStatus","TT.CoolanTemperatureError","TT.OilPressureSts","TT.ABSFailStatus","TT.WarningLampStatus","TT.TransFailureStatus","TT.FunctionLamp",
					"TT.BatteryStatus","TT.DoorStatus" };
	if (flag == true) 
	{ 
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>(TT[i]), 1);
		i++;
	}

	else
	{
		for (int a = 0; a < 16; a++)
		{
			m_datalayerPlugin->setProperty(DynamicPropertyType<int>(TT[a]), 0);
		}
	}
}

void SimulateData::simulate_Interaction()
{
	static int windowIndex = 0;
	static int menuIndex = 1;

	// window
	m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Interaction.Window_Status"), windowIndex);
	kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("SimulateData simulate_Interaction window index{} ...", windowIndex));

	// menu
	if (windowIndex >= 5 )
	{
		if (menuIndex < 4)
		{
			m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Interaction.Menu_Status"), menuIndex);
			kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("SimulateData simulate_Interaction Menu_Status index{} ...", menuIndex));
		}

		menuIndex++;
		if (menuIndex > 3)
		{
			menuIndex = 1;
		}
	}

	windowIndex++;
	if (windowIndex >=8)
	{
		windowIndex = 0;
	}
}

void SimulateData::simulate_Adas()
{
	static int targetTypeIndex = 0;
	static int targetRangeIndex = 0;

	m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Adas.ACCTargetLngRange"), targetRangeIndex);
	kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("SimulateData simulate_Adas.ACCTargetRange{} ...", targetRangeIndex));

	if (targetRangeIndex == 1)
	{
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Adas.ACCTargetType"), targetTypeIndex);
		kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("SimulateData simulate_Adas.ACCTargetType{} ...", targetTypeIndex));
	}

	targetRangeIndex++;


	if (targetRangeIndex == 1)
	{ 
		targetTypeIndex++;
	}

	if (targetRangeIndex > 1)
	{
		targetRangeIndex = 0;
	}


	if (targetTypeIndex > 7)
	{
		targetTypeIndex = 0;
	}
}

void SimulateData::simulate_Theme()
{
	static int value = 0;
	if (value == 0)
	{
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.Theme"), 0);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.Translation"), 0);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.SpecialEffects"), 0);
	}
	if (value == 1)
	{
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.Theme"), 0);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.Translation"), 1);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.SpecialEffects"), 1);
	}
	if (value == 2)
	{
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.Theme"), 1);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.Translation"), 0);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.SpecialEffects"), 0);
	}
	if (value == 3)
	{
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.Theme"), 1);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.Translation"), 1);
		m_datalayerPlugin->setProperty(DynamicPropertyType<int>("Gauge.SpecialEffects"), 1);
	}
	value++;
	if (value >= 4)
	{
		value = 0;
	}
}

