#pragma once

#include "Strategy.h"
#include "SonarSensor.h"
#include "Fifo.h"
#include "SonarObstacle.h"

class BoxStrategy : public Strategy {
  private:
    const int frontRange = 15;
    const int sideRange = 25;

    SonarSensor frontLeftSensor {11, 10};
    SonarSensor frontRightSensor {4, 12};
    SonarSensor wallSensor {A3, A2};
    Fifo fifo {4};
  public:
    void run(void (*f)()) {
      detectObstacles();
      SonarObstacle* obstacle = (SonarObstacle*)fifo.getLastObstacle();
      byte direction = obstacle->getDirection();
      if (direction) {
        switch (direction) {
          case 0x1:
            wallOnTheRight(obstacle);
            break;
          case 0x2:
          case 0x3:
            handleRightFrontObstacle(obstacle);
            break;
          case 0x4:
          case 0x5:
            handleLeftFrontObstacle(obstacle);
            break;
          case 0x6:
            handleFrontObstacles(obstacle);
            break;
          case 0x7:
            handleAllObstacles(obstacle);
            break;
        }
        delay(600);
      } else {
        f();
      }
    }
  
  private:
    void wallOnTheRight(SonarObstacle* obst) {
      if (obst->getRightDistance() > 10) {
        w.goRight();
        w.goRight();
        w.goLeft();
      }
      w.doStop();
    }

    void handleRightFrontObstacle(SonarObstacle* obst) {
      w.goLeft();
    }

    void handleLeftFrontObstacle(SonarObstacle* obst) {
      w.goRight();
    }

    void handleFrontObstacles(SonarObstacle* obst) {
      w.turnLeft();
    }
    
    void handleAllObstacles(SonarObstacle* obst) {
      w.goBackward(500);
      w.turnLeft();
    }

    void detectObstacles() {
      SonarObstacle obstacle;
      long distance;
      
      frontRightSensor.scan();
      delay(25);
      frontLeftSensor.scan();
      delay(25);
      wallSensor.scan();
      delay(25);
    
      distance = frontRightSensor.isInRange(frontRange);
      if (distance) {
        obstacle.addFront(distance);
      }
    
      distance = frontLeftSensor.isInRange(frontRange);
      if (distance) {
        obstacle.addLeft(distance);
      }
    
      distance = wallSensor.isInRange(sideRange);
      if (distance) {
        obstacle.addRight(distance);
      }
      
      
      if (!obstacle.isEmpty()) {
        fifo.addObstacle(&obstacle);
      }
    #ifdef DEBUG
        Serial.print("Obstacles detected = ");
        Serial.print(obstacle.getDirection());
        Serial.print("; left = ");
        Serial.print(obstacle.getLeftDistance());
        Serial.print("; front = ");
        Serial.print(obstacle.getFrontDistance());
        Serial.print("; right = ");
        Serial.print(obstacle.getRightDistance());
        Serial.println();
    #endif
    }
    
};

