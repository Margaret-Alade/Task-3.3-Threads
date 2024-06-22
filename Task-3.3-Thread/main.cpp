//
//  main.cpp
//  Task-3.3-Thread
//
//  Created by Маргарет  on 16.06.2024.
//

#include <iostream>
#include <thread>
#include <mutex>

class Data {
    
public:
    std::mutex m;
    int num1_;
    int num2_;
    std::string class_name_;
    
    Data(int num1, int num2, std::string class_name) {
        this->num1_ = num1;
        this->num2_ = num2;
        this->class_name_ = class_name;
    }
    
    void print_num() {
        std::cout << "Скалярные значения класса " << class_name_ << ": " << num1_ << " и " << num2_ << "\n";
    }
    
};

//при помощи lock
void swap(Data& data1, Data& data2) {
    std::lock(data1.m, data2.m);
    std::lock_guard lk(data1.m, std::adopt_lock);
    std::lock_guard lk2(data2.m, std::adopt_lock);
    int tmp1 = data1.num1_;
    data1.num1_= data2.num1_;
    data2.num1_ = tmp1;
    int tmp2 = data1.num2_;
    data1.num2_= data2.num2_;
    data2.num2_ = tmp2;
    data1.print_num();
    data2.print_num();
}


//через std::scoped_lock
//void swap(Data& data1, Data& data2) {
//    std::scoped_lock(data1.m, data2.m);
//    int tmp1 = data1.num1_;
//    data1.num1_= data2.num1_;
//    data2.num1_ = tmp1;
//    int tmp2 = data1.num2_;
//    data1.num2_= data2.num2_;
//    data2.num2_ = tmp2;
//    
//    data1.print_num();
//    data2.print_num();
//}

//через unique_lock
//void swap(Data& data1, Data& data2) {
//    std::unique_lock lk1(data1.m, std::defer_lock);
//    std::unique_lock lk2(data2.m, std::defer_lock);
//    std::lock(lk1, lk2);
//    int tmp1 = data1.num1_;
//    data1.num1_= data2.num1_;
//    data2.num1_ = tmp1;
//    int tmp2 = data1.num2_;
//    data1.num2_= data2.num2_;
//    data2.num2_ = tmp2;
//    
//    data1.print_num();
//    data2.print_num();
//}


int main(int argc, const char * argv[]) {
    
    Data data1(5,4, "data1");
    Data data2(6,7, "data2");
    
    std::thread th1(swap, std::ref(data1), std::ref(data2));
    th1.join();
    
    
    return 0;
}
