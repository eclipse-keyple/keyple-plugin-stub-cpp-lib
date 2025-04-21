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
#include <string>
#include <vector>

#include "keyple/core/plugin/spi/ObservablePluginSpi.hpp"
#include "keyple/core/plugin/spi/reader/ReaderSpi.hpp"
#include "keyple/plugin/stub/KeyplePluginStubExport.hpp"
#include "keyple/plugin/stub/StubPlugin.hpp"
#include "keyple/plugin/stub/StubPluginFactoryAdapter.hpp"
#include "keyple/plugin/stub/StubReaderAdapter.hpp"

namespace keyple {
namespace plugin {
namespace stub {

using StubReaderConfiguration
    = StubPluginFactoryAdapter::StubReaderConfiguration;

using keyple::core::plugin::spi::ObservablePluginSpi;
using keyple::core::plugin::spi::reader::ReaderSpi;

/**
 * (package-private)<br>
 * Internal adapter of the {@link StubPlugin}
 *
 * @since 2.0.0
 */
class KEYPLEPLUGINSTUB_API StubPluginAdapter : public StubPlugin,
                                               public ObservablePluginSpi {
public:
    /**
     * (package-private )constructor
     *
     * @param name name of the plugin
     * @param readerConfigurations configurations of the reader to plug
     * initially
     * @param monitoringCycleDuration duration between two monitoring cycles
     * @since 2.0.0
     */
    StubPluginAdapter(
        const std::string& name,
        const std::vector<std::shared_ptr<StubReaderConfiguration>>&
            readerConfigurations,
        const int monitoringCycleDuration);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    int getMonitoringCycleDuration() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::vector<std::string> searchAvailableReaderNames() override;

    /**
     * {@inheritDoc}
     *@
     * @since 2.0.0
     */
    std::shared_ptr<ReaderSpi>
    searchReader(const std::string& readerName) override;

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
    const std::vector<std::shared_ptr<ReaderSpi>>
    searchAvailableReaders() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void onUnregister() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void plugReader(
        const std::string& name,
        const bool isContactless,
        std::shared_ptr<StubSmartCard> card) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void unplugReader(const std::string& name) override;

private:
    /**
     *
     */
    const std::string mName;

    /**
     *
     */
    const int mMonitoringCycleDuration;

    /**
     *
     */
    std::map<std::string, std::shared_ptr<StubReaderAdapter>> mStubReaders;
};

} /* namespace stub */
} /* namespace plugin */
} /* namespace keyple */
