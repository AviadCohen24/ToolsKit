#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace HardwareManager {
    constexpr int MAX_SIZE = 200;

    // GPIO Pin Definitions
    enum GPIO_PINS {
        Reliability_Fire = 319,
        HI_MAGA = 321,
        LO_MAGA = 323,
        SINI_UP = 325,
        SINI_DN = 324,
        SINI_IN = 322,
        UUT_Power = 320
    };

    // GPIO Operations
    void GPIO_CONFIG();
    void exportGpio(int pin);
    void setGpioDirection(int pin, const char* direction);
    void writeGpioValue(int pin, int value);

    // BRAM Operations
    void ARinc_Height();
    void ARinc_WoW();

    // Functions Implementions
    void GPIO_CONFIG() {
        printf("GPIO_CONFIG for Discretes start\n");

        for(int gpioPin = Reliability_Fire; gpioPin <= SINI_UP; gpioPin++) {
            exportGpio(gpioPin);
            setGpioDirection(gpioPin, "out");
        }
        printf("Done confing\n");
    }

    void exportGpio(int pin) {
        FILE *exportFile = fopen("/sys/class/gpio/export", "w");
        if(exportFile == nullptr) {
            perror("error opening export file\n");
            exit(EXIT_FAILURE);
        }
        fprintf(exportFile, "%d", pin);
        fclose(exportFile);
    }

    void setGpioDirection(int pin, const char *direction) {
        char path[MAX_SIZE];
        snprintf(path, MAX_SIZE, "/sys/class/gpio/gpio%d/direction", pin);

        FILE *directionFile = fopen(path, "w");
        if (directionFile == nullptr) {
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
        if (valueFile == nullptr) {
            perror("Error opening value file");
            exit(EXIT_FAILURE);
        }

        fprintf(valueFile, "%d", value);
        fclose(valueFile);
    }

    void Write_Height(long height_data){
	    long height_bram_addr = 0xa0030000; 
    
	    char write_height[100];
	    snprintf(write_height,sizeof(write_height),"devmem2 0x%lx W 0x%lx",height_bram_addr,height_data);
    
	    int height_result = system(write_height);
	    if(height_result == 0) { 
	    	printf("Data Written successfully.\n");
	    } else{
	    	fprintf(stderr,"Error writing data using devmem2.\n");
	    }
    }

    void Write_WoW(long WoW_data) {
	    long WoW_bram_addr = 0xa0032000;
    
	    char write_WoW[100];
	    snprintf(write_WoW,sizeof(write_WoW),"devmem2 0x%lx W 0x%lx",WoW_bram_addr,WoW_data);

	    int WoW_result = system(write_WoW);
	    if(WoW_result == 0) { 
	    	printf("Data Written successfully.\n");

	    } else{
	    	fprintf(stderr,"Error writing data using devmem2.\n");
	    }
    }
}