#ifndef TURNTOHEADINGCOMMAND_H
#define TURNTOHEADINGCOMMAND_H

#include <PID_v2.h>
#include "./Command.h"
#include "../hardware/IMU.h"

class TurnToHeadingCommand: public Command {
  private:
    float target;
    bool absolute;
    float tol;
    int speed;
    
    PID_v2 controller;
    int initialLeftPos;
    int initialRightPos;


    static float kP_POS;

  public:
    TurnToHeadingCommand(float target, bool absolute, int speed, float tol);

    void init() override;
    void periodic() override;
    void end() override;
    bool isFinished() override;

};

#endif