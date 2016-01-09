class SonarSensor {
  byte trigger;
  byte echo;
public:
  SonarSensor(byte trigger, byte echo) {
    this->trigger = trigger;
    this->echo = echo;
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
  }

  long getDistance() {
    digitalWrite(trigger, LOW);
    delayMicroseconds(10);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
  
    return pulseIn(echo, HIGH)/58;
  }
};

