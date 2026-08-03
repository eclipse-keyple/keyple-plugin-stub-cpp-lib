/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the MIT License which is available at                             *
 * https://opensource.org/licenses/MIT.                                       *
 *                                                                            *
 * SPDX-License-Identifier: MIT                                               *
 ******************************************************************************/

#include "keyple/plugin/stub/StubPluginFactoryAdapter.hpp"

#include "keyple/core/common/CommonApiProperties.hpp"
#include "keyple/core/plugin/PluginApiProperties.hpp"
#include "keyple/plugin/stub/StubPluginAdapter.hpp"

namespace keyple {
namespace plugin {
namespace stub {

using keyple::core::common::CommonApiProperties_VERSION;
using keyple::core::plugin::PluginApiProperties_VERSION;

/* STUB READER CONFIGURATION
 * -------------------------------------------------------------------- */

StubPluginFactoryAdapter::StubReaderConfiguration::StubReaderConfiguration(
    const std::string& name,
    const bool isContactless,
    std::shared_ptr<StubSmartCard> card)
: mName(name)
, mIsContactless(isContactless)
, mCard(card)
{
}

const std::string&
StubPluginFactoryAdapter::StubReaderConfiguration::getName() const
{
    return mName;
}

bool
StubPluginFactoryAdapter::StubReaderConfiguration::getContactless() const
{
    return mIsContactless;
}

std::shared_ptr<StubSmartCard>
StubPluginFactoryAdapter::StubReaderConfiguration::getCard() const
{
    return mCard;
}

/* STUB PLUGIN FACTORY ADAPTER
 * ------------------------------------------------------------------ */

StubPluginFactoryAdapter::StubPluginFactoryAdapter(
    const std::string& pluginName,
    const std::vector<std::shared_ptr<StubReaderConfiguration>>&
        readerConfigurations,
    const int monitoringCycleDuration)
: mReaderConfigurations(readerConfigurations)
, mMonitoringCycleDuration(monitoringCycleDuration)
, mPluginName(pluginName)
{
}

const std::string
StubPluginFactoryAdapter::getPluginApiVersion() const
{
    return PluginApiProperties_VERSION;
}

const std::string
StubPluginFactoryAdapter::getCommonApiVersion() const
{
    return CommonApiProperties_VERSION;
}

const std::string&
StubPluginFactoryAdapter::getPluginName() const
{
    return mPluginName;
}

std::shared_ptr<PluginSpi>
StubPluginFactoryAdapter::getPlugin()
{
    return std::make_shared<StubPluginAdapter>(
        mPluginName, mReaderConfigurations, mMonitoringCycleDuration);
}

} /* namespace stub */
} /* namespace plugin */
} /* namespace keyple */
