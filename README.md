Chat Server and Dining Philosophers 🖥️🍽️

This repository contains two separate projects:

1.  Chat Server 💬 – a multithreaded TCP client-server chat application.
    
2.  Dining Philosophers 🍴 – a simulation of the classical Dining Philosophers problem using threads.
    

* * *

Chat Server 💬

How to Run ▶️:  
g++ Server.cpp -o Server -lws2\_32  
g++ Client.cpp -o Client -lws2\_32  
./Server  
./Client

Problem Description ℹ️:  
A simple Client-Server chat using TCP sockets. It allows multiple clients to communicate simultaneously using multithreading and synchronization of shared resources.

Threads 🧵:

-   Server main thread 🖥️: listens for incoming connections and creates new threads for clients.
    
-   Client thread (per connection) 👤: handles communication with a single client.
    
-   Client listening thread 👂: receives data from the server.
    
-   Client main thread ✍️: sends data to the server.
    

Critical Sections 🔒:

-   Reading chat history 📖
    
-   Adding messages to chat history ✉️
    
-   Sending messages to clients 📤
    
-   Adding clients ➕
    
-   Removing clients ❌
    

Deadlock Avoidance ✅:  
Each critical section uses only a single mutex; no waiting for multiple resources occurs.

* * *

Dining Philosophers Problem 🍴

How to Run ▶️:  
g++ main.cpp -o projekt  
./projekt (number\_of\_philosophers)

Problem Description ℹ️:  
Simulation of the classical Dining Philosophers problem, where philosophers need access to shared resources (forks) to eat while avoiding deadlocks.

Threads 🧵:

-   Each philosopher is a separate thread that cycles through:
    
    1.  Thinking 🤔
        
    2.  Becoming hungry 😋
        
    3.  Trying to eat 🍽️
        

Critical Sections 🔒:

-   Accessing forks 🍴: synchronized using mutex and condition\_variable to ensure neighbors do not eat simultaneously.
    
-   condition\_variable prevents philosophers from busy-waiting; they are notified when forks become available 🔔.
    

Deadlock Avoidance ✅:  
A philosopher waits until both forks are available before picking them up. After eating, the philosopher notifies neighbors that the forks have been released 📢.
