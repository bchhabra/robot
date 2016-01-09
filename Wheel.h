class Wheel {
  byte pin1;
  byte pin2;
public:
  Wheel(byte pin1, byte pin2) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }

  void forward() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  }

  void backward() {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
};
