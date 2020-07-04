//
//  player.cpp
//  effective
//
//  Created by Gautam Sharma on 6/21/20.
//  Copyright © 2020 Gautam Sharma. All rights reserved.
//

#include "../include/player.hpp"

//Default position if nothing is entered by the user
std::vector<int> Player::_goal = {5, 5};

/**
 * Default constructor of Player object
 * @param range Range of values that the agent can take. For example if range = 10, then the agent can take uniform integral values from [-5,5)
 **/
Player::Player(int range)
{

    _RANGE = (range / 2);
    //std::cout<<"Range is: "<<_RANGE;
    //After each epoch the player is set randomly by calling its constructor in the range [0,max_allowed_value)
    this->x = rand() % (_RANGE - 1) + 0;
    this->y = rand() % (_RANGE - 1) + 0;
    //this->z = rand() % (_RANGE - 1) + 0;
}

/**
 * Returns the position of the agent after taking a particular action
 * @param a dx
 * @param b dy 
 * @return vector of update position
 **/
std::vector<int> Player::move(int a, int b)
{
    std::vector<int> vec;

    this->x += a;
    //std::cout << "x is " << this->x;

    this->y += b;
    //std::cout << " y is " << this->y<<std::endl;

    // this->z += c;
    //  std::cout<<" z is "<<this->z<<std::endl;

    if (this->x < 0)
    {
        this->x = 0;
    }
    else if (this->x > (_RANGE - 1))
    {
        this->x = _RANGE - 1; //Looks good
    }
    if (this->y < 0)
    {
        this->y = 0;
    }
    else if (this->y > (_RANGE - 1))
    {
        this->y = _RANGE - 1;
    }
    /**
    if (this->z < 0)
    {
        this->z = 0;
    }
    else if (this->z > (_RANGE - 1))
    {
        this->z = _RANGE - 1;
    }
    std::cout<<" x is "<<this->x;
    std::cout<<" y is "<<this->y;
    std::cout<<" z is "<<this->z<<std::endl;
    **/
    vec = {this->x, this->y};
    return vec;
}

/**
 * Returns the position of the agent after taking a particular action
 * @param choice //Connected to the Player::move(int a, int b) function.
 * @return vector of update position to Player::move(int a, int b)
 */
std::vector<int> Player::action(int choice)
{
    std::vector<int> vec1;
    if (choice == 0)
    {
        vec1 = this->move(1, 0);
    }
    else if (choice == 1)
    {
        vec1 = this->move(-1, 0);
    }
    else if (choice == 2)
    {
        vec1 = this->move(0, 1);
    }
    else if (choice == 3)
    {
        vec1 = this->move(0, -1);
    }
    else
    {
        vec1 = this->move(0, 0);
    }
    /**
    else if (choice == 4)
    {
        vec1 = this->move(0, 0, 1);
    }
    else if (choice == 5)
    {
        vec1 = this->move(0, 0, -1); //Looks good
     }
     **/
    return vec1;
}

/**
 * Prints the current position of the agent after taking a particular action
 * @return void. Prints the current position of the player.
 **/

void Player::print() const
{

    std::cout << this->x << this->y << std::endl;
}

//std::vector<int> Player::GetGoal() const
//   {
//       return this->_goal;
//   }
