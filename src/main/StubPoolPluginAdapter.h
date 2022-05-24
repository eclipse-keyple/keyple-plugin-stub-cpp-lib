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

/* Keyple Plugin Stub */
#include "StubPluginAdapter.h"
#include "StubPoolPlugin.h"
#include "StubPoolPluginFactoryAdapter.h"
#include "StubSmartCard.h"

/* Keyple Core Plugin */
#include "ObservablePluginSpi.h"
#include "PoolPluginSpi.h"

namespace keyple {
namespace plugin {
namespace stub {

using namespace keyple::core::plugin::spi;

using StubPoolReaderConfiguration = StubPoolPluginFactoryAdapter::StubPoolReaderConfiguration;

/**
 * (package-private)<br>
 * Internal adapter of the {@link StubPoolPlugin}
 *
 * @since 2.0.0
 */
class StubPoolPluginAdapter
: public StubPoolPlugin, public PoolPluginSpi, public ObservablePluginSpi {
public:
    /**
     * (package-private )constructor
     *
     * @param name name of the plugin
     * @param readerConfigurations configurations of the reader to plug initially
     * @param monitoringCycleDuration duration between two monitoring cycle
     * @since 2.0.0
     */
    StubPoolPluginAdapter(
        const std::string& name,
        const std::vector<std::shared_ptr<StubPoolReaderConfiguration>>& readerConfigurations,
        const int monitoringCycleDuration);

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
    const std::vector<std::string> getReaderGroupReferences() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    std::shared_ptr<ReaderSpi> allocateReader(const std::string& readerGroupReference) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void releaseReader(std::shared_ptr<ReaderSpi> readerSpi) override;

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
    void plugPoolReader(const std::string& groupReference,
                        const std::string& readerName,
                        std::shared_ptr<StubSmartCard> card) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void unplugPoolReaders(const std::string& groupReference) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    void unplugPoolReader(const std::string& readerName) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    int getMonitoringCycleDuration() const  override;

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

private:
    /**
     *
     */
    std::shared_ptr<StubPluginAdapter> mStubPluginAdapter;

    /**
     *
     */
    std::map<std::string, std::string> mReaderToGroup;

    /**
     * List of allocated readers by their readerName
     */
    std::vector<std::string> mAllocatedReaders;

    /**
     * (private) lists all readers that match a group reference
     *
     * @param aGroupReference not nullable reference to a group reference
     * @return collection of reader names
     */
    const std::vector<std::string> listReadersByGroup(const std::string& aGroupReference);
};

}
}
}
