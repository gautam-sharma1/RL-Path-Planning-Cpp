//
//  player.hpp
//  effective
//
//  Created by Gautam Sharma on 6/21/20.
//  Copyright © 2020 Gautam Sharma. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "algorithms.hpp"

class Player
{

    friend class Logic;

public:
    static std::vector<int> _goal;
    //void static SetGoal(std::vector<int> vec);
    int x;
    int y;
    int z;
    Player(int range);

    std::vector<int> GetGoal() const;
    //std::vector<int> SetGoal();

    std::vector<int> action(int choice);

    void print() const;

    //This function defines the dynamics of the system. Feel free to modify based on your problem

    std::vector<int> move(int a, int b);

private:
    int _RANGE;
};

//std::vector<int> Player::_goal{2,2,2};

#endif /* player_hpp */
