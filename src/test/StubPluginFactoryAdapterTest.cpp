/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

#include "gmock/gmock.h"
#include "gtest/gtest.h"

/* Keyple Plugin Stub */
#include "StubPluginAdapter.h"
#include "StubPluginFactoryAdapter.h"
#include "StubPluginFactoryBuilder.h"
#include "StubSmartCard.h"

/* Keyple Core Plugin */
#include "PluginApiProperties.h"

/* Keyple Core Common */
#include "CommonApiProperties.h"

using namespace testing;

using namespace keyple::core::common;
using namespace keyple::core::plugin;
using namespace keyple::plugin::stub;

using StubReaderConfiguration = StubPluginFactoryAdapter::StubReaderConfiguration;

static std::shared_ptr<StubPluginFactoryAdapter> factory;
static std::shared_ptr<StubSmartCard> card;
static const int monitoringCycle = 100;
static const std::string READER_NAME = "test";
static const std::vector<uint8_t> powerOnData(1);
static const std::string protocol = "protocol";
static const std::string commandHex = "1234567890ABCDEFFEDCBA0987654321";
static const std::string responseHex = "response";

static std::shared_ptr<StubSmartCard> buildACard()
{
    return StubSmartCard::builder()->withPowerOnData(powerOnData)
                                    .withProtocol(protocol)
                                    .withSimulatedCommand(commandHex, responseHex)
                                    .build();
}

static void setUp()
{
    card = buildACard();
}

static void tearDown()
{
    card.reset();
}

TEST(StubPluginFactoryAdapterTest, init_factory_with_reader_configuration)
{
    setUp();

    factory = std::dynamic_pointer_cast<StubPluginFactoryAdapter>(
                  StubPluginFactoryBuilder::builder()->withStubReader(READER_NAME, true, card)
                                                      .withMonitoringCycleDuration(monitoringCycle)
                                                      .build());

    ASSERT_EQ(factory->getPluginApiVersion(), PluginApiProperties_VERSION);
    ASSERT_EQ(factory->getCommonApiVersion(), CommonApiProperties_VERSION);

    auto stubPlugin = std::dynamic_pointer_cast<StubPluginAdapter>(factory->getPlugin());

    ASSERT_NE(stubPlugin, nullptr);
    ASSERT_EQ(stubPlugin->getName(), StubPluginFactoryBuilder::PLUGIN_NAME);
    ASSERT_EQ(stubPlugin->getMonitoringCycleDuration(), monitoringCycle);
    ASSERT_EQ(stubPlugin->searchAvailableReaders().size(), 1);

    auto reader = std::dynamic_pointer_cast<StubReaderAdapter>(
                      stubPlugin->searchReader(READER_NAME));

    ASSERT_NE(reader, nullptr);
    ASSERT_EQ(reader->getSmartcard(), card);
    ASSERT_TRUE(reader->isContactless());

    tearDown();
}