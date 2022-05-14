## Beating the C++ compiler

### Testing the Faust DSP code

Testing the limiterStereo algorithm written in Faust (https://github.com/sletz/limiterStereo) by Dario Sanfilippo. Tested with `faustbench-llvm` (https://github.com/grame-cncm/faust/tree/master-dev/tools/benchmark#faustbench-llvm), which finds the `-vec -lv 0 -vs 4 -mcd 2 -g` as the best options.

Then using `faust2bench` (https://faustdoc.grame.fr/manual/optimizing/#faust2bench) with the best options, so:

- `faust2bench -vec -lv 0 -vs 4 -mcd 2 -g limiterStereo.dsp`
- `./limiterStereo` gives: `364.796 MBytes/sec (DSP CPU % : 0.195565 at 44100 Hz)`

### Testing the hand written C++ code

Dario manually rewrote a version in C++ (https://github.com/dariosanfilippo/LimiterClass). This code needs to be adapted to run inside the faust2bench tool. 

Here is the adaptation code (https://github.com/sletz/LimiterClass/blob/main/adapterTemplate.cpp). Next we run:

- `faust2bench -inj adapterTemplate.cpp limiter.dsp`
- `./limiter` gives: `291.423 MBytes/sec (DSP CPU % : 0.236259 at 44100 Hz)`
 
So a (365-291)/291 = 25% gain !
