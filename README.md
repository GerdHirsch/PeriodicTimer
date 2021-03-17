# PeriodicTimer
A std::thread based Simple Periodic Timer for multiple Receivers

see demos in src and tests in SimplePeriodicTimerCUTE   
the timer object must not expire before the detached thread ends
## timing constraints test 
between 1 ms and 500 ms   
periods < 30 ms are not applicable on Windows
periods >= 30 average within 10 timer calls (see TimingConstraintsTest and MockClassTimer)   
Period /   deviation   
to long   
30ms: < +4%   
50ms: < +14%   

to short   
100ms: < -4%   
300ms: < -10%   
500ms: < -10%   
