#include <stdio.h>


void fill_helper(int row, int column, int color, int image[5][5])
{
    if(image[row + 1][column] == image[row][column])
    {
        image[row + 1][column] == color;
        fill_helper(row + 1, column, color, image);
    }
    if(image[row + 1][column + 1] == image[row][column])
    {
        image[row + 1][column + 1] == color;
        fill_helper(row + 1, column + 1, color, image);
    }
    if(image[row + 1][column - 1] == image[row][column])
    {
        image[row + 1][column - 1] == color;
        fill_helper(row + 1, column - 1, color, image);
    }
    if(image[row][column + 1] == image[row][column])
    {
        image[row][column + 1] == color;
        fill_helper(row, column + 1, color, image);
    }
    if(image[row][column - 1] == image[row][column])
    {
        image[row][column - 1] == color;
        fill_helper(row, column - 1, color, image);
    }
    if(image[row - 1][column] == image[row][column])
    {
        image[row - 1][column] == color;
        fill_helper(row - 1, column, color, image);
    }
    if(image[row - 1][column + 1] == image[row][column])
    {
        image[row - 1][column + 1] == color;
        fill_helper(row - 1, column, color, image);
    }
    if(image[row - 1][column - 1] == image[row][column])
    {
        image[row - 1][column - 1] == color;
        fill_helper(row - 1, column - 1, color, image);
    }
    image[row][column] = color;
}


int main(void)
{
    int image[5][5], row, column, color, i, j;
    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            scanf("%d", &image[i][j]);
        }
    }
    fill_helper(1, 2, 1, image);
    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }
}
