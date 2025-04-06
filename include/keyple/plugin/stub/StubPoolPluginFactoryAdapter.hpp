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

#include "keyple/core/plugin/spi/PoolPluginFactorySpi.hpp"
#include "keyple/core/plugin/spi/PoolPluginSpi.hpp"
#include "keyple/plugin/stub/KeyplePluginStubExport.hpp"
#include "keyple/plugin/stub/StubPluginFactoryAdapter.hpp"
#include "keyple/plugin/stub/StubPoolPluginFactory.hpp"
#include "keyple/plugin/stub/StubPoolPluginFactoryAdapter.hpp"
#include "keyple/plugin/stub/StubSmartCard.hpp"

namespace keyple {
namespace plugin {
namespace stub {

using keyple::core::plugin::spi::PoolPluginFactorySpi;
using keyple::core::plugin::spi::PoolPluginSpi;

using StubReaderConfiguration
    = StubPluginFactoryAdapter::StubReaderConfiguration;
/**
 * (package-private)<br>
 * Factory of {@link StubPoolPlugin}.
 *
 * @since 2.0.0
 */
class KEYPLEPLUGINSTUB_API StubPoolPluginFactoryAdapter final
: public StubPoolPluginFactory,
  public PoolPluginFactorySpi {
public:
    /**
     *
     */
    class KEYPLEPLUGINSTUB_API StubPoolReaderConfiguration
    : public StubReaderConfiguration {
    public:
        /**
         * (package-private) constructor for a reader configuration
         *
         * @param groupReference groupReference of the reader (not nullable)
         * @param name name of the reader (not nullable)
         * @param card inserted card (nullable)
         * @since 2.0.0
         */
        StubPoolReaderConfiguration(
            const std::string& groupReference,
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
        const std::vector<std::shared_ptr<StubPoolReaderConfiguration>>&
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
    const std::vector<std::shared_ptr<StubPoolReaderConfiguration>>
        mReaderConfigurations;

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
