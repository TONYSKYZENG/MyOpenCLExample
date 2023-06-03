#pragma once
#ifndef _READMINIST_HPP_
#define _READMINIST_HPP_
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <TonyFlowLib/MatC20.hpp>
using namespace std;
using namespace TFL;
class ReadMinist {
 private:
  /* data */
 public:
  //from file
  ReadMinist(string fileName);
  uint32_t samples;
  MatC20 <float> trainData;
  vector<uint32_t> label;
  void printData(size_t idx);
  ~ReadMinist() {

  }
};

#endif