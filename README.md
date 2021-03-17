# PeriodicTimer
A std::thread based Simple Periodic Timer for multiple Receivers

see demos in src and tests in SimplePeriodicTimerCUTE
## timing constraints test 
between 50ms and 500ms   
average within 10 timer calls (see TimingConstraintsTest and MockClassTimer)   
Timer   deviation   
to long   
50ms: < +10%   
to short   
100ms: < -4%   
300ms: < -10%   
500ms: < -10%   
