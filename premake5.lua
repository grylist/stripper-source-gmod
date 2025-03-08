PROJECT_GENERATOR_VERSION = 3

newoption({
	trigger = "gmcommon",
	description = "Sets the path to the garrysmod_common (https://github.com/danielga/garrysmod_common) directory",
	value = "../garrysmod_common"
})

local gmcommon = assert(_OPTIONS.gmcommon or os.getenv("GARRYSMOD_COMMON"),
	"you didn't provide a path to your garrysmod_common (https://github.com/danielga/garrysmod_common) directory")
include(gmcommon)

--[[
	CreateWorkspace parameters:
		name 			- self-explanatory
		path 			- where to put .so files at ( default is (for generator v2 and 3) ./projects, WORKSPACE_DIRECTORY )
		allow_debug 	- deprecated, internally sets abi_compatible ( default is false )
		abi_compatible 	- removes "debug" make configuration, defines("_GLIBCXX_USE_CXX11_ABI=0") for linux and macosx ( default is false )

	CreateProject parameters:
		serverside		- self-explanatory, if true, adds "gmsv_", otherwise - "gmcl_". gmsv/gmcl can be removed at line 286 of premake/generator.lua ( default is false )
		source_path		- dir where your store .cpp and .h/.hpp ( default is ./source, SOURCE_DIRECTORY )
		manual_files	- if false, will simply look at source_path dir( not recursively ) for any possible files with a code, line 344 of premake/generator.lua ( default is false )
		abi_compatible	- removes "debug" make configuration ( default is false ), does
			local filepath = _GARRYSMOD_COMMON_DIRECTORY .. "/source/ABICompatibility.cpp"
			files(filepath)
			vpaths({["garrysmod_common"] = filepath})
		pch_header		- something for vgui and html
		pch_source		- something for vgui and html
		name			- use this name instead of CreateWorkspace's name

	Also:
		Global:
			GARRYSMOD_LUA_BIN_DIRECTORY - path to garrysmod/lua/bin

		CreateProject
			links({})					- links external libraries
				"dl"	- for dlopen() function and similar ones
			kind "SharedLib" 			- isn't this already "SharedLib" by default?
			symbols "On"				- no reason to forcefully add symbols
]]

CreateWorkspace({name = "stripper"})

	CreateProject({serverside = true})
		IncludeSDKCommon()
		IncludeSDKTier0()
		IncludeSDKTier1()

		IncludeHelpersExtended()
		IncludeDetouring()
		IncludeScanning()

		links { "pcre" }

		filter("system:windows")
			files({"source/win32/*.cpp", "source/win32/*.hpp"})

		filter("system:linux")
			targetextension(".so") -- So that we'll have a server plugin, not a binary module

		filter("system:linux or macosx")
			files({"source/posix/*.cpp", "source/posix/*.hpp"})