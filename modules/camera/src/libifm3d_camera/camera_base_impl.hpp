/*
 * Copyright 2021-present ifm electronic, gmbh
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef IFM3D_CAMERA_CAMERA_BASE_IMPL_HPP
#define IFM3D_CAMERA_CAMERA_BASE_IMPL_HPP

#include <vector>
#include <fmt/ostream.h>
#include <ifm3d/camera/camera_base.h>
#include <ifm3d/camera/logging.h>
#include <ifm3d/camera/semver.h>
#include <xmlrpc_wrapper.hpp>

namespace ifm3d
{
  class XMLRPCWrapper;
  //============================================================
  // Impl interface
  //============================================================
  class CameraBase::Impl
  {
  public:
    explicit Impl(std::shared_ptr<XMLRPCWrapper> xwrapper);
    ~Impl();

    // accessor/mutators
    std::shared_ptr<XMLRPCWrapper> XWrapper();
    std::string XPrefix();
    std::string IP();
    std::uint16_t XMLRPCPort();

    bool CheckMinimumFirmwareVersion(const SemVer& minimum_version);

    //
    // public xmlrpc interface methods
    //

    // Main
    std::string DeviceParameter(const std::string& param);
    std::vector<std::string> TraceLogs(int count);
    void Reboot(int mode);

  protected:
    std::shared_ptr<XMLRPCWrapper> xwrapper_;
  }; // end: class Camera::Impl
} // end: namespace ifm3d

//============================================================
// Impl - Implementation Details
//============================================================

//-------------------------------------
// ctor/dtor
//-------------------------------------

ifm3d::CameraBase::Impl::Impl(std::shared_ptr<XMLRPCWrapper> xwrapper)
  : xwrapper_(std::move(xwrapper))
{
  VLOG(IFM3D_TRACE) << "Initializing Camera: ip=" << this->IP()
                    << ", xmlrpc_port=" << this->XMLRPCPort();
  VLOG(IFM3D_TRACE) << "XMLRPC URL Prefix=" << this->XPrefix();
}

ifm3d::CameraBase::Impl::~Impl() { VLOG(IFM3D_TRACE) << "Dtor..."; }

//-------------------------------------
// Accessor/mutators
//-------------------------------------

std::shared_ptr<ifm3d::XMLRPCWrapper>
ifm3d::CameraBase::Impl::XWrapper()
{
  return this->xwrapper_;
}

std::string
ifm3d::CameraBase::Impl::XPrefix()
{
  return this->xwrapper_->XPrefix();
}

std::string
ifm3d::CameraBase::Impl::IP()
{
  return this->xwrapper_->IP();
}

std::uint16_t
ifm3d::CameraBase::Impl::XMLRPCPort()
{
  return this->xwrapper_->XMLRPCPort();
}

// =============================================
// Public XMLRPC interface - worker methods
// =============================================

// ---------------------------------------------
// Main (no edit session necessary)
// ---------------------------------------------

std::string
ifm3d::CameraBase::Impl::DeviceParameter(const std::string& param)
{
  return xmlrpc_c::value_string(
           this->xwrapper_->XCallMain("getParameter", param.c_str()))
    .cvalue();
}

bool
ifm3d::CameraBase::Impl::CheckMinimumFirmwareVersion(
  const ifm3d::SemVer& minimum_version)
{

  auto data = this->xwrapper_->value_struct_to_map(
    this->xwrapper_->XCallMain("getSWVersion"));
  const auto swversion = ifm3d::SemVer::Parse(data["IFM_Software"]);

  return swversion.value_or(ifm3d::SemVer(0, 0, 0)) >= minimum_version;
}

std::vector<std::string>
ifm3d::CameraBase::Impl::TraceLogs(int count)
{
  xmlrpc_c::value_array result(
    this->xwrapper_->XCallMain("getTraceLogs", count));
  std::vector<xmlrpc_c::value> const res_vec(result.vectorValueValue());

  std::vector<std::string> retval;
  for (auto& entry : res_vec)
    {
      xmlrpc_c::value_string const entry_str(entry);
      retval.push_back(static_cast<std::string>(entry_str));
    }
  return retval;
}

void
ifm3d::CameraBase::Impl::Reboot(int mode)
{
  this->xwrapper_->XCallMain("reboot", mode);
}

#endif // IFM3D_CAMERA_CAMERA_BASE_IMPL_HPP