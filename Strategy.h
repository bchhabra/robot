#pragma once

class Strategy {
  public:
    void init();
    void run(void (*f)());
};

