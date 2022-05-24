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

#include "StubPoolPluginFactoryAdapter.h"

/* Keyple Core Plugin */
#include "PluginApiProperties.h"

/* Keyple Core Common */
#include "CommonApiProperties.h"

/* Keyple Plugin Stub */
#include "StubPoolPluginAdapter.h"

namespace keyple {
namespace plugin {
namespace stub {

using namespace keyple::core::common;
using namespace keyple::core::plugin;

using StubPoolReaderConfiguration = StubPoolPluginFactoryAdapter::StubPoolReaderConfiguration;

/* STUB POOL READER CONFIGURATION --------------------------------------------------------------- */

StubPoolReaderConfiguration::StubPoolReaderConfiguration(
  const std::string& groupReference,
  const std::string& name,
  std::shared_ptr<StubSmartCard> card)
: StubReaderConfiguration(name, false, card), mGroupReference(groupReference) {}

const std::string& StubPoolReaderConfiguration::getGroupReference() const
{
    return mGroupReference;
}

/* STUB POOL PLUGIN FACTORY ADAPTER ------------------------------------------------------------- */

StubPoolPluginFactoryAdapter::StubPoolPluginFactoryAdapter(
  const std::string& pluginName,
  const std::vector<std::shared_ptr<StubPoolReaderConfiguration>>& readerConfigurations,
  const int monitoringCycleDuration)
: mReaderConfigurations(readerConfigurations),
  mMonitoringCycleDuration(monitoringCycleDuration),
  mPluginName(pluginName) {}

const std::string& StubPoolPluginFactoryAdapter::getPluginApiVersion() const
{
    return PluginApiProperties_VERSION;
}

const std::string& StubPoolPluginFactoryAdapter::getCommonApiVersion() const
{
    return CommonApiProperties_VERSION;
}

const std::string& StubPoolPluginFactoryAdapter::getPoolPluginName() const
{
    return mPluginName;
}

std::shared_ptr<PoolPluginSpi> StubPoolPluginFactoryAdapter::getPoolPlugin()
{
    return std::make_shared<StubPoolPluginAdapter>(mPluginName,
                                                   mReaderConfigurations,
                                                   mMonitoringCycleDuration);
}

}
}
}
