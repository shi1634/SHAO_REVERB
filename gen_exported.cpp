#include "gen_exported.h"

namespace gen_exported {

/****************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER 200k USD in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below 200k USD annual revenue or funding.

For entities with OVER 200k USD in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing (at) cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/360050779193-Gen-Code-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
****************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Delay m_delay_11;
	Delay m_delay_10;
	Delay m_delay_12;
	Delay m_delay_6;
	Delay m_delay_7;
	Delay m_delay_8;
	Delay m_delay_13;
	Delay m_delay_15;
	Delay m_delay_14;
	Delay m_delay_17;
	Delay m_delay_16;
	Delay m_delay_9;
	int __exception;
	int vectorsize;
	t_sample m_revtime_20;
	t_sample m_early_19;
	t_sample m_bandwidth_24;
	t_sample m_damping_21;
	t_sample m_roomsize_23;
	t_sample m_tail_22;
	t_sample m_history_5;
	t_sample m_spread_18;
	t_sample m_history_1;
	t_sample m_history_4;
	t_sample samplerate;
	t_sample m_history_3;
	t_sample m_history_2;
	t_sample m_dry_25;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_delay_6.reset("m_delay_6", ((int)7000));
		m_delay_7.reset("m_delay_7", ((int)5000));
		m_delay_8.reset("m_delay_8", ((int)6000));
		m_delay_9.reset("m_delay_9", ((int)16000));
		m_delay_10.reset("m_delay_10", ((int)15000));
		m_delay_11.reset("m_delay_11", ((int)48000));
		m_delay_12.reset("m_delay_12", ((int)12000));
		m_delay_13.reset("m_delay_13", ((int)10000));
		m_delay_14.reset("m_delay_14", ((int)48000));
		m_delay_15.reset("m_delay_15", ((int)48000));
		m_delay_16.reset("m_delay_16", ((int)48000));
		m_delay_17.reset("m_delay_17", ((int)48000));
		m_spread_18 = ((int)23);
		m_early_19 = ((t_sample)0.25);
		m_revtime_20 = ((int)11);
		m_damping_21 = ((t_sample)0.7);
		m_tail_22 = ((t_sample)0.25);
		m_roomsize_23 = ((int)75);
		m_bandwidth_24 = ((t_sample)0.5);
		m_dry_25 = ((int)1);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample expr_3486 = safepow(((t_sample)0.001), safediv(((int)1), (m_revtime_20 * samplerate)));
		t_sample expr_3487 = ((m_roomsize_23 * samplerate) * ((t_sample)0.0029411764705882));
		t_sample mul_3467 = (expr_3487 * ((t_sample)0.81649));
		t_sample expr_3480 = (-safepow(expr_3486, mul_3467));
		t_sample mul_3468 = (expr_3487 * ((int)1));
		t_sample expr_3485 = (-safepow(expr_3486, mul_3468));
		t_sample mul_3465 = (expr_3487 * ((t_sample)0.63245));
		t_sample expr_3478 = (-safepow(expr_3486, mul_3465));
		t_sample mul_3466 = (expr_3487 * ((t_sample)0.7071));
		t_sample expr_3479 = (-safepow(expr_3486, mul_3466));
		t_sample add_3391 = (expr_3487 + ((int)5));
		t_sample expr_3481 = safepow(expr_3486, add_3391);
		t_sample mul_3396 = (expr_3487 * ((t_sample)0.3));
		t_sample add_3393 = (mul_3396 + ((int)5));
		t_sample expr_3483 = safepow(expr_3486, add_3393);
		t_sample mul_3397 = (expr_3487 * ((t_sample)0.41));
		t_sample add_3394 = (mul_3397 + ((int)5));
		t_sample expr_3484 = safepow(expr_3486, add_3394);
		t_sample rsub_3476 = (((int)1) - m_bandwidth_24);
		t_sample mul_3395 = (expr_3487 * ((t_sample)0.155));
		t_sample add_3392 = (mul_3395 + ((int)5));
		t_sample expr_3482 = safepow(expr_3486, add_3392);
		t_sample mul_3462 = (expr_3487 * ((t_sample)0.000527));
		int int_3461 = int(mul_3462);
		t_sample mul_3430 = (m_spread_18 * ((t_sample)0.376623));
		t_sample add_3429 = (mul_3430 + ((int)931));
		t_sample rsub_3426 = (((int)1341) - add_3429);
		t_sample mul_3437 = (int_3461 * rsub_3426);
		t_sample mul_3402 = (m_spread_18 * (-0.380445));
		t_sample add_3401 = (mul_3402 + ((int)931));
		t_sample rsub_3398 = (((int)1341) - add_3401);
		t_sample mul_3411 = (int_3461 * rsub_3398);
		t_sample mul_3446 = (m_spread_18 * ((t_sample)0.125541));
		t_sample add_3428 = (mul_3446 + ((int)369));
		t_sample rsub_3427 = (add_3429 - add_3428);
		t_sample mul_3444 = (int_3461 * rsub_3427);
		t_sample mul_3404 = (m_spread_18 * (-0.568366));
		t_sample add_3400 = (mul_3404 + ((int)369));
		t_sample rsub_3399 = (add_3401 - add_3400);
		t_sample mul_3418 = (int_3461 * rsub_3399);
		t_sample mul_3460 = (expr_3487 * ((t_sample)0.110732));
		t_sample add_3445 = (mul_3446 + ((int)159));
		t_sample mul_3453 = (int_3461 * add_3445);
		t_sample add_3403 = (mul_3404 + ((int)159));
		t_sample mul_3425 = (int_3461 * add_3403);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_3335 = (in1 * m_dry_25);
			t_sample mul_3323 = (in2 * m_dry_25);
			t_sample mul_3325 = ((in1 + in2) * ((t_sample)0.707));
			t_sample mix_3493 = (mul_3325 + (rsub_3476 * (m_history_5 - mul_3325)));
			t_sample mix_3475 = mix_3493;
			t_sample tap_3473 = m_delay_17.read_linear(mul_3468);
			t_sample mul_3464 = (tap_3473 * expr_3485);
			t_sample mix_3494 = (mul_3464 + (m_damping_21 * (m_history_4 - mul_3464)));
			t_sample mix_3471 = mix_3494;
			t_sample tap_3371 = m_delay_16.read_linear(mul_3466);
			t_sample mul_3367 = (tap_3371 * expr_3479);
			t_sample mix_3495 = (mul_3367 + (m_damping_21 * (m_history_3 - mul_3367)));
			t_sample mix_3369 = mix_3495;
			t_sample tap_3365 = m_delay_15.read_linear(mul_3465);
			t_sample mul_3361 = (tap_3365 * expr_3478);
			t_sample mix_3496 = (mul_3361 + (m_damping_21 * (m_history_2 - mul_3361)));
			t_sample mix_3363 = mix_3496;
			t_sample tap_3377 = m_delay_14.read_linear(mul_3467);
			t_sample mul_3373 = (tap_3377 * expr_3480);
			t_sample mix_3497 = (mul_3373 + (m_damping_21 * (m_history_1 - mul_3373)));
			t_sample mix_3375 = mix_3497;
			t_sample tap_3436 = m_delay_13.read_linear(mul_3437);
			t_sample mul_3434 = (tap_3436 * ((t_sample)0.625));
			t_sample tap_3410 = m_delay_12.read_linear(mul_3411);
			t_sample mul_3408 = (tap_3410 * ((t_sample)0.625));
			t_sample tap_3379 = m_delay_11.read_linear(add_3394);
			t_sample tap_3380 = m_delay_11.read_linear(add_3393);
			t_sample tap_3381 = m_delay_11.read_linear(add_3392);
			t_sample tap_3382 = m_delay_11.read_linear(add_3391);
			t_sample mul_3389 = (tap_3379 * expr_3484);
			t_sample mul_3385 = (tap_3381 * expr_3482);
			t_sample mul_3383 = (tap_3382 * expr_3481);
			t_sample mul_3387 = (tap_3380 * expr_3483);
			t_sample add_3355 = (mix_3471 + mix_3375);
			t_sample add_3353 = (mix_3369 + mix_3363);
			t_sample sub_3352 = (add_3355 - add_3353);
			t_sample mul_3334 = (sub_3352 * ((t_sample)0.5));
			t_sample add_3359 = (mul_3334 + mul_3389);
			t_sample add_3348 = (add_3355 + add_3353);
			t_sample mul_3331 = (add_3348 * ((t_sample)0.5));
			t_sample add_3356 = (mul_3331 + mul_3383);
			t_sample sub_3354 = (mix_3471 - mix_3375);
			t_sample sub_3351 = (mix_3369 - mix_3363);
			t_sample sub_3350 = (sub_3354 - sub_3351);
			t_sample mul_3333 = (sub_3350 * ((t_sample)0.5));
			t_sample add_3358 = (mul_3333 + mul_3387);
			t_sample add_3349 = (sub_3354 + sub_3351);
			t_sample rsub_3347 = (((int)0) - add_3349);
			t_sample mul_3332 = (rsub_3347 * ((t_sample)0.5));
			t_sample add_3357 = (mul_3332 + mul_3385);
			t_sample tap_3443 = m_delay_10.read_linear(mul_3444);
			t_sample mul_3441 = (tap_3443 * ((t_sample)0.625));
			t_sample tap_3417 = m_delay_9.read_linear(mul_3418);
			t_sample mul_3415 = (tap_3417 * ((t_sample)0.625));
			t_sample tap_3459 = m_delay_8.read_linear(mul_3460);
			t_sample tap_3452 = m_delay_7.read_linear(mul_3453);
			t_sample mul_3450 = (tap_3452 * ((t_sample)0.75));
			t_sample tap_3424 = m_delay_6.read_linear(mul_3425);
			t_sample mul_3422 = (tap_3424 * ((t_sample)0.75));
			t_sample mul_3457 = (tap_3459 * ((t_sample)0.75));
			t_sample sub_3456 = (mix_3475 - mul_3457);
			t_sample mul_3455 = (sub_3456 * ((t_sample)0.75));
			t_sample add_3454 = (mul_3455 + tap_3459);
			t_sample mul_3346 = (mul_3334 * m_tail_22);
			t_sample mul_3344 = (mul_3332 * m_tail_22);
			t_sample add_3330 = (mul_3346 + mul_3344);
			t_sample mul_3345 = (mul_3333 * m_tail_22);
			t_sample mul_3343 = (mul_3331 * m_tail_22);
			t_sample add_3329 = (mul_3345 + mul_3343);
			t_sample sub_3338 = (add_3330 - add_3329);
			t_sample mul_3342 = (mul_3389 * m_early_19);
			t_sample mul_3340 = (mul_3385 * m_early_19);
			t_sample add_3328 = (mul_3342 + mul_3340);
			t_sample mul_3341 = (mul_3387 * m_early_19);
			t_sample mul_3339 = (mul_3383 * m_early_19);
			t_sample add_3327 = (mul_3341 + mul_3339);
			t_sample sub_3337 = (add_3328 - add_3327);
			t_sample add_3324 = (sub_3338 + sub_3337);
			t_sample add_3336 = (add_3324 + in1);
			t_sample sub_3449 = (add_3336 - mul_3450);
			t_sample mul_3448 = (sub_3449 * ((t_sample)0.75));
			t_sample add_3447 = (mul_3448 + tap_3452);
			t_sample sub_3440 = (add_3447 - mul_3441);
			t_sample mul_3439 = (sub_3440 * ((t_sample)0.625));
			t_sample add_3438 = (mul_3439 + tap_3443);
			t_sample sub_3433 = (add_3438 - mul_3434);
			t_sample mul_3432 = (sub_3433 * ((t_sample)0.625));
			t_sample add_3431 = (mul_3432 + tap_3436);
			t_sample out1 = (mul_3335 + add_3431);
			t_sample add_3326 = (add_3324 + in2);
			t_sample sub_3421 = (add_3326 - mul_3422);
			t_sample mul_3420 = (sub_3421 * ((t_sample)0.75));
			t_sample add_3419 = (mul_3420 + tap_3424);
			t_sample sub_3414 = (add_3419 - mul_3415);
			t_sample mul_3413 = (sub_3414 * ((t_sample)0.625));
			t_sample add_3412 = (mul_3413 + tap_3417);
			t_sample sub_3407 = (add_3412 - mul_3408);
			t_sample mul_3406 = (sub_3407 * ((t_sample)0.625));
			t_sample add_3405 = (mul_3406 + tap_3410);
			t_sample out2 = (mul_3323 + add_3405);
			t_sample history_3474_next_3488 = fixdenorm(mix_3475);
			t_sample history_3470_next_3489 = fixdenorm(mix_3471);
			t_sample history_3368_next_3490 = fixdenorm(mix_3369);
			t_sample history_3362_next_3491 = fixdenorm(mix_3363);
			t_sample history_3374_next_3492 = fixdenorm(mix_3375);
			m_delay_17.write(add_3359);
			m_delay_16.write(add_3357);
			m_delay_15.write(add_3356);
			m_delay_14.write(add_3358);
			m_delay_13.write(sub_3433);
			m_delay_12.write(sub_3407);
			m_delay_11.write(add_3454);
			m_delay_10.write(sub_3440);
			m_delay_9.write(sub_3414);
			m_delay_8.write(sub_3456);
			m_delay_7.write(sub_3449);
			m_delay_6.write(sub_3421);
			m_history_5 = history_3474_next_3488;
			m_history_4 = history_3470_next_3489;
			m_history_3 = history_3368_next_3490;
			m_history_2 = history_3362_next_3491;
			m_history_1 = history_3374_next_3492;
			m_delay_6.step();
			m_delay_7.step();
			m_delay_8.step();
			m_delay_9.step();
			m_delay_10.step();
			m_delay_11.step();
			m_delay_12.step();
			m_delay_13.step();
			m_delay_14.step();
			m_delay_15.step();
			m_delay_16.step();
			m_delay_17.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_spread(t_param _value) {
		m_spread_18 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_early(t_param _value) {
		m_early_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_revtime(t_param _value) {
		m_revtime_20 = (_value < 0.1 ? 0.1 : (_value > 1 ? 1 : _value));
	};
	inline void set_damping(t_param _value) {
		m_damping_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_tail(t_param _value) {
		m_tail_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_roomsize(t_param _value) {
		m_roomsize_23 = (_value < 0.1 ? 0.1 : (_value > 300 ? 300 : _value));
	};
	inline void set_bandwidth(t_param _value) {
		m_bandwidth_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_dry(t_param _value) {
		m_dry_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 8; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_bandwidth(value); break;
		case 1: self->set_damping(value); break;
		case 2: self->set_dry(value); break;
		case 3: self->set_early(value); break;
		case 4: self->set_revtime(value); break;
		case 5: self->set_roomsize(value); break;
		case 6: self->set_spread(value); break;
		case 7: self->set_tail(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_bandwidth_24; break;
		case 1: *value = self->m_damping_21; break;
		case 2: *value = self->m_dry_25; break;
		case 3: *value = self->m_early_19; break;
		case 4: *value = self->m_revtime_20; break;
		case 5: *value = self->m_roomsize_23; break;
		case 6: *value = self->m_spread_18; break;
		case 7: *value = self->m_tail_22; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(8 * sizeof(ParamInfo));
	self->__commonstate.numparams = 8;
	// initialize parameter 0 ("m_bandwidth_24")
	pi = self->__commonstate.params + 0;
	pi->name = "bandwidth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_bandwidth_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_damping_21")
	pi = self->__commonstate.params + 1;
	pi->name = "damping";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damping_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_dry_25")
	pi = self->__commonstate.params + 2;
	pi->name = "dry";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_dry_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_early_19")
	pi = self->__commonstate.params + 3;
	pi->name = "early";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_early_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_revtime_20")
	pi = self->__commonstate.params + 4;
	pi->name = "revtime";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_revtime_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_roomsize_23")
	pi = self->__commonstate.params + 5;
	pi->name = "roomsize";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_roomsize_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 300;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_spread_18")
	pi = self->__commonstate.params + 6;
	pi->name = "spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_spread_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_tail_22")
	pi = self->__commonstate.params + 7;
	pi->name = "tail";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tail_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // gen_exported::
