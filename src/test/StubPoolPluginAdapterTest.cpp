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

#include "keyple/core/plugin/PluginApiProperties.hpp"
#include "keyple/core/plugin/PluginIOException.hpp"
#include "keyple/core/plugin/spi/reader/ReaderSpi.hpp"
#include "keyple/core/util/cpp/Arrays.hpp"
#include "keyple/plugin/stub/StubPluginAdapter.hpp"
#include "keyple/plugin/stub/StubPluginFactoryAdapter.hpp"
#include "keyple/plugin/stub/StubPoolPluginAdapter.hpp"
#include "keyple/plugin/stub/StubPoolPluginFactoryAdapter.hpp"
#include "keyple/plugin/stub/StubSmartCard.hpp"

using keyple::core::plugin::PluginApiProperties_VERSION;
using keyple::core::plugin::PluginIOException;
using keyple::core::plugin::spi::reader::ReaderSpi;
using keyple::core::util::cpp::Arrays;
using keyple::plugin::stub::StubPluginAdapter;
using keyple::plugin::stub::StubPluginFactoryAdapter;
using keyple::plugin::stub::StubPoolPluginAdapter;
using keyple::plugin::stub::StubPoolPluginFactoryAdapter;
using keyple::plugin::stub::StubSmartCard;

using StubPoolReaderConfiguration
    = StubPoolPluginFactoryAdapter::StubPoolReaderConfiguration;

static std::shared_ptr<StubPoolPluginAdapter> pluginPoolAdapter;
static std::shared_ptr<StubSmartCard> card;
static std::vector<std::shared_ptr<StubPoolReaderConfiguration>>
    readerConfigurations;
static const std::string READER_NAME = "readerName";
static const std::string READER_NAME_2 = "readerName2";
static const std::string group1 = "group1";
static const std::string group2 = "group2";
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
    pluginPoolAdapter = std::make_shared<StubPoolPluginAdapter>(
        READER_NAME, readerConfigurations, 0);
    card = buildACard();
}

static void
tearDown()
{
    card.reset();
    pluginPoolAdapter.reset();
    readerConfigurations.clear();
}

static void
__initPlugin_withMultipleReader()
{
    readerConfigurations.push_back(
        std::make_shared<StubPoolReaderConfiguration>(
            group1, READER_NAME, card));
    readerConfigurations.push_back(
        std::make_shared<StubPoolReaderConfiguration>(
            group1, READER_NAME_2, card));

    pluginPoolAdapter = std::make_shared<StubPoolPluginAdapter>(
        READER_NAME, readerConfigurations, 0);

    ASSERT_EQ(pluginPoolAdapter->searchAvailableReaders().size(), 2);
    ASSERT_FALSE(pluginPoolAdapter->searchReader(READER_NAME)->isContactless());
}

TEST(StubPoolPluginAdapterTest, initPlugin_withMultipleReader)
{
    setUp();

    __initPlugin_withMultipleReader();

    tearDown();
}

static void
__plugReader_should_create_reader()
{
    pluginPoolAdapter->plugPoolReader(group1, READER_NAME, card);

    ASSERT_EQ(pluginPoolAdapter->searchAvailableReaders().size(), 1);
}

TEST(StubPoolPluginAdapterTest, plugReader_should_create_reader)
{
    setUp();

    __plugReader_should_create_reader();

    tearDown();
}

TEST(StubPoolPluginAdapterTest, allocate_reader_without_group)
{
    setUp();

    __initPlugin_withMultipleReader();

    std::shared_ptr<ReaderSpi> reader = pluginPoolAdapter->allocateReader("");
    const std::vector<std::string> names = {READER_NAME, READER_NAME_2};

    ASSERT_TRUE(Arrays::contains(names, reader->getName()));

    tearDown();
}

static void
__allocate_reader_with_group()
{
    __plugReader_should_create_reader();

    std::shared_ptr<ReaderSpi> reader
        = pluginPoolAdapter->allocateReader(group1);

    ASSERT_EQ(reader->getName(), READER_NAME);
}

TEST(StubPoolPluginAdapterTest, allocate_reader_with_group)
{
    setUp();

    __allocate_reader_with_group();

    tearDown();
}

TEST(StubPoolPluginAdapterTest, unplugReader_should_remove_reader)
{
    setUp();

    __plugReader_should_create_reader();

    pluginPoolAdapter->plugPoolReader(group2, READER_NAME_2, card);
    pluginPoolAdapter->unplugPoolReader(READER_NAME);

    ASSERT_EQ(pluginPoolAdapter->searchAvailableReaders().size(), 1);

    tearDown();
}

TEST(StubPoolPluginAdapterTest, unplugReaders_should_remove_readers)
{
    setUp();

    __plugReader_should_create_reader();

    pluginPoolAdapter->plugPoolReader(group1, READER_NAME_2, card);
    pluginPoolAdapter->unplugPoolReaders(group1);

    ASSERT_EQ(pluginPoolAdapter->searchAvailableReaders().size(), 0);

    tearDown();
}

TEST(
    StubPoolPluginAdapterTest, allocate_reader_on_group_when_no_reader_throw_ex)
{
    setUp();

    __allocate_reader_with_group();

    EXPECT_THROW(pluginPoolAdapter->allocateReader(group1), PluginIOException);

    tearDown();
}

TEST(StubPoolPluginAdapterTest, allocate_reader_when_no_reader_throw_ex)
{
    setUp();

    EXPECT_THROW(pluginPoolAdapter->allocateReader(""), PluginIOException);

    tearDown();
}
