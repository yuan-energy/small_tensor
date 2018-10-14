#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include "../include_small_tensor.h"
void f1(int n)
{
    // =============================================
    // Option 1:
    int a = 2;
    // =============================================
    // Option 2:
    static int b = 2;
    // =============================================
    // Option 3:
    static thread_local int c = 2;
    // =============================================
    // Option 4:
    tensor1<int,3> obj4;  obj4(1) = 2;
    // =============================================
    // Option 5:
    static tensor1<int,3> obj5(obj4) ;  //obj5(1) = 2;
    // =============================================
    // Option 6:
    static thread_local tensor1<int,3> obj6(obj4) ;//  obj6(1) = 2;
    // =============================================
    for (int i = 2; i < 7; ++i) {
        printf("============================\n"     );
        printf("One Round::Iteration  = %d  \n" , i );
        printf("             int a    = %d  \n" , a );
        printf("      static int b    = %d  \n" , b );
        printf("thread_local int c    = %d  \n" , c );
        printf("             int obj4 = %d  \n" , obj4(1) );
        printf("      static int obj5 = %d  \n" , obj5(1) );
        printf("thread_local int obj6 = %d  \n" , obj6(1) );
        printf("============================\n"     );
        ++n; 
        a++; b++; c++;
        obj4(1) = obj4(1) + 1;
        obj5(1) = obj5(1) + 1;
        obj6(1) = obj6(1) + 1;
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
 
void f2(int& n)
{
    // std::cout<<"a= " <<a<< std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 2 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
 
int main()
{
    int n = 0;
    std::thread t1; // t1 is not a thread
    std::thread t2(f1, n); // pass by value
    t2.join();
    printf("\n\n\n sleep_for 20 milliseconds \n\n\n\n\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    std::thread t3(f1, n); // pass by value
    // std::thread t3(f2, std::ref(n)); // pass by reference
    // std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
    t3.join();
    // std::cout << "Final value of n is " << n << '\n';
}