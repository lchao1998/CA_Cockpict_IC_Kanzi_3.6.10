#include "DataLayerCache.hpp"

#define SYNC_SIGNALCELL(cells)\
for(auto& cell : cells)\
	cell.m_signal->syncValue();\


#define SET_SIGNAL_VALUE(cells, proName, value)\
for(auto& cell : cells ){\
	if(cell.m_dataCell.kanziProName == proName){\
		cell.m_signal->setTempValue(value);\
	}\
}\

DataLayerCache::DataLayerCache()
{
}

DataLayerCache::~DataLayerCache()
{
}

void DataLayerCache::updateSignalValue()
{
	SYNC_SIGNALCELL(m_bSignalCells);
	SYNC_SIGNALCELL(m_iSignalCells);
	SYNC_SIGNALCELL(m_fSignalCells);
	SYNC_SIGNALCELL(m_sSignalCells);
}

void DataLayerCache::setSignalValue(DataIdentify id, bool value)
{
	SET_SIGNAL_VALUE(m_bSignalCells, g_dataCells[id].kanziProName, value);
}

void DataLayerCache::setSignalValue(DataIdentify id, int value)
{
	SET_SIGNAL_VALUE(m_iSignalCells, g_dataCells[id].kanziProName, value);
}

void DataLayerCache::setSignalValue(DataIdentify id, unsigned int value)
{
	SET_SIGNAL_VALUE(m_uSignalCells, g_dataCells[id].kanziProName, value);
}

void DataLayerCache::setSignalValue(DataIdentify id, float value)
{
	SET_SIGNAL_VALUE(m_fSignalCells, g_dataCells[id].kanziProName, value);
}

void DataLayerCache::setSignalValue(DataIdentify id, string value)
{
	SET_SIGNAL_VALUE(m_sSignalCells, g_dataCells[id].kanziProName, value);
}
