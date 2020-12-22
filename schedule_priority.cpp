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
#include "pri_btree.h"

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

    BST ReadyQueue;             //holds PCB in waiting to run
    PCB PTable[MAX_SIZE];       //place all finished PCB here
    int turn_around = 0;        //keeps track of turn around time for scheduler
    int total_turnaround = 0;   //keeps track of total turn around time
    int total_wait = 0;         //keeps track of total wait time
    PCB tmp1;                   //temporary PCB to hold running processes
    string s;//file name
    cout << "Enter a file to open" << endl;
    cin >> s;

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
        ReadyQueue.InsertVertex(myPCB);
        index++;
    }

    // TODO: Add your code to run the scheduler and print out statistics
    while (ReadyQueue.total >= 0)
    {
        if (turn_around == 0)//first element
        {
            tmp1 = ReadyQueue.findNext();
            ReadyQueue.DeleteVertex(tmp1);
            cout << "Running task = ";
            cout << "[" << tmp1.name << "] " << "[" << tmp1.priority << "] " << "[" << tmp1.burst << "] ";
            cout << "for " << tmp1.burst << " units." << endl;
        }
        if (tmp1.burst == 0)//the PCB is done if burst is zero
        {
            tmp1.turnaround_time = turn_around;             //update the turnaround time
            total_turnaround += turn_around;                //update total turn around time 
            total_wait += tmp1.wait_time;                   //update total wait time
            PTable[tmp1.ID] = tmp1;                         //place PCB into PTable
            if (ReadyQueue.total > 0)//checks if the readyqueue is empty or not
            {//there are still some items in queue
                tmp1 = ReadyQueue.findNext();
                ReadyQueue.DeleteVertex(tmp1);
                cout << "Running task = ";
                cout << "[" << tmp1.name << "] " << "[" << tmp1.priority << "] " << "[" << tmp1.burst << "] ";
                cout << "for " << tmp1.burst << " units." << endl;
            }
            else//queue is empty
            {
                break;
            }
        }
        else//PCB is not done yet
        {
            tmp1.burst--;//decrease PCB's burst time by one
            ReadyQueue.increaseWait();//increase wait time for all PCB in ReadyQueue
            turn_around++;//increase turn around time by 1
        }
    }
    //prints all PCB with correct times
    for (int j = 0; j < MAX_SIZE; j++)
    {
        cout << PTable[j].name << " turn-around time = " << PTable[j].turnaround_time << ", ";
        cout << " waiting time = " << PTable[j].wait_time << endl;
    }

    //print averages
    cout << "Average turn-around time = " << total_turnaround / MAX_SIZE << ", ";
    cout << "Average waiting time = " << total_wait / MAX_SIZE << endl;

    return 0;
}
*/