m = module(project_name)

m.env["LIBPATH"] += [os.path.join("..", "..", "..", "lib", platform_name)]

m.env["LIBS"] += ["DataLayerPlugin"]

del m
