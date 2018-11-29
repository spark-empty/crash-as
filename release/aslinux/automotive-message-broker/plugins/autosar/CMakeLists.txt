if(autosar_plugin)
############################################################################################################################################

pkg_check_modules(json REQUIRED json)

include_directories(${CMAKE_SOURCE_DIR}/lib ${include_dirs} ${gio_INCLUDE_DIRS} ${gio-unix_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/plugins/common ${Boost_INCLUDE_DIRS} ${json_INCLUDE_DIRS})

set(autosarplugin_headers autosarplugin.h)
set(autosarplugin_sources autosarplugin.cpp)

add_library(autosarplugin MODULE ${autosarplugin_sources} ${autosarplugin_headers})
set_target_properties(autosarplugin PROPERTIES PREFIX "")

## cd build/lib; ln -fs ../../plugins/autosar/out/libposix.a  libascore.so
target_link_libraries(autosarplugin amb amb-plugins-common -L${CMAKE_CURRENT_BINARY_DIR}/plugins/common ${link_libraries} -lrt ${json_LIBRARIES}
	-lascore)

install(TARGETS autosarplugin LIBRARY DESTINATION ${PLUGIN_INSTALL_PATH})

############################################################################################################################################

endif(autosar_plugin)