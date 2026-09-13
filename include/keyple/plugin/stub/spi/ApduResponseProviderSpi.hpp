/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the MIT License which is available at                             *
 * https://opensource.org/licenses/MIT.                                       *
 *                                                                            *
 * SPDX-License-Identifier: MIT                                               *
 ******************************************************************************/

#pragma once

#include <string>

namespace keyple {
namespace plugin {
namespace stub {
namespace spi {

/**
 * This interface must be used to provide an APDU response according to an APDU
 * request. It is used by StubSmartCard} to delegate it APDU response providing
 * to another class.
 *
 * @since 2.1.0
 */
class ApduResponseProviderSpi {
public:
    /**
     *
     */
    virtual ~ApduResponseProviderSpi() = default;

    /**
     * Provide APDU responses according to an APDU request.
     *
     * @param apduRequest hexadecimal string format (without spaces)
     * @return the APDU response in hexadecimal string format (without spaces)
     * @since 2.1.0
     */
    virtual const std::string
    getResponseFromRequest(const std::string& apduRequest)
        = 0;
};

} /* namespace spi */
} /* namespace stub */
} /* namespace plugin */
} /* namespace keyple */
