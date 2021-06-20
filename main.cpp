
#include"Stack.hpp"
using namespace std;

template<typename T>
void message(T str){
    cout << str << endl;
}

template<typename T1, typename T2>
void message(T1 key, T2 val){
    cout << key << ": " << val << endl;
}

template<typename T>
void print(Stack<T>& my_stack){
    if(my_stack.empty()) {
        message("stack is empty!");
        return;
        }
    while (my_stack.size())
    {   
        cout << my_stack.top() << "  ";
        my_stack.pop();
    }
    cout << endl;
    
}

template<typename T>
void fill(Stack<T>& my_stack, int size){
    for(int cnt=0; cnt<size; cnt++) my_stack.push(cnt+1);  
}

int main(){
        // create Stac object
        Stack<int> my_stack;    
        try{
        message("create a stack \"my_stack\" of 10 elments ...");
        for(int cnt=0; cnt<10; cnt++) my_stack.push(cnt+1);

        message("size of my_stack", my_stack.size());
        cout << "print the contents of my_stack\n";
        print(my_stack);
        message("size of my_stack", my_stack.size());

        message("print the stack cp");
        Stack<int> cp = my_stack;
        print(cp);

        message("fill my_stack with new 15 elements ...");
        fill(my_stack, 15);

        
        Stack<int> stack_1;        
        // push new elements to stack_1 
        stack_1.push(19);
        stack_1.push(29);
        Stack<int> stack_2 = std::move(stack_1);
        cout << "print the contents of stack_1\n";
        stack_1 = my_stack;
        print(stack_1);
        cout << "print the contents of stack_2\n";
        print(stack_2);
        fill(stack_2, 5);
        Stack<string> s3;
        s3.push("one"); 
        s3.push("two"); 
        s3.push("three");
        cout << "top of stack s3 is: " << s3.top() << endl;
        Stack<int> s1{15};
        
        s1 = stack_2;
        Stack<int> s2 = s1;
        s2.push(5); 
        s2.push(10);
        s2.pop();
        s2 = std::move(s1);
        s1 = stack_2;
        s1.pop();
        s1.push(20);
        s2.push(30);
        cout << "s1.top() = " << s1.top() << " , s1.size() = " << s1.size() << " , s2.top() = " << s2.top() << " , s2.size() = " << s2.size() << endl;
        s2.swap(s1);
        cout << "s1.top() = " << s1.top() << " , s1.size() = " << s1.size() << " , s2.top() = " << s2.top() << " , s2.size() = " << s2.size() << endl;
    }

    catch(Exception& e){cout << e.what() << endl;}
    catch(std::bad_alloc& e){cout << e.what() << endl;}
    cout << "program is excited correctly\n";
    return 0;
}