//
// Created by o2-touati on 01/05/2026.
//

#include "waveform.h"
#include <math.h>
double compute_mean(double *data, size_t n)
sum += *(data + i);
return sum / n;
double compute_rms(double *data, size_t n)
        double val = *(data + i);
                sum += val * val;
return sqrt(sum / n);
double compute_peak_to_peak(double *data, size_t n)
        double min = *data;
        double max = *data;
if (val < min) min = val;
if (val > max) max = val;
return max - min;
int detect_clipping(double *data, size_t n) //  1
if (fabs(*(data + i)) >= 324.9) // 2
return 1;
...
return 0; // 3