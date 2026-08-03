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

#include "keyple/plugin/stub/StubPluginAdapter.hpp"
#include "keyple/plugin/stub/StubPluginFactoryAdapter.hpp"
#include "keyple/plugin/stub/StubSmartCard.hpp"

using keyple::plugin::stub::StubPluginAdapter;
using keyple::plugin::stub::StubPluginFactoryAdapter;
using keyple::plugin::stub::StubSmartCard;

using StubReaderConfiguration
    = StubPluginFactoryAdapter::StubReaderConfiguration;

static std::shared_ptr<StubPluginAdapter> pluginAdapter;
static std::shared_ptr<StubSmartCard> card;
static const std::string NAME = "name";
static std::vector<std::shared_ptr<StubReaderConfiguration>>
    readerConfigurations;
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
    pluginAdapter
        = std::make_shared<StubPluginAdapter>(NAME, readerConfigurations, 0);
    card = buildACard();
}

static void
tearDown()
{
    card.reset();
    pluginAdapter.reset();
}

TEST(StubPluginAdapterTest, initPlugin_withOneReader)
{
    setUp();

    readerConfigurations.push_back(
        std::make_shared<StubReaderConfiguration>(NAME, true, card));
    pluginAdapter
        = std::make_shared<StubPluginAdapter>(NAME, readerConfigurations, 0);

    ASSERT_EQ(pluginAdapter->searchAvailableReaders().size(), 1);
    ASSERT_EQ(pluginAdapter->searchAvailableReaderNames().size(), 1);
    ASSERT_NE(pluginAdapter->searchReader(NAME), nullptr);
    ASSERT_TRUE(pluginAdapter->searchReader(NAME)->isContactless());
    ASSERT_TRUE(pluginAdapter->searchReader(NAME)->checkCardPresence());

    tearDown();
}

TEST(StubPluginAdapterTest, plugReader_should_create_reader)
{
    setUp();

    pluginAdapter->plugReader(NAME, true, card);

    ASSERT_EQ(pluginAdapter->searchAvailableReaders().size(), 1);

    tearDown();
}

TEST(StubPluginAdapterTest, unplugReader_should_remove_reader)
{
    setUp();

    pluginAdapter->plugReader(NAME, true, card);

    ASSERT_EQ(pluginAdapter->searchAvailableReaders().size(), 1);

    pluginAdapter->unplugReader(NAME);

    ASSERT_EQ(pluginAdapter->searchAvailableReaders().size(), 0);

    tearDown();
}
