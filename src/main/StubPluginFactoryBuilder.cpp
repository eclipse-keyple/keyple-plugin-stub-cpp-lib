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

#include "StubPluginFactoryBuilder.h"

namespace keyple {
namespace plugin {
namespace stub {

using Builder = StubPluginFactoryBuilder::Builder;

const std::string StubPluginFactoryBuilder::PLUGIN_NAME = "StubPlugin";

/* BUILDER -------------------------------------------------------------------------------------- */

Builder::Builder() : mMonitoringCycleDuration(0) {}

Builder& Builder::withStubReader(const std::string& name,
                                 const bool isContactLess,
                                 std::shared_ptr<StubSmartCard> card)
{
    mReaderConfigurations.push_back(
        std::make_shared<StubReaderConfiguration>(name, isContactLess, card));

    return *this;
}

Builder& Builder::withMonitoringCycleDuration(const int duration)
{
    mMonitoringCycleDuration = duration;

    return *this;
}

std::shared_ptr<StubPluginFactory> Builder::build() const
{
    return std::make_shared<StubPluginFactoryAdapter>(PLUGIN_NAME,
                                                      mReaderConfigurations,
                                                      mMonitoringCycleDuration);
}

/* STUB PLUGIN FACTORY BUILDER ------------------------------------------------------------------ */

std::unique_ptr<Builder> StubPluginFactoryBuilder::builder()
{
    return std::unique_ptr<Builder>(new Builder());
}

}
}
}
