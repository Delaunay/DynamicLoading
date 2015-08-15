aux_source_directory(. DLL_SOURCE)

# Make file show in the IDE
set(DLL_HEADER
    DynamicObject.h
    ErrorPolicy.h
    Plugin.h
)

add_library(plugin_library ${DLL_SOURCE} ${DLL_HEADER})
