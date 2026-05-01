//
// Created by o2-touati on 01/05/2026.
//

#include "waveform.h"
#include <math.h> // 1

double compute_mean(double *data, size_t n) {
    double sum = 0.0; // 2

    for (size_t i = 0; i < n; i++) {
        sum += *(data + i);
    } // 3

    return sum / n; // 4
}

double compute_rms(double *data, size_t n) {
    double sum = 0.0;                          // 5

    for (size_t i = 0; i < n; i++) {
        double val = *(data + i);
        sum += val * val;
    }

    return sqrt(sum / n);
}

double compute_peak_to_peak(double *data, size_t n) {
    double min = *data;
    double max = *data;

    for (size_t i = 1; i < n; i++) {
        double val = *(data + i);

        if (val < min) min = val;
        if (val > max) max = val;
    }

    return max - min;
}

int detect_clipping(double *data, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (fabs(*(data + i)) >= 324.9) {
            return 1;
        }
    }

    return 0;
}

int check_tolerance(double rms) {
    return (rms >= 207.0 && rms <= 253.0);
}
