#ifndef DATALAYERPLUGIN_HPP
#define DATALAYERPLUGIN_HPP

// Use kanzi.hpp only when you are learning to develop Kanzi applications. 
// To improve compilation time in production projects, include only the header files of the Kanzi functionality you are using.
#include <kanzi/kanzi.hpp>
#include "DataLayerModel.hpp"
#include "DataLayerCache.hpp"
#include <functional>
#include <memory.h>

using namespace std::placeholders;

#define DECL_META_PROPERTY(type, cells, properties)\
for (auto& cell : cells) {\
	std::shared_ptr<DataLayerPropertyType<type>> customType(new DataLayerPropertyType<type>(MetadataGeneratedName(cell.m_dataCell.kanziProName), cell.m_defaultValue, 0, false));\
	properties.push_back(customType);\
	KZ_METACLASS_PROPERTY_TYPE(AbstractPropertyType(customType->get()));\
}\

using namespace kanzi;

class DataLayerPlugin;
typedef kanzi::shared_ptr<DataLayerPlugin> DataLayerPluginSharedPtr;

// The template component.
class DATALAYERPLUGIN_API DataLayerPlugin : public kanzi::Node2D
{
public:
	template<class T>
	class DataLayerPropertyType : public PropertyType<T> {
	public:
		explicit DataLayerPropertyType() {};
		explicit DataLayerPropertyType(MetadataGeneratedName name, T defaultValue, uint32_t changeFlags, bool inheritable) :
			PropertyType<T>(name, defaultValue, changeFlags, inheritable) {}
	};

	static PropertyType<int> tt;
	//static PropertyType<SRTValue2D> a;


	KZ_METACLASS_BEGIN(DataLayerPlugin, Node2D, "Datalayer")
		// Property
		DECL_META_PROPERTY(bool, DataLayerCache::getInstance().m_bSignalCells, m_bProperties);
		DECL_META_PROPERTY(int, DataLayerCache::getInstance().m_iSignalCells, m_iProperties);
		DECL_META_PROPERTY(float, DataLayerCache::getInstance().m_fSignalCells, m_fProperties);
		DECL_META_PROPERTY(string, DataLayerCache::getInstance().m_sSignalCells, m_sProperties);

		KZ_METACLASS_PROPERTY_TYPE(tt);
		//KZ_METACLASS_PROPERTY_TYPE(a);
		KZ_METACLASS_END()

		// Creates the property editor info for the DataLayerPlugin.
		static kanzi::PropertyTypeEditorInfoSharedPtr makeEditorInfo();


	// Creates a DataLayerPlugin.
	static DataLayerPluginSharedPtr create(kanzi::Domain* domain, kanzi::string_view name);
	/// Node-specific rendering implementation.
	/// Default implementation throws an error, since the default implementation should not generate a render state.
	/// \param renderer Renderer to use.
	/// \param renderState Render state to use.
	virtual void renderOverride(Renderer3D& renderer, CompositionStack& compositionStack);
protected:

	// Constructor.
	explicit DataLayerPlugin(kanzi::Domain* domain, kanzi::string_view name) :
		kanzi::Node2D(domain, name)
	{
	}

	// Initializes the created Kanzi Engine plugin.
	// Kanzi node classes typically have a static create() member function, which creates the instance of a node,
	// initializes it, and returns a shared pointer to the instance. To initialize an instance of a Kanzi Engine 
	// plugin, in the create() function call the initialize() function on the instance of that Kanzi Engine plugin. 
	// You must initialize a node in the initialize() function, not in the constructor.
	void initialize();

private:
	void initPropertyDefaultValue();
	void initPropertyListen();
private:
	template<typename T>
	void listenSignalConnect(SignalCell<T> cell)
	{
		if (cell.m_dataCell.dataDirec == DD_Memory_To_Plugin)
		{
			cell.m_signal->connect(boost::bind<void>([&](T value, string kanziProName) {
				setProperty(DynamicPropertyType<T>(kanziProName), value);
			}, std::placeholders::_1, cell.m_dataCell.kanziProName));
		}
	}
public:
	static vector<std::shared_ptr<DataLayerPlugin::DataLayerPropertyType<bool>>>	m_bProperties;
	static vector<std::shared_ptr<DataLayerPlugin::DataLayerPropertyType<int>>>		m_iProperties;
	static vector<std::shared_ptr<DataLayerPlugin::DataLayerPropertyType<float>>>	m_fProperties;
	static vector<std::shared_ptr<DataLayerPlugin::DataLayerPropertyType<string>>>	m_sProperties;
};
#endif
