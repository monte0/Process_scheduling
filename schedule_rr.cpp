/**
 * Driver program
 *
 * Add other data structures and .cpp and .h files as needed.
 *
 * The input file is in the format:
 *
 *  [name], [priority], [CPU burst]
 */
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include "PCB.h"

using namespace std;
const int MAX_SIZE = 8;

int main(int argc, char* argv[])
{
    std::cout << "CS 433 Programming assignment 3" << std::endl;
    std::cout << "Author: xxxxxx and xxxxxxx" << std::endl;
    std::cout << "Date: xx/xx/20xx" << std::endl;
    std::cout << "Course: CS433 (Operating Systems)" << std::endl;
    std::cout << "Description : **** " << std::endl;
    std::cout << "=================================" << std::endl;

    queue<PCB> ReadyQueue;
    PCB PTable[MAX_SIZE];
    PCB tmp1;
    PCB tmp2;
    int turn_around = 0;//keeps track of the turn around time the scheduler is at
    int total_wait = 0;//adds up the wait time for all processes
    int total_turnaround = 0;//adds up the turn around time for all processes
    string s;//file name
    cout << "Enter a file to open" << endl;
    cin >> s;

    int QUANTUM;
    // Read the time quantum if provided.
    cout << "enter a time splice" << endl;
    cin >> QUANTUM;
    
    if (QUANTUM < 1) 
    {
        QUANTUM = 10;
    }
    int rr = QUANTUM;

    // Read task name, priority and burst length from the input file 
    string sname;
    int priority;
    int burst;

    // open the input file

    std::ifstream infile;
    infile.open(s);
    string line;
    if (!infile)
    {
        cout << "Cant open file" << endl;
        exit(1);
    }
    int index = 0;
    while (getline(infile, line)) {
        std::istringstream ss(line);
        // Get the task name
        getline(ss, sname, ',');

        // Get the task priority 
        string token;
        getline(ss, token, ',');
        priority = std::stoi(token);

        // Get the task burst length 
        getline(ss, token, ',');
        burst = std::stoi(token);

        cout << sname << " " << priority << " " << burst << endl;
        // TODO: add the task to the scheduler's ready queue
        // You will need a data structure, i.e. PCB, to represent a task 
        PCB myPCB(sname, priority, burst, ProcState::NEW, index);
        ReadyQueue.push(myPCB);
        index++;
    }

    // TODO: Add your code to run the scheduler and print out statistics
    while (ReadyQueue.size() >= 0)
    {
        if (turn_around == 0)//first element
        {
            tmp1 = ReadyQueue.front();
            ReadyQueue.pop();
            if (tmp1.burst >= QUANTUM)
            {
                cout << "Running task = ";
                cout << "[" << tmp1.name << "] " << "[" << tmp1.priority << "] " << "[" << tmp1.burst << "] ";
                cout << "for " << QUANTUM << " units." << endl;
            }
            else
            {
                cout << "Running task = ";
                cout << "[" << tmp1.name << "] " << "[" << tmp1.priority << "] " << "[" << tmp1.burst << "] ";
                cout << "for " << tmp1.burst << " units." << endl;
            }
        }
        if (tmp1.burst == 0)//the PCB is done if burst is zero, 
        {
            cout << "Task " << tmp1.name << " is finished." << endl;
            tmp1.turnaround_time = turn_around;             //update the turnaround time
            total_turnaround += turn_around;       //update total turn around time 
            total_wait += tmp1.wait_time;                   //update total wait time
            PTable[tmp1.ID] = tmp1;
            if (ReadyQueue.size() > 0)//checks if the readyqueue is empty or not
            {//there are still some items in queue
                QUANTUM = rr;
                tmp1 = ReadyQueue.front();
                ReadyQueue.pop();
                if (tmp1.burst >= QUANTUM)
                {
                    cout << "Running task = ";
                    cout << "[" << tmp1.name << "] " << "[" << tmp1.priority << "] " << "[" << tmp1.burst << "] ";
                    cout << "for " << QUANTUM << " units." << endl;
                }
                else
                {
                    cout << "Running task = ";
                    cout << "[" << tmp1.name << "] " << "[" << tmp1.priority << "] " << "[" << tmp1.burst << "] ";
                    cout << "for " << tmp1.burst << " units." << endl;
                }
            }
            else//queue is empty
            {
                break;
            }
        }
        else if (QUANTUM == 0)//time is up time to switch
        {
            ReadyQueue.push(tmp1);
            tmp1 = ReadyQueue.front();
            ReadyQueue.pop();
            QUANTUM = rr;   //reset time splice
            if (tmp1.burst >= QUANTUM)
            {
                cout << "Running task = ";
                cout << "[" << tmp1.name << "] " << "[" << tmp1.priority << "] " << "[" << tmp1.burst << "] ";
                cout << "for " << QUANTUM << " units." << endl;
            }
            else
            {
                cout << "Running task = ";
                cout << "[" << tmp1.name << "] " << "[" << tmp1.priority << "] " << "[" << tmp1.burst << "] ";
                cout << "for " << tmp1.burst << " units." << endl;
            }
        }
        else//PCB is not done yet
        {
            QUANTUM--;
            tmp1.burst--;//decrease PCB's burst time by one
            for (int i = 0; i < ReadyQueue.size(); i++) //increase wait time for all PCBs in readyqueue by one
            {
                tmp2 = ReadyQueue.front();
                ReadyQueue.pop();
                tmp2.wait_time++;
                ReadyQueue.push(tmp2);
            }
            turn_around++;//increase turn around time by 1
        }
    }

    for (int j = 0; j < MAX_SIZE; j++)
    {
        cout << PTable[j].name << " turn-around time = " << PTable[j].turnaround_time << ", ";
        cout << " waiting time = " << PTable[j].wait_time << endl;
    }

    //print averages
    cout << "Average turn-around time = " << total_turnaround / MAX_SIZE << ", ";
    cout << "Average waiting time = " << total_wait / MAX_SIZE << endl;

    return 0;
}*/