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
#include "keyple/plugin/stub/StubSmartCard.hpp"
#include "keyple/plugin/stub/spi/ApduResponseProviderSpi.hpp"

using keyple::core::plugin::CardIOException;
using keyple::core::util::HexUtil;
using keyple::plugin::stub::StubSmartCard;
using keyple::plugin::stub::spi::ApduResponseProviderSpi;

static std::shared_ptr<StubSmartCard> card;
static const std::vector<uint8_t> powerOnData(1);
static const std::string protocol = "protocol";
static const std::string commandHex = "1234567890ABCDEFFEDCBA0987654321";
static const std::string commandHexRegexp = "1234.*";
static const std::string responseHex = "response";

class ApduResponseProviderSpiMock : public ApduResponseProviderSpi {
public:
    const std::string
    getResponseFromRequest(const std::string& apduRequest) override
    {
        return (apduRequest == commandHex) ? responseHex : "";
    }
};

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

TEST(StubSmartCardTest, sendApdu_apduExists_sendResponse)
{
    setUp();

    const std::vector<uint8_t> apduResponse
        = card->processApdu(HexUtil::toByteArray(commandHex));

    ASSERT_EQ(apduResponse, HexUtil::toByteArray(responseHex));

    tearDown();
}

TEST(StubSmartCardTest, sendApdu_adpuRegexpExists_sendResponse)
{
    setUp();

    card = StubSmartCard::builder()
               ->withPowerOnData(powerOnData)
               .withProtocol(protocol)
               .withSimulatedCommand(commandHexRegexp, responseHex)
               .build();
    const std::vector<uint8_t> apduResponse
        = card->processApdu(HexUtil::toByteArray(commandHex));

    ASSERT_EQ(apduResponse, HexUtil::toByteArray(responseHex));

    tearDown();
}

TEST(StubSmartCardTest, sendApdu_adpuNotExists_sendException)
{
    setUp();

    EXPECT_THROW(
        card->processApdu(HexUtil::toByteArray("excp")), CardIOException);

    tearDown();
}

TEST(StubSmartCardTest, shouldUse_a_apduResponseProvider_to_sendResponse)
{
    setUp();

    const auto response
        = std::dynamic_pointer_cast<ApduResponseProviderSpiMock>(
            std::make_shared<ApduResponseProviderSpiMock>());
    card = StubSmartCard::builder()
               ->withPowerOnData(powerOnData)
               .withProtocol(protocol)
               .withApduResponseProvider(response)
               .build();
    const std::vector<uint8_t> apduResponse
        = card->processApdu(HexUtil::toByteArray(commandHex));

    ASSERT_EQ(apduResponse, HexUtil::toByteArray(responseHex));

    tearDown();
}

TEST(StubSmartCardTest, open_close_physical_channel)
{
    setUp();

    ASSERT_FALSE(card->isPhysicalChannelOpen());

    card->openPhysicalChannel();

    ASSERT_TRUE(card->isPhysicalChannelOpen());

    card->closePhysicalChannel();

    ASSERT_FALSE(card->isPhysicalChannelOpen());

    tearDown();
}
