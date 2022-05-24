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

#if defined(WIN32)
#if defined(KEYPLEPLUGINSTUB_EXPORT)
#define KEYPLEPLUGINSTUB_API __declspec(dllexport)
#else
#define KEYPLEPLUGINSTUB_API __declspec(dllimport)
#endif
#else
#define KEYPLEPLUGINSTUB_API
#endif