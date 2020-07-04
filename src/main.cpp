//
//  main.cpp
//  effective
//
//  Created by Gautam Sharma on 6/20/20.
//  Copyright © 2020 Gautam Sharma. All rights reserved.
// Welcome to Efficient Reinforcement Learning Toolbox

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "../include/algorithms.hpp"
#include "../include/logic.hpp"
#include "../include/player.hpp"
// #include "../include/io.hpp"

int main(int argc, const char *argv[])
{
    // insert code here...

    // QLearning(int state size, int range of values state can take, int action size vector)
    QLearning q(2, 30, 4);
    q.SetEpsilon(0.99); //A function to set Epsilon
    q.GetEpsilon();     //Print Epsilon to the console
    //q.Show();
    //Player p(20);
    Player::_goal = {13, 13}; //Function to set the goal coordinates of the agent in {int x, int y, int z}. Note: Goal should be within the statespace

    Logic l;      //The brains behind implementation
    l.Run(q, 30); //10 is the same range as above in QLearning q;
}