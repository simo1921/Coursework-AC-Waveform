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