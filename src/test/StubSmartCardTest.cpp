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
#include "StubSmartCard.h"

/* Keyple Core Util */
#include "HexUtil.h"

/* Keyple Core Plugin */
#include "CardIOException.h"

using namespace testing;

using namespace keyple::core::plugin;
using namespace keyple::core::util;
using namespace keyple::plugin::stub;

static std::shared_ptr<StubSmartCard> card;
static const std::vector<uint8_t> powerOnData(1);
static const std::string protocol = "protocol";
static const std::string commandHex = "1234567890ABCDEFFEDCBA0987654321";
static const std::string commandHexRegexp = "1234.*";
static const std::string responseHex = "response";

class ApduResponseProviderSpiImpl : public ApduResponseProviderSpi {
public:
    const std::string getResponseFromRequest(const std::string& apduRequest) override
    {
        return apduRequest == commandHex ? responseHex : "";
    }
};

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

TEST(StubSmartCardTest, sendApdu_adpuExists_sendResponse)
{
    setUp();

    const std::vector<uint8_t> apduResponse = card->processApdu(HexUtil::toByteArray(commandHex));

    ASSERT_EQ(apduResponse, HexUtil::toByteArray(responseHex));

    tearDown();
}

TEST(StubSmartCardTest, sendApdu_adpuRegexpExists_sendResponse)
{
    setUp();

    card = StubSmartCard::builder()->withPowerOnData(powerOnData)
                                    .withProtocol(protocol)
                                    .withSimulatedCommand(commandHexRegexp, responseHex)
                                    .build();
    const std::vector<uint8_t> apduResponse = card->processApdu(HexUtil::toByteArray(commandHex));

    ASSERT_EQ(apduResponse, HexUtil::toByteArray(responseHex));

    tearDown();
}

TEST(StubSmartCardTest, sendApdu_adpuNotExists_sendException)
{
    setUp();

    EXPECT_THROW(card->processApdu(HexUtil::toByteArray("excp")), CardIOException);

    tearDown();
}

TEST(StubSmartCardTest, shouldUse_a_apduResponseProvider_to_sendResponse)
{
    setUp();

    card = StubSmartCard::builder()->withPowerOnData(powerOnData)
                                    .withProtocol(protocol)
                                    .withApduResponseProvider(
                                        std::make_shared<ApduResponseProviderSpiImpl>())
                                    .build();
    const std::vector<uint8_t> apduResponse = card->processApdu(HexUtil::toByteArray(commandHex));

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
