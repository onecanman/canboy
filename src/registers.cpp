#include "registers.h"

bool Registers::checkFlag(FLAGS flag) { return (this->f & flag) != 0; }

void Registers::setFlag(FLAGS flag, bool state) {
  if (state == true) {
    f |= flag;
  } else {
    f &= ~flag;
  }
}
