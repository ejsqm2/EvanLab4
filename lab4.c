#include <stdio.h>
#include <stdlib.h>

void readFile(double data[], char* str);
void printFile(char* str, double data[]);
void offset(double data[], double offset);
void scale(double data[], double n);
void stats(double data[], char* str);
void center(double data[]);
void normal(double data[]);

int main(){
	char str[15];
	int file;
	double data[2000];
	printf("What file do you want to choose? ");
	scanf("%d", &file);	//get file name
	sprintf(str, "Raw_data_%02d.txt", file); //save file name as a string
	printf("You chose the file: %s\n", str);
	readFile(data, str);//save data from file
	printf("Read file correctly\n");
	
	int choice;
	double value;
	printf("Would you like to \n(1)Offset\n(2)Scaling Factor\n");
        printf("(3)Statistics\n(4)Center\n(5)Normalize\n>>");
	scanf("%d", &choice);
        
	if(choice==1){//options
		printf("Enter value for offset: ");
		scanf("%lf", &value);
                data[1] = value;
                sprintf(str, "Offset_data_%02d.txt", file);
                offset(data, value);
                printFile(str, data);
	}	
	else if(choice==2){
		printf("Enter scaling value: ");
		scanf("%lf", &value);
                data[1] = value;
                sprintf(str, "Scaled_data_%02d.txt", file);
                scale(data, value);
                printFile(str, data);
	}
        else if(choice==3){
            sprintf(str, "Statistics_data_%02d.txt", file);
            stats(data, str);
	}
        else if(choice==4){
	        sprintf(str, "Centered_data_%02d.txt", file);
                center(data);
                printFile(str, data);
	}
	else if(choice==5){
	        sprintf(str, "Normalized_data_%02d.txt", file);
                normal(data);
                printFile(str, data);
	}
	
        return 0;
}

void readFile(double data[], char* str){
        FILE* fp;
        fp = fopen(str, "r");//open file
        double size, max;
        fscanf(fp, "%lf %lf", &size, &max);//get size and max value
        data[0] = size;
        data[1] = max;//first two values in array 
        int i;
        for(i=2; i<data[0]+2; i++){
                fscanf(fp,"%lf", &data[i]);//get data from file
	}
        fclose(fp);//close file

}

void printFile(char* str, double* data){
	FILE* fp = fopen(str, "w");//open file
	if(fp==NULL)
		printf("error opening file\n");
	fprintf(fp,"%d %.4lf\n", (int)data[0], data[1]);//print first row
	
	int i;
	for(i=2; i<(data[0]+2); i++){
            fprintf(fp, "%.4lf\n", data[i]);//print data to file
	}
	fclose(fp);//close file
	printf("Data printed to %s\n", str);
}

void offset(double* data, double offset){
    int i;
    for(i=2; i<data[0]+2; i++){
        data[i]+=offset;
    }
}
void scale(double* data, double n){
    int i;
    for(i=2; i<data[0]+2; i++){
        data[i]*=n;
    }
}
void stats(double* data, char* str){
    double max, total=0, average;
    max = data[2];//set max to first value
    int i;
    for(i=2; i<data[0]+2; i++){
        total += data[i];//get total for average
        if(data[i]>max)
            max = data[i];//reset max if larger number is found
    }
    average = total/data[0];
    FILE* fp = fopen(str, "w");//write info to file
    fprintf(fp, "%.4lf %.4lf\n", average, max);
    printf("Data printed to %s\n\n", str);
    fclose(fp);//close file
}
void center(double data[]){
    double total=0, average;
    int i;
    for(i=2; i<data[0]+2; i++){
        total += data[i];//get total for average
    }
    average = total/data[0];
    offset(data, (average*-1));//offset data with average to center
}

void normal(double data[]){
    double max;
    max = data[2];//set max to first value
    int i;
    for(i=2; i<data[0]+2; i++){
        if(data[i]>max)
            max = data[i];//reset max if larger number is found
    }
    scale(data, (1/max));//call scale function with scale of 1/max
    
}