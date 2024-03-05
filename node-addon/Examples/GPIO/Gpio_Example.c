#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 200

#define ON 1
#define OFF 0



#define Reliability_Fire 319
#define HI_MAGA 321
#define LO_MAGA 323
#define SINI_UP 325
#define SINI_DN 324
#define SINI_IN 322
#define UUT_Power 320


void GPIO_CONFIG(void);
void exportGpio(int pin);
void setGpioDirection(int pin, const char *direction);
void writeGpioValue(int pin, int value);


int main(){

    GPIO_CONFIG();
    writeGpioValue(Reliability_Fire,OFF);
    writeGpioValue(HI_MAGA,OFF);
    writeGpioValue(LO_MAGA,OFF);
    writeGpioValue(SINI_UP,OFF);
    writeGpioValue(SINI_DN,OFF);
    writeGpioValue(SINI_IN,OFF);
    writeGpioValue(UUT_Power,OFF);

    return 0;
    
}

void GPIO_CONFIG(void){
    printf("GPIO_CONFIG for Discretes start\n");

    //0xA0001000
    for(int gpioPin = 319;gpioPin<=325;gpioPin++){
        exportGpio(gpioPin);
        setGpioDirection(gpioPin,"out");
    }    
    printf("Done confing\n");
}



void exportGpio(int pin){
    FILE *exportFile = fopen("/sys/class/gpio/export","w");
    if(exportFile == NULL){
        perror("error openening export file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(exportFile,"%d",pin);
    fclose(exportFile);
}



void setGpioDirection(int pin, const char *direction) {
    char path[MAX_SIZE];
    snprintf(path, MAX_SIZE, "/sys/class/gpio/gpio%d/direction", pin);

    FILE *directionFile = fopen(path, "w");

    if (directionFile == NULL) {
        perror("Error opening direction file");
        exit(EXIT_FAILURE);
    }

    fprintf(directionFile, "%s", direction);
    fclose(directionFile);
}




void writeGpioValue(int pin, int value) {

    char write_path[MAX_SIZE];
    snprintf(write_path, MAX_SIZE, "/sys/class/gpio/gpio%d/value", pin);

    FILE *valueFile = fopen(write_path, "w");

    if (valueFile == NULL) {
        perror("Error opening value file");
        exit(EXIT_FAILURE);
    }

    fprintf(valueFile, "%d", value);
    fclose(valueFile);
}

