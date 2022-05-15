#include <cmath>
#include <cstdint>

#include "faust/dsp/dsp.h"
#include "Limiter.hpp"

struct mydsp : public dsp {
    
    Limiter<float> limiterStereo;
    FAUSTFLOAT** noise_inputs;
    
    void init(int sample_rate)
    {
        limiterStereo.SetSR(sample_rate);
    }
    
    // Adapted DSP does not have inputs anymore
    int getNumInputs() { return 0; }
    
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
    
    mydsp()
    {
        noise_inputs = new FAUSTFLOAT*[2];
        for (int chan = 0; chan < 2; chan++) {
            noise_inputs[chan] = new FAUSTFLOAT[1024];
        }
    }
    
    ~mydsp()
    {
        for (int chan = 0; chan < 2; chan++) {
            delete [] noise_inputs[chan];
        }
        delete [] noise_inputs;
    }
    
    // For noise generation
    int32_t state = 0;
    int32_t seed = 12345;
    const int32_t MAX = 2147483648 - 1;
    
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        limiterStereo.SetPreGain(120.0);
        limiterStereo.SetAttTime(0.01);
        limiterStereo.SetHoldTime(0.05);
        limiterStereo.SetRelTime(0.15);
        limiterStereo.SetThreshold(0.0);
        
        // Generates noise
        for (int i = 0; i < count; i++) {
            state = state * 1103515245 + seed;
            noise_inputs[0][i] = state / FAUSTFLOAT(MAX);
            noise_inputs[1][i] = noise_inputs[0][i];
        }
      
        limiterStereo.Process(noise_inputs, outputs, count);
    }
    
};

/*
int main()
{
    mydsp DSP;
    
    float** inputs = new FAUSTFLOAT*[2];
    for (int i = 0; i < 2; i++) {
        inputs[i] = new FAUSTFLOAT[256];
    }
    
    float** outputs = new FAUSTFLOAT*[2];
    for (int i = 0; i < 2; i++) {
        outputs[i] = new FAUSTFLOAT[256];
    }
    
    DSP.init(44100);
    DSP.compute(256, inputs, outputs);
    
    return 0;
}
*/
