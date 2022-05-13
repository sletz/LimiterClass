#include <cmath>
#include <cstdint>

#include "faust/dsp/dsp.h"
#include "Limiter.hpp"

struct mydsp : public dsp {
    
    Limiter<float> limiterStereo;
    
    void init(int sample_rate)
    {
        limiterStereo.SetSR(sample_rate);
    }
    
    int getNumInputs() { return 2; }
    int getNumOutputs() { return 2; }
    
    int getSampleRate() { return 44100; }
    
    void instanceInit(int sample_rate)
    {}
    
    void instanceConstants(int sample_rate)
    {}
    void instanceResetUserInterface()
    {}
    void instanceClear()
    {}
    
    void buildUserInterface(UI* ui_interface)
    {}
    
    dsp* clone()
    {
        return new mydsp();
    }
    void metadata(Meta* m)
    {}
    
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        limiterStereo.SetPreGain(0.0);
        limiterStereo.SetAttTime(0.01);
        limiterStereo.SetHoldTime(0.05);
        limiterStereo.SetRelTime(0.15);
        limiterStereo.SetThreshold(0.0);
      
        limiterStereo.Process(inputs, outputs, count);
    }
    
};
