// -*- c++ -*-
/*
 * Copyright 2022-present ifm electronic, gmbh
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef IFM3D_DESERIALIZE_STRUCT_O3R__ODS_INFO_V1_HPP
#define IFM3D_DESERIALIZE_STRUCT_O3R__ODS_INFO_V1_HPP

#include <array>
#include <chrono>
#include <ifm3d/device/device.h>
#include <ifm3d/device/err.h>
#include <ifm3d/fg/organizer_utils.h>
#include <ifm3d/fg/buffer.h>
#include <ifm3d/deserialize/deserialize_utils.hpp>

namespace ifm3d
{
  namespace
  {
    constexpr auto ODS_INFO_TIMESTAMP_NS_INDEX = 0x0000;
    constexpr auto ODS_INFO_ZONE_OCCUPIED_INDEX = 0x0008;
    constexpr auto ODS_INFO_ZONE_CONFIG_ID_INDEX = 0x000B;
  };

  class ODSInfoV1
  {
  public:
    using Ptr = std::shared_ptr<ODSInfoV1>;

    void
    Read(const uint8_t* data, size_t size)
    {
      if (size < ods_info_v1)
        {
          throw ifm3d::Error(IFM3D_BUFFER_NOT_COMPATIABLE);
        }
      const uint8_t* start_ptr = data;
      timestamp_ns =
        mkval<std::uint64_t>(start_ptr + ODS_INFO_TIMESTAMP_NS_INDEX);
      mkarray<uint8_t, 3>(start_ptr + ODS_INFO_ZONE_OCCUPIED_INDEX,
                          zone_occupied);
      zone_config_id = mkval<float>(start_ptr + ODS_INFO_ZONE_CONFIG_ID_INDEX);
    };

    uint64_t timestamp_ns;
    std::array<uint8_t, 3> zone_occupied;
    uint32_t zone_config_id;
    const size_t ods_info_v1 = 15;

    static ODSInfoV1
    Deserialize(const Buffer& tof_info_buffer)
    {
      ODSInfoV1 ods_info_v1;

      ods_info_v1.Read(tof_info_buffer.ptr<uint8_t>(0),
                       tof_info_buffer.size());
      return ods_info_v1;
    }
  };
} // end namespace ifm3d

#endif // IFM3D_DESERIALIZE_STRUCT_O3R__ODS_INFO_V1_HPP