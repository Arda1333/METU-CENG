#include <stdio.h>

#define max_width 5
#define max_height 5

void fill_helper(int row, int column, int color, int image[max_height][max_width])
{
    if((row >= 0 && column >= 0) && (row < max_height && column < max_width))
    {
        int prev_color = image[row][column];
        image[row][column] = color;
        if(image[row + 1][column] == prev_color)
        {
            fill_helper(row + 1, column, color, image);
        }
        if(image[row + 1][column + 1] == prev_color)
        {
            fill_helper(row + 1, column + 1, color, image);
        }
        if(image[row + 1][column - 1] == prev_color)
        {
            fill_helper(row + 1, column - 1, color, image);
        }
        if(image[row][column + 1] == prev_color)
        {
            fill_helper(row, column + 1, color, image);
        }
        if(image[row][column - 1] == prev_color)
        {
            fill_helper(row, column - 1, color, image);
        }
        if(image[row - 1][column] == prev_color)
        {
            fill_helper(row - 1, column, color, image);
        }
        if(image[row - 1][column + 1] == prev_color)
        {
            fill_helper(row - 1, column, color, image);
        }
        if(image[row - 1][column - 1] == prev_color)
        {
            fill_helper(row - 1, column - 1, color, image);
        }
    }
}



int main(void)
{
    int image[max_height][max_width], i, j, select_row, select_column, initial_row, initial_column, select_color, current_color;
    char operation;

    for (i = 0; i < max_height; i++)
    {
        for (j = 0; j < max_width; j++)
        {
            scanf("%d", &image[i][j]);
        }
    }
    scanf(" %c", &operation);
    scanf("%d %d", &select_row, &select_column);
    scanf("%d %d", &initial_row, &initial_column);
    if(operation == 'F')
    {
        if(select_row < 0 && select_column < 0)
        {
            select_color = 0;
        }
        else if(select_row < 0 && select_column < 5)
        {
            select_color = 1;
        }
        else if(select_row < 0 && select_column >= 5)
        {
            select_color = 2;
        }
        else if(select_row < 5 && select_column >= 5)
        {
            select_color = 3;
        }
        else if(select_row >= 5 && select_column >= 5)
        {
            select_color = 4;
        }
        else if(select_row >= 5 && select_column < 0)
        {
            select_color = 6;
        }
        else if(select_row >= 5 && select_column < 5)
        {
            select_color = 5;
        }
        else if(select_row < 5 && select_column < 0)
        {
            select_color = 7;
        }
        else
        {
            select_color = image[select_row][select_column];
        }
        fill_helper(initial_row, initial_column, select_color, image);
        for(i = 0; i < max_height; i++)
        {
            for(j = 0; j < max_width; j++)
            {
                printf("%d ", image[i][j]);
            }
            printf("\n");
        }
    }
    else if(operation == 'P')
    {

    }
    else if(operation == 'R')
    {

    }
    return 0;
}
