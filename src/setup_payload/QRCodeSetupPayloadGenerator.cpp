/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
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

/**
 *    @file
 *      This file implements a QRCode Setup Payload generator in accordance
 *      with the CHIP specification.
 *
 */

#include "QRCodeSetupPayloadGenerator.h"
#include "Base38.h"

#include <core/CHIPCore.h>
#include <core/CHIPTLV.h>
#include <core/CHIPTLVData.hpp>
#include <core/CHIPTLVDebug.hpp>
#include <core/CHIPTLVUtilities.hpp>
#include <protocols/Protocols.h>
#include <support/CodeUtils.h>
#include <support/RandUtils.h>

#include <stdlib.h>
#include <string.h>

namespace chip {

// Populates numberOfBits starting from LSB of input into bits, which is assumed to be zero-initialized
static CHIP_ERROR populateBits(uint8_t * bits, size_t & offset, uint64_t input, size_t numberOfBits,
                               size_t totalPayloadDataSizeInBits)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    size_t index;

    VerifyOrExit(offset + numberOfBits <= totalPayloadDataSizeInBits, err = CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrExit(input < 1u << numberOfBits, err = CHIP_ERROR_INVALID_ARGUMENT);

    index = offset;
    offset += numberOfBits;
    while (input != 0)
    {
        if (input & 1)
        {
            bits[index / 8] |= static_cast<uint8_t>(1 << index % 8);
        }
        index++;
        input >>= 1;
    }
exit:
    return err;
}

static CHIP_ERROR populateTLVBits(uint8_t * bits, size_t & offset, const uint8_t * tlvBuf, size_t tlvBufSizeInBytes,
                                  size_t totalPayloadDataSizeInBits)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    for (size_t i = 0; i < tlvBufSizeInBytes; i++)
    {
        uint8_t value = tlvBuf[i];
        err           = populateBits(bits, offset, value, 8, totalPayloadDataSizeInBits);
        if (err != CHIP_NO_ERROR)
        {
            return err;
        }
    }
    return err;
}

CHIP_ERROR writeTag(TLV::TLVWriter & writer, uint64_t tag, OptionalQRCodeInfo & info)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    if (info.type == optionalQRCodeInfoTypeString)
    {
        err = writer.PutString(tag, info.data.c_str());
    }
    else if (info.type == optionalQRCodeInfoTypeInt32)
    {
        err = writer.Put(tag, info.int32);
    }
    else
    {
        err = CHIP_ERROR_INVALID_ARGUMENT;
    }

    return err;
}

CHIP_ERROR writeTag(TLV::TLVWriter & writer, uint64_t tag, OptionalQRCodeInfoExtension & info)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    if (info.type == optionalQRCodeInfoTypeString || info.type == optionalQRCodeInfoTypeInt32)
    {
        err = writeTag(writer, tag, static_cast<OptionalQRCodeInfo &>(info));
    }
    else if (info.type == optionalQRCodeInfoTypeInt64)
    {
        err = writer.Put(tag, info.int64);
    }
    else if (info.type == optionalQRCodeInfoTypeUInt32)
    {
        err = writer.Put(tag, info.uint32);
    }
    else if (info.type == optionalQRCodeInfoTypeUInt64)
    {
        err = writer.Put(tag, info.uint64);
    }
    else
    {
        err = CHIP_ERROR_INVALID_ARGUMENT;
    }

    return err;
}

CHIP_ERROR QRCodeSetupPayloadGenerator::generateTLVFromOptionalData(SetupPayload & outPayload, uint8_t * tlvDataStart,
                                                                    uint32_t maxLen, size_t & tlvDataLengthInBytes)
{
    CHIP_ERROR err                                                 = CHIP_NO_ERROR;
    std::vector<OptionalQRCodeInfo> optionalData                   = outPayload.getAllOptionalVendorData();
    std::vector<OptionalQRCodeInfoExtension> optionalExtensionData = outPayload.getAllOptionalExtensionData();
    VerifyOrExit(!optionalData.empty() || !optionalExtensionData.empty(), err = CHIP_NO_ERROR);

    TLV::TLVWriter rootWriter;
    rootWriter.Init(tlvDataStart, maxLen);

    TLV::TLVWriter innerStructureWriter;

    err = rootWriter.OpenContainer(TLV::AnonymousTag, TLV::kTLVType_Structure, innerStructureWriter);
    SuccessOrExit(err);

    for (OptionalQRCodeInfo info : optionalData)
    {
        err = writeTag(innerStructureWriter, TLV::ContextTag(info.tag), info);
        SuccessOrExit(err);
    }

    for (OptionalQRCodeInfoExtension info : optionalExtensionData)
    {
        err = writeTag(innerStructureWriter, TLV::ContextTag(info.tag), info);
        SuccessOrExit(err);
    }

    err = rootWriter.CloseContainer(innerStructureWriter);
    SuccessOrExit(err);

    err = rootWriter.Finalize();
    SuccessOrExit(err);

    tlvDataLengthInBytes = rootWriter.GetLengthWritten();

exit:
    return err;
}

