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

#include <memory>
#include <string>

/* Keyple Core Common */
#include "KeyplePluginExtension.h"

/* Keyple Plugin Stub */
#include "StubSmartCard.h"

namespace keyple {
namespace plugin {
namespace stub {

using namespace keyple::core::common;

/**
 * Specific methods of the Stub Plugin. Implemented as a {@link KeyplePluginExtension}. To invoke
 * those methods use Plugin#getExtension(StubPlugin.class) from the Plugin class.
 *
 * @since 2.0.0
 */
class StubPlugin : public KeyplePluginExtension {
public:
    /**
     * Plug a new {@link StubReader}. This operation is asynchronous and will raise a
     * READER_CONNECTED event. A new {@link StubReader} is created and make available in the plugin
     *
     * @param name name for the reader (not nullable and unique)
     * @param isContactless true if the created reader should be contactless, false if not.
     * @param card created reader can contain a card (nullable)
     * @since 2.0.0
     */
    virtual void plugReader(const std::string& name,
                            const bool isContactless,
                            std::shared_ptr<StubSmartCard> card) = 0;

    /**
     * Unplug a {@link StubReader}. This operation is asynchronous and will raise a
     * READER_DISCONNECTED event. The reader is removed from the * available list of reader. It does
     * nothing if no reader matches the name.
     *
     * @param name the name of the reader to unplug (not nullable)
     * @since 2.0.0
     */
    virtual void unplugReader(const std::string& name) = 0;
};

}
}
}
