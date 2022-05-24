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

#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

/* Keyple Plugin Stub */
#include "KeyplePluginStubExport.h"

namespace keyple {
namespace plugin {
namespace stub {

/**
 * Simulated smart card that can be inserted into a {@link StubReader}. Use the {@link Builder} to
 * create this object
 *
 * @since 2.0.0
 */
class KEYPLEPLUGINSTUB_API StubSmartCard {
public:
    class CommandStep {
    public:
        /**
         * Add simulated command/response to the StubSmartCard to build. Command and
         * response should be hexadecimal.
         *
         * @param command hexadecimal command to respond to (can be a regexp to match multiple apdu)
         * @param response hexadecimal response
         * @return next step of builder
         * @since 2.0.0
         */
        virtual CommandStep& withSimulatedCommand(const std::string& command,
                                                  const std::string& response) = 0;

        /**
         * Build the StubSmartCard
         *
         * @return new instance a StubSmartCard
         */
        virtual std::shared_ptr<StubSmartCard> build() = 0;
    };

    class ProtocolStep {
    public:
        /**
         * Define simulated protocol for the StubSmartCard to build
         *
         * @param protocol (not nullable) protocol name
         * @return next step of builder
         * @since 2.0.0
         */
        virtual CommandStep& withProtocol(const std::string& protocol) = 0;
    };

    class PowerOnDataStep {
    public:
        /**
         * 
         */
        virtual ~PowerOnDataStep() = default;

        /**
         * Define simulated power-on data for the {@link StubSmartCard} to build
         *
         * @param powerOnData (not nullable) byte of array
         * @return next step of builder
         * @since 2.0.0
         */
        virtual ProtocolStep& withPowerOnData(const std::vector<uint8_t>& powerOnData) = 0;
    };

    /**
     * Builder class for StubSmartCard.
     *
     * @since 2.0.0
     */
    class Builder : public PowerOnDataStep, public ProtocolStep, public CommandStep {
    public:
        /**
         *
         */
        friend class StubSmartCard;

        /**
         * {@inheritDoc}
         *
         * @since 2.0.0
         */
        Builder& withSimulatedCommand(const std::string& command, const std::string& response)
            override;

        /**
         * {@inheritDoc}
         *
         * @since 2.0.0
         */
        std::shared_ptr<StubSmartCard> build() override;

        /**
         * {@inheritDoc}
         *
         * @since 2.0.0
         */
        ProtocolStep& withPowerOnData(const std::vector<uint8_t>& powerOnData) override;

        /**
         * {@inheritDoc}
         *
         * @since 2.0.0
         */
        Builder& withProtocol(const std::string& protocol) override;

    private:
        /**
         *
         */
        std::vector<uint8_t> mPowerOnData;

        /**
         *
         */
        std::string mCardProtocol;

        /**
         *
         */
        std::map<std::string, std::string> mHexCommands;

        /**
         *
         */
        Builder();
    };

    /**
     *
     */
    friend class Builder;

    /**
     * (package-private) <br>
     * Gets the card protocol supported by the card
     *
     * @return A not empty String.
     * @since 2.0.0
     */
    const std::string& getCardProtocol() const;

    /**
     * (package-private) <br>
     * Get the card power-on data
     *
     * @return Null if no power-on data are available.
     * @since 2.0.0
     */
    const std::vector<uint8_t>& getPowerOnData() const;

    /**
     * (package-private) <br>
     * Get the status of the physical channel
     *
     * @return True if the physical channel is open
     * @since 2.0.0
     */
    bool isPhysicalChannelOpen() const;

    /**
     * (package-private) <br>
     * Open the physical channel of the card
     *
     * @since 2.0.0
     */
    void openPhysicalChannel();

    /**
     * (package-private) <br>
     * Close the physical channel of the card
     *
     * @since 2.0.0
     */
    void closePhysicalChannel();

    /**
     * (package-private) <br>
     * Return APDU Response to APDU Request
     *
     * @param apduIn commands to be processed
     * @return APDU response
     * @since 2.0.0
     */
    const std::vector<uint8_t> processApdu(const std::vector<uint8_t>& apduIn);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<StubSmartCard> ssc);

    /**
     * Creates a builder for the {@link StubSmartCard}
     *
     * @return Next step of the builder
     * @since 2.0.0
     */
    static std::unique_ptr<PowerOnDataStep> builder();

private:
    /**
     *
     */
    const std::vector<uint8_t> mPowerOnData;

    /**
     *
     */
    const std::string mCardProtocol;

    /**
     *
     */
    bool mIsPhysicalChannelOpen;

    /**
     *
     */
    const std::map<std::string, std::string> mHexCommands;

    /**
     * (private) <br>
     * Create a simulated smart card with mandatory parameters
     *
     * @param powerOnData (non nullable) power-on data of the card
     * @param cardProtocol (non nullable) card protocol
     * @param hexCommands (non nullable) set of simulated commands
     * @since 2.0.0
     */
    StubSmartCard(const std::vector<uint8_t>& powerOnData,
                  const std::string& cardProtocol,
                  const std::map<std::string, std::string>& hexCommands);
};

}
}
}
