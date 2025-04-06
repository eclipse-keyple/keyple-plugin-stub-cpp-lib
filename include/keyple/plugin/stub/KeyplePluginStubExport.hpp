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

#if defined(WIN32)
#if defined(KEYPLEPLUGINSTUB_EXPORT)
#define KEYPLEPLUGINSTUB_API __declspec(dllexport)
#else
#define KEYPLEPLUGINSTUB_API __declspec(dllimport)
#endif
#else
#define KEYPLEPLUGINSTUB_API
#endif
