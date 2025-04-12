/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the MIT License which is available at                             *
 * https://opensource.org/licenses/MIT.                                       *
 *                                                                            *
 * SPDX-License-Identifier: MIT                                               *
 ******************************************************************************/

#include <memory>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "keyple/core/common/CommonApiProperties.hpp"
#include "keyple/core/plugin/PluginApiProperties.hpp"
#include "keyple/plugin/stub/StubPoolPluginAdapter.hpp"
#include "keyple/plugin/stub/StubPoolPluginFactoryAdapter.hpp"
#include "keyple/plugin/stub/StubPoolPluginFactoryBuilder.hpp"
#include "keyple/plugin/stub/StubReaderAdapter.hpp"
#include "keyple/plugin/stub/StubSmartCard.hpp"

using keyple::core::common::CommonApiProperties_VERSION;
using keyple::core::plugin::PluginApiProperties_VERSION;
using keyple::plugin::stub::StubPoolPluginAdapter;
using keyple::plugin::stub::StubPoolPluginFactoryAdapter;
using keyple::plugin::stub::StubPoolPluginFactoryBuilder;
using keyple::plugin::stub::StubReaderAdapter;
using keyple::plugin::stub::StubSmartCard;

static std::shared_ptr<StubPoolPluginFactoryAdapter> factory;
static std::shared_ptr<StubSmartCard> card;
static const std::string READER_NAME = "test";
static const std::string READER_NAME_2 = "test2";
static const int monitoringCycle = 100;
static const std::string GROUP = "group1";
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

TEST(StubPoolPluginFactoryAdapterTest, init_factory_with_reader_configuration)
{
    setUp();

    factory = std::dynamic_pointer_cast<StubPoolPluginFactoryAdapter>(
        StubPoolPluginFactoryBuilder::builder()
            ->withStubReader(GROUP, READER_NAME, card)
            .withStubReader(GROUP, READER_NAME_2, card)
            .withMonitoringCycleDuration(monitoringCycle)
            .build());

    ASSERT_EQ(factory->getPluginApiVersion(), PluginApiProperties_VERSION);
    ASSERT_EQ(factory->getCommonApiVersion(), CommonApiProperties_VERSION);

    auto stubPlugin = std::dynamic_pointer_cast<StubPoolPluginAdapter>(
        factory->getPoolPlugin());

    ASSERT_NE(stubPlugin, nullptr);
    ASSERT_EQ(stubPlugin->getName(), StubPoolPluginFactoryBuilder::PLUGIN_NAME);
    ASSERT_EQ(stubPlugin->getMonitoringCycleDuration(), monitoringCycle);
    ASSERT_EQ(stubPlugin->searchAvailableReaders().size(), 2);

    auto reader = std::dynamic_pointer_cast<StubReaderAdapter>(
        stubPlugin->searchReader(READER_NAME));

    ASSERT_NE(reader, nullptr);
    ASSERT_EQ(reader->getName(), READER_NAME);
    ASSERT_EQ(reader->getSmartcard(), card);
    ASSERT_FALSE(reader->isContactless());

    auto reader2 = std::dynamic_pointer_cast<StubReaderAdapter>(
        stubPlugin->searchReader(READER_NAME_2));

    ASSERT_NE(reader2, nullptr);
    ASSERT_EQ(reader2->getName(), READER_NAME_2);
    ASSERT_EQ(reader2->getSmartcard(), card);
    ASSERT_FALSE(reader2->isContactless());

    tearDown();
}
