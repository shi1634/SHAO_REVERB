#include "gen_exported.h"
#include <emscripten.h>

CommonState* dsp = nullptr;

extern "C" {

EMSCRIPTEN_KEEPALIVE
void init_dsp(double samplerate, int buffersize) {
    if (dsp) gen_exported::destroy(dsp);
    dsp = (CommonState*)gen_exported::create(samplerate, buffersize);
    gen_exported::reset(dsp);
}

EMSCRIPTEN_KEEPALIVE
void set_param(int index, double value) {
    gen_exported::setparameter(dsp, index, value, nullptr);
}

EMSCRIPTEN_KEEPALIVE
void process(double* in1, double* in2, double* out1, double* out2, int size) {
    double* inputs[] = { in1, in2 };
    double* outputs[] = { out1, out2 };
    gen_exported::perform(dsp, inputs, 2, outputs, 2, size);
}

}

