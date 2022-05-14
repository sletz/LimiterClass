# LimiterClass
C++ class for an IIR look-ahead limiter implementing cascaded exponential smoothers for low-distortion peak-limiting and maximisation.

Reference:

 Sanfilippo, D. (2022). Envelope following via cascaded exponential smoothers 
 for low-distortion peak limiting and maximisation. In Proceedings of the
 International Faust Conference, Saint-Étienne, France.

### Benchmarking the C++ code with faust2bench

- `faust2bench -inj adapterTemplate.cpp limiter.dsp`

- `./limiter`
