/*
 * Copyright 2014-present Facebook. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#pragma once
#include <string>
#include <stdexcept>
#include <fstream>
#include <glog/logging.h>
#include "SensorAttribute.h"
#include "SensorApi.h"

namespace openbmc {
namespace ipc {

/**
 * Sensor API for reading and writing value of the attribute from the
 * SensorObject path.
 */
class SensorSysfsApi : public SensorApi {
  private:
    std::string fsPath_;

  public:
    SensorSysfsApi(const std::string &fsPath) {
      fsPath_ = fsPath;
    }

    const std::string& getFsPath() const {
      return fsPath_;
    }

    /**
     * Reads value from the path specified by object and attr. The path
     * will be constructed from fsPath_ and addr in attribute.
     * Only reads the first line.
     *
     * @param object of Attribute to be read
     * @param attr of the value to be read
     * @throw errno if the file cannot be opened
     * @return value read
     */
    const std::string readValue(const SensorObject    &object,
                                const SensorAttribute &attr) override;

    /**
     * Writes value to the path specified by object and attr. The path
     * will be constructed from fsPath_ and addr in attribute.
     *
     * @param value to be written
     * @param object of Attribute to be written
     * @param attr of the value to be written
     * @throw errno if the file cannot be opened
     */
    void writeValue(const std::string     &value,
                    const SensorObject    &object,
                    const SensorAttribute &attr) override;
};
} // namespace ipc
} // namespace openbmc