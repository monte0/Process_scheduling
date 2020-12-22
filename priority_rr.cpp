/**
 * Driver program
 *
 * Add other data structures and .cpp and .h files as needed.
 *
 * The input file is in the format:
 *
 *  [name], [priority], [CPU burst]
 */
 
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
 void printRunning(PCB p, BST &tree, int time);

 int main(int argc, char* argv[])
 {
     std::cout << "CS 433 Programming assignment 3" << std::endl;
     std::cout << "Author: xxxxxx and xxxxxxx" << std::endl;
     std::cout << "Date: xx/xx/20xx" << std::endl;
     std::cout << "Course: CS433 (Operating Systems)" << std::endl;
     std::cout << "Description : **** " << std::endl;
     std::cout << "=================================" << std::endl;

     BST ReadyQueue;                //store processes that are waiting here
     PCB PTable[MAX_SIZE];          //store finished processes in table 
     int turn_around = 0;           //keeps track of turn around time for scheduler
     int total_turnaround = 0;      //keeps track of total turn around time
     int total_wait = 0;            //keeps track of total wait time
     PCB tmp1;                      //temporary PCB to hold running processes

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
     int rr = QUANTUM;//rr keeps track of the user entered quantum, since quantum will be reduced later

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
     int index = 0;             //give each process an id, so it can be stored in table later
     while (getline(infile, line))
     {
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
             printRunning(tmp1, ReadyQueue, QUANTUM);
         }//end of first getting first element
         if (tmp1.priority == ReadyQueue.findNext().priority)// check if there are multiple tasks with same priority
         {
             if (tmp1.burst == 0)
             {//task ended
                 cout << "Task " << tmp1.name << " is finished." << endl;
                 tmp1.turnaround_time = turn_around;            //update the task's turnaround time
                 total_turnaround += turn_around;               //update total turn around time 
                 total_wait += tmp1.wait_time;                  //update total wait time
                 PTable[tmp1.ID] = tmp1;                        //add task to Table
                 if (ReadyQueue.total > 0)//checks if the readyqueue is empty or not
                 {//there are still some items in queue
                     QUANTUM = rr;                  //reset the quantum
                     tmp1 = ReadyQueue.findNext();  //get next task
                     ReadyQueue.DeleteVertex(tmp1);
                     printRunning(tmp1, ReadyQueue, QUANTUM);
                 }
                 else//queue is empty, nothing more to get
                 {
                     break;
                 }
             }
             else if (QUANTUM == 0)//time is up, time to switch
             {
                 ReadyQueue.InsertVertex(tmp1); //insert task back to readyqueue
                 tmp1 = ReadyQueue.findNext();  //get next task
                 ReadyQueue.DeleteVertex(tmp1);
                 QUANTUM = rr;                  //reset time quantum
                 printRunning(tmp1, ReadyQueue, QUANTUM);
             }
             else//task is running 
             {
                 QUANTUM--;                     //decrease time quantum
                 tmp1.burst--;                  //decrease PCB's burst time by one
                 ReadyQueue.increaseWait();     //increase wait time for all tasks in readyqueue
                 turn_around++;                 //increase turn around time by 1
             }
         }
         else//the task doesnt share a priority
         {
             if (tmp1.burst == 0)//the task is done if burst is zero
             {
                 cout << "Task " << tmp1.name << " is finished." << endl;
                 tmp1.turnaround_time = turn_around;            //update the task's turnaround time
                 total_turnaround += turn_around;               //update total turn around time
                 total_wait += tmp1.wait_time;                  //update total wait time
                 PTable[tmp1.ID] = tmp1;
                 if (ReadyQueue.total > 0)//checks if the readyqueue is empty or not
                 {//there are still some items in queue
                     tmp1 = ReadyQueue.findNext();
                     ReadyQueue.DeleteVertex(tmp1);
                     printRunning(tmp1, ReadyQueue, QUANTUM);
                 }
                 else//queue is empty
                 {
                     break;
                 }
             }
             else//PCB is not done yet
             {
                 tmp1.burst--;//decrease PCB's burst time by one
                 ReadyQueue.increaseWait();//increase wait time
                 turn_around++;//increase turn around time by 1
             }
         }//end of solo process 
     }//end of while

     for (int j = 0; j < MAX_SIZE; j++)//prints table with each task's stats
     {
         cout << PTable[j].name << " turn-around time = " << PTable[j].turnaround_time << ", ";
         cout << " waiting time = " << PTable[j].wait_time << endl;
     }

     //print averages
     cout << "Average turn-around time = " << total_turnaround / MAX_SIZE << ", ";
     cout << "Average waiting time = " << total_wait / MAX_SIZE << endl;

     return 0;
 }
 //this function prints how long the task will be running for
 //if the task shares a priority and the burst time remaining is
 //more than the quantum, then it runs for quantum units
 //else it prints its remaining burst
 void printRunning(PCB p, BST &tree, int time)
 {
     if (p.priority == tree.findNext().priority && p.burst >= time)
     {
         cout << "Running task = ";
         cout << "[" << p.name << "] " << "[" << p.priority << "] " << "[" << p.burst << "] ";
         cout << "for " << time << " units." << endl;
     }
     else//no duplicates, or it has a burst that is less than thee QUANTUM
     {
         cout << "Running task = ";
         cout << "[" << p.name << "] " << "[" << p.priority << "] " << "[" << p.burst << "] ";
         cout << "for " << p.burst << " units." << endl;
     }
 }