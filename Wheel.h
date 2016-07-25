class Wheel {
  byte pin1;
  byte pin2;
  byte speedPin;
  byte speed;
public:
  Wheel(byte pin1, byte pin2, byte speedPin) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->speedPin = speedPin;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(speedPin, OUTPUT);
  }

  void stop() {
    digitalWrite(speedPin, LOW);
  }

  void forward() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(speedPin, speed);
  }

  void backward() {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(speedPin, speed);
  }

  void setSpeed(byte value) {
    this->speed = value;
    analogWrite(speedPin, value);
  }
};

