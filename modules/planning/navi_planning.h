/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef MODULES_PLANNING_NAVI_PLANNING_H_
#define MODULES_PLANNING_NAVI_PLANNING_H_

#include <string>

#include "modules/planning/planning_base.h"

/**
 * @namespace apollo::planning
 * @brief apollo::planning
 */
namespace apollo {
namespace planning {

/**
 * @class planning
 *
 * @brief Planning module main class. It processes GPS and IMU as input,
 * to generate planning info.
 */
class NaviPlanning : public PlanningBase {
 public:
  NaviPlanning() = default;
  virtual ~NaviPlanning();
  /**
   * @brief module name
   * @return module name
   */
  std::string Name() const override;

  /**
   * @brief module initialization function
   * @return initialization status
   */
  apollo::common::Status Init() override;

  /**
   * @brief module start function
   * @return start status
   */
  apollo::common::Status Start() override;

  /**
   * @brief module stop function
   */
  void Stop() override;

  /**
   * @brief main logic of the planning module, runs periodically triggered by
   * timer.
   */
  void RunOnce() override;

  void OnTimer(const ros::TimerEvent&) override;

 private:
  void SetFallbackTrajectory(ADCTrajectory* cruise_trajectory) override;

  class VehicleConfig {
   public:
    double x_ = 0.0;
    double y_ = 0.0;
    double theta_ = 0.0;
    bool is_valid_ = false;
  };
  VehicleConfig last_vehicle_config_;

  VehicleConfig ComputeVehicleConfigFromLocalization(
      const localization::LocalizationEstimate& localization) const;
};

}  // namespace planning
}  // namespace apollo

#endif  // MODULES_PLANNING_NAVI_PLANNING_H_
