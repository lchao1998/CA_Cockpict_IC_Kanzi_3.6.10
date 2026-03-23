#include "datalayerplugin_module.hpp"
#include "datalayerplugin.hpp"
#include "DataLayerModel.hpp"

using namespace kanzi;

void DataLayerPluginModule::registerModule(Domain* domain)
{
    domain->registerModule<DataLayerPluginModule>("DataLayerPlugin");
}

DataLayerPluginModule::MetaclassContainer DataLayerPluginModule::getMetaclassesOverride()
{
	DataLayerModel::getInstance()->init();
    MetaclassContainer metaclasses;
    metaclasses.push_back(DataLayerPlugin::getStaticMetaclass());
    return metaclasses;
}

#if defined(KANZI_API_IMPORT) || defined(ANDROID)

extern "C"
{

	DATALAYERPLUGIN_API Module* createModule(uint32_t /*kanziVersionMajor*/, uint32_t /*kanziVersionMinor*/)
	{
		return new DataLayerPluginModule;
	}

}

#endif
