//
//  logic.hpp
//  effective
//
//  Created by Gautam Sharma on 6/21/20.
//  Copyright © 2020 Gautam Sharma. All rights reserved.
//

#ifndef logic_hpp
#define logic_hpp

#include <stdio.h>
#include "algorithms.hpp"
#include "player.hpp"
#include <stdlib.h>

struct Logic
{

public:
  void Run(QLearning &q, const int &r);
  template <typename T, typename A>
  int arg_max(std::vector<T, A> const &vec)
  {
    return static_cast<int>(std::distance(vec.begin(), max_element(vec.begin(), vec.end())));
  }

private:
  const float _RAND_MAX = 1;
  int _action;
  std::vector<int> _observations = {0, 0};
};

#endif /* logic_hpp */
