/*
 * Copyright 2018-present ifm electronic, gmbh
 * Copyright 2017 Love Park Robotics, LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ifm3d/tools/ls_app.h>
#include <iostream>
#include <ifm3d/tools/cmdline_app.h>
#include <ifm3d/camera.h>

ifm3d::LsApp::LsApp(int argc, const char** argv, const std::string& name)
  : ifm3d::CmdLineApp(argc, argv, name)
{}

int
ifm3d::LsApp::Run()
{
  if (this->vm_->count("help"))
    {
      this->_LocalHelp();
      return 0;
    }

  json apps =
    std::static_pointer_cast<ifm3d::Camera>(this->cam_)->ApplicationList();
  std::cout << apps.dump(2) << std::endl;

  return 0;
}

bool
ifm3d::LsApp::CheckCompatibility()
{
  return this->cam_->IsO3D() || this->cam_->IsO3X();
}