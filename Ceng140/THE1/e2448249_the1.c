#include <stdio.h>

#define max_width 25
#define max_height 25

void fill_helper(int row, int column, int color, int image[max_height][max_width])
{
	/*this function paints the pixel in (row, column) with color and checks for other 
	pixels with its initial color around it recursively*/
	int prev_color = image[row][column];
	image[row][column] = color;
	
	if(row < max_height - 1 && image[row + 1][column] == prev_color)
	{
		fill_helper(row + 1, column, color, image);
	}
	if((row < max_height - 1 && column < max_width - 1) && image[row + 1][column + 1] == prev_color)
	{
		fill_helper(row + 1, column + 1, color, image);
	}
	if((row < max_height - 1 && column > 0) && image[row + 1][column - 1] == prev_color)
	{
		fill_helper(row + 1, column - 1, color, image);
	}
	if(image[row][column + 1] == prev_color)
	{
		fill_helper(row, column + 1, color, image);
	}
	if(column > 0 && image[row][column - 1] == prev_color)
	{
		fill_helper(row, column - 1, color, image);
	}
	if(row > 0 && image[row - 1][column] == prev_color)
	{
		fill_helper(row - 1, column, color, image);
	}
	if((row > 0 && column < max_width - 1) && image[row - 1][column + 1] == prev_color)
	{
		fill_helper(row - 1, column + 1, color, image);
	}
	if((row > 0 && column > 0) && image[row - 1][column - 1] == prev_color)
	{
		fill_helper(row - 1, column - 1, color, image);
	}
}


