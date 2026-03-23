#ifndef DATALAYERPLUGIN_MODULE_HPP
#define DATALAYERPLUGIN_MODULE_HPP

#include <kanzi/core/module/plugin.hpp>


class DataLayerPluginModule : public kanzi::Plugin
{
public:

    static void registerModule(kanzi::Domain* domain);

protected:

    MetaclassContainer getMetaclassesOverride() override;
};

#endif
