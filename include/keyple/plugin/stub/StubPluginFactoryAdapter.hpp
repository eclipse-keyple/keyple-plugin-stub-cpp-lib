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

#include <memory>
#include <string>
#include <vector>

#include "keyple/core/plugin/spi/PluginFactorySpi.hpp"
#include "keyple/core/plugin/spi/PluginSpi.hpp"
#include "keyple/plugin/stub/KeyplePluginStubExport.hpp"
#include "keyple/plugin/stub/StubPluginFactory.hpp"
#include "keyple/plugin/stub/StubSmartCard.hpp"

namespace keyple {
namespace plugin {
namespace stub {

using keyple::core::plugin::spi::PluginFactorySpi;
using keyple::core::plugin::spi::PluginSpi;

/**
 * (package-private)<br>
 * Factory of {@link StubPlugin}.
 *
 * @since 2.0.0
 */
class KEYPLEPLUGINSTUB_API StubPluginFactoryAdapter final
: public StubPluginFactory,
  public PluginFactorySpi {
public:
    /**
     * (package-private)
     *
     * <p>Configuration for an initially plugged stubReader
     *
     * @since 2.0.0
     */
    class KEYPLEPLUGINSTUB_API StubReaderConfiguration {
    public:
        /**
         * (package-private) constructor for a reader configuration
         *
         * @param name name of the reader (not nullable)
         * @param isContactless true if the reader should be contactless (not
         * nullable)
         * @param card inserted card (nullable)
         * @since 2.0.0
         */
        StubReaderConfiguration(
            const std::string& name,
            const bool isContactless,
            std::shared_ptr<StubSmartCard> card);

        /**
         * (package-private)<br>
         * Get the name of the reader
         *
         * @return not nullable name
         * @since 2.0.0
         */
        const std::string& getName() const;

        /**
         * (package-private)<br>
         * Should the reader be contactless
         *
         * @return not nullable boolean
         * @since 2.0.0
         */
        bool getContactless() const;

        /**
         * (package-private)<br>
         * Card inserted in the reader
         *
         * @return nullable object
         * @since 2.0.0
         */
        std::shared_ptr<StubSmartCard> getCard() const;

    private:
        /**
         *
         */
        const std::string mName;

        /**
         *
         */
        const bool mIsContactless;

        /**
         *
         */
        std::shared_ptr<StubSmartCard> mCard;
    };

    /**
     * (package-private)<br>
     * Creates an instance, sets the fields from the factory builder.
     *
     * @param pluginName name of the plugin
     * @param readerConfigurations readerConfigurations to be created at init
     * @param monitoringCycleDuration duration of each monitoring cycle
     * @since 2.0.0
     */
    StubPluginFactoryAdapter(
        const std::string& pluginName,
        const std::vector<std::shared_ptr<StubReaderConfiguration>>&
            readerConfigurations,
        const int monitoringCycleDuration);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string getPluginApiVersion() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string getCommonApiVersion() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string& getPluginName() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    std::shared_ptr<PluginSpi> getPlugin() override;

private:
    /**
     *
     */
    std::vector<std::shared_ptr<StubReaderConfiguration>> mReaderConfigurations;

    /**
     *
     */
    const int mMonitoringCycleDuration;

    /**
     *
     */
    const std::string mPluginName;
};

} /* namespace stub */
} /* namespace plugin */
} /* namespace keyple */
