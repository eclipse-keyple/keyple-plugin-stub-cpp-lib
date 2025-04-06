/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the MIT License which is available at                             *
 * https://opensource.org/licenses/MIT.                                       *
 *                                                                            *
 * SPDX-License-Identifier: MIT                                               *
 ******************************************************************************/

#include "keyple/plugin/stub/StubPluginAdapter.hpp"

namespace keyple {
namespace plugin {
namespace stub {

StubPluginAdapter::StubPluginAdapter(
    const std::string& name,
    const std::vector<std::shared_ptr<StubReaderConfiguration>>&
        readerConfigurations,
    const int monitoringCycleDuration)
: mName(name)
, mMonitoringCycleDuration(monitoringCycleDuration)
{
    for (const auto& configuration : readerConfigurations) {
        plugReader(
            configuration->getName(),
            configuration->getContactless(),
            configuration->getCard());
    }
}

int
StubPluginAdapter::getMonitoringCycleDuration() const
{
    return mMonitoringCycleDuration;
}

const std::vector<std::string>
StubPluginAdapter::searchAvailableReaderNames()
{
    std::vector<std::string> readers;
    for (const auto& reader : mStubReaders) {
        readers.push_back(reader.first);
    }

    return readers;
}

std::shared_ptr<ReaderSpi>
StubPluginAdapter::searchReader(const std::string& readerName)
{
    const auto it = mStubReaders.find(readerName);
    if (it != mStubReaders.end()) {
        return it->second;
    }

    return nullptr;
}

const std::string&
StubPluginAdapter::getName() const
{
    return mName;
}

const std::vector<std::shared_ptr<ReaderSpi>>
StubPluginAdapter::searchAvailableReaders()
{
    std::vector<std::shared_ptr<ReaderSpi>> readers;
    for (const auto& reader : mStubReaders) {
        readers.push_back(reader.second);
    }

    return readers;
}

void
StubPluginAdapter::onUnregister()
{
    /* NO-OP */
}

void
StubPluginAdapter::plugReader(
    const std::string& name,
    const bool isContactless,
    std::shared_ptr<StubSmartCard> card)
{
    mStubReaders.insert(
        {name, std::make_shared<StubReaderAdapter>(name, isContactless, card)});
}

void
StubPluginAdapter::unplugReader(const std::string& name)
{
    mStubReaders.erase(name);
}

} /* namespace stub */
} /* namespace plugin */
} /* namespace keyple */
