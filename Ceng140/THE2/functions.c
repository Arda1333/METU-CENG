#include <stdlib.h>
#include <stdio.h>

#define n_sector 3

/* Fill in the functions and define helper functions if you need to */

float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
    float*** table;
    float time1, time2, time3;
    int i, j, drivers, laps;
    drivers = *n_drivers;
    laps = *n_laps;

    table = (float***) malloc(sizeof(float**) * drivers);


    for(i = 0; i < drivers; i++)
    {

        table[i] = (float**) malloc(sizeof(float*) * laps);

    }

    for(i = 0; i < drivers; i++)
    {

        for(j = 0; j < laps; j++)
        {

            table[i][j] = (float*) malloc(sizeof(float) * n_sector);

        }

    }


    for(i = 0; i < drivers; i++)
    {

        for(j = 0; j < laps; j++)
        {

            scanf("%f %f %f", &time1, &time2, &time3);
            table[i][j][0] = time1;
            table[i][j][1] = time2;
            table[i][j][2] = time3;

        }
    }

    return table;

}


unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
    return NULL;
}


float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
    return NULL;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    return 0;
}


unsigned int find_driver_fastest_lap(float lap_times_of_driver[][3], unsigned int n_laps){
    return 0;
}


float* selection_sort(float* arr, unsigned int len, char ord){
    return NULL;
}


unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    return NULL;
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,
    unsigned int driver2){
    return NULL;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
    return NULL;
}


unsigned int find_season_ranking(int* total_points, unsigned int p_drivers, unsigned int id){
    return 0;
}
