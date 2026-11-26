# *****************************************************************************
# Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/     *
#                                                                             *
# This program and the accompanying materials are made available under the    *
# terms of the MIT License which is available at                              *
# https://opensource.org/licenses/MIT.                                        *
#                                                                             *
# SPDX-License-Identifier: MIT                                                *
# *****************************************************************************/

SET(LIBRARY_NAME keyplepluginstubcpplib)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DKEYPLEPLUGINSTUB_EXPORT")

# Dependencies are supplied by Conan (requires) via CMakeDeps
FIND_PACKAGE(keyple-common-cpp-api REQUIRED CONFIG)
FIND_PACKAGE(keyple-plugin-cpp-api REQUIRED CONFIG)
FIND_PACKAGE(keyple-util-cpp-lib REQUIRED CONFIG)
FIND_PACKAGE(keypop-reader-cpp-api REQUIRED CONFIG)

ADD_LIBRARY(

    ${LIBRARY_NAME}

    ${LIBRARY_TYPE}

    ${CMAKE_CURRENT_SOURCE_DIR}/StubPluginAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubPluginFactoryAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubPluginFactoryBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubPoolPluginAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubPoolPluginFactoryAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubPoolPluginFactoryBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubReaderAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubSmartCard.cpp
)

TARGET_INCLUDE_DIRECTORIES(

    ${LIBRARY_NAME}

    PUBLIC

    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

TARGET_LINK_LIBRARIES(

    ${LIBRARY_NAME}

    PUBLIC

    Keyple::Util
    Keyple::Common
    Keyple::Plugin
    Keypop::Reader
)

ADD_LIBRARY(

    Keyple::Plugin::Stub

    ALIAS

    ${LIBRARY_NAME}
)

INSTALL(

    TARGETS ${LIBRARY_NAME}

    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

INSTALL(

    DIRECTORY ${PROJECT_SOURCE_DIR}/include/

    DESTINATION include
)
