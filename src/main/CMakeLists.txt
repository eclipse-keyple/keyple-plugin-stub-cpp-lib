#/*************************************************************************************************
# * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                       *
# *                                                                                               *
# * See the NOTICE file(s) distributed with this work for additional information regarding        *
# * copyright ownership.                                                                          *
# *                                                                                               *
# * This program and the accompanying materials are made available under the terms of the Eclipse *
# * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                 *
# *                                                                                               *
# * SPDX-License-Identifier: EPL-2.0                                                              *
# *************************************************************************************************/

SET(LIBRARY_NAME keyplepluginstubcpplib)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DKEYPLEPLUGINSTUB_EXPORT")

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

    ${CMAKE_CURRENT_SOURCE_DIR}
    spi
)

# Careful, link order matters here as there are includes with the same name, and we cannot
# discriminate based on path
TARGET_LINK_LIBRARIES(

    ${LIBRARY_NAME}

    PUBLIC

    Keyple::Util
    Keyple::CommonApi
    Keyple::PluginApi
)

ADD_LIBRARY(Keyple::PluginStub ALIAS ${LIBRARY_NAME})
