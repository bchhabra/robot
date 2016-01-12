class SonarSensor {
  byte trigger;
  byte echo;
  long distance;
public:
  SonarSensor(byte trigger, byte echo) {
    this->trigger = trigger;
    this->echo = echo;
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
  }

  void sendSignal() {
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    distance = pulseIn(echo, HIGH)/58;
  }

  long isInRange(int range) {
    return (distance <= range && distance > 0);
  }
};

