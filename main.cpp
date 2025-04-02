#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <cstdlib>

using namespace std;

vector<thread> ThreadVector;
mutex mtx;
vector<condition_variable> varPhi;
vector<int> status;
int num_philosophers;

void dining(int id)
{
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
        {
            unique_lock<mutex> lock(mtx);
            status[id] = 1;

            while (status[(id + 1) % num_philosophers] == 0 || status[(id + num_philosophers - 1) % num_philosophers] == 0)
            {
                varPhi[id].wait(lock);
            }

            status[id] = 0;
        }

        this_thread::sleep_for(chrono::milliseconds(1000));
        {
            lock_guard<mutex> lock(mtx);
            status[id] = 2;

            varPhi[(id + 1) % num_philosophers].notify_one();
            varPhi[(id + num_philosophers - 1) % num_philosophers].notify_one();
        }
    }
}

int main(int argc, char* argv[])
{
    

    num_philosophers = atoi(argv[1]);
    

    status.resize(num_philosophers, 2);
    varPhi = vector<condition_variable>(num_philosophers);

    for (int i = 0; i < num_philosophers; i++)
    {
        ThreadVector.emplace_back(dining, i);
    }

    while (true)
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        for (int i = 0; i < num_philosophers; i++)
        {
            if (status[i] == 0)
            {
                cout << "PHILOSOPHER: " << i << " IS EATING" << endl;
            }
            else if (status[i] == 1)
            {
                cout << "PHILOSOPHER: " << i << " IS HUNGRY" << endl;
            }
            else
            {
                cout << "PHILOSOPHER: " << i << " IS THINKING" << endl;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    for (auto &th : ThreadVector)
    {
        if (th.joinable())
        {
            th.join();
        }
    }

    return 0;
}
