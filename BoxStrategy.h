#include "Strategy.h"
#include "SonarSensor.h"
#include "Fifo.h"

class BoxStrategy : public Strategy {
  private:
    const int frontRange = 25;
    const int sideRange = 23;

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

    void run() {
      detectObstacles();
      byte obstacle = fifo.getLastObstacle()->getDirection();
      if (obstacle) {
        switch (obstacle) {
          case 0x4:
            handleLeftObstacle();
            break;
          case 0x2:
            handleRightObstacle();
            break;
          case 0x6:
            handleFrontObstacle();
            break;
            
          case 0x1:
            handleRightObstacle();
            break;
          case 0x3:
            handleRightFrontObstacle();
            break;
          case 0x5:
          case 0x7:
            handleAllObstacles();
            break;
        }
        delay(600);
      } else {
        doResume();
      }
    }
  
  private:
    void handleLeftObstacle() {
      Obstacle* obst = fifo.getLastObstacle();
      if (obst->same(fifo.getObstacle(-1))) {
        w->doStop();
        w->goLeftBack();
      } else {
        w->goRight();
      }
      w->doStop();
    }
    
    void handleLeftFrontObstacle() {
      Obstacle* obst = fifo.getLastObstacle();
      if (obst->same(fifo.getObstacle(-1))) {
        w->turnRight();
      } else {
        w->goLeftBack();
      }
      w->doStop();
    }
    
    void handleRightObstacle() {
      Obstacle* obst = fifo.getLastObstacle();
      if (obst->same(fifo.getObstacle(-1))) {
        w->doStop();
        w->goRightBack();
      } else {
        w->goLeft();
      }
      w->doStop();
    }
    
    void handleRightFrontObstacle() {
      Obstacle* obst = fifo.getLastObstacle();
      if (obst->same(fifo.getObstacle(-1))) {
        w->turnLeft();
      } else {
        w->goRightBack();
      }
      w->doStop();
    }
    
    void handleFrontObstacle() {
      w->goBackward();
      delay(250);
      w->doStop();
    }
    
    void handleAllObstacles() {
      Obstacle* obst = fifo.getLastObstacle();
      if (obst->same(fifo.getObstacle(-1))) {
        w->turnRight();
      } else {
        w->goBackward();
        delay(500);
      }
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
    
      distance = wallSensor.isInRange(frontRange);
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
        Serial.print("; right = ");
        Serial.print(obstacle.getRightDistance());
        Serial.print("; front = ");
        Serial.print(obstacle.getFrontDistance());
        Serial.println();
    #endif
    }
};

