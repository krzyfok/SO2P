#include<iostream>
#include <thread>
#include<mutex>
#include<vector>
#include <stdlib.h> 
using namespace std;

#define n 10
vector<thread> ThreadVector;
mutex mtx;
vector<int> status(n,2);

void dining(int id)
{
    while (true)
    {
        {
            this_thread::sleep_for(chrono::milliseconds(500));
            lock_guard<mutex> lock(mtx);
            lock_guard<mutex> unlock(mtx);
           
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    
    
}

int main()
{
    
   for(int i=0;i<n;i++)
   {
    ThreadVector.emplace_back(dining,i);
   }

   
   while (true)
    {
        system("cls");
       
        for (int i = 0; i < n; i++) {
            if (status[i] == 0) {
                cout << "PHILOSOPHER: " << i << " IS EATING" << endl;
            } else if (status[i] == 1) {
                cout << "PHILOSOPHER: " << i << " IS HUNGRY" << endl;
            } else {
                cout << "PHILOSOPHER: " << i << " IS THINKING" << endl;
            }
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