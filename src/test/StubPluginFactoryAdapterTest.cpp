/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the MIT License which is available at                             *
 * https://opensource.org/licenses/MIT.                                       *
 *                                                                            *
 * SPDX-License-Identifier: MIT                                               *
 ******************************************************************************/

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "keyple/core/common/CommonApiProperties.hpp"
#include "keyple/core/plugin/PluginApiProperties.hpp"
#include "keyple/plugin/stub/StubPluginAdapter.hpp"
#include "keyple/plugin/stub/StubPluginFactoryAdapter.hpp"
#include "keyple/plugin/stub/StubPluginFactoryBuilder.hpp"
#include "keyple/plugin/stub/StubReaderAdapter.hpp"
#include "keyple/plugin/stub/StubSmartCard.hpp"

using keyple::core::common::CommonApiProperties_VERSION;
using keyple::core::plugin::PluginApiProperties_VERSION;
using keyple::plugin::stub::StubPluginAdapter;
using keyple::plugin::stub::StubPluginFactoryAdapter;
using keyple::plugin::stub::StubPluginFactoryBuilder;
using keyple::plugin::stub::StubReaderAdapter;
using keyple::plugin::stub::StubSmartCard;

using StubReaderConfiguration
    = StubPluginFactoryAdapter::StubReaderConfiguration;

static std::shared_ptr<StubPluginFactoryAdapter> factory;
static std::shared_ptr<StubSmartCard> card;
static const int monitoringCycle = 100;
static const std::string READER_NAME = "test";
static const std::vector<uint8_t> powerOnData(1);
static const std::string protocol = "protocol";
static const std::string commandHex = "1234567890ABCDEFFEDCBA0987654321";
static const std::string responseHex = "response";

static std::shared_ptr<StubSmartCard>
buildACard()
{
    return StubSmartCard::builder()
        ->withPowerOnData(powerOnData)
        .withProtocol(protocol)
        .withSimulatedCommand(commandHex, responseHex)
        .build();
}

static void
setUp()
{
    card = buildACard();
}

static void
tearDown()
{
    card.reset();
}

TEST(StubPluginFactoryAdapterTest, init_factory_with_reader_configuration)
{
    setUp();

    factory = std::dynamic_pointer_cast<StubPluginFactoryAdapter>(
        StubPluginFactoryBuilder::builder()
            ->withStubReader(READER_NAME, true, card)
            .withMonitoringCycleDuration(monitoringCycle)
            .build());

    ASSERT_EQ(factory->getPluginApiVersion(), PluginApiProperties_VERSION);
    ASSERT_EQ(factory->getCommonApiVersion(), CommonApiProperties_VERSION);

    auto stubPlugin
        = std::dynamic_pointer_cast<StubPluginAdapter>(factory->getPlugin());

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
