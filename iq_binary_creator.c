/*
* This file will take iq data from the given file (iq data should be in this format i,q) and convert it into signed 16 bit integer binary file (of .iq format file).
* 
* Input file name  : input_iq_data.txt
* Output file name : binary_iq_file.iq
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
	FILE *fp_1 = NULL;
	FILE *fp_2 = NULL;
	float val_1 = 0;
	float val_2 = 0;
	float max_val_i = 0;
	float max_val_q = 0;
	int16_t i_val = 0;
	int16_t q_val = 0;
	int count = 0;

	fp_1 = fopen("input_iq_data.txt","r");
	fp_2 = fopen("binary_iq_file.iq","w");

	while (!feof(fp_1))
	{
		fscanf(fp_1, "%f,%f\n", &val_1, &val_2);

		if(val_1 > max_val_i)
		{
			max_val_i = val_1;
		}

		if(val_2 > max_val_q)
		{
			max_val_q = val_2;
		}
		count++;
	}

	count = 0;
	fseek(fp_1, 0, SEEK_SET);


	while (!feof(fp_1))
	{
		fscanf(fp_1, "%f,%f\n", &val_1, &val_2);

		i_val = (int16_t)((val_1 * 10000)/max_val_i);
		q_val = (int16_t)((val_2 * 10000)/max_val_q);

		fwrite(&i_val, sizeof(int16_t), 1, fp_2);
		fwrite(&q_val, sizeof(int16_t), 1, fp_2);
		count++;
	}

	fclose(fp_1);
	fclose(fp_2);

	return 0;
}