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

#include "StubReaderAdapter.h"

/* Keyple Core Util */
#include "Arrays.h"
#include "ByteArrayUtil.h"
#include "InterruptedException.h"
#include "KeypleAssert.h"
#include "Thread.h"

/* Keyple Core Plugin */
#include "CardIOException.h"
#include "TaskCanceledException.h"

namespace keyple {
namespace plugin {
namespace stub {

using namespace keyple::core::plugin;
using namespace keyple::core::util;
using namespace keyple::core::util::cpp;
using namespace keyple::core::util::cpp::exception;

StubReaderAdapter::StubReaderAdapter(
  const std::string& name, const bool isContactLess, std::shared_ptr<StubSmartCard> card)
: mName(name),
  mIsContactLess(isContactLess),
  mSmartCard(card),
  mContinueWaitForCardRemovalTask(false) {}

void StubReaderAdapter::onStartDetection()
{
    mLogger->trace("Detection has been started on reader %\n", getName());
}

void StubReaderAdapter::onStopDetection()
{
    mLogger->trace("Detection has been stopped on reader %\n", getName());
}

const std::string& StubReaderAdapter::getName() const
{
    return mName;
}

bool StubReaderAdapter::isProtocolSupported(const std::string& readerProtocol) const
{
    (void)readerProtocol;

    /* Do not block any protocol */
    return true;
}

void StubReaderAdapter::activateProtocol(const std::string& readerProtocol)
{
    mActivatedProtocols.push_back(readerProtocol);
}

void StubReaderAdapter::deactivateProtocol(const std::string& readerProtocol)
{
    const auto it = std::find(mActivatedProtocols.begin(),
                              mActivatedProtocols.end(),
                              readerProtocol);
    if (it != mActivatedProtocols.end()) {
        mActivatedProtocols.erase(it);
    }
}

bool StubReaderAdapter::isCurrentProtocol(const std::string& readerProtocol) const
{
    if (mSmartCard != nullptr && mSmartCard->getCardProtocol() != "") {
        return mSmartCard->getCardProtocol() == readerProtocol;
    } else {
        return false;
    }
}

void StubReaderAdapter::openPhysicalChannel()
{
    if (mSmartCard != nullptr) {
        mSmartCard->openPhysicalChannel();
    }
}

void StubReaderAdapter::closePhysicalChannel()
{
    if (mSmartCard != nullptr) {
        mSmartCard->closePhysicalChannel();
    }
}

bool StubReaderAdapter::isPhysicalChannelOpen() const
{
    return mSmartCard != nullptr && mSmartCard->isPhysicalChannelOpen();
}

bool StubReaderAdapter::checkCardPresence()
{
    return mSmartCard != nullptr;
}

const std::string StubReaderAdapter::getPowerOnData() const
{
    return ByteArrayUtil::toHex(mSmartCard->getPowerOnData());
}

const std::vector<uint8_t> StubReaderAdapter::transmitApdu(const std::vector<uint8_t>& apduIn)
{
    if (mSmartCard == nullptr) {
        throw CardIOException("No card available.");
    }

    return mSmartCard->processApdu(apduIn);
}

bool StubReaderAdapter::isContactless()
{
    return mIsContactLess;
}

void StubReaderAdapter::onUnregister()
{
    /* NO-OP */
}

void StubReaderAdapter::insertCard(std::shared_ptr<StubSmartCard> smartCard)
{
    Assert::getInstance().notNull(smartCard, "smart card");

    if (checkCardPresence()) {
        mLogger->warn("You must remove the inserted card before inserted another one\n");
        return;
    }

    const std::string protocol = smartCard->getCardProtocol();
    if (!Arrays::contains(mActivatedProtocols, protocol)) {
        mLogger->trace("Inserted card protocol % does not match any activated protocol, please " \
                       "use activateProtocol() method\n",
                       protocol);

        return;
    }

    mLogger->trace("Inserted card %\n", smartCard);

    mSmartCard = smartCard;
}

void StubReaderAdapter::removeCard()
{
    if (mSmartCard != nullptr) {
        mLogger->trace("Remove card %\n", mSmartCard);
        closePhysicalChannel();
        mSmartCard = nullptr;
    }
}

std::shared_ptr<StubSmartCard> StubReaderAdapter::getSmartcard()
{
    return mSmartCard;
}

void StubReaderAdapter::waitForCardRemovalDuringProcessing()
{
    mContinueWaitForCardRemovalTask = true;

    while (mSmartCard != nullptr &&
           mContinueWaitForCardRemovalTask == true /* &&
           !Thread.currentThread().isInterrupted() */) {
        try {
            Thread::sleep(100);
        } catch (const InterruptedException& e) {
            (void)e;
            //Thread.currentThread().interrupt();
        }
    }

    if (!mContinueWaitForCardRemovalTask) {
        throw TaskCanceledException("Wait for card removal task cancelled");
    }
}

void StubReaderAdapter::stopWaitForCardRemovalDuringProcessing()
{
    mContinueWaitForCardRemovalTask = false;
}

}
}
}
