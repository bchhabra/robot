class Obstacle {
  long left;
  long front;
  long right;
  byte direction = 0;
public:
  void addLeft(long distance) {
    left = distance;
    this->direction |= 0x4;
  }

  void addFront(long distance) {
    front = distance;
    this->direction |= 0x2;
  }

  void addRight(long distance) {
    right = distance;
    this->direction |= 0x1;
  }

  long getLeftDistance() {
    return left;
  }

  long getFrontDistance() {
    return front;
  }

  long getRightDistance() {
    return right;
  }

  byte getDirection() {
    return direction;
  }
};

