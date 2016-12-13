/**
 @file    a_robot_interface.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Sep 6, 2016
 @brief   Declares the class RobotInterface
 */

#ifndef XPP_XPP_OPT_INCLUDE_XPP_OPT_A_ROBOT_INTERFACE_H_
#define XPP_XPP_OPT_INCLUDE_XPP_OPT_A_ROBOT_INTERFACE_H_

#include <Eigen/Dense>
#include <map>
#include <iostream>

namespace xpp {
namespace opt {

// refactor generalize all LegIDs with this
enum class EndeffectorID { E0, E1, E2, E3, E4, E5 };

inline std::ostream& operator<<(std::ostream& out, const EndeffectorID& e)
{
  std::map<EndeffectorID, std::string> map {
    { EndeffectorID::E0, "LF" },
    { EndeffectorID::E1, "RF" },
    { EndeffectorID::E2, "LH" },
    { EndeffectorID::E3, "RH" }
  };

  out << map[e];
  return out;
}


/** @brief Abstracts all robot specific values
  *
  * This is the interface that the optimization code is programmed against.
  * To use a specific robot, derive from this class and pass that object to
  * the required costs/constraints.
  */
class ARobotInterface {
public:
  using PosXY = Eigen::Vector2d;
  using MaxDevXY = std::array<double,2>;

  ARobotInterface ();
  virtual ~ARobotInterface ();

  /** @brief default contact position of the endeffectors
    */
  virtual PosXY GetNominalStanceInBase(EndeffectorID leg_id) const = 0;

  /** How much the Endeffector can deviate from the default (x,y) position
    * while still remaining in the range of motion.
    *
    * Used by RangeOfMotionConstraint.
    */
  virtual MaxDevXY GetMaxDeviationXYFromNominal() const = 0;
};

} /* namespace opt */
} /* namespace xpp */

#endif /* XPP_XPP_OPT_INCLUDE_XPP_OPT_A_ROBOT_INTERFACE_H_ */
