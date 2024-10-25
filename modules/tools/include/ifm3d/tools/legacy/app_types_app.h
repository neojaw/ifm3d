// -*- c++ -*-
/*
 * Copyright 2018-present ifm electronic, gmbh
 * Copyright 2017 Love Park Robotics, LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef IFM3D_TOOLS_APP_TYPES_APP_H
#define IFM3D_TOOLS_APP_TYPES_APP_H

#include <string>
#include <CLI/CLI.hpp>
#include <ifm3d/tools/command.hpp>
#include <ifm3d/tools/main_command.hpp>
#include <ifm3d/device/device.h>
#include <ifm3d/device.h>

namespace ifm3d
{
  /**
   * Concrete implementation of the `app-types` subcommand to the `ifm3d`
   * command-line utility.
   */
  class AppTypesApp : public Command
  {
  public:
    ~AppTypesApp();

    virtual void Execute(CLI::App* app) override;
    virtual CLI::App* CreateCommand(CLI::App* parent) override;

  }; // end: class AppTypeApp
} // end: namespace ifm3d

#endif // IFM3D_TOOLS_APP_TYPES_APP_H