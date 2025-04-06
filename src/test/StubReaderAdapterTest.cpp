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

#include "keyple/core/plugin/CardIOException.hpp"
#include "keyple/core/util/HexUtil.hpp"
#include "keyple/core/util/cpp/exception/IllegalArgumentException.hpp"
#include "keyple/plugin/stub/StubReaderAdapter.hpp"
#include "keyple/plugin/stub/StubSmartCard.hpp"

using keyple::core::plugin::CardIOException;
using keyple::core::util::HexUtil;
using keyple::core::util::cpp::exception::IllegalArgumentException;
using keyple::plugin::stub::StubReaderAdapter;
using keyple::plugin::stub::StubSmartCard;

static std::shared_ptr<StubReaderAdapter> adapter;
static std::shared_ptr<StubSmartCard> card;
static const std::string NAME = "name";
static const std::string PROTOCOL = "any";
static bool IS_CONTACT_LESS = true;
static const std::string commandHex = "1234567890ABCDEFFEDCBA0987654321";
static const std::string responseHex = "response";

static std::shared_ptr<StubSmartCard>
buildCard(const std::string& protocol)
{
    return StubSmartCard::builder()
        ->withPowerOnData(HexUtil::toByteArray("0000"))
        .withProtocol(protocol)
        .withSimulatedCommand(commandHex, responseHex)
        .build();
}

static void
setUp()
{
    card = buildCard(PROTOCOL);
    adapter
        = std::make_shared<StubReaderAdapter>(NAME, IS_CONTACT_LESS, nullptr);
}

static void
tearDown()
{
    adapter.reset();
    card.reset();
}

TEST(StubReaderAdapterTest, test_constructor)
{
    setUp();

    ASSERT_EQ(adapter->getName(), NAME);
    ASSERT_EQ(adapter->isContactless(), IS_CONTACT_LESS);
    ASSERT_TRUE(adapter->isProtocolSupported("any"));

    tearDown();
}

TEST(StubReaderAdapterTest, insertCard_withNull_shouldThrow_Ex)
{
    setUp();

    EXPECT_THROW(adapter->insertCard(nullptr), IllegalArgumentException);

    tearDown();
}

TEST(StubReaderAdapterTest, insert_card_with_activated_protocol)
{
    setUp();

    adapter->activateProtocol(PROTOCOL);
    adapter->insertCard(card);

    ASSERT_EQ(adapter->getSmartcard(), card);
    ASSERT_EQ(
        adapter->getPowerOnData(), HexUtil::toHex(card->getPowerOnData()));
    ASSERT_EQ(adapter->isPhysicalChannelOpen(), card->isPhysicalChannelOpen());
    ASSERT_TRUE(adapter->checkCardPresence());
    ASSERT_TRUE(adapter->isCurrentProtocol(PROTOCOL));
    ASSERT_EQ(
        adapter->transmitApdu(HexUtil::toByteArray(commandHex)),
        HexUtil::toByteArray(responseHex));

    tearDown();
}

TEST(StubReaderAdapterTest, insert_card_without_activated_protocol_return_null)
{
    setUp();

    adapter->activateProtocol(PROTOCOL);
    adapter->deactivateProtocol(PROTOCOL);
    adapter->insertCard(card);

    ASSERT_EQ(adapter->getSmartcard(), nullptr);

    tearDown();
}

TEST(StubReaderAdapterTest, remove_inserted_card)
{
    setUp();

    adapter->activateProtocol(PROTOCOL);
    adapter->insertCard(card);

    ASSERT_EQ(adapter->getSmartcard(), card);

    adapter->removeCard();

    ASSERT_EQ(adapter->getSmartcard(), nullptr);

    tearDown();
}

TEST(StubReaderAdapterTest, insert_card_with_inserted_card_does_nothing)
{
    setUp();

    std::shared_ptr<StubSmartCard> card2 = buildCard(PROTOCOL);
    adapter->activateProtocol(PROTOCOL);
    adapter->insertCard(card);
    adapter->insertCard(card2);

    ASSERT_EQ(adapter->getSmartcard(), card);

    tearDown();
}

TEST(StubReaderAdapterTest, test_open_close_channel)
{
    setUp();

    adapter->activateProtocol(PROTOCOL);
    adapter->insertCard(card);

    ASSERT_FALSE(adapter->isPhysicalChannelOpen());

    adapter->openPhysicalChannel();

    ASSERT_TRUE(adapter->isPhysicalChannelOpen());

    adapter->closePhysicalChannel();

    ASSERT_FALSE(adapter->isPhysicalChannelOpen());

    tearDown();
}

TEST(StubReaderAdapterTest, op_without_card)
{
    setUp();

    ASSERT_FALSE(adapter->isCurrentProtocol("any"));

    EXPECT_THROW(
        adapter->transmitApdu(HexUtil::toByteArray(commandHex)),
        CardIOException);

    tearDown();
}
