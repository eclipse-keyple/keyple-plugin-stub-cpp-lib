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
#include "KeypleReaderExtension.h"

/* Keyple Plugin Stub */
#include "StubSmartCard.h"

namespace keyple {
namespace plugin {
namespace stub {

using namespace keyple::core::common;

/**
 * The Stub Reader supports programmatically the insertion and removal of {@link StubSmartCard} <br>
 * To invoke those methods use Reader#getExtension(StubReader.class) from the Reader class.
 *
 * @since 2.0.0
 */
class StubReader : public KeypleReaderExtension {
public:
    /**
     * Insert a stub card into the reader. The card is taken into account by the reader only if its
     * protocol has been activated previously by the method
     * keyple::core::plugin::spi::reader::ConfigurableReaderSpi::activateProtocol(). In
     * such case it raises a CARD_INSERTED event.
     *
     * @param smartCard stub card to be inserted in the reader (not nullable)
     * @since 2.0.0
     */
    virtual void insertCard(std::shared_ptr<StubSmartCard> smartCard) = 0;

    /**
     * Remove card from reader if any
     *
     * @since 2.0.0
     */
    virtual void removeCard() = 0;

    /**
     * Get inserted card
     *
     * @return instance of a {@link StubSmartCard}, can be null if no card inserted
     * @since 2.0.0
     */
    virtual std::shared_ptr<StubSmartCard> getSmartcard() = 0;
};

}
}
}
