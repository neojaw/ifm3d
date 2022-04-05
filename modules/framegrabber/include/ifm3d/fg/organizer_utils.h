/*
 * Copyright 2022-present ifm electronic, gmbh
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef IFM3D_FG_ORGANIZER_UTILS_H
#define IFM3D_FG_ORGANIZER_UTILS_H

#include <map>
#include <optional>
#include <vector>
#include <tuple>
#include <ifm3d/camera/camera.h>
#include <ifm3d/fg/image.h>
#include <ifm3d/fg/frame.h>

namespace ifm3d
{
  constexpr std::size_t IMG_BUFF_START = 8;

  std::map<image_chunk, std::size_t> get_image_chunks(
    const std::vector<std::uint8_t>& data,
    std::size_t start_idx);

  std::size_t get_format_size(pixel_format fmt);
  std::size_t get_format_channels(pixel_format fmt);

  Image create_image(const std::vector<std::uint8_t>& data,
                     std::size_t idx,
                     std::size_t width,
                     std::size_t height);

  Image create_image(const std::vector<std::uint8_t>& data,
                     std::size_t idx,
                     std::size_t width,
                     std::size_t height,
                     pixel_format fmt);

  Image create_xyz_image(const std::vector<std::uint8_t>& data,
                         std::size_t xidx,
                         std::size_t yidx,
                         std::size_t zidx,
                         std::size_t width,
                         std::size_t height,
                         pixel_format fmt,
                         const std::optional<Image>& mask);

  auto find_metadata_chunk(std::map<image_chunk, std::size_t> chunks)
    -> decltype(chunks.end());

  std::tuple<uint32_t, uint32_t> get_image_size(
    const std::vector<std::uint8_t>& data,
    std::size_t idx);

  pixel_format get_chunk_format(const std::vector<std::uint8_t>& data,
                                std::size_t idx);

  std::vector<TimePointT> get_chunk_timestamps(
    const std::vector<uint8_t>& data,
    std::size_t idx);

  std::size_t get_chunk_pixeldata_offset(const std::vector<std::uint8_t>& data,
                                         std::size_t idx);

  std::size_t get_chunk_pixeldata_size(const std::vector<std::uint8_t>& data,
                                       std::size_t idx);

  void mask_image(Image& image, const Image& mask);

  /**
   * Create a value of type T from sizeof(T) bytes of the passed in byte
   * buffer. Given that the ifm sensors transmit data in little endian
   * format, this function will swap bytes if necessary for the host
   * representation of T.
   *
   * @param[in] buff A pointer to a buffer in memory intended to be
   * interpreted as data of type T and assuming the buffer is little endian.
   *
   * @return An interpretation of `buff` as type T with bytes swapped as
   * appropriate for the host's byte ordering semantics.
   */
  template <typename T>
  T
  mkval(const unsigned char* buff)
  {
    union
    {
      T v;
      unsigned char bytes[sizeof(T)];
    } value;

#if !defined(_WIN32) && __BYTE_ORDER == __BIG_ENDIAN
    std::reverse_copy(buff, buff + sizeof(T), value.bytes);
#else
    std::copy(buff, buff + sizeof(T), value.bytes);
#endif

    return value.v;
  }
} // end: namespace ifm3d

#endif // IFM3D_FG_ORGANIZER_UTILS_H