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

/* Keyple Core Common */
#include "KeyplePluginExtension.h"

namespace keyple {
namespace plugin {
namespace stub {

using namespace keyple::core::common;

/**
 * Simulates a keyple::core::plugin::spi::PoolPluginSpi with StubReader and StubSmartCard. Manages
 * allocation readers by group reference.
 */
class StubPoolPlugin : public KeyplePluginExtension {
public:
    /**
     * Plug synchronously a new StubReader in the StubPoolPlugin associated to groupReference and a
     * stub card. A READER_CONNECTED event will be raised.
     *
     * @param groupReference group reference of the new stub reader (mandatory)
     * @param readerName name of the new stub reader (mandatory). Each reader should have a unique
     *        name, no matter to what groupReference they are associated to
     * @param card insert a card at creation (can be null)
     */
    virtual void plugPoolReader(const std::string& groupReference,
                                const std::string& readerName,
                                std::shared_ptr<StubSmartCard> card) = 0;

    /**
     * Unplug synchronously all readers associated to a groupReference. A READER_DISCONNECTED event
     * will be raised.
     *
     * @param groupReference groupReference of the reader(s) to be unplugged (mandatory)
     * @since 2.0.0
     */
    virtual void unplugPoolReaders(const std::string& groupReference) = 0;

    /**
     * Unplug synchronously a pool reader. A READER_DISCONNECTED event will be raised.
     *
     * @param readerName name of the reader to be unplugged (mandatory)
     * @since 2.0.0
     */
    virtual void unplugPoolReader(const std::string& readerName) = 0;
};

}
}
}
