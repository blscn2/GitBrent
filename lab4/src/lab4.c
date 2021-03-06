/*
 ============================================================================
 Name        : lab4.c
 Author      : Brent Schultz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
int *Readfile(int file);
void helpmenu();
void renameFile(char *new_filename, int oldfilenum);
void WriteFile(char file_name[20], double *array, double x);
double mean(int *array);
double max(int *array);
void createStatisticsFile(int *array, int file);
void offsetSignal(int *array, double offset_value, char file_name[20]);
void scaleSignal(int *array, double scale_factor, char file_name[20]);
void centerSignal(int *array, char file_name[20]);
void normalizeSignal(int *array, char file_name[20]);

//Global variables
int length = 0;
double offset,scale;
int max_value;

int main( int argc, char *argv[]){
	int i, statistics = 0, center = 0, normalize = 0, rename = 0, filenumber = 0, help = 0, offset_check = 0, scale_check = 0;
	float offset_value = 0, scale_factor = 0;
	char *filename = NULL;
	char file_name[50];

	// Loop through command line to find needed key words
	for(i=1;i<argc;i++){
		printf("Command line argument: %s \n", argv[i]);
		// if "-n" in argument
		if(strcmp(argv[i],"-n") == 0){

			filenumber = atoi(argv[i+1]);
			if(filenumber != 0){
				i++;
			}
		}

		// if "-o" in argument
		else if(strcmp(argv[i],"-o") == 0){
			offset_check = 1;

			offset_value = atof(argv[i+1]);
			if(offset_value != 0){
				// skip over the offset value to the next argument
				i++;
			}
		}

		// if "-s" in argument
		else if(strcmp(argv[i],"-s") == 0){
			scale_check = 1;
			scale_factor = atof(argv[i+1]);
			if(scale_factor != 0){
				// skip over the scale factor to the next argument
				i++;
			}
		}
		// if "-S" in argument
		else if(strcmp(argv[i],"-S") == 0){
			statistics = 1;
		}
		// if "-C" in argument
		else if(strcmp(argv[i],"-C") == 0){
			center = 1;
		}
		// if "-N" in argument
		else if(strcmp(argv[i],"-N") == 0){
			normalize = 1;
		}
		// if "-r" in argument
		else if(strcmp(argv[i],"-r") == 0){
			filename = argv[i+1];
			// check that a newfilename was given
			if(filename == NULL){
				printf("No new filename given\n");
			}
			else if(strcmp(filename,"-n") == 0){
				printf("No new filename given\n");
			}
			else if(strcmp(filename,"-o") == 0){
				printf("No new filename given\n");
			}
			else if(strcmp(filename,"-s") == 0){
				printf("No new filename given\n");
			}
			else if(strcmp(filename,"-S") == 0){
				printf("No new filename given\n");
			}
			else if(strcmp(filename,"-C") == 0){
				printf("No new filename given\n");
			}
			else if(strcmp(filename,"-N") == 0){
				printf("No new filename given\n");
			}
			else if(strcmp(filename,"-r") == 0){
				printf("No new filename given\n");
			}
			else if(strcmp(filename,"-h") == 0){
				printf("No new filename given\n");
			}
			else{
				rename = 1;
				i++;
			}
		}
		// if "-h" in argument
		else if(strcmp(argv[i],"-h") == 0){
			help = 1;
		}

	}

		// if the help flag is set
		if(help == 1){
			helpmenu();
			return 0;
		}

		// if no file number was given
		if(filenumber == 0){
			printf("No file number given\n");
			return -1;
		}else{
			if((filenumber < 1) | (filenumber > 20)){
				printf("Invalid file number\n");
				return -1;
			}
		}

		// read from the file
		int *array = Readfile(filenumber);
		if(array == NULL){
			printf("Could not find file\n");
			return -1;
		}

		// if the offset flag is set
		if(offset_check == 1){
			if(offset_value == 0){
				printf("No offset value\n");
			}else{
				printf("Offsetting values by %.2f \n", offset_value );
				if(filenumber<10){
					sprintf(file_name,"Offset_data_0%d.txt",filenumber);
				}else{
					sprintf(file_name,"Offset_data_%d.txt",filenumber);
				}
				offsetSignal(array, offset_value, file_name);
			}
		}

		// if the scale flag is set
		if(scale_check == 1){
			printf("File number = %d \n", filenumber);
			if(scale_factor == 0){
				printf("No scale factor\n");
			}else{
				printf("Scaling by a factor of %.2f \n", scale_factor);
				if(filenumber<10){
					sprintf(file_name,"Scaled_data_0%d.txt",filenumber);
				}else{
					sprintf(file_name,"Scaled_data_%d.txt",filenumber);
				}
				scaleSignal(array, scale_factor, file_name);
			}
		}

		// if the rename flag is set
		if(rename == 1){
			printf("Doing rename\n");
			renameFile(filename,filenumber);
		}

		// if the statistics flag is set
		if(statistics == 1){
			printf("Doing statistics\n");
			createStatisticsFile(array,filenumber);
		}

		// if the center flag is set
		if(center == 1){
			printf("Doing center \nFilenumber = %d \n", filenumber);
			if(filenumber<10){
				sprintf(file_name,"Centered_data_0%d.txt",filenumber);
			}else{
				sprintf(file_name,"Centered_data_%d.txt",filenumber);
			}

			printf("New text file created.\n");
			centerSignal(array,file_name);
		}

		// if the normalize flag is set
		if(normalize == 1){
			printf("Doing normalize\nFilenumber = %d \n", filenumber);
			if(filenumber<10){
				sprintf(file_name,"Normalized_data_0%d.txt",filenumber);
			}else{
				sprintf(file_name,"Normalized_data_%d.txt",filenumber);
			}

			printf("Created normalized data txt file.\n");
			normalizeSignal(array,file_name);
		}
	return 0;
}




// This function reads in the data from a file to an integer array and returns a pointer to the array
int *Readfile(int file){
 	int cell, i;
 	int array[2000];
 	int *arrayPtr = array;
	char file_name[20];

	//Formats the file name based on the number input by the user
	if(file<9){ // includes a zero in the name
		sprintf(file_name,"Raw_data_0%d.txt",file);
	}else{ //doesn't include a zero in the name
		sprintf(file_name,"Raw_data_%d.txt",file);
	}
	FILE *fp = fopen(file_name,"r");
	if (fp == NULL){
		return NULL;
	}
	fscanf(fp,"%d %d",&length,&max_value);
	for(i=0;i<length;i++){
		fscanf(fp,"%d",&cell);
		array[i] = cell;
	}

	fclose(fp);
	return arrayPtr;
}

// This function displays the help menu
void helpmenu(){
	printf("The options/parameters that need to be handled are:\n");
	printf("\t-n: File Number\n");
	printf("\t-o: Offset Signal\n");
	printf("\t-s: Scale Signal\n");
	printf("\t-S: Create Statistics File\n");
	printf("\t-C: Center Signal\n");
	printf("\t-N: Normalize Signal\n");
	printf("\t-r: Rename File\n");
	printf("\t-h: Display help menu\n");
}

// This function creates a new file with the new filename given and writes the contents to it
void renameFile(char *new_filename, int oldfilenum){
	int cell, i;
	char file_name[20];
	//Formats the file name based on the number input by the user
	if(oldfilenum<9){ // includes a zero in the name
		sprintf(file_name,"Raw_data_0%d.txt",oldfilenum);
	}else{ //doesn't include a zero in the name
		sprintf(file_name,"Raw_data_%d.txt",oldfilenum);
	}

	FILE *fp = fopen(file_name,"r");
	FILE *out = fopen(new_filename,"w");
	fscanf(fp,"%d %d",&length,&max_value);
	fprintf(out,"%d %d\n",length,max_value);
	for(i=0;i<length;i++){
		fscanf(fp,"%d",&cell);
		fprintf(out,"%d\n",cell);
	}

	fclose(fp);
	fclose(out);
}

// This function writes the values in a double array to a file
void WriteFile(char file_name[20], double *array, double x){ // the x represents the offset or scale factor used in the transformations
	int i;

	FILE *fp = fopen(file_name,"w");
	if(fp == NULL){
		printf("Error opening file\n");
	}
	fprintf(fp,"%d %.2f\r\n",length,x);
	for(i=0;i<length;i++){
		fprintf(fp,"%.2f\r\n",array[i]);
	}
	fclose(fp);
}

// This function calculates the mean (average) of an integer array
double mean(int *array){
	double total = 0.0;
	int i=0;
	for(i=0;i<length;i++){
		total = total+(double)array[i];
	}
	return total/(double)length; //type cast because length is type int
}

// This function returns the maximum possible value of the signal
double max(int *array){

	return (double)max_value;
}

// This function generates a file containing the mean and max of each raw file
void createStatisticsFile(int *array, int file){

	char file_name[50];
	if(file<10){
		sprintf(file_name,"Statistics_data_0%d.txt",file);
	}else{
		sprintf(file_name,"Statistics_data_%d.txt",file);
	}

	FILE * fp = fopen(file_name,"w");
	fprintf(fp,"%.4f %.0f \n",mean(array),max(array));
	fclose(fp);
	printf("Statistics text file created.\n");
}

// This function offsets the signal based on an offset value inputted
void offsetSignal(int *array, double offset_value, char file_name[20]){
	int i;
	double arrayD[2000];
	for(i=0;i<length;i++){
		arrayD[i] = (double)array[i] + offset_value;
	}
	//Writes the new array to a file
	WriteFile(file_name, arrayD, offset_value);
}

//This function scales the signal based on a scale factor inputted
void scaleSignal(int *array, double scale_factor, char file_name[20]){
	int i;

	double arrayD[2000];
	for(i=0;i<length;i++){
		arrayD[i] = (double)array[i] * scale_factor;
	}
	//Writes the new array to a file
	WriteFile(file_name, arrayD, scale_factor);
}

//This function centers the signal
void centerSignal(int *array, char file_name[20]){

	offsetSignal(array, -(mean(array)), file_name);
}

// This function normalizes the signal
void normalizeSignal(int *array, char file_name[20]){

	scaleSignal(array, 1/(max(array)), file_name);
}
