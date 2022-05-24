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

#include "StubPoolPluginFactoryBuilder.h"

/* Keyple Plugin Stub */
#include "StubPoolPluginFactoryAdapter.h"

namespace keyple {
namespace plugin {
namespace stub {

using Builder = StubPoolPluginFactoryBuilder::Builder;
using StubPoolReaderConfiguration = StubPoolPluginFactoryAdapter::StubPoolReaderConfiguration;

/* BUILDER -------------------------------------------------------------------------------------- */

Builder::Builder() : mMonitoringCycleDuration(0) {}

Builder& Builder::withStubReader(const std::string& groupReference,
                                 const std::string& name,
                                 std::shared_ptr<StubSmartCard> card)
{
    mReaderConfigurations.push_back(
        std::make_shared<StubPoolReaderConfiguration>(groupReference, name, card));

    return *this;
}

Builder& Builder::withMonitoringCycleDuration(const int duration)
{
    mMonitoringCycleDuration = duration;

    return *this;
}

std::shared_ptr<StubPoolPluginFactory> Builder::build()
{
    return std::shared_ptr<StubPoolPluginFactoryAdapter>(
              new StubPoolPluginFactoryAdapter(PLUGIN_NAME,
                                               mReaderConfigurations,
                                               mMonitoringCycleDuration));
}

/* STUB POOL PLUGIN FACTORY BUILDER ------------------------------------------------------------- */

const std::string StubPoolPluginFactoryBuilder::PLUGIN_NAME = "StubPoolPlugin";

StubPoolPluginFactoryBuilder::StubPoolPluginFactoryBuilder() {}

std::unique_ptr<Builder> StubPoolPluginFactoryBuilder::builder()
{
    return std::unique_ptr<Builder>(new Builder());
}

}
}
}
