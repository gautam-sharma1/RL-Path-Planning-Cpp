//
//  logic.cpp
//  effective
//
//  Created by Gautam Sharma on 6/21/20.
//  Copyright © 2020 Gautam Sharma. All rights reserved.
//
#include <iostream>
#include "../include/logic.hpp"
#include <algorithm>
#include <functional>
#include <opencv2/core.hpp>

#include <opencv2/highgui.hpp>

#include <opencv2/videoio.hpp>

#include <opencv2/objdetect.hpp>

#include <opencv2/imgproc.hpp>

/**
 * Main function that runs Q-Learning
 * @param q A Q-learning object instantiated in main.cpp
 * @param r Range of values that the agent can take. For example if range = 10, then the agent can take uniform integral values from [-5,5) 
 */
using namespace cv; //For using OpenCV to simulate agent's motion

void Logic::Run(QLearning &q, const int &r)
{

    //int k = erl::QLearning::_EPISODES;

    for (int i = 0; i < 5000; i++)
    {
        Player p(r);
        double episode_reward = 0;
        std::vector<int> player_pos;

        for (int j = 0; j < 200; j++)
        {
            player_pos = {p.x, p.y};
            //std::cout << "Previous position " << p.x << " " << p.y << std::endl;
            // std::transform(player_pos.begin(),player_pos.end(),(p.GetGoal()).begin(), std::back_inserter(_observations),std::minus<int>()); //to be completed
            for (int i = 0; i < 2; i++)
            {
                _observations[i] = player_pos.at(i) - Player::_goal.at(i);
            }
            //std::cout<<"Observation<<"<<_observations[0]<< " "<<_observations[1]<<" " <<_observations[2]<<std::endl;
            //
            srand((unsigned)time(NULL));
            //std::cout<<q.GetEpsilon()<<std::endl;

            if (((double)rand() / (RAND_MAX)) > q.GetEpsilon())
            {
                //std::cout<<((double) rand() / (RAND_MAX)) <<std::endl;
                std::vector<float> vec = q._q_table[_observations];
                _action = arg_max(vec);
                //std::cout<<"action selected is "<<_action<<std::endl;
            }
            else
            {
                _action = (int)rand() % (q._actionSize) + 0;
                //std::cout<<"action selected is "<<_action<<std::endl;
                //std::cout<<"exit "<<((double) rand() / (RAND_MAX))<<std::endl;
            }
            player_pos = p.action(_action);
            //Play around with the reward function                                                //Player takes action in this stage
            double reward = 1 / ((player_pos.at(0) -  Player::_goal.at(0)) + (player_pos.at(1) -  Player::_goal.at(1)) + 0.001); //Assuming we had a vector with 2 states
            //std::cout<<reward<<std::endl;

            //std::cout << "New position " << player_pos.at(0) << " " << player_pos.at(1) << std::endl;

            if (player_pos.at(0) ==  Player::_goal.at(0) && player_pos.at(1) ==  Player::_goal.at(1))
            {
                std::cout << "Goal reached" << std::endl;
                break;
            }

            std::vector<int> new_obs;
            std::transform(player_pos.begin(), player_pos.end(), (Player::_goal).begin(), std::back_inserter(new_obs), std::minus<int>());
            //std::cout << "New Observation<<" << new_obs[0] << " " << new_obs[1] << " " << std::endl;

            std::vector<float> max_future;
            try
            {
                max_future = q._q_table[new_obs];
            }
            catch (const std::exception &er)
            {
                std::cout << "Error caught" << er.what() << std::endl;
            }
            std::vector<float>::iterator max_future_q;
            try
            {                                                                             //get all qvalues corresponding next best state
                max_future_q = max_element(std::begin(max_future), std::end(max_future)); // c++11
            }
            catch (const std::exception &er)
            {
                std::cout << "Error caught" << er.what() << std::endl;
            }
            //std::cout << "Observation<<" << _observations[0] << " " << _observations[1] << std::endl;
            //std::cout << "Action<<" << _action << std::endl;
            //std::cout<<q._q_table[_observations][_action]<<std::endl;
            float current_q;
            try
            {
                float current_q = q._q_table[_observations][_action];
            } //get the best qvalue corresponding next best state
            catch (const std::exception &er)
            {
                std::cout << "Error caught" << er.what() << std::endl;
            }
            //std::cout<<current_q<<std::endl;
            float new_q;
            try
            {
                float new_q = (1 - QLearning::_LEARNING_RATE) * current_q + QLearning::_LEARNING_RATE * (reward + QLearning::_DISCOUNT * (*max_future_q));
            }
            catch (const std::exception &er)
            {
                std::cout << "Error caught" << er.what() << std::endl;
            }

            try
            {
                q._q_table[_observations][_action] = new_q;
            }
            catch (const std::exception &er)
            {
                std::cout << "Error caught" << er.what() << std::endl;
            }
            episode_reward += reward;

            //
            //
            //
            //
        }

        float ep = q.GetEpsilon();
        std::cout << "#----------------------" << i << " Episode Reward: " << episode_reward << std::endl;
        q.SetEpsilon(ep * (QLearning::_EPS_DECAY)); //Epsilon Decay;
        //     // Read the image file

        Mat Picture(320, 240, CV_8UC3, cv::Scalar(0, 0, 0));
        // Check for failure
        if (Picture.empty())
        {
            std::cout << "Could not instantiate the image" << std::endl;
            std::cin.get(); //wait for any key press
        }

        resize(Picture, Picture, Size(500, 500));

        //A Parameters x (start in x axes horizontal) y (start in vertical)

        // w (vertical lenght)  h (Horizontal lenght)

        //Rect RectangleToDraw(2, 2, 100, 100);
        //Scaling by 20
        circle(Picture, Point(Player::_goal.at(0)*20, Player::_goal.at(1)*20), 20, Scalar(0, 255, 0), 2, 8, 0);

        Point p1 = Point(20 * p.x, 20 * p.y);
        circle(Picture, p1, 20, Scalar(255, 0, 255), -2, 8, 0);

        imshow("Path planner Reinforcement-Learning", Picture);
        waitKey(10);
        destroyWindow("Path planner Reinforcement-Learning");
    }
}
