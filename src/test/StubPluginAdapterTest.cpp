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
#include "StubSmartCard.h"

using namespace testing;

using namespace keyple::plugin::stub;

using StubReaderConfiguration = StubPluginFactoryAdapter::StubReaderConfiguration;

static std::shared_ptr<StubPluginAdapter> pluginAdapter;
static std::shared_ptr<StubSmartCard> card;
static const std::string NAME = "name";
static std::vector<std::shared_ptr<StubReaderConfiguration>> readerConfigurations;
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
    pluginAdapter = std::make_shared<StubPluginAdapter>(NAME, readerConfigurations, 0);
    card = buildACard();
}

static void tearDown()
{
    card.reset();
    pluginAdapter.reset();
}

TEST(StubPluginAdapterTest, initPlugin_withOneReader)
{
    setUp();

    readerConfigurations.push_back(std::make_shared<StubReaderConfiguration>(NAME, true, card));
    pluginAdapter = std::make_shared<StubPluginAdapter>(NAME, readerConfigurations, 0);

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
