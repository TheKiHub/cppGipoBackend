add_executable( main src/main.cpp )
target_link_libraries( main PRIVATE gipoBackend)

if(USE_GUI)
    add_executable( guiMain src/guiMain.cpp )
    target_link_libraries( guiMain PRIVATE gipoBackend)
endif()
