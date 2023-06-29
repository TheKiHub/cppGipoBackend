#-------------------------------------------------------------------------------------------------------
# Create target
#-------------------------------------------------------------------------------------------------------
message(DEBUG "Creating ${PROJECT_NAME}")

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PRIVATE
            src/gipoManager.cpp
            src/gipoI2cBus.cpp
            src/i2cDevice.cpp
            src/gipoPwmPin.cpp
        )

# define relocatable include files for target
target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

# add alias for easier use
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# enable all compiler specific warnings for the target
set_target_warnings(${PROJECT_NAME})
set_target_cpp_compiler_flags(${PROJECT_NAME})

#-------------------------------------------------------------------------------------------------------
# Declare dependencies
#-------------------------------------------------------------------------------------------------------
handleExternals(NAME quill)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            quill
        )

option(GIPOBACKEND_MRAA "Using mraa as Gipo backend" OFF)
option(GIPO_MANAGER_GUI "Using the Gui instead of the terminal" OFF)

if(GIPO_MANAGER_GUI)
    target_compile_definitions(${PROJECT_NAME} PUBLIC USE_GUI)
#    target_sources(${PROJECT_NAME}
#            PRIVATE
#            src/gui.cpp
#            )
    CPMAddPackage(
            NAME imGuiBackend
            URL https://github.com/TheKiHub/imGuiBackend/releases/latest/download/package_files.zip
            VERSION latest
    )
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
                guiBackend
            )
endif()

if(GIPOBACKEND_MRAA)
    target_compile_definitions(${PROJECT_NAME} PUBLIC MRAA)
    handleExternals(NAME mraa)
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
                mraa
            )
    message(DEBUG "Using mraa for Gipo backend")
else()
    message(DEBUG "Using no Gipo backend")
endif()

#-------------------------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------------------------
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)
packageProject(
        NAME ${PROJECT_NAME}
        VERSION ${PROJECT_VERSION}
        NAMESPACE ${PROJECT_NAME}
        BINARY_DIR ${PROJECT_BINARY_DIR}
        INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/
        INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
        VERSION_HEADER "${VERSION_HEADER_LOCATION}"
        COMPATIBILITY SameMajorVersion
        DEPENDENCIES ""
)
