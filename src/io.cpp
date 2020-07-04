//
//  io.cpp
//  effective
//
//  Created by Gautam Sharma on 6/25/20.
//  Copyright © 2020 Gautam Sharma. All rights reserved.
//
#include "../include/io.hpp"



void Input::GetFile(){
    std::ifstream MyReadFile(("/Users/gautamsharma/Desktop/effective-RL/effective/input.txt"));
    
    std::cout << "Reading from the file" << std::endl;
    std::string myText;
    float x,y,z,d;
    char i,j,k;
    while (getline (MyReadFile, myText)){
    std::istringstream(myText) >>x>>i>>y>>j>>z>>k>>d;
    Input::vec.push_back({x,y,z});   
    Input::result.push_back(d);       
    }
}
