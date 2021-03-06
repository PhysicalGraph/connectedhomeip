/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// THIS FILE IS GENERATED BY ZAP

// Prevent multiple inclusion
#pragma once

// Default values for the attributes longer than a pointer,
// in a form of a binary blob
// Separate block is generated for big-endian and little-endian cases.
#if BIGENDIAN_CPU
#define GENERATED_DEFAULTS                                                                                                         \
    {                                                                                                                              \
    }

#else // !BIGENDIAN_CPU
#define GENERATED_DEFAULTS                                                                                                         \
    {                                                                                                                              \
    }

#endif // BIGENDIAN_CPU

#define GENERATED_DEFAULTS_COUNT (0)

#define ZAP_TYPE(type) ZCL_##type##_ATTRIBUTE_TYPE
#define ZAP_LONG_DEFAULTS_INDEX(index)                                                                                             \
    {                                                                                                                              \
        (uint8_t *) (&generatedDefaults[index])                                                                                    \
    }
#define ZAP_MIN_MAX_DEFAULTS_INDEX(index)                                                                                          \
    {                                                                                                                              \
        (uint8_t *) (&minMaxDefault[index])                                                                                        \
    }
#define ZAP_EMPTY_DEFAULT()                                                                                                        \
    {                                                                                                                              \
        (uint8_t *) 0                                                                                                              \
    }
#define ZAP_SIMPLE_DEFAULT(x)                                                                                                      \
    {                                                                                                                              \
        (uint8_t *) x                                                                                                              \
    }

// This is an array of EmberAfAttributeMinMaxValue structures.
#define GENERATED_MIN_MAX_DEFAULT_COUNT 0
#define GENERATED_MIN_MAX_DEFAULTS                                                                                                 \
    {                                                                                                                              \
    }

#define ZAP_ATTRIBUTE_MASK(mask) ATTRIBUTE_MASK_##mask
// This is an array of EmberAfAttributeMetadata structures.
#define GENERATED_ATTRIBUTE_COUNT 10
#define GENERATED_ATTRIBUTES                                                                                                       \
    {                                                                                                                              \
                                                                                                                                   \
        /* Endpoint: 1, Cluster: Window Covering (server) */                                                                       \
        { 0x0000, ZAP_TYPE(ENUM8), 1, 0, ZAP_SIMPLE_DEFAULT(0x00) },        /* window covering type */                             \
            { 0x0003, ZAP_TYPE(INT16U), 2, 0, ZAP_SIMPLE_DEFAULT(0x0000) }, /* current position - lift */                          \
            { 0x0004, ZAP_TYPE(INT16U), 2, 0, ZAP_SIMPLE_DEFAULT(0x0000) }, /* current position - tilt */                          \
            { 0x0007, ZAP_TYPE(BITMAP8), 1, 0, ZAP_SIMPLE_DEFAULT(0x03) },  /* config status */                                    \
            { 0x0010, ZAP_TYPE(INT16U), 2, 0, ZAP_SIMPLE_DEFAULT(0x0000) }, /* installed open limit - lift */                      \
            { 0x0011, ZAP_TYPE(INT16U), 2, 0, ZAP_SIMPLE_DEFAULT(0xFFFF) }, /* installed closed limit - lift */                    \
            { 0x0012, ZAP_TYPE(INT16U), 2, 0, ZAP_SIMPLE_DEFAULT(0x0000) }, /* installed open limit - tilt */                      \
            { 0x0013, ZAP_TYPE(INT16U), 2, 0, ZAP_SIMPLE_DEFAULT(0xFFFF) }, /* installed closed limit - tilt */                    \
            { 0x0017, ZAP_TYPE(BITMAP8), 1, ZAP_ATTRIBUTE_MASK(WRITABLE), ZAP_SIMPLE_DEFAULT(0x14) }, /* mode */                   \
            { 0xFFFD, ZAP_TYPE(INT16U), 2, 0, ZAP_SIMPLE_DEFAULT(3) },                                /* cluster revision */       \
    }

