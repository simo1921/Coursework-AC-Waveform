//
// Created by o2-touati on 01/05/2026.
//

#include "io.h"
#include <stdio.h>
#include <stdlib.h>

WaveformSample* load_csv(const char *filename, size_t *count) {

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file\n");
        return NULL;
    }

    size_t capacity = 1000;
    WaveformSample *data = malloc(capacity * sizeof(WaveformSample));

    if (!data) {
        printf("Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    char line[256];
    fgets(line, sizeof(line), file); // skip header

    size_t i = 0;

    while (fgets(line, sizeof(line), file)) {

        if (i >= capacity) {
            capacity *= 2;

            WaveformSample *temp = realloc(data, capacity * sizeof(WaveformSample));
            if (!temp) {
                printf("Memory reallocation failed\n");
                free(data);
                fclose(file);
                return NULL;
            }

            data = temp;
        }

        sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
               &data[i].timestamp,
               &data[i].phase_A_voltage,
               &data[i].phase_B_voltage,
               &data[i].phase_C_voltage,
               &data[i].line_current,
               &data[i].frequency,
               &data[i].power_factor,
               &data[i].thd_percent);

        i++;
    }

    fclose(file);
    *count = i;

    return data;
}
    void write_results(const char *filename,                              // Part 2
                       double rmsA, double rmsB, double rmsC,
                       double p2pA, double p2pB, double p2pC,
                       double dcA, double dcB, double dcC,
                       int clipA, int clipB, int clipC) {

        FILE *file = fopen(filename, "w");
        if (!file) {
            printf("Error: Cannot write file\n");
            return;
        }

        fprintf(file, "RMS:\nA: %.2f (%s)\nB: %.2f (%s)\nC: %.2f (%s)\n\n",
                rmsA, check_tolerance(rmsA) ? "OK" : "Out of range",
                rmsB, check_tolerance(rmsB) ? "OK" : "Out of range",
                rmsC, check_tolerance(rmsC) ? "OK" : "Out of range");

        fprintf(file, "Peak-to-Peak:\nA: %.2f\nB: %.2f\nC: %.2f\n\n",
                p2pA, p2pB, p2pC);

        fprintf(file, "DC Offset:\nA: %.2f\nB: %.2f\nC: %.2f\n\n",
                dcA, dcB, dcC);

        fprintf(file, "Clipping:\nA: %s\nB: %s\nC: %s\n",
                clipA ? "Yes" : "No",
                clipB ? "Yes" : "No",
                clipC ? "Yes" : "No");

        fclose(file);
    }         // End of part 2