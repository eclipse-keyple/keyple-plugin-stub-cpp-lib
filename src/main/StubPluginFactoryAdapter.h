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

/* Keyple Core Plugin */
#include "PluginFactorySpi.h"

/* Keyple Plugin Stub */
#include "StubPluginFactory.h"
#include "StubSmartCard.h"

namespace keyple {
namespace plugin {
namespace stub {

using namespace keyple::core::plugin::spi;

/**
 * (package-private)<br>
 * Factory of {@link StubPlugin}.
 *
 * @since 2.0.0
 */
class StubPluginFactoryAdapter final : public StubPluginFactory, public PluginFactorySpi {
public:
    /**
     * (package-private)
     *
     * <p>Configuration for an initially plugged stubReader
     *
     * @since 2.0.0
     */
    class StubReaderConfiguration {
    public:
        /**
         * (package-private) constructor for a reader configuration
         *
         * @param name name of the reader (not nullable)
         * @param isContactless true if the reader should be contactless (not nullable)
         * @param card inserted card (nullable)
         * @since 2.0.0
         */
        StubReaderConfiguration(const std::string& name,
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
        const std::vector<std::shared_ptr<StubReaderConfiguration>> readerConfigurations,
        const int monitoringCycleDuration);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string& getPluginApiVersion() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string& getCommonApiVersion() const override;

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

}
}
}
