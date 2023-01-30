/*
 * Copyright (c) 2017-2022 The Forge Interactive Inc.
 *
 * This file is part of The-Forge
 * (see https://github.com/ConfettiFX/The-Forge).
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
*/

#ifndef GAINPUTHID_H_
#define GAINPUTHID_H_

#include "gainput/gainput.h"

//#define HID_VERBOSE_LOGGING

namespace gainput { class InputDeltaState; }

// Initialize the HID driver, controller parsers, and request the system
//   for prompts when devices are fully available (after driver installation,
//   not merely after being connected)
int HIDInit(void* window);
// Clean up everything initialized above
int HIDExit();

// Used to detect if there is system message indicating a device has been
//   installed or removed
bool HIDHandleSystemMessage(void const* message);
// Used to prompt the HID subsystem to fetch the input state for each HID
//   device and forward changes to Gainput
void HIDPromptForDeviceStateReports(gainput::InputDeltaState* state);


// --- Controller Management

#define INVALID_DEV_ID 0

// button_any devID should be retrieved through input events
//   For opening, though, they should be opened when a device connection
//   event is pushed and/or through polling

char const * HIDControllerName(uint8_t index);
bool HIDControllerConnected(uint8_t index);

// Returns 0 if none available, devID otherwise
//   Sets given pointers if not null
uint8_t HIDGetNextNewControllerID(uint8_t* outPlatform, uint16_t* outVendorID, uint16_t* outproductID);

// devID should come from the event sent out when the device is connected.
void HIDLoadController(uint8_t devID, uint8_t playerNum);
void HIDUnloadController(uint8_t devID);

void HIDSetPlayer(uint8_t devID, uint8_t playerNum);
void HIDSetLights(uint8_t devID, uint8_t r, uint8_t g, uint8_t b);
void HIDDoRumble(uint8_t devID, float left, float right, uint32_t durationMS);

void HIDSetDeviceChangeCallback(void (*deviceChange)(const char*, bool, int));
#endif
