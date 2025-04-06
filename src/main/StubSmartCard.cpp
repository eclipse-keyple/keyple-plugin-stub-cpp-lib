/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the MIT License which is available at                             *
 * https://opensource.org/licenses/MIT.                                       *
 *                                                                            *
 * SPDX-License-Identifier: MIT                                               *
 ******************************************************************************/

#include "keyple/plugin/stub/StubSmartCard.hpp"

#include "keyple/core/plugin/CardIOException.hpp"
#include "keyple/core/util/HexUtil.hpp"
#include "keyple/core/util/cpp/KeypleStd.hpp"
#include "keyple/core/util/cpp/Pattern.hpp"

namespace keyple {
namespace plugin {
namespace stub {

using keyple::core::plugin::CardIOException;
using keyple::core::util::HexUtil;
using keyple::core::util::cpp::Pattern;

/* BUILDER ------------------------------------------------------------------ */

StubSmartCard::Builder::Builder()
{
}

StubSmartCard::SimulatedCommandStep&
StubSmartCard::Builder::withSimulatedCommand(
    const std::string& command, const std::string& response)
{
    /* Add commands without space */
    std::string cmd = command;
    std::string resp = response;

    mHexCommands.insert({std::trim(cmd), std::trim(resp)});

    return *this;
}

std::shared_ptr<StubSmartCard>
StubSmartCard::Builder::build()
{
    return std::shared_ptr<StubSmartCard>(new StubSmartCard(
        mPowerOnData, mCardProtocol, mHexCommands, mApduResponseProvider));
}

StubSmartCard::ProtocolStep&
StubSmartCard::Builder::withPowerOnData(const std::vector<uint8_t>& powerOnData)
{
    mPowerOnData = powerOnData;

    return *this;
}

StubSmartCard::CommandStep&
StubSmartCard::Builder::withProtocol(const std::string& protocol)
{
    mCardProtocol = protocol;

    return *this;
}

StubSmartCard::BuildStep&
StubSmartCard::Builder::withApduResponseProvider(
    const std::shared_ptr<ApduResponseProviderSpi> apduResponseProvider)
{
    mApduResponseProvider = apduResponseProvider;

    return *this;
}

/* STUB SMARTCARD ----------------------------------------------------------- */

const std::string&
StubSmartCard::getCardProtocol() const
{
    return mCardProtocol;
}

const std::vector<uint8_t>&
StubSmartCard::getPowerOnData() const
{
    return mPowerOnData;
}

bool
StubSmartCard::isPhysicalChannelOpen() const
{
    return mIsPhysicalChannelOpen;
}

void
StubSmartCard::openPhysicalChannel()
{
    mIsPhysicalChannelOpen = true;
}

void
StubSmartCard::closePhysicalChannel()
{
    mIsPhysicalChannelOpen = false;
}

const std::vector<uint8_t>
StubSmartCard::processApdu(const std::vector<uint8_t>& apduIn)
{
    if (apduIn.size() == 0) {
        return std::vector<uint8_t>();
    }

    /* Convert apduIn to hex */
    const std::string hexApdu = HexUtil::toHex(apduIn);

    if (mApduResponseProvider != nullptr) {
        const std::string responseFromRequest
            = mApduResponseProvider->getResponseFromRequest(hexApdu);
        if (responseFromRequest != "") {
            return HexUtil::toByteArray(responseFromRequest);
        }

    } else if (!mHexCommands.empty()) {
        /* Return matching hex response if the provided APDU matches the regex
         */
        for (const auto& hexCommand : mHexCommands) {
            std::shared_ptr<Pattern> p = Pattern::compile(hexCommand.first);
            if (p->matcher(hexApdu)->matches()) {
                return HexUtil::toByteArray(hexCommand.second);
            }
        }
    }

    /* Throw a CardIOException if not found */
    throw CardIOException("No response available for this request: " + hexApdu);
}

std::ostream&
operator<<(std::ostream& os, const std::shared_ptr<StubSmartCard> ssc)
{
    os << "STUB_SMART_CARD: {"
       << "POWER_ON_DATA = " << HexUtil::toHex(ssc->mPowerOnData) << ", "
       << "CARD_PROTOCOL = " << ssc->mCardProtocol << ", "
       << "IS_PHYSICAL_CHANNEL_OPEN = " << ssc->mIsPhysicalChannelOpen << ", "
       << "HEX_COMMANDS(#) = " << ssc->mHexCommands.size() << "}";

    return os;
}

std::unique_ptr<StubSmartCard::PowerOnDataStep>
StubSmartCard::builder()
{
    return std::unique_ptr<Builder>(new Builder());
}

StubSmartCard::StubSmartCard(
    const std::vector<uint8_t>& powerOnData,
    const std::string& cardProtocol,
    const std::map<std::string, std::string>& hexCommands,
    const std::shared_ptr<ApduResponseProviderSpi> apduResponseProvider)
: mPowerOnData(powerOnData)
, mCardProtocol(cardProtocol)
, mIsPhysicalChannelOpen(false)
, mHexCommands(hexCommands)
, mApduResponseProvider(apduResponseProvider)
{
}

} /* namespace stub */
} /* namespace plugin */
} /* namespace keyple */
