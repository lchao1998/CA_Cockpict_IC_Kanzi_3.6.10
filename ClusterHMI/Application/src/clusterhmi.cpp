// Use kanzi.hpp only when you are learning to develop Kanzi applications.
// To improve compilation time in production projects, include only the header files of the Kanzi functionality you are using.
#include <kanzi/kanzi.hpp>
#include "datalayerplugin_module.hpp"

using namespace kanzi;

class ClusterHMI : public ExampleApplication
{
public:

    virtual void onConfigure(ApplicationProperties& configuration) KZ_OVERRIDE
    {
        configuration.binaryName = "clusterhmi.kzb.cfg";
    }

    virtual void onProjectLoaded() KZ_OVERRIDE
    {
        // Project file has been loaded from .kzb file.

        // Add initialization code here.
    }
    virtual void registerMetadataOverride(ObjectFactory& /*factory*/) KZ_OVERRIDE
    {
        KanziComponentsModule::registerModule(getDomain());
    #if defined(ANDROID) || !defined(KANZI_API_IMPORT)
        DataLayerPluginModule::registerModule(getDomain());
    #endif
    }

};

Application* createApplication()
{
    return new ClusterHMI;
}
