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

/* Keyple Plugin Stub */
#include "keyple/plugin/stub/KeyplePluginStubExport.hpp"
#include "keyple/plugin/stub/StubPoolPluginFactory.hpp"
#include "keyple/plugin/stub/StubPoolPluginFactoryAdapter.hpp"
#include "keyple/plugin/stub/StubSmartCard.hpp"

namespace keyple {
namespace plugin {
namespace stub {

using StubPoolReaderConfiguration
    = StubPoolPluginFactoryAdapter::StubPoolReaderConfiguration;

/**
 * Builds instances of StubPoolPluginFactory.
 *
 * @since 2.0.0
 */
class KEYPLEPLUGINSTUB_API StubPoolPluginFactoryBuilder final {
public:
    /**
     * Builder to build a StubPoolPluginFactory.
     *
     * @since 2.0.0
     */
    class KEYPLEPLUGINSTUB_API Builder {
    public:
        /**
         *
         */
        friend class StubPoolPluginFactoryBuilder;

        /**
         * Initialize the plugin with a stub reader. Multiple readers can be
         * added. The reader can contain a smart card. Readers name should be
         * unique.
         *
         * @param groupReference Reader group reference.
         * @param name name for the initially inserted reader (not nullable and
         * unique)
         * @param card (optional) inserted smart card
         * @return instance of the builder
         * @since 2.0.0
         */
        Builder& withStubReader(
            const std::string& groupReference,
            const std::string& name,
            std::shared_ptr<StubSmartCard> card);

        /**
         * Configure the sleep time between two cycles for card and reader
         * monitoring
         *
         * @param duration in milliseconds, default value : 0
         * @return instance of the builder
         * @since 2.0.0
         */
        Builder& withMonitoringCycleDuration(const int duration);

        /**
         * Returns an instance of StubPoolPluginFactory created from the fields
         * set on this builder.
         *
         * @return A {@link StubPoolPluginFactory}
         * @since 2.0.0
         */
        std::shared_ptr<StubPoolPluginFactory> build();

    private:
        /**
         *
         */
        std::vector<std::shared_ptr<StubPoolReaderConfiguration>>
            mReaderConfigurations;

        /**
         *
         */
        int mMonitoringCycleDuration;

        /**
         * (private) Constructs an empty Builder
         */
        Builder();
    };

    /**
     *
     */
    friend class Builder;

    /**
     * The plugin default name
     *
     * @since 2.0.0
     */
    static const std::string PLUGIN_NAME;

    /**
     * Creates builder to build a {@link StubPoolPluginFactory}.
     *
     * @return created builder
     * @since 2.0.0
     */
    static std::unique_ptr<Builder> builder();

private:
    /**
     *
     */
    StubPoolPluginFactoryBuilder();
};

} /* namespace stub */
} /* namespace plugin */
} /* namespace keyple */
