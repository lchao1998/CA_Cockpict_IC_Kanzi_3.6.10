
#dependencies = ["kzjs", "kzui"]
dependencies = ["kzappfw"]

m = module(project_name)
m.type = "a"
if build_from_sources:
    m.depends += dependencies
    if GetOption("build-dynamic-libs"): # This option is set when --dynamic is used
        m.type = "so"
        m.env["SHLINKFLAGS"] += ["-shared"]
else:
    m.used_libraries += dependencies

m.include_paths += [os.path.join("..", "..", "..", "src", "plugin", "src")]
m.include_paths += [os.path.join("..", "..", "..", "src", "plugin", "src", "Common")]
m.include_paths += [os.path.join("..", "..", "..", "src", "plugin", "src", "Model")]
m.include_paths += [os.path.join("..", "..", "..", "src", "plugin", "src", "SharedMemory")]
m.include_paths += [os.path.join("..", "..", "..", "src", "plugin", "src", "Simulate")]

m.root = os.path.join("..", "..", "..", "src", "plugin")
#m.output_path = os.path.join("..", "..", "..", "output", platform_name, profile_string, "plugin")

#m.env["CPPDEFINES"] += ["DATALAYERPLUGIN_API="]

del m


