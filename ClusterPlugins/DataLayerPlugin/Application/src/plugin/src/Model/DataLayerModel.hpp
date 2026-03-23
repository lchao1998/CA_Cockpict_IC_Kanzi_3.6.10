/**
* @file         DataLayerModel.hpp
* @brief        DataLayer Model class
* @details      Handler the Model data here.
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

class DataLayerModel
{
public:
	static DataLayerModel* getInstance()
	{
		if (NULL == m_instance)
			m_instance = new DataLayerModel();
		return m_instance;
	}
	static void destoryInstance()
	{
		if (NULL != m_instance)
		{
			delete m_instance;
			m_instance = NULL;
		}
	}
public:
	DataLayerModel() {};
	~DataLayerModel() { destoryInstance(); };
private:
	static DataLayerModel* m_instance;
public:
	/**
	* @fn init
	* @brief init data layer model property
	* @return true/false
	*/
	bool init();

	/**
	* @fn recvData
	* @brief update data from sharedmemory
	* @return 
	*/
	void recvData();

private:
	/**
	* @fn make_property
	* @brief make a new property with bool value
	* @param id : property id
	* @param defaultValue : default property value
	* @return
	*/
	void make_property(DataIdentify id, bool defaultValue);

	/**
	* @fn make_property
	* @brief make a new property with int value
	* @param id : property id
	* @param defaultValue : default property value
	* @return
	*/
	void make_property(DataIdentify id, int defaultValue);

	/**
	* @fn make_property
	* @brief make a new property with int value
	* @param id : property id
	* @param defaultValue : default property value
	* @return
	*/
	void make_property(DataIdentify id, unsigned int defaultValue);

	/**
	* @fn make_property
	* @brief make a new property with float value
	* @param id : property id
	* @param defaultValue : default property value
	* @return
	*/
	void make_property(DataIdentify id, float defaultValue);

	/**
	* @fn make_property
	* @brief make a new property with string value
	* @param id : property id
	* @param defaultValue : default property value
	* @return
	*/
	void make_property(DataIdentify id, string defaultValue);

private:
	/**
	* @fn checkPropertyName
	* @brief check property name with sharedmemory.
	* @return
	*/
	void checkPropertyName();

	/**
	* @fn createKanziProperty
	* @brief create kanzi property which show on kanzi studio editor.
	* @return
	*/
	void createKanziProperty();

	/**
	* @fn checkDataChange
	* @brief check data change which from sharedmemory.
	* @return
	*/
	void checkDataChange();
private:
	bool m_bInit = false;
};

