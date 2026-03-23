// Use kanzi.hpp only when you are learning to develop Kanzi applications. 
// To improve compilation time in production projects, include only the header files of the Kanzi functionality you are using.
#include <kanzi/kanzi.hpp>


#if !defined(ANDROID) && !defined(KANZI_API_IMPORT)
#include <datalayerplugin_module.hpp>

#if defined(DATALAYERPLUGIN_CODE_BEHIND_API)
#include <DataLayerPlugin_code_behind_module.hpp>
#endif

#endif

using namespace kanzi;


// Application class.
// Implements application logic.
class DataLayerPluginApplication : public ExampleApplication
{
protected:

    // Configures application.
    void onConfigure(ApplicationProperties& configuration) override
    {
        configuration.binaryName = "datalayerplugin.kzb.cfg";
    }

    // Initializes application after project has been loaded.
    void onProjectLoaded() override
    {
        // Code to run after the .KZB has been loaded.
		kzLogInfo(KZ_LOG_CATEGORY_GENERIC,("onProjectLoaded..."));
    }

    void registerMetadataOverride(ObjectFactory& factory) override
    {
        ExampleApplication::registerMetadataOverride(factory);

#if !defined(ANDROID) && !defined(KANZI_API_IMPORT)
        Domain* domain = getDomain();
        DataLayerPluginModule::registerModule(domain);

#if defined(DATALAYERPLUGIN_CODE_BEHIND_API)
        DataLayerPluginCodeBehindModule::registerModule(domain);
#endif

#endif
    }
};

// Creates application instance. Called by framework.
Application* createApplication()
{
    return new DataLayerPluginApplication();
}
