//
//  algorithms.cpp
//  effective
//
//  Created by Gautam Sharma on 6/20/20.
//  Copyright © 2020 Gautam Sharma. All rights reserved.
//

#include "../include/algorithms.hpp"
#include "../include/io.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <math.h>
#include <sstream>
#include <fstream>

static std::vector<float> result;
static std::vector<std::vector<float>> vec;

//Constructor

QLearning::QLearning(const int &s, const int &r, const int &a) : _stateSize(s), _range(r), _actionSize(a + 1)
{
    try
    {
        if (s > 0 && a > 0)
        {
            std::cout << "Constructor call successful" << std::endl;
            QtableLogic(_range, _stateSize, _actionSize);
            std::cout << "Q table generated successfully successful" << std::endl;
            _init = true;
        }
        else
        {
            throw 69;
        }
    }
    catch (...)
    {
        std::cerr << "State or action size is 0" << std::endl;
    }
}

//Function to convert 1D array indices to multi-array indices
/**
 * Returns multiarray indices
 *
 * @param one_dimensional_index  1D index that is converted to multiD index
 * @param nn  one_dimensional_index   Indicated the range of value the states can take. For example nn=20 means state can take values form -10 to 10
 * @param depth number of states
 * @return multi array index
 */
std::vector<int> QLearning::IndexFromMulti(int one_dimensional_index, int nn, int depth)
{
    std::vector<int> index(depth, 0);
    for (int i = 0; i < depth; i++)
    {
        index[i] = (one_dimensional_index % nn);
        one_dimensional_index /= nn;
    }
    return index;
}

//Main function that constructs the Qtable
/**
 * Returns multiarray indices
 *
 * @param nn one_dimensional_index   Indicated the range of value the states can take. For example nn=20 means state can take values form -10 to 10
 * @param depth number of states
 * @param breadth number of action variables
 * 
 */
void QLearning::QtableLogic(int nn, int depth, int breadth)
{

    if (nn == 0)
    {
        std::cerr << "size cannot be 0" << std::endl;
    }

    float size = nn / 2;
    int max_index = pow(nn, depth);

    for (int i = 0; i < max_index; i++)
    {
        std::vector<int> key = IndexFromMulti(i, nn, depth);
        //change the interval [0,nn) to the interval [-size,size).
        for (int j = 0; j < depth; j++)
            key[j] -= size;

        //Fill in the value
        std::vector<float> value(breadth, 0);
        for (int j = 0; j < breadth; j++)
            value[j] = (rand() % 5) + 1;

        this->_q_table[key] = value;
    }
    //return q_table;
}

//Function to print with pretty formatting

/**
 * Function to print with pretty formatting
 *
 *
 *
 */
void QLearning::Show() const
{
    if (_init)
    {
        std::cout << "qtable populated with: " << std::endl;
        for (auto iter = this->_q_table.begin(); iter != this->_q_table.end(); ++iter)
        {
            std::cout << "qtable[{";
            for (size_t i = 0; i < iter->first.size(); i++)
            {
                std::cout << iter->first[i];
                if (i != iter->first.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "}]=[";
            for (size_t i = 0; i < iter->second.size(); i++)
            {
                std::cout << iter->second[i];
                if (i != iter->second.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "];" << std::endl;
        }
    }
    else
    {
        std::cerr << "Qtable not initialised" << std::endl;
    }
}

//std::vector<float> erl::QLearning::GetObs() const{
//    return this->_observations;
//}

//
/**
 * Returns multiarray indices
 * @return Epsilon
 */
float QLearning::GetEpsilon() const
{
    return _EPSILON;
}

/**
 * Returns multiarray indices
 *
 * @param e new epsilon to be set
 * 
 */
void QLearning::SetEpsilon(float e)
{
    this->_EPSILON = e;
    std::cout << "EPSILON set to " << this->_EPSILON << std::endl;
}

double QLearning::_DISCOUNT = 0.9;
float QLearning::_EPS_DECAY = 0.99;
double QLearning::_LEARNING_RATE = 0.01;

//---------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------//

LMS::LMS(const float &a, const int &w) : _ALPHA(a), _WEIGHTS(w)
{
    std::cout << "LMS algorithm initiated" << std::endl;
}

void LMS::SetWeights()
{
    srand((unsigned)time(NULL));
    _weights = std::vector<float>(_WEIGHTS, 0);
}

std::vector<float> LMS::GetWeights() const
{
    return _weights;
}

void LMS::ShowWeights() const
{
    for (auto &v : _weights)
    {
        std::cout << v << " ";
    }
}

void LMS::Run(int iter, std::string filename)
{
    std::ifstream MyReadFile(filename);

    std::vector<float> parameters(_WEIGHTS, 0);
    std::vector<std::string> commas(_WEIGHTS, " ");
    std::cout << "Reading from the file" << std::endl;
    std::string myText;
    //Number of input variables x,y,z should match with number of char variables i,j,k
    //float x, y, z, d; //Change according to the number of input variables
    //char i, j, k;     //Change according to the number of input variables
    while (getline(MyReadFile, myText))
    {
        std::istringstream ss(myText);
        //std::cout<<myText.length()<<myText.size()<<std::endl;
        std::vector<float> temp;
        int counter = 0;
        for (auto i = 0; i < 2 * _WEIGHTS + 1; ++i)
        {
            if (i == 2 * _WEIGHTS)
            {
                float d;
                ss >> d;
                result.push_back(d);
                break;
            }
            else if (i % 2 == 0)
            {
                float x;
                ss >> x;
                temp.push_back(x);
                counter++;
            }
            else if (i % 2 == 1)
            {
                char c;
                ss >> c;
            }
        }
        //std::istringstream(myText) >> x >> i >> y >> j >> z >> k >> d;
        //vec.push_back({x, y, z});
        vec.push_back(temp);
        //result.push_back(parameters.at(*(parameters.end()-1)));
        //result.push_back(d);
    }
    for (auto v : result)
    {
        std::cout << v << std::endl;
    }

    for (int k = 0; k < iter; k++)
    {
        double error;
        for (int i = 0; i < result.size(); ++i)
        {

            double sum = 0;
            for (int j = 0; j < _WEIGHTS; ++j)
            {
                sum += _weights.at(j) * vec[i][j];
            }
            error = result[i] - sum;
            for (int j = 0; j < _WEIGHTS; ++j)
            {
                _weights.at(j) = _weights.at(j) + _ALPHA * vec[i][j] * error;
            }
        }
        if (k % 1000 == 0)
        {
            std::cout << "#Iteration:" << k << ", Error :" << error << std::endl;
        }
    }
}
