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
#include "KeyplePluginExtensionFactory.h"

namespace keyple {
namespace plugin {
namespace stub {

using namespace keyple::core::common;

/**
 * Stub specific KeyplePluginExtensionFactory to be provided to the Keyple SmartCard service
 * to register the Stub Pool plugin, built by StubPoolPluginFactoryBuilder.
 *
 * @since 2.0.0
 */
class StubPoolPluginFactory : public KeyplePluginExtensionFactory {};

}
}
}
