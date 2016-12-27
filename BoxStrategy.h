#pragma once

#include "Strategy.h"
#include "SonarSensor.h"
#include "Fifo.h"

class BoxStrategy : public Strategy {
  private:
    const int frontRange = 15;
    const int sideRange = 25;

    SonarSensor frontLeftSensor {11, 10};
    SonarSensor frontRightSensor {4, 12};
    SonarSensor wallSensor {A3, A2};
    Fifo fifo;
    Wheels* w;
  public:
    BoxStrategy(Wheels* wheels) {
      w = wheels;
    }
    
    void init() {
    }

    void run(void (*f)()) {
      detectObstacles();
      Obstacle* obstacle = fifo.getLastObstacle();
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
    void wallOnTheRight(Obstacle* obst) {
      if (obst->getRightDistance() > 10) {
        w->goRight();
        w->goRight();
        w->goLeft();
      }
      w->doStop();
    }

    void handleRightFrontObstacle(Obstacle* obst) {
      w->goLeft();
      w->doStop();
    }

    void handleLeftFrontObstacle(Obstacle* obst) {
      w->goRight();
      w->doStop();
    }

    void handleFrontObstacles(Obstacle* obst) {
      w->turnLeft();
      w->doStop();
    }
    
    void handleAllObstacles(Obstacle* obst) {
      w->goBackward();
      delay(500);
      w->turnLeft();
      w->doStop();
    }

    void detectObstacles() {
      Obstacle obstacle;
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

