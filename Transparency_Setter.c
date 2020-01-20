#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>	//For rand
#include <math.h>	//pow, sqrt

#include "png_assist.h"


void invalid_input(){
	printf("\nWrong number of arguments provided. This is the format\n");
	printf("./Transparency_Remover --input-image [png_filename_1]--output-image [png_filename_2]\n");

	exit(1);
}

//Just to make it more obvious to people viewing the code what is happening
bool string_equals(char * a, char * b){
	return !strcmp(a, b);
}

int main(int argC, char ** argV){
	bool flag_input_image = false;
	bool flag_output_image = false;
	uint8_t input_image_index = 0;
	uint8_t output_image_index = 0;
	for(int i = 1; i < argC; i++){
		if(string_equals(argV[i], "--input-image")){
			if(++i >= argC){
				invalid_input();
			}
			flag_input_image = true;
			input_image_index = i;
		}
		else if(string_equals(argV[i], "--output-image")){
			if(++i >= argC){
				invalid_input();
			}
			flag_output_image = true;
			output_image_index = i;
		}
	}

	//A file path is not set, can't continue
	if(!flag_input_image || !flag_output_image){
		invalid_input();
	}

	png_details_t p_det;

	read_png_file(argV[input_image_index], &p_det);

	for(int y = 0; y < p_det.height; y++){
		for(int x = 0; x < p_det.width; x++){

			png_bytep px = &(p_det.row_pointers[y][x * 4]);

			if(px[3] == 0){
				px[0] = 0;
				px[1] = 0;
				px[2] = 0;
			}
		}
	}

	write_png_file(argV[output_image_index], &p_det);

	return 0;
}
