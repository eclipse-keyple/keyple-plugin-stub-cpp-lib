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

/* Keyple Core Common */
#include "keyple/core/common/KeyplePluginExtensionFactory.hpp"

namespace keyple {
namespace plugin {
namespace stub {

using keyple::core::common::KeyplePluginExtensionFactory;

/**
 * Stub specific {@link KeyplePluginExtensionFactory} to be provided to the
 * Keyple SmartCard service to register the Stub plugin, built by {@link
 * StubPluginFactoryBuilder}.
 *
 * @since 2.0.0
 */
class StubPluginFactory : public KeyplePluginExtensionFactory {
public:
    /**
     * Virtual destructor.
     */
    virtual ~StubPluginFactory() = default;
};

} /* namespace stub */
} /* namespace plugin */
} /* namespace keyple */
