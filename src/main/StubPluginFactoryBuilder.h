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

/* Keyple Plugin Stub */
#include "KeyplePluginStubExport.h"
#include "StubPluginFactoryAdapter.h"

namespace keyple {
namespace plugin {
namespace stub {

using StubReaderConfiguration = StubPluginFactoryAdapter::StubReaderConfiguration;

/**
 * Builds instances of {@link StubPluginFactory}.
 *
 * @since 2.0.0
 */
class KEYPLEPLUGINSTUB_API StubPluginFactoryBuilder final {
public:
    /**
     * The plugin default name
     *
     * @since 2.0.0
     */
    static const std::string PLUGIN_NAME;

    /**
     * Builder to build a {@link StubPluginFactory}.
     *
     * @since 2.0.0
     */
    class KEYPLEPLUGINSTUB_API Builder {
    public:
        /**
         *
         */
        friend class StubPluginFactoryBuilder;

        /**
         * Initialize the plugin with a stub reader. Multiple readers can be added. The reader can
         * contain a smart card. Readers name should be unique.
         *
         * @param name name for the initially inserted reader (not nullable and unique)
         * @param isContactLess true if the created reader should be contactless, false if not.
         * @param card (optional) inserted smart card
         * @return instance of the builder
         * @since 2.0.0
         */
        Builder& withStubReader(const std::string& name,
                                const bool isContactLess,
                                std::shared_ptr<StubSmartCard> card);

        /**
         * Configure the sleep time between two cycles for card and reader monitoring
         *
         * @param duration in milliseconds, default value : 0
         * @return instance of the builder
         * @since 2.0.0
         */
        Builder& withMonitoringCycleDuration(const int duration);

        /**
         * Returns an instance of StubPluginFactory created from the fields set on this builder.
         *
         * @return A {@link StubPluginFactory}
         * @since 2.0.0
         */
        std::shared_ptr<StubPluginFactory> build() const;

    private:
        /**
         *
         */
        std::vector<std::shared_ptr<StubReaderConfiguration>> mReaderConfigurations;

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
     * Creates builder to build a StubPluginFactory.
     *
     * @return created builder
     * @since 2.0.0
     */
    static std::unique_ptr<Builder> builder();

private:
    /**
     *
     */
    StubPluginFactoryBuilder() {}
};

}
}
}