int main(void)
{
	int image[max_height][max_width], i, j, select_color;
	char operation;

	/*the image is obtained in this loop*/
	for(i = 0; i < max_height; i++)
	{
		for(j = 0; j < max_width; j++)
		{
			scanf("%d", &image[i][j]);
		}
	}
	
	scanf(" %c", &operation);
	
	if(operation == 'F')
	{
		int select_row, select_column, initial_row, initial_column;

		scanf("%d %d", &select_row, &select_column);
		scanf("%d %d", &initial_row, &initial_column);
		
		if(select_row < 0 && select_column < 0) select_color = 0;
		
		else if(select_row < 0 && select_column < max_width) select_color = 1;
		
		else if(select_row < 0 && select_column >= max_width) select_color = 2;
		
		else if(select_row < max_height && select_column >= max_width) select_color = 3;
		
		else if(select_row >= max_height && select_column >= max_width) select_color = 4;
		
		else if(select_row >= max_height && select_column < 0) select_color = 6;
		
		else if(select_row >= max_height && select_column < max_width) select_color = 5;
		
		else if(select_row < max_height && select_column < 0) select_color = 7;
		
		else select_color = image[select_row][select_column];
		
		fill_helper(initial_row, initial_column, select_color, image);
		
		/*the image is printed here*/		
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
		int copy_point1_row, copy_point1_col, copy_point2_row, copy_point2_col, paste_point1_row, paste_point1_col, paste_point2_row, paste_point2_col;
		int copy_top_row, copy_top_col, paste_top_row, paste_top_col;
		int changed_pixels = 0, width, height;

		scanf("%d %d %d %d", &copy_point1_row, &copy_point1_col, &copy_point2_row, &copy_point2_col);
		scanf("%d %d %d %d", &paste_point1_row, &paste_point1_col, &paste_point2_row, &paste_point2_col);

		/*copy_top_row and copy_top_col refer to the top left point of the copy area .Same goes for paste_top_row and paste_top_col.
		The following if statements are for finding those points and the height and width of the area.*/
		
		if(copy_point1_row >= copy_point2_row && copy_point1_col >= copy_point2_col)
		{
			copy_top_row = copy_point2_row;
			copy_top_col = copy_point2_col;
			height = copy_point1_row - copy_point2_row + 1;
			width = copy_point1_col - copy_point2_col + 1;
		}
		else if(copy_point1_row >= copy_point2_row && copy_point1_col <= copy_point2_col)
		{
			copy_top_row = copy_point2_row;
			copy_top_col = copy_point1_col;
			height = copy_point1_row - copy_point2_row + 1;
			width = copy_point2_col - copy_point1_col + 1;
		}
		else if(copy_point1_row <= copy_point2_row && copy_point1_col >= copy_point2_col)
		{
			copy_top_row = copy_point1_row;
			copy_top_col = copy_point2_col;
			height = copy_point2_row - copy_point1_row + 1;
			width = copy_point1_col - copy_point2_col + 1;
		}
		else
		{
			copy_top_row = copy_point1_row;
			copy_top_col = copy_point1_col;
			height = copy_point2_row - copy_point1_row + 1;
			width = copy_point2_col - copy_point1_col + 1;
		}


		if(paste_point1_row >= paste_point2_row && paste_point1_col >= paste_point2_col)
		{
			paste_top_row = paste_point2_row;
			paste_top_col = paste_point2_col;
		}
		else if(paste_point1_row >= paste_point2_row && paste_point1_col <= paste_point2_col)
		{
			paste_top_row = paste_point2_row;
			paste_top_col = paste_point1_col;
		}
		else if(paste_point1_row <= paste_point2_row && paste_point1_col >= paste_point2_col)
		{
			paste_top_row = paste_point1_row;
			paste_top_col = paste_point2_col;
		}
		else
		{
			paste_top_row = paste_point1_row;
			paste_top_col = paste_point1_col;
		}

		/*the area is copied and pasted starting from the top left pixel*/
		for(i = 0; i < height; i++)
		{
			for(j = 0; j < width; j++)
			{
				if(image[paste_top_row + i][paste_top_col + j] != image[copy_top_row + i][copy_top_col + j]) changed_pixels++;
				
				image[paste_top_row + i][paste_top_col + j] = image[copy_top_row + i][copy_top_col + j];
			}
		}

		/*the image is printed here*/
		for(i = 0; i < max_height; i++)
		{
			for(j = 0; j < max_width; j++)
			{
				printf("%d ", image[i][j]);
			}
			printf("\n");
		}
		printf("%d\n", changed_pixels);
	}
	
	else if(operation == 'R')
	{
		int degree, copy_point1_row, copy_point1_col, copy_point2_row, copy_point2_col, paste_point1_row, paste_point1_col, paste_point2_row, paste_point2_col;
		int changed_pixels = 0, height, width, paste_point_row, paste_point_col;
		char direction;

		scanf(" %c %d", &direction, &degree);
		scanf("%d %d %d %d", &copy_point1_row, &copy_point1_col, &copy_point2_row, &copy_point2_col);
		scanf("%d %d %d %d", &paste_point1_row, &paste_point1_col, &paste_point2_row, &paste_point2_col);

		height = copy_point2_row - copy_point1_row + 1;
		width = copy_point2_col - copy_point1_col + 1;

		/*(paste_point_row,paste_point_col) refers to the point (copy_point1_row,copy_point1_col) is supposed
		to be pasted and the pasting is done starting from that point*/
		if((direction == 'R' && degree == 90) || (direction == 'L' && degree == 270))
		{
			paste_point_row = paste_point1_row;
			paste_point_col = paste_point2_col;
			
			for(i = 0; i < height; i++)
			{
				for (j = 0; j < width; j++)
				{
					if(image[paste_point_row + j][paste_point_col - i] != image[copy_point1_row + i][copy_point1_col + j]) changed_pixels++;

					image[paste_point_row + j][paste_point_col - i] = image[copy_point1_row + i][copy_point1_col + j];
				}
			}	
		}
		else if((direction == 'R' && degree == 180) || (direction == 'L' && degree == 180))
		{
			paste_point_row = paste_point2_row;
			paste_point_col = paste_point2_col;
			
			for(i = 0; i < height; i++)
			{
				for (j = 0; j < width; j++)
				{
					if(image[paste_point_row - i][paste_point_col - j] != image[copy_point1_row + i][copy_point1_col + j]) changed_pixels++;

					image[paste_point_row - i][paste_point_col - j] = image[copy_point1_row + i][copy_point1_col + j];
				}
			}	
		}
		else if((direction == 'R' && degree == 270) || (direction == 'L' && degree == 90))
		{
			paste_point_row = paste_point2_row;
			paste_point_col = paste_point1_col;
			
			for(i = 0; i < height; i++)
			{
				for (j = 0; j < width; j++)
				{
					if(image[paste_point_row - j][paste_point_col + i] != image[copy_point1_row + i][copy_point1_col + j]) changed_pixels++;

					image[paste_point_row - j][paste_point_col + i] = image[copy_point1_row + i][copy_point1_col + j];
				}
			}	
		}

		/*the image is printed here*/
		for(i = 0; i < max_height; i++)
		{
			for(j = 0; j < max_width; j++)
			{
				printf("%d ", image[i][j]);
			}
			printf("\n");
		}
		printf("%d\n", changed_pixels);
	}
	return 0;
}