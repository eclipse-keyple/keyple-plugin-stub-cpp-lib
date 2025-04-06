/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the MIT License which is available at                             *
 * https://opensource.org/licenses/MIT.                                       *
 *                                                                            *
 * SPDX-License-Identifier: MIT                                               *
 ******************************************************************************/

#include "keyple/plugin/stub/StubPoolPluginFactoryAdapter.hpp"

#include "keyple/core/common/CommonApiProperties.hpp"
#include "keyple/core/plugin/PluginApiProperties.hpp"
#include "keyple/plugin/stub/StubPoolPluginAdapter.hpp"

namespace keyple {
namespace plugin {
namespace stub {

using keyple::core::common::CommonApiProperties_VERSION;
using keyple::core::plugin::PluginApiProperties_VERSION;

using StubPoolReaderConfiguration
    = StubPoolPluginFactoryAdapter::StubPoolReaderConfiguration;

/* STUB POOL READER CONFIGURATION
 * --------------------------------------------------------------- */

StubPoolReaderConfiguration::StubPoolReaderConfiguration(
    const std::string& groupReference,
    const std::string& name,
    std::shared_ptr<StubSmartCard> card)
: StubReaderConfiguration(name, false, card)
, mGroupReference(groupReference)
{
}

const std::string&
StubPoolReaderConfiguration::getGroupReference() const
{
    return mGroupReference;
}

/* STUB POOL PLUGIN FACTORY ADAPTER
 * ------------------------------------------------------------- */

StubPoolPluginFactoryAdapter::StubPoolPluginFactoryAdapter(
    const std::string& pluginName,
    const std::vector<std::shared_ptr<StubPoolReaderConfiguration>>&
        readerConfigurations,
    const int monitoringCycleDuration)
: mReaderConfigurations(readerConfigurations)
, mMonitoringCycleDuration(monitoringCycleDuration)
, mPluginName(pluginName)
{
}

const std::string
StubPoolPluginFactoryAdapter::getPluginApiVersion() const
{
    return PluginApiProperties_VERSION;
}

const std::string
StubPoolPluginFactoryAdapter::getCommonApiVersion() const
{
    return CommonApiProperties_VERSION;
}

const std::string&
StubPoolPluginFactoryAdapter::getPoolPluginName() const
{
    return mPluginName;
}

std::shared_ptr<PoolPluginSpi>
StubPoolPluginFactoryAdapter::getPoolPlugin()
{
    return std::make_shared<StubPoolPluginAdapter>(
        mPluginName, mReaderConfigurations, mMonitoringCycleDuration);
}

} /* namespace stub */
} /* namespace plugin */
} /* namespace keyple */
