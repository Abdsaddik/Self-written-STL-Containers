#include"Stack.hpp"
#include"Queue.hpp"

template<typename T>
void message(T str){
    cout << str << endl;
}

template<typename T1, typename T2>
void message(T1 key, T2 val){
    cout << key << ": " << val << endl;
}

template<typename T>
void fill(T& container, int size){
    for(int cnt=0; cnt<size; cnt++) container.push(cnt+1);  
}

template<typename T>
void test_container(T& con){
    message("create a con \"my_con\" of 10 elments ...");
    fill(con, 10);
    message("size of my_con", con.size());
    message("create copy con \"cp\" from my_con");
    T cp = con;
    message("print the contents of cp");
    cout << cp;
    cout << "print the contents of my_con\n";
    cout << con;
    message("size of my_con", con.size());
    message("size of cp", cp.size());
    T con_1;        
    con_1.push(19);
    con_1.push(29);
    // call move constructor
    T con_2 = std::move(con_1);
    message("print the contents of con_1, con_1 should be empty now");
    cout << con_1;
    // call assignment operator
    con_1 = con_2;
    message("print the contents of queue_1 again");
    cout << con_1;
    message("print the contents of queue_2");
    cout << con_2;
    message("create a new queue queue_3");
    T con_3;
    con_3.push(1); 
    con_3.push(2); 
    con_3.push(3);
    message("create a new queue queue_4");
    T con_4;
    con_4.push(4); 
    con_4.push(5); 
    con_4.push(6);
    con_4.push(7); 
    con_4.push(8); 
    con_4.push(9);
    message("size of con_3", con_3.size());
    message("size of con_4", con_4.size());
    message("swapping con_3 with con_4");
    con_3.swap(con_4);
    message("size of con_3", con_3.size());
    message("size of con_4", con_4.size());
    message("print con_3");
    cout << con_3;
    message("print con_4");
    cout << con_4;
}
template<typename T>
void memory_test(T& Contnr){
    message("push contents into the container ...");
    for(auto cnt=0; cnt<5; cnt++){
        message("heap memory", Contnr.dynamic());
        message("Container size", Contnr.size());
        fill(Contnr, 100);
    }
    message("heap memory", Contnr.dynamic());
    message("Container size", Contnr.size());

    message("popping contents from the container ...");
    for(auto cnt=0; cnt<5; cnt++){
        for(int cnt=0;cnt<100;cnt++) Contnr.pop();
        message("heap memory", Contnr.dynamic());
        message("Container size", Contnr.size());
    }
}

void demo_memory(){
    Queue<int> queue_1;
    message("Showing Queue Memory Allocation");
    memory_test(queue_1);
    message("***********************************************************");
    Stack<int> stack_1;
    message("Showing Stack Memory Allocation");
    memory_test(stack_1);
    message("************************************************************");
}

int main(){  
    try{
        // uncomment to show how memory is allocated
        // demo_memory();
        Queue<int> queue_1;
        Stack<int> stack_1;
        message("\nTesting of Queue APIs");
        test_container(queue_1);
        message("\n***********************************************************\n");
        message("Testing of Stack APIs");
        test_container(stack_1);
    }

    catch(Exception& e){cout << e.what() << endl;}
    catch(std::bad_alloc& e){cout << e.what() << endl;}
    cout << "program is closed correctly\n";
    return 0;
}
