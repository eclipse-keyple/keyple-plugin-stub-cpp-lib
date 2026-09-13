/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the MIT License which is available at                             *
 * https://opensource.org/licenses/MIT.                                       *
 *                                                                            *
 * SPDX-License-Identifier: MIT                                               *
 ******************************************************************************/

#include "keyple/plugin/stub/StubReaderAdapter.hpp"

#include "keyple/core/plugin/CardIOException.hpp"
#include "keyple/core/plugin/TaskCanceledException.hpp"
#include "keyple/core/util/HexUtil.hpp"
#include "keyple/core/util/KeypleAssert.hpp"
#include "keyple/core/util/cpp/Any.hpp"
#include "keyple/core/util/cpp/Arrays.hpp"
#include "keyple/core/util/cpp/Thread.hpp"
#include "keyple/core/util/cpp/exception/InterruptedException.hpp"

namespace keyple {
namespace plugin {
namespace stub {

using keyple::core::plugin::CardIOException;
using keyple::core::plugin::TaskCanceledException;
using keyple::core::util::Assert;
using keyple::core::util::HexUtil;
using keyple::core::util::cpp::any;
using keyple::core::util::cpp::Arrays;
using keyple::core::util::cpp::Thread;
using keyple::core::util::cpp::exception::InterruptedException;

StubReaderAdapter::StubReaderAdapter(
    const std::string& name,
    const bool isContactLess,
    std::shared_ptr<StubSmartCard> card)
: mName(name)
, mIsContactLess(isContactLess)
, mSmartCard(card)
, mContinueWaitForCardRemovalTask(false)
{
}

void
StubReaderAdapter::onStartDetection()
{
    // NOP
}

void
StubReaderAdapter::onStopDetection()
{
    // NOP
}

const std::string&
StubReaderAdapter::getName() const
{
    return mName;
}

bool
StubReaderAdapter::isProtocolSupported(const std::string& readerProtocol) const
{
    (void)readerProtocol;

    /* Do not block any protocol */
    return true;
}

void
StubReaderAdapter::activateProtocol(const std::string& readerProtocol)
{
    mActivatedProtocols.push_back(readerProtocol);
}

void
StubReaderAdapter::deactivateProtocol(const std::string& readerProtocol)
{
    const auto it = std::find(
        mActivatedProtocols.begin(), mActivatedProtocols.end(), readerProtocol);
    if (it != mActivatedProtocols.end()) {
        mActivatedProtocols.erase(it);
    }
}

bool
StubReaderAdapter::isCurrentProtocol(const std::string& readerProtocol) const
{
    if (mSmartCard != nullptr && mSmartCard->getCardProtocol() != "") {
        return mSmartCard->getCardProtocol() == readerProtocol;
    } else {
        return false;
    }
}

void
StubReaderAdapter::openPhysicalChannel()
{
    if (mSmartCard != nullptr) {
        mSmartCard->openPhysicalChannel();
    }
}

void
StubReaderAdapter::closePhysicalChannel()
{
    if (mSmartCard != nullptr) {
        mSmartCard->closePhysicalChannel();
    }
}

bool
StubReaderAdapter::isPhysicalChannelOpen() const
{
    return mSmartCard != nullptr && mSmartCard->isPhysicalChannelOpen();
}

bool
StubReaderAdapter::checkCardPresence()
{
    return mSmartCard != nullptr;
}

const std::string
StubReaderAdapter::getPowerOnData() const
{
    return HexUtil::toHex(mSmartCard->getPowerOnData());
}

const std::vector<uint8_t>
StubReaderAdapter::transmitApdu(const std::vector<uint8_t>& apduIn)
{
    if (mSmartCard == nullptr) {
        throw CardIOException("No card is available");
    }

    return mSmartCard->processApdu(apduIn);
}

bool
StubReaderAdapter::isContactless()
{
    return mIsContactLess;
}

void
StubReaderAdapter::onUnregister()
{
    /* NO-OP */
}

void
StubReaderAdapter::insertCard(std::shared_ptr<StubSmartCard> smartCard)
{
    Assert::getInstance().notNull(smartCard, "smart card");

    if (checkCardPresence()) {
        mLogger->warn(
            "[readerExt=%] A card is already inserted. First remove the " \
            "inserted card before inserting a new one\n",
            getName());
        return;
    }

    const std::string protocol = smartCard->getCardProtocol();
    if (!Arrays::contains(mActivatedProtocols, protocol)) {
        mLogger->trace(
            "[readerExt=%] Inserted card protocol does not match any " \
            "activated protocol. Please use 'activateProtocol()' method first" \
            "[cardProtocol=%]\n",
            getName(),
            protocol);

        return;
    }

    mLogger->trace(
        "[readerExt=%] Card inserted [smartCard=%]\n", getName(), smartCard);

    mSmartCard = smartCard;
}

void
StubReaderAdapter::removeCard()
{
    if (mSmartCard != nullptr) {
        mLogger->trace(
            "[readerExt=%] Card removed [smartCard=%]\n",
            getName(),
            mSmartCard);
        closePhysicalChannel();
        mSmartCard = nullptr;
    }
}

std::shared_ptr<StubSmartCard>
StubReaderAdapter::getSmartcard()
{
    return mSmartCard;
}

std::shared_ptr<any>
StubReaderAdapter::getSelectedSmartCard() const
{
    return nullptr;
}

int
StubReaderAdapter::getCardInsertionMonitoringSleepDuration() const
{
    return 0;
}

int
StubReaderAdapter::getCardRemovalMonitoringSleepDuration() const
{
    return 0;
}

} /* namespace stub */
} /* namespace plugin */
} /* namespace keyple */
