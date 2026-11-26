# *****************************************************************************
# Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/     *
#                                                                             *
# This program and the accompanying materials are made available under the    *
# terms of the MIT License which is available at                              *
# https://opensource.org/licenses/MIT.                                        *
#                                                                             *
# SPDX-License-Identifier: MIT                                                *
# *****************************************************************************/

SET(EXECTUABLE_NAME keyplepluginstubcpplib_ut)

INCLUDE_DIRECTORIES(

    ${CMAKE_CURRENT_SOURCE_DIR}
)

ADD_EXECUTABLE(

    ${EXECTUABLE_NAME}

    ${CMAKE_CURRENT_SOURCE_DIR}/StubPluginAdapterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubPluginFactoryAdapterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubPoolPluginAdapterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubPoolPluginFactoryAdapterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubReaderAdapterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StubSmartCardTest.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/MainTest.cpp
)

TARGET_INCLUDE_DIRECTORIES(

    ${EXECTUABLE_NAME}

    PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}
)

# GTest/GMock are supplied by Conan (test_requires) via CMakeDeps
FIND_PACKAGE(GTest REQUIRED CONFIG)

TARGET_LINK_LIBRARIES(

    ${EXECTUABLE_NAME}

    PUBLIC

    GTest::gtest
    GTest::gmock

    Keyple::Plugin::Stub
)
