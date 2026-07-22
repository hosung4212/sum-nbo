#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
	if (argc < 2){
		printf("syntax : %s <file1> [<file2>...]\n", argv[0]);
		return -1;
	}
	uint32_t sum= 0;
	for (int i =1; i < argc; i++){
		FILE *fp = fopen(argv[i],"rb");
		if (fp == NULL){
			printf("Cannot open %s\n", argv[i]);
			return -1;
		}
		uint32_t network_num;
		size_t read_count = fread(&network_num, sizeof(uint32_t),1,fp);
		if (read_count !=1){
			printf("Failed to read 4 bytes from %s\n", argv[i]);
			fclose(fp);
			return -1;
		}
		fclose(fp);
		uint32_t host_num = ntohl(network_num);
		sum += host_num;
		printf("%u(0x%08x)", host_num, host_num);
		if (i < argc -1){
			printf(" + ");
		}
	}
	printf(" = %u(0x%08x)\n", sum, sum);
	return 0;

}
