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

#include <string>

/* Keyple Plugin  Stub */
#include "StubPluginFactoryAdapter.h"
#include "StubPoolPluginFactory.h"
#include "StubPoolPluginFactoryAdapter.h"
#include "StubSmartCard.h"

/* Keyple Core Plugin */
#include "PoolPluginFactorySpi.h"

namespace keyple {
namespace plugin {
namespace stub {

using namespace keyple::core::plugin::spi;

using StubReaderConfiguration = StubPluginFactoryAdapter::StubReaderConfiguration;
/**
 * (package-private)<br>
 * Factory of {@link StubPoolPlugin}.
 *
 * @since 2.0.0
 */
class StubPoolPluginFactoryAdapter final
: public StubPoolPluginFactory, public PoolPluginFactorySpi {
public:
    /**
     *
     */
    class StubPoolReaderConfiguration : public StubReaderConfiguration {
    public:
        /**
         * (package-private) constructor for a reader configuration
         *
         * @param groupReference groupReference of the reader (not nullable)
         * @param name name of the reader (not nullable)
         * @param card inserted card (nullable)
         * @since 2.0.0
         */
        StubPoolReaderConfiguration(const std::string& groupReference,
                                    const std::string& name,
                                    std::shared_ptr<StubSmartCard> card);

        /**
         *
         */
        const std::string& getGroupReference() const;

    private:
        /**
         *
         */
        const std::string mGroupReference;

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
    StubPoolPluginFactoryAdapter(
        const std::string& pluginName,
        const std::vector<std::shared_ptr<StubPoolReaderConfiguration>>& readerConfigurations,
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
    const std::string& getPoolPluginName() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    std::shared_ptr<PoolPluginSpi> getPoolPlugin() override;

private:
    /**
     *
     */
    const std::vector<std::shared_ptr<StubPoolReaderConfiguration>> mReaderConfigurations;

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
