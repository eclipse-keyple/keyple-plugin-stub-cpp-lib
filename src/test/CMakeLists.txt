# *************************************************************************************************
# Copyright (c) 2021 Calypso Networks Association                                                 *
# https://www.calypsonet-asso.org/                                                                *
#                                                                                                 *
# See the NOTICE file(s) distributed with this work for additional information regarding          *
# copyright ownership.                                                                            *
#                                                                                                 *
# This program and the accompanying materials are made available under the terms of the Eclipse   *
# Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                   *
#                                                                                                 *
# SPDX-License-Identifier: EPL-2.0                                                                *
# *************************************************************************************************/

SET(EXECTUABLE_NAME keyplepluginstubcpplib_ut)

SET(KEYPLE_UTIL_DIR        "../../../keyple-util-cpp-lib")
SET(KEYPLE_PLUGIN_DIR      "../../../keyple-plugin-cpp-api")
SET(KEYPLE_COMMON_DIR      "../../../keyple-common-cpp-api")

SET(KEYPLE_UTIL_LIB        "keypleutilcpplib")
SET(KEYPLE_STUB_LIB        "keyplepluginstubcpplib")

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../main
    ${CMAKE_CURRENT_SOURCE_DIR}/../main/spi

    ${KEYPLE_UTIL_DIR}/src/main
    ${KEYPLE_UTIL_DIR}/src/main/cpp
    ${KEYPLE_UTIL_DIR}/src/main/cpp/exception

    ${KEYPLE_PLUGIN_DIR}/src/main
    ${KEYPLE_PLUGIN_DIR}/src/main/spi
    ${KEYPLE_PLUGIN_DIR}/src/main/spi/reader
    ${KEYPLE_PLUGIN_DIR}/src/main/spi/reader/observable
    ${KEYPLE_PLUGIN_DIR}/src/main/spi/reader/observable/state
    ${KEYPLE_PLUGIN_DIR}/src/main/spi/reader/observable/state/insertion
    ${KEYPLE_PLUGIN_DIR}/src/main/spi/reader/observable/state/processing
    ${KEYPLE_PLUGIN_DIR}/src/main/spi/reader/observable/state/removal

    ${KEYPLE_COMMON_DIR}/src/main
)

ADD_EXECUTABLE(
    ${EXECTUABLE_NAME}

    ${CMAKE_CURRENT_SOURCE_DIR}/MainTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubPluginAdapterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubPluginFactoryAdapterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubPoolPluginAdapterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubPoolPluginFactoryAdapterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubReaderAdapterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubSmartCardTest.cpp
)

# Add Google Test
SET(GOOGLETEST_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
INCLUDE(CMakeLists.txt.googletest)

TARGET_LINK_LIBRARIES(${EXECTUABLE_NAME} gtest gmock ${KEYPLE_STUB_LIB})
