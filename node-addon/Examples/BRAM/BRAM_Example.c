#include <stdio.h>
#include <stdlib.h>


void ARinc_Height();
void ARinc_WoW();


int main(){
	
	ARinc_Height();
	ARinc_WoW();
	
	return 0;
}


void ARinc_Height(){
	long height_bram_addr = 0xa0030000; 
	long height_data = 0xE4C80074; //random data
	
	char write_height[100];
	snprintf(write_height,sizeof(write_height),"devmem2 0x%lx W 0x%lx",height_bram_addr,height_data);
	
	int height_result = system(write_height);
	if(height_result == 0) { 
		printf("Data Written successfully.\n");
	} else{
		fprintf(stderr,"Error writing data using devmem2.\n");
	}
}



void ARinc_WoW() {

	long WoW_bram_addr = 0xa0032000;
	long WoW_data = 0x810420F6; //random data
	
	char write_WoW[100];
	snprintf(write_WoW,sizeof(write_WoW),"devmem2 0x%lx W 0x%lx",WoW_bram_addr,WoW_data);

	int WoW_result = system(write_WoW);
	if(WoW_result == 0) { 
		printf("Data Written successfully.\n");

	} else{
		fprintf(stderr,"Error writing data using devmem2.\n");
	}



}
