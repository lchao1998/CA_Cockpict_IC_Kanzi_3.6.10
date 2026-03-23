#include "datalayerplugin.hpp"
#include "Simulate/SimulateData.hpp"
#include <thread>
#include <chrono>


using namespace kanzi;

vector<std::shared_ptr<DataLayerPlugin::DataLayerPropertyType<bool>>>	DataLayerPlugin::m_bProperties(NULL);
vector<std::shared_ptr<DataLayerPlugin::DataLayerPropertyType<int>>>	DataLayerPlugin::m_iProperties(NULL);
vector<std::shared_ptr<DataLayerPlugin::DataLayerPropertyType<float>>>	DataLayerPlugin::m_fProperties(NULL);
vector<std::shared_ptr<DataLayerPlugin::DataLayerPropertyType<string>>>	DataLayerPlugin::m_sProperties(NULL);

 int a;


PropertyType<int>DataLayerPlugin::tt(MetadataGeneratedName("TT"), NULL, 0, false);
//PropertyType<SRTValue2D>DataLayerPlugin::a(MetadataGeneratedName("transformation"), SRTValue2D(Vector2(1, 1), 0, Vector2(0, 0)), 0, false);

// Creates the property editor info for the DataLayerPlugin.
PropertyTypeEditorInfoSharedPtr DataLayerPlugin::makeEditorInfo()
{
	kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("DataLayerPlugin makeEditorInfo..."));
    return PropertyTypeEditorInfoSharedPtr(
        KZ_DECLARE_EDITOR_METADATA(
            metadata.tooltip = "Description for DataLayerPlugin.";
			metadata.displayName = "Datalayer";
        ));
}

// Creates a DataLayerPlugin.
DataLayerPluginSharedPtr DataLayerPlugin::create(Domain* domain, string_view name)
{
    auto enginePlugin = DataLayerPluginSharedPtr(new DataLayerPlugin(domain, name));

    enginePlugin->initialize();
	kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("DataLayerPlugin create..."));
    return enginePlugin;
}

void DataLayerPlugin::renderOverride(Renderer3D& renderer, CompositionStack& compositionStack)
{
	//kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("DataLayerPlugin renderOverride..."));
	Node2D::renderOverride(renderer, compositionStack);
	DataLayerCache::getInstance().updateSignalValue();

	SimulateData::getInstance().simulate(this);
	//kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("DataLayerPlugin renderOverride..."));
}

// Initializes the created Kanzi Engine plugin.
// Kanzi node classes typically have a static create() member function, which creates the instance of a node,
// initializes it, and returns a shared pointer to the instance. To initialize an instance of a Kanzi Engine 
// plugin, in the create() function call the initialize() function on the instance of that Kanzi Engine plugin. 
// You must initialize a node in the initialize() function, not in the constructor.
void DataLayerPlugin::initialize()
{
    // Initialize base class.
	Node2D::initialize();

	initPropertyDefaultValue();
	initPropertyListen();
	kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("DataLayerPlugin initialize..."));
}

void DataLayerPlugin::initPropertyDefaultValue()
{
	for (auto& cell : DataLayerCache::getInstance().m_bSignalCells)
	{
		setProperty(DynamicPropertyType<bool>(cell.m_dataCell.kanziProName), cell.m_defaultValue);
	}

	for (auto& cell : DataLayerCache::getInstance().m_iSignalCells)
	{
		setProperty(DynamicPropertyType<int>(cell.m_dataCell.kanziProName), cell.m_defaultValue);
	}

	for (auto& cell : DataLayerCache::getInstance().m_fSignalCells)
	{
		setProperty(DynamicPropertyType<float>(cell.m_dataCell.kanziProName), cell.m_defaultValue);
	}

	for (auto& cell : DataLayerCache::getInstance().m_sSignalCells)
	{
		setProperty(DynamicPropertyType<string>(cell.m_dataCell.kanziProName), cell.m_defaultValue);
	}
}

void DataLayerPlugin::initPropertyListen()
{
	for (auto& cell : DataLayerCache::getInstance().m_bSignalCells)
	{
		//listenSignalConnect<bool>(cell);
	}

	for (auto& cell : DataLayerCache::getInstance().m_iSignalCells)
	{
		//listenSignalConnect<int>(cell);
	}

	for (auto& cell : DataLayerCache::getInstance().m_fSignalCells)
	{
		//listenSignalConnect<float>(cell);
	}

	for (auto& cell : DataLayerCache::getInstance().m_sSignalCells)
	{
		//listenSignalConnect<string>(cell);
	}
}