// This is an array of EmberAfCluster structures.
#define ZAP_ATTRIBUTE_INDEX(index) ((EmberAfAttributeMetadata *) (&generatedAttributes[index]))

// Cluster function static arrays
#define GENERATED_FUNCTION_ARRAYS

#define ZAP_CLUSTER_MASK(mask) CLUSTER_MASK_##mask
#define GENERATED_CLUSTER_COUNT 1
#define GENERATED_CLUSTERS                                                                                                         \
    {                                                                                                                              \
        {                                                                                                                          \
            0x0102, ZAP_ATTRIBUTE_INDEX(0), 10, 17, ZAP_CLUSTER_MASK(SERVER), NULL                                                 \
        }, /* Endpoint: 1, Cluster: Window Covering (server) */                                                                    \
    }

#define ZAP_CLUSTER_INDEX(index) ((EmberAfCluster *) (&generatedClusters[index]))

// This is an array of EmberAfEndpointType structures.
#define GENERATED_ENDPOINT_TYPES                                                                                                   \
    {                                                                                                                              \
        { ZAP_CLUSTER_INDEX(0), 1, 17 },                                                                                           \
    }

// Largest attribute size is needed for various buffers
#define ATTRIBUTE_LARGEST (3)

// Total size of singleton attributes
#define ATTRIBUTE_SINGLETONS_SIZE (0)

// Total size of attribute storage
#define ATTRIBUTE_MAX_SIZE (17)

// Number of fixed endpoints
#define FIXED_ENDPOINT_COUNT (1)

// Array of endpoints that are supported, the data inside
// the array is the endpoint number.
#define FIXED_ENDPOINT_ARRAY                                                                                                       \
    {                                                                                                                              \
        0x0001                                                                                                                     \
    }

// Array of profile ids
#define FIXED_PROFILE_IDS                                                                                                          \
    {                                                                                                                              \
        0x0104                                                                                                                     \
    }

// Array of device ids
#define FIXED_DEVICE_IDS                                                                                                           \
    {                                                                                                                              \
        0                                                                                                                          \
    }

// Array of device versions
#define FIXED_DEVICE_VERSIONS                                                                                                      \
    {                                                                                                                              \
        1                                                                                                                          \
    }

// Array of endpoint types supported on each endpoint
#define FIXED_ENDPOINT_TYPES                                                                                                       \
    {                                                                                                                              \
        0                                                                                                                          \
    }

// Array of networks supported on each endpoint
#define FIXED_NETWORKS                                                                                                             \
    {                                                                                                                              \
        0                                                                                                                          \
    }

