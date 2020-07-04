//
//  algorithms.hpp
//  effective
//
//  Created by Gautam Sharma on 6/20/20.
//  Copyright © 2020 Gautam Sharma. All rights reserved.
//

#ifndef algorithms_hpp
#define algorithms_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <array>
#include <stdlib.h>
#include "io.hpp"
//#include "logic.hpp"

class QLearning
{

public:
    friend class Logic;
    friend class Player;
    QLearning(const int &s, const int &r, const int &a);
    std::vector<int> IndexFromMulti(int one_dimensional_index, int nn, int depth);
    void QtableLogic(int nn, int depth, int breadth);
    void Show() const;
    float GetEpsilon() const;
    void SetEpsilon(float e);
    int GetRange() const
    {
        return _range;
    }

    // std::vector<float> GetObs() const;

private:
    const int _stateSize;
    const int _actionSize;
    const int _range;
    static int _RANGE;
    std::vector<float> _actionRange;
    std::map<std::vector<int>, std::vector<float>> _q_table;
    bool _init;
    float _EPSILON;
    static double _DISCOUNT;
    const static int _EPISODES = 10;
    static float _EPS_DECAY;
    static double _LEARNING_RATE;
};

/**
 * The following class implemets LMS algorithm
**/
class LMS
{
public:
    LMS(const float &a, const int &w);
    void SetWeights();
    std::vector<float> GetWeights() const;
    void ShowWeights() const;
    void Run(int iter, std::string filename);

private:
    const float _ALPHA;
    const int _WEIGHTS;
    std::vector<float> _weights;
    std::vector<float> _input = {4, 1, 1}; //Random initialization
    float d = 10;                          //Random initialization
};

#endif /* algorithms_hpp */
