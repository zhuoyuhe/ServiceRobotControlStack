#pragma once
// Copyright 2019 kvedder@seas.upenn.edu
// School of Engineering and Applied Sciences,
// University of Pennsylvania
//
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// ========================================================================

#include <algorithm>
#include <limits>
#include <random>
#include <string>
#include <vector>

#include "cs/path_finding/path_finder.h"
#include "cs/util/constants.h"
#include "cs/util/visualization.h"
#include "shared/math/geometry.h"
#include "shared/math/math_util.h"

namespace cs {
namespace path_finding {

class AStar : public PathFinder {
 public:
  explicit AStar(const util::Map& map,
                 const float& robot_radius,
                 const float& safety_margin);

  Path2d FindPath(const util::Map& dynamic_map,
                  const Eigen::Vector2f& start,
                  const Eigen::Vector2f& goal,
                  ros::Publisher* pub) override;

 private:
  const float& robot_radius;
  const float& safety_margin;

  bool IsLineColliding(const util::Map& dynamic_map,
                       const Eigen::Vector2f& p1,
                       const Eigen::Vector2f& p2) const;

  Path2d SmoothPath(const util::Map& dynamic_map, Path2d path);

  Path2d GenerateNewPath(const util::Map& dynamic_map,
                         const Eigen::Vector2f& start,
                         const Eigen::Vector2f& goal,
                         ros::Publisher* pub);

  bool IsPathColliding(const util::Map& dynamic_map,
                       const Path2d& path) const override;

  bool IsNearGoal(const Eigen::Vector2f& goal,
                  const Eigen::Vector2f& point) const;
};

}  // namespace path_finding
}  // namespace cs