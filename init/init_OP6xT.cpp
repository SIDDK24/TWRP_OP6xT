/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdlib>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

#include <android-base/properties.h>
#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using std::string;

void property_override(string prop, string value)
{
    auto pi = (prop_info*) __system_property_find(prop.c_str());

    if (pi != nullptr)
        __system_property_update(pi, value.c_str(), value.size());
    else
        __system_property_add(prop.c_str(), prop.size(), value.c_str(), value.size());
}

void model_property_override(const std::string& name, const std::string& device, const std::string& model)
{
    property_override("ro.product.name", name);
    property_override("ro.product.odm.name", name);
    property_override("ro.product.system.name", name);
    property_override("ro.product.vendor.name", name);
    property_override("ro.product.system_ext.name", name);
    property_override("ro.product.device", device);
    property_override("ro.product.odm.device", device);
    property_override("ro.product.system.device", device);
    property_override("ro.product.vendor.device", device);
    property_override("ro.product.system_ext.device", device);
    property_override("ro.product.model", model);
    property_override("ro.product.odm.model", model);
    property_override("ro.product.system.model", model);
    property_override("ro.product.vendor.model", model);
    property_override("ro.product.system_ext.model", model);
}

void vendor_load_properties()
{
    const std::string project_codename = GetProperty("ro.boot.project_codename", "");

    if (project_codename == "enchilada") {
        property_override("ro.boot.product.vendor.sku", "km3");
        model_property_override("OnePlus6", "OnePlus6", "OnePlus A6000");
    } else if (project_codename == "fajita") {
        property_override("ro.boot.product.vendor.sku", "km4");
        model_property_override("OnePlus6T", "OnePlus6T", "OnePlus A6013");
    } else if (project_codename == "fajitat") {
        property_override("ro.boot.product.vendor.sku", "km4");
        model_property_override("OnePlus6T", "OnePlus6T", "OnePlus A6013");
    }
}
