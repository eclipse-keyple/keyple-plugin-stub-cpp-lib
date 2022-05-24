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

#pragma once

#include <atomic>
#include <memory>
#include <string>
#include <vector>

/* Keyple Core Util */
#include "LoggerFactory.h"

/* Keyple Core Plugin */
#include "ConfigurableReaderSpi.h"
#include "ObservableReaderSpi.h"
#include "WaitForCardInsertionNonBlockingSpi.h"
#include "WaitForCardRemovalDuringProcessingBlockingSpi.h"
#include "WaitForCardRemovalNonBlockingSpi.h"

/* Keyple Plugin Stub */
#include "KeyplePluginStubExport.h"
#include "StubReader.h"
#include "StubSmartCard.h"

namespace keyple {
namespace plugin {
namespace stub {

using namespace keyple::core::plugin::spi::reader;
using namespace keyple::core::plugin::spi::reader::observable;
using namespace keyple::core::plugin::spi::reader::observable::state::insertion;
using namespace keyple::core::plugin::spi::reader::observable::state::processing;
using namespace keyple::core::plugin::spi::reader::observable::state::removal;
using namespace keyple::core::util::cpp;

/**
 * (package-private)<br>
 * The adapter for the StubReader is also an ObservableReaderSpi
 *
 * @since 2.0.0
 */
class KEYPLEPLUGINSTUB_API StubReaderAdapter final
: public StubReader,
  public ConfigurableReaderSpi,
  public ObservableReaderSpi,
  public WaitForCardInsertionNonBlockingSpi,
  public WaitForCardRemovalDuringProcessingBlockingSpi,
  public WaitForCardRemovalNonBlockingSpi {
public:
    /**
     * (package-private)<br>
     * constructor
     *
     * @param name name of the reader
     * @param isContactLess true if contactless
     * @param card (optional) inserted smart card at creation
     * @since 2.0.0
     */
    StubReaderAdapter(const std::string& name,
                      const bool isContactLess,
                      std::shared_ptr<StubSmartCard> card);

    /*
    * ObservableReaderSpi
    */

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void onStartDetection() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void onStopDetection() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string& getName() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    bool isProtocolSupported(const std::string& readerProtocol) const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void activateProtocol(const std::string& readerProtocol) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void deactivateProtocol(const std::string& readerProtocol) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    bool isCurrentProtocol(const std::string& readerProtocol) const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void openPhysicalChannel() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void closePhysicalChannel() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    bool isPhysicalChannelOpen() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    bool checkCardPresence() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string getPowerOnData() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::vector<uint8_t> transmitApdu(const std::vector<uint8_t>& apduIn) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    bool isContactless() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void onUnregister() override;

    /*
    * StubReader
    */

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void insertCard(std::shared_ptr<StubSmartCard> smartCard) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void removeCard() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    std::shared_ptr<StubSmartCard> getSmartcard() override ;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void waitForCardRemovalDuringProcessing() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void stopWaitForCardRemovalDuringProcessing() override;

private:
    /**
     *
     */
    const std::unique_ptr<Logger> mLogger = LoggerFactory::getLogger(typeid(StubReaderAdapter));

    /**
     *
     */
    const std::string mName;

    /**
     *
     */
    const bool mIsContactLess;

    /**
     *
     */
    std::vector<std::string> mActivatedProtocols;

    /**
     *
     */
    std::shared_ptr<StubSmartCard> mSmartCard;

    /**
     *
     */
    std::atomic<bool> mContinueWaitForCardRemovalTask;
};

}
}
}
