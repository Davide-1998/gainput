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

#include "GainputHIDWhitelist.h"
#include <hidapi.h>

#include <algorithm>

#define CONCAT_VID_PID(vid, pid) (((uint32_t)vid << 16) + (uint32_t)pid)

struct WhitelistedItem
{
    uint32_t uid;
    uint8_t type;
};

static WhitelistedItem whitelistedControllerIDs[] =
{
    //// Playstation
    { CONCAT_VID_PID(vSony,      pidSonyDS4),                   ctPS4 },
    { CONCAT_VID_PID(vSony,      pidSonyDS4Slim),               ctPS4 },
    { CONCAT_VID_PID(vSony,      pidSonyDS5),                   ctPS5 },
    //// Stadia
    //{ CONCAT_VID_PID(vGoogle,    pidGoogleStadia),              ctStadia },
    //// Switch
    //{ CONCAT_VID_PID(vNintendo,  pidNintendoSwitchPro),         ctSwitchPro },
    //{ CONCAT_VID_PID(vNintendo,  pidNintendoSwitchJoyConLeft),  ctSwitchJoyConL },
    //{ CONCAT_VID_PID(vNintendo,  pidNintendoSwitchJoyConRight), ctSwitchJoyConR },
    //// Xbox
    //{ CONCAT_VID_PID(vMicrosoft, pidXbox360WiredController),    ctXbox360 },
    //{ CONCAT_VID_PID(vMicrosoft, pidXboxOne),                   ctXboxOne },
    //{ CONCAT_VID_PID(vMicrosoft, pidXboxOne2015),               ctXboxOne },
    //{ CONCAT_VID_PID(vMicrosoft, pidXboxOneS),                  ctXboxOne },
    //{ CONCAT_VID_PID(vMicrosoft, pidXboxOneXboxGIP),            ctXboxOne },
    //{ CONCAT_VID_PID(vMicrosoft, pidXboxSeriesX),               ctXboxOne },
    //{ CONCAT_VID_PID(vMicrosoft, pidXboxSeriesXBTLowEnergy),    ctXboxOne },
};
static const int32_t numWhitelisted = sizeof(whitelistedControllerIDs) / sizeof(*whitelistedControllerIDs);

char const* ControllerName(uint32_t type)
{
    static char const * controllerTypeStr[] =
    {
#define CONVERT(x) #x,
        CONTROLLER_TYPE_LIST
#undef CONVERT

        NULL
    };

    static uint32_t const len = (sizeof controllerTypeStr / sizeof * controllerTypeStr);

    if (type >=  len)
        type = len - 1;

    return controllerTypeStr[type];
}

bool HIDIsController(hid_device_info *dev)
{
    if (dev->vendor_id != vValve)
    {
        if (dev->usage_page > upDesktop)
            return false;

        switch (dev->usage)
        {
        case uUndef:
        case uJoystick:
        case uGamepad:
        case uMultiAxisController:
            break;

        default:
            // filter out all the devices we do not want
            return false;
        }
    }

    return true;
}

bool HIDIsSupported(hid_device_info * dev, uint8_t * outType)
{
    uint32_t id = CONCAT_VID_PID(dev->vendor_id, dev->product_id);
    WhitelistedItem * end = whitelistedControllerIDs + numWhitelisted;

    for (WhitelistedItem *it = whitelistedControllerIDs; it < end; ++it)
        if (it->uid == id)
        {
            if (outType)
                *outType = it->type;
            return true;
        }

    return false;
}

bool HIDIsSupported(uint16_t vendor, uint16_t product)
{
    uint32_t id = CONCAT_VID_PID(vendor, product);
    WhitelistedItem * end = whitelistedControllerIDs + numWhitelisted;

    for (WhitelistedItem *it = whitelistedControllerIDs; it < end; ++it)
        if (it->uid == id)
            return true;

    return false;
}
