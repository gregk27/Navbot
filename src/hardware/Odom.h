#ifndef ODOM_H
#define ODOM_H

namespace Odom {
  /**
   * Smaller struct holding basic location information, realtive to start
  */
 struct Location {
   int x;
   int y;
 };

  /**
   * Structure representing the robot's position, relative to start
  */
  struct Position {
    float x;
    float y;
    float heading;
    
    /**
     * Automatically downcast to location when needed
    */
    operator Location() {
      return {(int) x, (int) y};
    }
  };

  /**
    * Initialise the Odom
    * This should be done after intialising the drivetrain and sensors
  */
  void init();

  /**
   * Get the robot's position based on sensor readings
  */
  Position getPosition();

  /**
   * Print data in format accepted by ArduPlot
  */
  void toPlot();
  
  /**
   * Get the heading in radians to a target point
   * @param x x position of the point
   * @param y y position of the point
   * @return The heading in radians facing the point
  */
  float headingTo(float x, float y);

  /**
   * Get the relative acute angle to a target heading
   * @param h The target heading
   * @return The relative acute angle
  */
  float angleTo(float h);
}

#endif