class SonarSensor {
  byte trigger;
  byte echo;
  long distance;

  long readDistance() {
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    return pulseIn(echo, HIGH)/58;
  }
public:
  SonarSensor(byte trigger, byte echo) {
    this->trigger = trigger;
    this->echo = echo;
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
  }

  void sendSignal() {
    long distance1 = readDistance();
    distance = readDistance();
    if (abs(distance1-distance) > 3000) {
      distance = max(distance1, distance);
    }
  }

  long isInRange(int range) {
    return (distance > 0 && distance <= range) ? distance : 0;
  }
};

