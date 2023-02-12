#-------------------------------------------------------------------------------------------------------
# Create target
#-------------------------------------------------------------------------------------------------------
project(gipoLibrary VERSION 0.1.0 LANGUAGES CXX)

message(DEBUG "Creating ${PROJECT_NAME}")

add_library(${PROJECT_NAME}
        src/gipoI2c.cpp
        src/pwm.cpp
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

#-------------------------------------------------------------------------------------------------------
# Declare dependencies
#-------------------------------------------------------------------------------------------------------
handleExternals(NAME quill)
option(GIPOBACKEND_MRAA "Using mraa as Gipo backend" OFF)

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
    if(USE_GUI_WITHOUT_BACKEND)

    endif()
endif()

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            quill
        )

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
