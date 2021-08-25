#ifndef TIMER_H
#define TIMER_H
#include <functional>

#include <thread>
#include <chrono>

class Timer
{
    std::thread Thread;
    bool Alive = false;
    long CallNumber = -1L; //-1 is default value, and determines how many times to call the function
    long repeat_count = -1L; //certain times function has been called..
    std::chrono::milliseconds interval = std::chrono::milliseconds(0);
    std::function<void(void)> funct = nullptr;  //function that takes nothing is initialised to nullptr which is nothing

    void SleepAndRun()
    {
        std::this_thread::sleep_for(interval);
        if(Alive)
            Function()(); //represents a function calls funtion defined below
    }

    void ThreadFunc()
    {
        if(CallNumber == Infinite)
            while(Alive)
                SleepAndRun();
        else
            while(repeat_count--)
                SleepAndRun();
    }

public:
    static const long Infinite = -1L;

    Timer(){} //global as variables die after being used

    Timer(const std::function<void(void)> &f) : funct (f) {}

    Timer(const std::function<void(void)> &f,
          const unsigned long &i,
          const long repeat = Timer::Infinite) : funct (f),
                                                 interval(std::chrono::milliseconds(i)),
                                                 CallNumber(repeat){}


    void Start(bool Async = true)
      {
          if(IsALive())
              return;
          Alive = true;
          repeat_count = CallNumber;
          if(Async)
            Thread = std::thread(ThreadFunc, this);
          else
            this->ThreadFunc();
          }

          void Stop()
          {
              Alive = false;
              Thread.join();
          }

          void SetFunction(const std::function<void(void)> &f)
          {
              funct = f;
          }

          bool IsALive() const {return Alive;}

          void RepeatCount(const long r)
          {
              if(Alive)
                return;
              CallNumber = r;
          }

          long GetLeftCount() const {return repeat_count;}
          long RepeatCount() const {return CallNumber;}

          void SetInterval(const unsigned long &i)
          {
              if(Alive)
                return;
              interval = std::chrono::milliseconds(i);
          }

          unsigned long Interval() const {return interval.count();}

          const std::function<void(void)> &Function() const //this method calls/returns a function
          {
              return funct;
          }

};

#endif // TIMER_H
