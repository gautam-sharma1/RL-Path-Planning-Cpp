//
//  io.hpp
//  effective
//
//  Created by Gautam Sharma on 6/25/20.
//  Copyright © 2020 Gautam Sharma. All rights reserved.
//Input Output File
#ifndef io_hpp
#define io_hpp
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "../include/algorithms.hpp"

class Input{
public:
static std::vector<float> result;
static  std::vector<std::vector<float>> vec;
static void GetFile();
friend class LMS;
};

#endif
