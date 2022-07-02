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
#include <string>
#include <vector>

/* Keyple Core Plugin */
#include "ObservablePluginSpi.h"

/* Keyple Plugin Stub */
#include "KeyplePluginStubExport.h"
#include "StubPlugin.h"
#include "StubPluginFactoryAdapter.h"
#include "StubReaderAdapter.h"

namespace keyple {
namespace plugin {
namespace stub {

using StubReaderConfiguration = StubPluginFactoryAdapter::StubReaderConfiguration;

using namespace keyple::core::plugin::spi;

/**
 * (package-private)<br>
 * Internal adapter of the {@link StubPlugin}
 *
 * @since 2.0.0
 */
class KEYPLEPLUGINSTUB_API StubPluginAdapter : public StubPlugin, public ObservablePluginSpi {
public:
    /**
     * (package-private )constructor
     *
     * @param name name of the plugin
     * @param readerConfigurations configurations of the reader to plug initially
     * @param monitoringCycleDuration duration between two monitoring cycles
     * @since 2.0.0
     */
    StubPluginAdapter(
        const std::string& name,
        const std::vector<std::shared_ptr<StubReaderConfiguration>>& readerConfigurations,
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
     *
     * @since 2.0.0
     */
    std::shared_ptr<ReaderSpi> searchReader(const std::string& readerName) override;

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
    const std::vector<std::shared_ptr<ReaderSpi>> searchAvailableReaders() override;

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
    void plugReader(const std::string& name,
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

}
}
}
