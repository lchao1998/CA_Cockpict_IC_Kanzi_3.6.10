/**
* @file         DataLayerCache.hpp
* @brief        DataLayer Model cache class
* @details      Handler the Model data cache here.
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
#include "DataLayerModelDefine.hpp"

class DataLayerCache
{
public:
	static DataLayerCache& getInstance()
	{
		static DataLayerCache instance;
		return instance;
	}
private:
	explicit DataLayerCache();
	~DataLayerCache();
	DataLayerCache(const DataLayerCache&) = delete;
	DataLayerCache& operator=(const DataLayerCache&) = delete;

public:
	/**
	* @fn updateSignalValue
	* @brief update stored signal value to kanzi.
	* @return None
	*/
	void updateSignalValue();

	/**
	* @fn setSignalValue
	* @brief make a new property with bool value
	* @param id : property id
	* @param value :  property value
	* @return None
	*/
	void setSignalValue(DataIdentify id, bool value);

	/**
	* @fn setSignalValue
	* @brief make a new property with int value
	* @param id : property id
	* @param value :  property value
	* @return None
	*/
	void setSignalValue(DataIdentify id, int value);

	/**
	* @fn setSignalValue
	* @brief make a new property with  unsigned int value
	* @param id : property id
	* @param value :  property value
	* @return None
	*/
	void setSignalValue(DataIdentify id, unsigned int value);

	/**
	* @fn setSignalValue
	* @brief make a new property with float value
	* @param id : property id
	* @param value :  property value
	* @return None
	*/
	void setSignalValue(DataIdentify id, float value);

	/**
	* @fn setSignalValue
	* @brief make a new property with string value
	* @param id : property id
	* @param value :  property value
	* @return None
	*/
	void setSignalValue(DataIdentify id, string value);
public:
	vector<SignalCell<bool>>			m_bSignalCells;
	vector<SignalCell<int>>				m_iSignalCells;
	vector<SignalCell<unsigned int>>	m_uSignalCells;
	vector<SignalCell<float>>			m_fSignalCells;
	vector<SignalCell<string>>			m_sSignalCells;

	bool m_bStartSync = false;

};

