#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

class Singleton
{
    protected:
    Singleton(const string value): value_(value) {}
    static Singleton* singleton_;
    string value_;

    public:
    Singleton(Singleton &other) = delete;
    void operator=(const Singleton &) = delete;

    static Singleton *GetInstance(const string& value);
    void SomeBusinessLogic() {}
    string value() const {return value_;}
};

Singleton* Singleton::singleton_ = nullptr;
Singleton *Singleton::GetInstance(const string& value)
{
    if (singleton_==nullptr) {
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

void ThreadFoo(){
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton* singleton = 
        Singleton::GetInstance("FOO ");
    cout<<singleton->value() <<endl;
}

void ThreadBar(){
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton* singleton = 
        Singleton::GetInstance("BAR ");
    cout << singleton->value() << endl;
}

int main() {
    std::cout <<"If you see the same value, "
        <<"then singleton was reused (yay!\n" 
        <<"If you see different values, then 2 "
        <<"singletons were created (booo!!)\n\n" 
        <<"RESULT:\n";

    thread t1(ThreadFoo);
    thread t2(ThreadBar);
    t1.join();
    t2.join();
}
