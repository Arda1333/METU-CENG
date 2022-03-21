#include "functions.h"


/*
You will not submit this file, just use for testing your code.
All your implementations should be in functions.c
*/

/*
To compile your code, use "make main"
Then "./main" to run.
If you want to compile again, you need to delete the previous executable.
You may do this by "make clean" or simply "rm main"
*/

int main(){

    /*
    Function calls here to test your code
    Example:
    float ***sector_times, **laptimes;
    unsigned int fastest_lap, **positions;
    sector_times = create_sector_times(...);
    positions = create_positions(...);
    lap_times = calculate_lap_times(...);
    fastest_lap = find_fastest_lap(lap_times, ...);
    printf("Printing fastest lap to check the answer: %d\n", fastest_lap);
    */
	

	float ***sector_times, **lap_times, **sector_times_of_driver, *differences;
	unsigned int i, j, k, *n_drivers, *n_laps, *n_races, a, b, c, fastest_lap, fastest_driver_lap, *finish_positions, **positions, *total_points, rank;
	float *sorted, array[10] = {1.2, 3.5, 2.4, 3.3, 4.0, 12.0, 42.0, 23.0, 412.0, 221.0};
	unsigned int len = 10;



	n_drivers = &a;
	n_laps = &b;
	n_races = &c;

	sector_times = create_sector_times(n_drivers, n_laps);




	printf("%u %u\n", *n_drivers, *n_laps);
	for(i = 0; i < *n_drivers; i++)
	{
		for (j = 0; j < *n_laps; ++j)
		{
			for(k = 0; k < 3; k++)
			{
				printf("%.2f ", sector_times[i][j][k]);
			}
			printf("\n");
		}
	}

	



    positions = create_positions(n_drivers, n_races);

    printf("%u %u\n", *n_drivers, *n_races);

    for(i = 0; i < *n_drivers; i++)
    {
    	for(j = 0; j < *n_races; j++)
    	{
    		printf("%u ", positions[i][j]);
    	}
    	printf("\n");
    }





	lap_times = calculate_lap_times(sector_times, *n_drivers, *n_laps);

	for(i = 0; i < *n_drivers; i++)
	{
		for(j = 0; j < *n_laps; j++)
		{
			printf("%.2f ", lap_times[i][j]);
		}
		printf("\n");
	}





	fastest_lap = find_fastest_lap(lap_times, *n_drivers, *n_laps);

	printf("%u\n", fastest_lap);



	sector_times_of_driver = (float**) malloc(sizeof(float*) * 3);
	for(i = 0; i < 3; i++)
	{
		sector_times_of_driver[i] = (float*) malloc(sizeof(float) * 3);
	}
	sector_times_of_driver[0][0] = 22.17;
	sector_times_of_driver[0][1] = 34.85;
	sector_times_of_driver[0][2] = 30.19;
	sector_times_of_driver[1][0] = 32.48;
	sector_times_of_driver[1][1] = 27.51;
	sector_times_of_driver[1][2] = 23.17;
	sector_times_of_driver[2][0] = 15.10;
	sector_times_of_driver[2][1] = 29.02;
	sector_times_of_driver[2][2] = 27.46;


	fastest_driver_lap = find_driver_fastest_lap(sector_times_of_driver, 3);

	printf("%u\n", fastest_driver_lap);






	sorted = selection_sort(array, len, 'A');

	for(i = 0; i < len; i++)
	{
		printf("%f\n", sorted[i]);
	}



	finish_positions = find_finishing_positions(lap_times, *n_drivers, *n_laps);

	for(i = 0; i < *n_drivers; i++) printf("%u ", finish_positions[i]);
	printf("\n");



	differences = find_time_diff(lap_times, *n_drivers, *n_laps, 0, 1);

	for(i = 0; i < *n_laps; i++) printf("%.2f ", differences[i]);
	printf("\n");





    total_points = calculate_total_points(positions, *n_drivers, *n_races);

    for(i = 0; i < *n_drivers; i++)
    {
    	printf("%u ", total_points[i]);
    }
    printf("\n");



    rank = find_season_ranking(total_points, *n_drivers, 1);

    printf("%u\n", rank);



    return 0;
}
