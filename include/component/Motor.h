#pragma once

class Motor {

protected:
  uint8_t pin1;
  uint8_t pin2;

public:
  Motor(uint8_t pin1, uint8_t pin2) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  virtual void stop() = 0;
  virtual void forward() = 0;
  virtual void backward() = 0;

};
