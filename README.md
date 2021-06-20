# Self written Containers equivalent to the C++ Standard Template Library (STL) Containers
Self written stack and Queue equivalent to the stack and queue in the C++ STL Library. I added some examples to show how to use the Stack in main.cpp. Extra Containers might come in the future. 
## Container's APIs
- Both Containers Stack and Queue are overloaded with ostream operator. But then their contents are popped. The containers allocate and deallocate memory depending on the current elements number in the container. 
- The user can see how much memory is allocated by calling the method dynamic(). The returned number * the size of one element = the total allocated memory. See the function memory_test() in main.cpp for further info about the method dynamic().
## Memory management
Both containers Stack and Queue apply memory reallocation to resize the container size. The allocated memory has more than the maximum current size by max 100 * sizeof(one element). For example, a Stack container of data type int has 100 elments, then by pushing the next element to the container, the heap memory of the container is reallocated to fit the size of 200 int.
## Workflow
- Open the terminal and download the repogit 
```
git clone https://github.com/Abdsaddik/Self-written-STL-Containers.git
```  
- Compile the code and generate the binary file as follows:
```
g++ -std=c++11 -Wall main.cpp -o Container
```
- Run the code as follows:
```
./Container
```

## Teriminal Output
The current terminal output of this software is:
```

Testing of Queue APIs
create a con "my_con" of 10 elments ...
size of my_con: 10
create copy con "cp" from my_con
print the contents of cp
1  2  3  4  5  6  7  8  9  10
print the contents of my_con
1  2  3  4  5  6  7  8  9  10
size of my_con: 0
size of cp: 0
print the contents of con_1, con_1 should be empty now
Queue is empty!
print the contents of queue_1 again
19  29
print the contents of queue_2
19  29
create a new queue queue_3
create a new queue queue_4
size of con_3: 3
size of con_4: 6
swapping con_3 with con_4
size of con_3: 6
size of con_4: 3
print con_3
4  5  6  7  8  9
print con_4
1  2  3

***********************************************************

Testing of Stack APIs
create a con "my_con" of 10 elments ...
size of my_con: 10
create copy con "cp" from my_con
print the contents of cp
10  9  8  7  6  5  4  3  2  1
print the contents of my_con
10  9  8  7  6  5  4  3  2  1
size of my_con: 0
size of cp: 0
print the contents of con_1, con_1 should be empty now
Stack is empty!
print the contents of queue_1 again
29  19
print the contents of queue_2
29  19  
create a new queue queue_3
create a new queue queue_4
size of con_3: 3
size of con_4: 6
swapping con_3 with con_4
size of con_3: 6
size of con_4: 3
print con_3
9  8  7  6  5  4
print con_4
3  2  1
program is closed correctly
```
