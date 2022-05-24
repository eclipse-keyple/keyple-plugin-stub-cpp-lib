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

#include "StubPoolPluginAdapter.h"

#include <algorithm>

/* Keyple Core Plugin */
#include "PluginIOException.h"

/* Keyple Core Util */
#include "IllegalArgumentException.h"
#include "KeypleAssert.h"

namespace keyple {
namespace plugin {
namespace stub {

using namespace keyple::core::plugin;
using namespace keyple::core::util;
using namespace keyple::core::util::cpp::exception;

StubPoolPluginAdapter::StubPoolPluginAdapter(
  const std::string& name,
  const std::vector<std::shared_ptr<StubPoolReaderConfiguration>>& readerConfigurations,
  const int monitoringCycleDuration)
{
    /*
     * C++: cannot directly use readerConfigurations to build mStubPluginAdapter, need to cast
     *      to a new sort of vector
     */
    std::vector<std::shared_ptr<StubReaderConfiguration>> configurations;
    for (const auto &config : readerConfigurations) {
        configurations.push_back(std::dynamic_pointer_cast<StubReaderConfiguration>(config));
    }

    mStubPluginAdapter = std::make_shared<StubPluginAdapter>(name,
                                                             configurations,
                                                             monitoringCycleDuration);

    for (const auto& readerConfiguration : readerConfigurations) {
        mReaderToGroup.insert({readerConfiguration->getName(),
                               readerConfiguration->getGroupReference()});
    }
}

const std::string& StubPoolPluginAdapter::getName() const
{
    return mStubPluginAdapter->getName();
}

const std::vector<std::shared_ptr<ReaderSpi>> StubPoolPluginAdapter::searchAvailableReaders()
{
    return mStubPluginAdapter->searchAvailableReaders();
}

const std::vector<std::string> StubPoolPluginAdapter::getReaderGroupReferences() const
{
    std::vector<std::string> references;
    for (const auto& ref : mReaderToGroup) {
        references.push_back(ref.second);
    }

    return references;
}

std::shared_ptr<ReaderSpi> StubPoolPluginAdapter::allocateReader(
    const std::string& readerGroupReference)
{
    std::vector<std::string> candidateReadersName;

    if (readerGroupReference == "") {
        /* Every reader is candidate for allocation */
        candidateReadersName = mStubPluginAdapter->searchAvailableReaderNames();
    } else {
        /* Only readers from the readerGroupReference are candidates for allocation */
        candidateReadersName = listReadersByGroup(readerGroupReference);
    }

    /* Find the first non allocated reader among candidates */
    for (const auto& readerName : candidateReadersName) {
        /* Find if already existing */
        const auto it = std::find(mAllocatedReaders.begin(), mAllocatedReaders.end(), readerName);
        if (it == mAllocatedReaders.end()) {
            mAllocatedReaders.push_back(readerName);
            return mStubPluginAdapter->searchReader(readerName);
        }
    }

    throw PluginIOException("No reader is available in the groupReference : " +
                            readerGroupReference);
}

void StubPoolPluginAdapter::releaseReader(std::shared_ptr<ReaderSpi> readerSpi)
{
    Assert::getInstance().notNull(readerSpi, "reader SPI");

    const auto stub = std::dynamic_pointer_cast<StubReader>(readerSpi);
    if (!stub) {
        throw IllegalArgumentException("Can not release reader, Reader should be of type " \
                                       "StubReader");
    }

    const auto it = std::find(mAllocatedReaders.begin(),
                              mAllocatedReaders.end(),
                              readerSpi->getName());
    mAllocatedReaders.erase(it);
}

void StubPoolPluginAdapter::onUnregister()
{
    /* NO-OP */
}

void StubPoolPluginAdapter::plugPoolReader(const std::string& groupReference,
                                           const std::string& readerName,
                                           std::shared_ptr<StubSmartCard> card)
{
    /* Create new reader */
    mStubPluginAdapter->plugReader(readerName, false, card);

    /* Map reader to groupReference */
    mReaderToGroup.insert({readerName, groupReference});
}

void StubPoolPluginAdapter::unplugPoolReaders(const std::string& groupReference)
{
    /* Find the reader in the readerPool */
    const std::vector<std::string> readerNames = listReadersByGroup(groupReference);
    for (const auto& readerName : readerNames) {
        unplugPoolReader(readerName);
    }
}

void StubPoolPluginAdapter::unplugPoolReader(const std::string& readerName)
{
    /* Remove reader from pool */
    mReaderToGroup.erase(mReaderToGroup.find(readerName));

    /* Remove reader from allocate list */
    const auto it = std::find(mAllocatedReaders.begin(), mAllocatedReaders.end(), readerName);
    if (it != mAllocatedReaders.end()) {
        mAllocatedReaders.erase(it);
    }

    /* Remove reader from plugin */
    mStubPluginAdapter->unplugReader(readerName);
}

int StubPoolPluginAdapter::getMonitoringCycleDuration() const
{
    return mStubPluginAdapter->getMonitoringCycleDuration();
}

const std::vector<std::string> StubPoolPluginAdapter::searchAvailableReaderNames()
{
    return mStubPluginAdapter->searchAvailableReaderNames();
}

std::shared_ptr<ReaderSpi> StubPoolPluginAdapter::searchReader(const std::string& readerName)
{
    return mStubPluginAdapter->searchReader(readerName);
}

const std::vector<std::string> StubPoolPluginAdapter::listReadersByGroup(
    const std::string& aGroupReference)
{
    std::vector<std::string> readers;

    /* Find the reader in the readerPool */
    for (const auto& entry : mReaderToGroup) {
        const std::string readerName = entry.first;
        const std::string groupReference = entry.second;
        if (groupReference == aGroupReference) {
            readers.push_back(readerName);
        }
    }

    return readers;
}

}
}
}
