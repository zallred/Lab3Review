//
// Created by Zach Allred on 1/18/24.
//

#define CATCH_CONFIG_RUNNER
#include "cmdline.h"
#include <iostream>
//Function to take in arguments from command line
//Operations depend on arguments taken in.
//Parameters: argc and argv from main

void use_arguments(int argc, char **argv){
    bool testTracker = false;
    for(int i=1; i <argc; i++){
        //if value is --help, print the command list
        if(strcmp(argv[i], "--help") == 0){
            std::cout << "Available Commands are:\n" << "--help: Get commands list\n" << "--test: Check if tests pass\n";
            exit(0);
        }
            //if value is test, run test routine.
            //if tests already ran, print already sent.
        else if(strcmp(argv[i], "--test") == 0){
            if(!testTracker){
                if(Catch::Session().run(1, argv)!=0){
                    exit(1);
                }
                testTracker = true;
            }
            else {
                std::cerr << "Already sent --test\n";
                exit(1);
            }
        }

            //If neither of the two above options, its invalid.
        else{
            std::cerr << "Invalid Argument\n";
            exit(1);
        }
    }
    return;
}
