//
// Created by o2-touati on 02/05/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "io.h"        // 1

int main(int argc, char *argv[]) {      //2
    if (argc != 2) {
        printf("Usage: %s <input.csv>\n", argv[0]);
        return 1;
    }        // 3


size_t count = 0;    // 4
WaveformSample *samples = load_csv(argv[1], &count); // 5
    if (!samples) {
           printf("Error loading data\n");
             return 1;
}                                                        // 6
double *phaseA = malloc(count * sizeof(double));
double *phaseB = malloc(count * sizeof(double));
double *phaseC = malloc(count * sizeof(double));  // 7

      if (!phaseA || !phaseB || !phaseC) {
          printf("Memory allocation failed\n");
            free(samples);
               return 1;
}                           // 8

for (size_t i = 0; i < count; i++) {
phaseA[i] = samples[i].phase_A_voltage;
phaseB[i] = samples[i].phase_B_voltage;
phaseC[i] = samples[i].phase_C_voltage;
}                                           // 9

double rmsA = compute_rms(phaseA, count);
double rmsB = compute_rms(phaseB, count);
double rmsC = compute_rms(phaseC, count);     // 10

double p2pA = compute_peak_to_peak(phaseA, count);
double p2pB = compute_peak_to_peak(phaseB, count);
double p2pC = compute_peak_to_peak(phaseC, count);    // 11

double dcA = compute_mean(phaseA, count);
double dcB = compute_mean(phaseB, count);
double dcC = compute_mean(phaseC, count);  // 12

int clipA = detect_clipping(phaseA, count);
int clipB = detect_clipping(phaseB, count);
int clipC = detect_clipping(phaseC, count);   // 13

write_results("results.txt", rmsA, rmsB, rmsC,p2pA, p2pB, p2pC, dcA, dcB, dcC, clipA, clipB, clipC); // 14

free(samples);
free(phaseA);
free(phaseB);
free(phaseC);  // 15

printf("Analysis complete. Results saved to results.txt\n");
return 0;
}                            // 16