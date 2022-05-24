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

#include "StubPluginFactoryAdapter.h"

/* Keyple Core Plugin */
#include "PluginApiProperties.h"

/* Keyple Core Common */
#include "CommonApiProperties.h"

/* Keyple Plugin Stub */
#include "StubPluginAdapter.h"

namespace keyple {
namespace plugin {
namespace stub {

using namespace keyple::core::common;
using namespace keyple::core::plugin;

/* STUB READER CONFIGURATION -------------------------------------------------------------------- */

StubPluginFactoryAdapter::StubReaderConfiguration::StubReaderConfiguration(
  const std::string& name, const bool isContactless,  std::shared_ptr<StubSmartCard> card)
: mName(name), mIsContactless(isContactless), mCard(card) {}

const std::string& StubPluginFactoryAdapter::StubReaderConfiguration::getName() const
{
    return mName;
}

bool StubPluginFactoryAdapter::StubReaderConfiguration::getContactless() const
{
    return mIsContactless;
}

std::shared_ptr<StubSmartCard> StubPluginFactoryAdapter::StubReaderConfiguration::getCard() const
{
    return mCard;
}

/* STUB PLUGIN FACTORY ADAPTER ------------------------------------------------------------------ */

StubPluginFactoryAdapter::StubPluginFactoryAdapter(
  const std::string& pluginName,
  const std::vector<std::shared_ptr<StubReaderConfiguration>> readerConfigurations,
  const int monitoringCycleDuration)
: mReaderConfigurations(readerConfigurations),
  mMonitoringCycleDuration(monitoringCycleDuration),
  mPluginName(pluginName) {}

const std::string& StubPluginFactoryAdapter::getPluginApiVersion() const
{
    return PluginApiProperties_VERSION;
}

const std::string& StubPluginFactoryAdapter::getCommonApiVersion() const
{
    return CommonApiProperties_VERSION;
}

const std::string& StubPluginFactoryAdapter::getPluginName() const
{
    return mPluginName;
}

std::shared_ptr<PluginSpi> StubPluginFactoryAdapter::getPlugin()
{
    return std::make_shared<StubPluginAdapter>(mPluginName,
                                               mReaderConfigurations,
                                               mMonitoringCycleDuration);
}

}
}
}
