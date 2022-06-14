/*
 * Copyright 2021-present ifm electronic, gmbh
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef IFM3D_DEVICE_EXPORT_HPP
#define IFM3D_DEVICE_EXPORT_HPP

#if defined(IFM3D_DEVICE_STATIC_LIB) || !defined(_MSC_VER)
#  define IFM3D_DEVICE_EXPORT
#else
#  ifdef IFM3D_DEVICE_DLL_BUILD
#    define IFM3D_DEVICE_EXPORT __declspec(dllexport)
#  else
#    define IFM3D_DEVICE_EXPORT __declspec(dllimport)
#  endif
#endif

#endif /* IFM3D_CAMERA_EXPORT_HPP */