// Array of EmberAfCommandMetadata structs.
#define ZAP_COMMAND_MASK(mask) COMMAND_MASK_##mask
#define EMBER_AF_GENERATED_COMMAND_COUNT (7)
#define GENERATED_COMMANDS                                                                                                         \
    {                                                                                                                              \
                                                                                                                                   \
        /* Endpoint: 1, Cluster: Window Covering (server) */                                                                       \
        { 0x0102, 0x00, ZAP_COMMAND_MASK(INCOMING_SERVER) },     /* WindowCoveringUpOpen */                                        \
            { 0x0102, 0x01, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* WindowCoveringDownClose */                                     \
            { 0x0102, 0x02, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* WindowCoveringStop */                                          \
            { 0x0102, 0x04, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* WindowCoveringGoToLiftValue */                                 \
            { 0x0102, 0x05, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* WindowCoveringGoToLiftPercentage */                            \
            { 0x0102, 0x07, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* WindowCoveringGoToTiltValue */                                 \
            { 0x0102, 0x08, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* WindowCoveringGoToTiltPercentage */                            \
    }

// Array of EmberAfManufacturerCodeEntry structures for commands.
#define GENERATED_COMMAND_MANUFACTURER_CODE_COUNT (0)
#define GENERATED_COMMAND_MANUFACTURER_CODES                                                                                       \
    {                                                                                                                              \
        {                                                                                                                          \
            0x00, 0x00                                                                                                             \
        }                                                                                                                          \
    }

// This is an array of EmberAfManufacturerCodeEntry structures for clusters.
#define GENERATED_CLUSTER_MANUFACTURER_CODE_COUNT (0)
#define GENERATED_CLUSTER_MANUFACTURER_CODES                                                                                       \
    {                                                                                                                              \
        {                                                                                                                          \
            0x00, 0x00                                                                                                             \
        }                                                                                                                          \
    }

// This is an array of EmberAfManufacturerCodeEntry structures for attributes.
#define GENERATED_ATTRIBUTE_MANUFACTURER_CODE_COUNT (0)
#define GENERATED_ATTRIBUTE_MANUFACTURER_CODES                                                                                     \
    {                                                                                                                              \
        {                                                                                                                          \
            0x00, 0x00                                                                                                             \
        }                                                                                                                          \
    }

// Array of EmberAfPluginReportingEntry structures.
#define ZRD(x) EMBER_ZCL_REPORTING_DIRECTION_##x
#define ZAP_REPORT_DIRECTION(x) ZRD(x)

// User options for plugin Reporting
#define EMBER_AF_PLUGIN_REPORTING_TABLE_SIZE (8)
#define EMBER_AF_PLUGIN_REPORTING_ENABLE_GROUP_BOUND_REPORTS

#define EMBER_AF_GENERATED_REPORTING_CONFIG_DEFAULTS_TABLE_SIZE (8)
#define EMBER_AF_GENERATED_REPORTING_CONFIG_DEFAULTS                                                                               \
    {                                                                                                                              \
                                                                                                                                   \
        /* Endpoint: 1, Cluster: Window Covering (server) */                                                                       \
        {                                                                                                                          \
            ZAP_REPORT_DIRECTION(REPORTED), 0x0001, 0x0102, 0x0000, ZAP_CLUSTER_MASK(SERVER), 0x0000, { { 0, 65344, 0 } }          \
        }, /* window covering type */                                                                                              \
            {                                                                                                                      \
                ZAP_REPORT_DIRECTION(REPORTED), 0x0001, 0x0102, 0x0003, ZAP_CLUSTER_MASK(SERVER), 0x0000, { { 0, 65344, 0 } }      \
            }, /* current position - lift */                                                                                       \
            {                                                                                                                      \
                ZAP_REPORT_DIRECTION(REPORTED), 0x0001, 0x0102, 0x0004, ZAP_CLUSTER_MASK(SERVER), 0x0000, { { 0, 65344, 0 } }      \
            }, /* current position - tilt */                                                                                       \
            {                                                                                                                      \
                ZAP_REPORT_DIRECTION(REPORTED), 0x0001, 0x0102, 0x0007, ZAP_CLUSTER_MASK(SERVER), 0x0000, { { 0, 65344, 0 } }      \
            }, /* config status */                                                                                                 \
            {                                                                                                                      \
                ZAP_REPORT_DIRECTION(REPORTED), 0x0001, 0x0102, 0x0010, ZAP_CLUSTER_MASK(SERVER), 0x0000, { { 0, 65344, 0 } }      \
            }, /* installed open limit - lift */                                                                                   \
            {                                                                                                                      \
                ZAP_REPORT_DIRECTION(REPORTED), 0x0001, 0x0102, 0x0011, ZAP_CLUSTER_MASK(SERVER), 0x0000, { { 0, 65344, 0 } }      \
            }, /* installed closed limit - lift */                                                                                 \
            {                                                                                                                      \
                ZAP_REPORT_DIRECTION(REPORTED), 0x0001, 0x0102, 0x0012, ZAP_CLUSTER_MASK(SERVER), 0x0000, { { 0, 65344, 0 } }      \
            }, /* installed open limit - tilt */                                                                                   \
            {                                                                                                                      \
                ZAP_REPORT_DIRECTION(REPORTED), 0x0001, 0x0102, 0x0013, ZAP_CLUSTER_MASK(SERVER), 0x0000, { { 0, 65344, 0 } }      \
            }, /* installed closed limit - tilt */                                                                                 \
    }
