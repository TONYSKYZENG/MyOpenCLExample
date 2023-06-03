#pragma once
#ifndef _ABSTRACTTFLUNIT_HPP_
#define _ABSTRACTTFLUNIT_HPP_
#include <CLContainer.hpp>
#include <vector>
namespace TFL {
typedef enum {
  TFLDefault = 0,
  TFLGPU = 1,
  TFLFPGA,
  TFLDSP
} TFLDeviceType;
template<class InputTypeT, class OutputTypeT>
class AbstractTFLUnit {
 private:
  /* data */
 protected:
  InputTypeT gInput;
  OutputTypeT gOutput;
 public:
  AbstractTFLUnit(/* args */);
  ~AbstractTFLUnit();
  virtual void eval(InputTypeT mInput) {
    gInput = mInput;
  }
};

}

#endif