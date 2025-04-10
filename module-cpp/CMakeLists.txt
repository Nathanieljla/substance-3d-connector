#[[
Copyright 2019 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
]]

#########################################################
#                   Connector Framework                 #
#########################################################

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

#########################################################
#                   Project Description                 #
#########################################################

set(CONNECTOR_FRAMEWORK_BUILD_MAJOR_VERSION 0)
set(CONNECTOR_FRAMEWORK_BUILD_MINOR_VERSION 4)
set(CONNECTOR_FRAMEWORK_BUILD_PATCH_VERSION 2)

set(CONNECTOR_FRAMEWORK_BUILD_VERSION ${CONNECTOR_FRAMEWORK_BUILD_MAJOR_VERSION}.${CONNECTOR_FRAMEWORK_BUILD_MINOR_VERSION}.${CONNECTOR_FRAMEWORK_BUILD_PATCH_VERSION})

#########################################################
#                       Building                        #
#########################################################

set(CONNECTOR_FRAMEWORK_SOURCES
    src/framework/application.cpp
    src/framework/core.cpp
    src/framework/system.cpp
    src/framework/uuid.cpp
    src/framework/features/livelink.cpp
    src/framework/features/sendsbsar.cpp
    src/framework/features/sendmesh.cpp
    src/framework/details/callbacks.cpp
    src/framework/details/dynamicload.cpp
    src/framework/schemas/sendtoschema.cpp
    src/framework/schemas/sendmeshschema.cpp
    src/framework/schemas/connectionschema.cpp
)

set(CONNECTOR_FRAMEWORK_HEADERS
    include/substance/connector/framework/application.h
    include/substance/connector/framework/callbackstype.h
    include/substance/connector/framework/system.h
    include/substance/connector/framework/uuid.h
    include/substance/connector/framework/features/livelink.h
    include/substance/connector/framework/features/sendsbsar.h
    include/substance/connector/framework/features/sendmesh.h
    include/substance/connector/framework/details/callbacks.h
    include/substance/connector/framework/details/dynamicload.h
    include/substance/connector/framework/schemas/sendtoschema.h
    include/substance/connector/framework/schemas/sendmeshschema.h
    include/substance/connector/framework/schemas/connectionschema.h
)

# Before building, make sure core is also included
# if (NOT TARGET substance_connector_core)
#  message(FATAL_ERROR "Missing target substance_connector_core")
# endif ()

#########################################################
#                       Libraries                       #
#########################################################
include(cmake/modules/jsoncpp.cmake)

if (NOT (DEFINED SUBSTANCE_CONNECTOR_FRAMEWORK_LIBRARY_TARGET_NAME))
    set(SUBSTANCE_CONNECTOR_FRAMEWORK_LIBRARY_TARGET_NAME "substanceconnector_framework")
endif ()

 add_library(${SUBSTANCE_CONNECTOR_FRAMEWORK_LIBRARY_TARGET_NAME} STATIC ${CONNECTOR_FRAMEWORK_SOURCES} ${CONNECTOR_FRAMEWORK_HEADERS})

set_target_properties(${SUBSTANCE_CONNECTOR_FRAMEWORK_LIBRARY_TARGET_NAME} PROPERTIES OUTPUT_NAME "substanceconnector_framework")

target_include_directories(
    ${SUBSTANCE_CONNECTOR_FRAMEWORK_LIBRARY_TARGET_NAME} PUBLIC
    ${JSON_INCLUDE_PATH} PUBLIC

    "include"
)

if (NOT (DEFINED SUBSTANCE_CONNECTOR_LIBRARY_TARGET_NAME))
    set(SUBSTANCE_CONNECTOR_LIBRARY_TARGET_NAME "substance_connector")
endif ()

target_link_libraries(
    ${SUBSTANCE_CONNECTOR_FRAMEWORK_LIBRARY_TARGET_NAME}
    ${SUBSTANCE_CONNECTOR_LIBRARY_TARGET_NAME}
    jsoncpp::jsoncpp
)

target_compile_definitions(
    ${SUBSTANCE_CONNECTOR_FRAMEWORK_LIBRARY_TARGET_NAME} PRIVATE
    -DSUBSTANCE_CONNECTOR_FRAMEWORK_VERSION="${CONNECTOR_FRAMEWORK_BUILD_VERSION}"
)

if (CONNECTOR_ENABLE_BUILD_TESTS)
    add_subdirectory("tests")
endif ()
