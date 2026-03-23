dependencies = ["kzjs", "kzui"]

m = module("DataLayerPlugin_component")
m.type = "a"
if build_from_sources:
    m.depends += dependencies
    if GetOption("build-dynamic-libs"): # This option is set when --dynamic is used
        m.type = "so"
        m.env["SHLINKFLAGS"] += ["-shared"]
else:
    m.used_libraries += dependencies

m.root = os.path.join("..", "..", "..", "src", "plugin")
m.output_path = os.path.join("..", "..", "..", "output", platform_name, profile_string, "plugin")

m.env["CPPDEFINES"] += ["DATALAYERPLUGIN_API="]

del m

m = module(project_name)
m.depends += ["DataLayerPlugin_component"]

if build_from_sources:
    m.depends += dependencies

else:
    m.used_libraries += dependencies

m.include_paths += [os.path.join("..", "..", "..", "src", "plugin", "src")]

m.root = os.path.join("..", "..", "..", "src", "executable")
m.output_path = os.path.join("..", "..", "..", "output", platform_name, profile_string, "executable")

m.used_libraries += ["v8"]
m.env["CPPDEFINES"] += ["KANZI_V8_API="]
m.env["CPPDEFINES"] += ["DATALAYERPLUGIN_API="]

del m
