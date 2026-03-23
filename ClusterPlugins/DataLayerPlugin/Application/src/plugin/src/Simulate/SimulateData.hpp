/**
* @file         SimulateData.hpp
* @brief        Simulate Data class
* @details      Simulate the Model data here.
* @author       xu.qiang@zlingsmart.com
* @date         2022-5-24
* @version      v0.0.1
* @copyright    Copyright (c) 2022, zlingsmart Corporation.
**********************************************************************************
* @attention
*
* @par modity log:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2022/05/24  <td>v0.0.1   <td>          <td>Create
* </table>
*
**********************************************************************************
*/
#pragma once
#include "datalayerplugin.hpp"

#include <chrono>

class SimulateData {
public:
	static SimulateData& getInstance() {
		static SimulateData instance;
		return instance;
	}
protected:
	explicit SimulateData() {};
	~SimulateData() {};
public:
	void simulate(DataLayerPlugin* plugin);
private:
	void simulate_ODO();
	void simulate_GearForDisplay();
	void simulate_VehicleSpeed();
	void simulate_EngineSpeed();
	void simulate_TurnIndicator();
	void simulate_Warning();
	void simulate_SysTime();
	void simulate_TT();
	void simulate_Interaction();
	void simulate_Adas();
	void simulate_Theme();
private:
	DataLayerPlugin* m_datalayerPlugin = NULL;
	std::chrono::steady_clock::time_point m_begin_01;
	std::chrono::steady_clock::time_point m_begin_05;
	std::chrono::steady_clock::time_point m_begin_1;
	std::chrono::steady_clock::time_point m_begin_3;
	std::chrono::steady_clock::time_point m_begin_5;
	std::chrono::steady_clock::time_point m_begin_10;
	std::chrono::steady_clock::time_point m_begin_15;
	std::chrono::steady_clock::time_point start;
};