static CHIP_ERROR generateBitSet(SetupPayload & payload, uint8_t * bits, uint8_t * tlvDataStart, size_t tlvDataLengthInBytes)
{
    CHIP_ERROR err                = CHIP_NO_ERROR;
    size_t offset                 = 0;
    size_t totalPayloadSizeInBits = kTotalPayloadDataSizeInBits + (tlvDataLengthInBytes * 8);
    err = populateBits(bits, offset, payload.version, kVersionFieldLengthInBits, kTotalPayloadDataSizeInBits);
    err = populateBits(bits, offset, payload.vendorID, kVendorIDFieldLengthInBits, kTotalPayloadDataSizeInBits);
    err = populateBits(bits, offset, payload.productID, kProductIDFieldLengthInBits, kTotalPayloadDataSizeInBits);
    err = populateBits(bits, offset, payload.requiresCustomFlow, kCustomFlowRequiredFieldLengthInBits, kTotalPayloadDataSizeInBits);
    err = populateBits(bits, offset, payload.rendezvousInformation.Raw(), kRendezvousInfoFieldLengthInBits,
                       kTotalPayloadDataSizeInBits);
    err = populateBits(bits, offset, payload.discriminator, kPayloadDiscriminatorFieldLengthInBits, kTotalPayloadDataSizeInBits);
    err = populateBits(bits, offset, payload.setUpPINCode, kSetupPINCodeFieldLengthInBits, kTotalPayloadDataSizeInBits);
    err = populateBits(bits, offset, 0, kPaddingFieldLengthInBits, kTotalPayloadDataSizeInBits);
    err = populateTLVBits(bits, offset, tlvDataStart, tlvDataLengthInBytes, totalPayloadSizeInBits);
    return err;
}

// TODO: issue #3663 - Unbounded stack in payloadBase38RepresentationWithTLV()
#if !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstack-usage="
#endif

static CHIP_ERROR payloadBase38RepresentationWithTLV(SetupPayload & setupPayload, std::string & base38Representation,
                                                     size_t bitsetSize, uint8_t * tlvDataStart, size_t tlvDataLengthInBytes)
{
    uint8_t bits[bitsetSize];
    memset(bits, 0, bitsetSize);
    std::string encodedPayload;
    CHIP_ERROR err = generateBitSet(setupPayload, bits, tlvDataStart, tlvDataLengthInBytes);
    SuccessOrExit(err);

    encodedPayload = base38Encode(bits, ArraySize(bits));
    encodedPayload.insert(0, kQRCodePrefix);
    base38Representation = encodedPayload;
exit:
    return err;
}

CHIP_ERROR QRCodeSetupPayloadGenerator::payloadBase38Representation(std::string & base38Representation)
{
    // 6.1.2.2. Table: Packed Binary Data Structure
    // The TLV Data should be 0 length if TLV is not included.
    return payloadBase38Representation(base38Representation, nullptr, 0);
}

CHIP_ERROR QRCodeSetupPayloadGenerator::payloadBase38Representation(std::string & base38Representation, uint8_t * tlvDataStart,
                                                                    uint32_t tlvDataStartSize)
{
    CHIP_ERROR err              = CHIP_NO_ERROR;
    size_t tlvDataLengthInBytes = 0;

    VerifyOrExit(mPayload.isValidQRCodePayload(), err = CHIP_ERROR_INVALID_ARGUMENT);
    err = generateTLVFromOptionalData(mPayload, tlvDataStart, tlvDataStartSize, tlvDataLengthInBytes);
    SuccessOrExit(err);

    err = payloadBase38RepresentationWithTLV(mPayload, base38Representation, kTotalPayloadDataSizeInBytes + tlvDataLengthInBytes,
                                             tlvDataStart, tlvDataLengthInBytes);
    SuccessOrExit(err);

exit:
    return err;
}

#if !defined(__clang__)
#pragma GCC diagnostic pop // -Wstack-usage
#endif

} // namespace chip
