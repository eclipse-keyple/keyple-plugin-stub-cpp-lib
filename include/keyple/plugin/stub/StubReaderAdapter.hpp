/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the MIT License which is available at                             *
 * https://opensource.org/licenses/MIT.                                       *
 *                                                                            *
 * SPDX-License-Identifier: MIT                                               *
 ******************************************************************************/

#pragma once

#include <atomic>
#include <memory>
#include <string>
#include <vector>

#include "keyple/core/plugin/spi/reader/ConfigurableReaderSpi.hpp"
#include "keyple/core/plugin/spi/reader/PoolReaderSpi.hpp"
#include "keyple/core/plugin/spi/reader/observable/ObservableReaderSpi.hpp"
#include "keyple/core/plugin/spi/reader/observable/state/insertion/CardInsertionWaiterNonBlockingSpi.hpp"
#include "keyple/core/plugin/spi/reader/observable/state/removal/CardRemovalWaiterNonBlockingSpi.hpp"
#include "keyple/core/util/cpp/Any.hpp"
#include "keyple/core/util/cpp/LoggerFactory.hpp"
#include "keyple/plugin/stub/KeyplePluginStubExport.hpp"
#include "keyple/plugin/stub/StubReader.hpp"
#include "keyple/plugin/stub/StubSmartCard.hpp"

namespace keyple {
namespace plugin {
namespace stub {

using keyple::core::plugin::spi::reader::ConfigurableReaderSpi;
using keyple::core::plugin::spi::reader::PoolReaderSpi;
using keyple::core::plugin::spi::reader::observable::ObservableReaderSpi;
using keyple::core::plugin::spi::reader::observable::state::insertion::
    CardInsertionWaiterNonBlockingSpi;
using keyple::core::plugin::spi::reader::observable::state::removal::
    CardRemovalWaiterNonBlockingSpi;
using keyple::core::util::cpp::any;
using keyple::core::util::cpp::Logger;
using keyple::core::util::cpp::LoggerFactory;

/**
 * (package-private)<br>
 * The adapter for the StubReader is also an ObservableReaderSpi
 *
 * @since 2.0.0
 */
class KEYPLEPLUGINSTUB_API StubReaderAdapter final
: public StubReader,
  public ConfigurableReaderSpi,
  public PoolReaderSpi,
  public ObservableReaderSpi,
  public CardInsertionWaiterNonBlockingSpi,
  public CardRemovalWaiterNonBlockingSpi {
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
    StubReaderAdapter(
        const std::string& name,
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
    const std::vector<uint8_t>
    transmitApdu(const std::vector<uint8_t>& apduIn) override;

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
    std::shared_ptr<StubSmartCard> getSmartcard() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.2.0
     */
    std::shared_ptr<any> getSelectedSmartCard() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.2.0
     */
    int getCardInsertionMonitoringSleepDuration() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.2.0
     */
    int getCardRemovalMonitoringSleepDuration() const override;

private:
    /**
     *
     */
    const std::unique_ptr<Logger> mLogger
        = LoggerFactory::getLogger(typeid(StubReaderAdapter));

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

} /* namespace stub */
} /* namespace plugin */
} /* namespace keyple */
