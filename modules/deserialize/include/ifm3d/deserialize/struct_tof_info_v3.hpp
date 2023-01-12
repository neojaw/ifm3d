// -*- c++ -*-
/*
 * Copyright 2022-present ifm electronic, gmbh
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef IFM3D_DESERIALIZE_STRUCT_TOF_INFO_V3_HPP
#define IFM3D_DESERIALIZE_STRUCT_TOF_INFO_V3_HPP

#include <array>
#include <chrono>
#include <ifm3d/device/device.h>
#include <ifm3d/device/err.h>
#include <ifm3d/fg/organizer_utils.h>
#include <ifm3d/fg/buffer.h>
#include <ifm3d/deserialize/deserialize_utils.hpp>
#include <ifm3d/deserialize/struct_calibration.hpp>

namespace ifm3d
{
  namespace
  {
    constexpr auto TOF_INFO_VERSION_INDEX = 0x0000;
    constexpr auto TOF_INFO_DISTANCE_RESOLUTION_INDEX = 0x0004;
    constexpr auto TOF_INFO_AMPLITUDE_RESOLUTION_INDEX = 0x0008;
    constexpr auto TOF_INFO_AMPLITUDE_NORM_FACTOR_INDEX = 0x000C;
    constexpr auto TOF_INFO_EXTRINSIC_OPTICAL_TO_USER_INDEX = 0x0018;
    constexpr auto TOF_INFO_INTRINSIC_CALIBRATION_INDEX = 0x0030;
    constexpr auto TOF_INFO_INVERSE_INTRINSIC_CALIBRATION_INDEX = 0x00B4;
    constexpr auto TOF_INFO_EXPOSURE_TIMESTAMPS_INDEX = 0x0138;
    constexpr auto TOF_INFO_EXPOSURE_TIMES_INDEX = 0x0150;
    constexpr auto TOF_INFO_ILLUTEMPERATURE_INDEX = 0x015C;
    constexpr auto TOF_INFO_MODE_INDEX = 0x0160;
    constexpr auto TOF_INFO_IMAGER_INDEX = 0x0180;
  };

  class TofInfoV3
  {

  public:
    using Ptr = std::shared_ptr<TofInfoV3>;

    void
    Read(const uint8_t* data, size_t size)
    {
      if (size < tof_info_v3_size)
        {
          throw ifm3d::Error(IFM3D_BUFFER_NOT_COMPATIABLE);
        }
      const uint8_t* start_ptr = data;
      version = mkval<std::uint32_t>(start_ptr + TOF_INFO_VERSION_INDEX);
      distance_resolution =
        mkval<float>(start_ptr + TOF_INFO_DISTANCE_RESOLUTION_INDEX);
      amplitude_resolution =
        mkval<float>(start_ptr + TOF_INFO_AMPLITUDE_RESOLUTION_INDEX);
      mkarray<float, 3>(start_ptr + TOF_INFO_AMPLITUDE_NORM_FACTOR_INDEX,
                        amp_normalization_factors);
      extrisic_optic_to_user.Read(start_ptr +
                                  TOF_INFO_EXTRINSIC_OPTICAL_TO_USER_INDEX);
      intrinsic_calibration.Read(start_ptr +
                                 TOF_INFO_INTRINSIC_CALIBRATION_INDEX);
      inverse_intrinsic_calibration.Read(
        start_ptr + TOF_INFO_INVERSE_INTRINSIC_CALIBRATION_INDEX);
      mkarray<uint64_t, 3>(start_ptr + TOF_INFO_EXPOSURE_TIMESTAMPS_INDEX,
                           exposure_timestamps_ns);
      mkarray<uint32_t, 3>(start_ptr + TOF_INFO_EXPOSURE_TIMES_INDEX,
                           exposure_times_s);
      illu_temperature =
        mkval<float>(start_ptr + TOF_INFO_ILLUTEMPERATURE_INDEX);
      mkarray<char, 32>(start_ptr + TOF_INFO_MODE_INDEX, mode);
      mkarray<char, 32>(start_ptr + TOF_INFO_IMAGER_INDEX, imager);
    };

    uint32_t version;
    float distance_resolution;
    float amplitude_resolution;
    std::array<float, 3> amp_normalization_factors;
    calibration::ExtrinsicOpticToUser extrisic_optic_to_user;
    calibration::IntrinsicCalibration intrinsic_calibration;
    calibration::InverseIntrinsicCalibration inverse_intrinsic_calibration;
    std::array<uint64_t, 3> exposure_timestamps_ns;
    std::array<uint32_t, 3> exposure_times_s;
    float illu_temperature;
    std::array<char, 32> mode;
    std::array<char, 32> imager;
    const size_t tof_info_v3_size = 416;

    static TofInfoV3
    Deserialize(const Buffer& tof_info_buffer)
    {
      TofInfoV3 tof_info_v3;

      tof_info_v3.Read(tof_info_buffer.ptr<uint8_t>(0),
                       tof_info_buffer.size());
      return tof_info_v3;
    }
  };
} // end namespace ifm3d

#endif // IFM3D_DESERIALIZE_STRUCT_TOF_INFO_V3_HPP