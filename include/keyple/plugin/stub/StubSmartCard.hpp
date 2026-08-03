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

#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "keyple/plugin/stub/KeyplePluginStubExport.hpp"
#include "keyple/plugin/stub/spi/ApduResponseProviderSpi.hpp"

namespace keyple {
namespace plugin {
namespace stub {

using keyple::plugin::stub::spi::ApduResponseProviderSpi;

/**
 * Simulated smart card that can be inserted into a {@link StubReader}. Use the
 * {@link Builder} to create this object
 *
 * @since 2.0.0
 */
class KEYPLEPLUGINSTUB_API StubSmartCard {
public:
    /**
     * Provides methods to add simulated commands and responses to a
     * StubSmartCard builder.
     *
     * @since 2.1.0
     */
    class SimulatedCommandStep {
    public:
        /**
         * Add simulated command/response to the StubSmartCard to build. Command and response
         * should be hexadecimal.
         *
         * @param command hexadecimal command to respond to (can be a regexp to
         * match multiple apdu)
         * @param response hexadecimal response
         * @return next step of builder
         * @since 2.1.0
         */
        virtual SimulatedCommandStep& withSimulatedCommand(
            const std::string& command, const std::string& response)
            = 0;

        /**
         * Build the StubSmartCard
         *
         * @return new instance a StubSmartCard
         */
        virtual std::shared_ptr<StubSmartCard> build() = 0;
    };

    /**
     * Build step for creating a {@link StubSmartCard} instance.
     *
     * @since 2.1.0
     */
    class BuildStep {
    public:
        /**
         * Build the StubSmartCard
         *
         * @return new instance a StubSmartCard
         * @since 2.1.0
         */
        virtual std::shared_ptr<StubSmartCard> build() = 0;
    };

    /**
     * CommandStep interface provides methods to build and configure a
     * StubSmartCard object.
     *
     * @since 2.0.0
     */
    class CommandStep {
    public:
        /**
         * Add simulated command/response to the StubSmartCard to build. Command and
         * response should be hexadecimal.
         *
         * @param command hexadecimal command to respond to (can be a regexp to
         * match multiple apdu)
         * @param response hexadecimal response
         * @return next step of builder
         * @since 2.0.0
         */
        virtual SimulatedCommandStep& withSimulatedCommand(
            const std::string& command, const std::string& response)
            = 0;

        /**
         * Provide simulated command/response to the StubSmartCard using a custom provider
         * implementing of ApduResponseProviderSpi.
         *
         * @param apduResponseProvider hexadecimal command to respond to (can be
         * a regexp to match multiple apdu)
         * @return next step of builder
         * @since 2.1.0
         */
        virtual BuildStep& withApduResponseProvider(
            const std::shared_ptr<ApduResponseProviderSpi> apduResponseProvider)
            = 0;

        /**
         * Build the StubSmartCard
         *
         * @return new instance a StubSmartCard
         */
        virtual std::shared_ptr<StubSmartCard> build() = 0;
    };

    /**
     * Provides a method to define the simulated protocol for the StubSmartCard
     * to build.
     *
     * @since 2.0.0
     */
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

    /**
     * Provides a method for defining simulated power-on data for the
     * StubSmartCard to build.
     *
     * @since 2.0.0
     */
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
        virtual ProtocolStep&
        withPowerOnData(const std::vector<uint8_t>& powerOnData)
            = 0;
    };

    /**
     * Builder class for StubSmartCard.
     *
     * @since 2.0.0
     */
    class Builder : public PowerOnDataStep,
                    public ProtocolStep,
                    public CommandStep,
                    public BuildStep,
                    public SimulatedCommandStep {
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
        SimulatedCommandStep& withSimulatedCommand(
            const std::string& command, const std::string& response) override;

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
        ProtocolStep&
        withPowerOnData(const std::vector<uint8_t>& powerOnData) override;

        /**
         * {@inheritDoc}
         *
         * @since 2.0.0
         */
        CommandStep& withProtocol(const std::string& protocol) override;

        /**
         * {@inheritDoc}
         *
         * @since 2.1.0
         */
        BuildStep& withApduResponseProvider(
            const std::shared_ptr<ApduResponseProviderSpi> apduResponseProvider)
            override;

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
        std::shared_ptr<ApduResponseProviderSpi> mApduResponseProvider;

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
    friend std::ostream&
    operator<<(std::ostream& os, const std::shared_ptr<StubSmartCard> ssc);

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
     *
     */
    const std::shared_ptr<ApduResponseProviderSpi> mApduResponseProvider;

    /**
     * (private) <br>
     * Create a simulated smart card with mandatory parameters The response APDU
     * can be provided
     * using <code>apduResponseProvider</code> if it is not null or <code>hexCommands</code> by
     * default.
     *
     * @param powerOnData (non nullable) power-on data of the card
     * @param cardProtocol (non nullable) card protocol
     * @param hexCommands (non nullable) set of simulated commands
     * @param apduResponseProvider (nullable) an external provider of simulated
     * commands
     * @since 2.0.0
     */
    StubSmartCard(
        const std::vector<uint8_t>& powerOnData,
        const std::string& cardProtocol,
        const std::map<std::string, std::string>& hexCommands,
        const std::shared_ptr<ApduResponseProviderSpi> apduResponseProvider);
};

} /* namespace stub */
} /* namespace plugin */
} /* namespace keyple */
