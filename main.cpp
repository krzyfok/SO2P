#include<iostream>
#include <thread>
#include<mutex>
#include<vector>
#include <stdlib.h> 
using namespace std;

#define n 10
vector<thread> ThreadVector;
mutex mtx;
vector<int> status;

void dining(int id)
{
    while (true)
    {
        {
            lock_guard<mutex> lock(mtx);
            status[id]++;
            //cout << "PHILOSOPHER: " << id << " IS THINKING" << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    
    
}

int main()
{
    for(int i=0;i<n;i++)
   {
    status.push_back(i);
   }
   for(int i=0;i<n;i++)
   {
    ThreadVector.emplace_back(dining,i);
   }

   
   while (true)
    {
        system("cls");
       
        for(int i=0;i<n;i++){
        cout << "PHILOSOPHER: " << status[i] << " IS THINKING" << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }
   for (auto &th : ThreadVector) {
    if (th.joinable()) {
        th.join();
    }
    }
    
    
    return 0;
}