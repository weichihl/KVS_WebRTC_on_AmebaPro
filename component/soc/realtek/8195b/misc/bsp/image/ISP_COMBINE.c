#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024
#define HEADER_SIZE 64
int get_file_size(FILE *fp)
{
	int size = 0;
	if(fp){
		fseek(fp, 0, SEEK_END); // seek to end of file
		size = ftell(fp);
	}
	fseek(fp, 0, SEEK_SET);
	return size;
}
int fwite_isp_bin(char *str,FILE *fw)
{
	FILE *fr = NULL;
	int size = 0;
	unsigned char *buffer = NULL;
	if((fr = fopen(str,"rb")) == NULL){
		printf("Open failed %s\r\n",str);
		return -1;
	}else{
		printf("Open %s\r\n",str);
	}
	size = get_file_size(fr);
	buffer = (unsigned char *)malloc(size);
	fread(buffer,1,size,fr);
	fwrite(buffer,1,size,fw);
	fclose(fr);
	return size;
}
unsigned int swap_int32(unsigned int val )
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF ); 
    return (val << 16) | ((val >> 16) & 0xFFFF);
}
int hexadecimalToDecimal(char hexVal[]) 
{    
    int len = strlen(hexVal); 
      
    // Initializing base value to 1, i.e 16^0 
    int base = 1; 
      
    int dec_val = 0; 
      
	int i = 0;  
    // Extracting characters as digits from last character 
    for (i=len-1; i>=0; i--) 
    {    
        // if character lies in '0'-'9', converting  
        // it to integral 0-9 by subtracting 48 from 
        // ASCII value. 
        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
                  
            // incrementing base by power 
            base = base * 16; 
        } 
  
        // if character lies in 'A'-'F' , converting  
        // it to integral 10 - 15 by subtracting 55  
        // from ASCII value 
        else if (hexVal[i]>='A' && hexVal[i]<='F') 
        { 
            dec_val += (hexVal[i] - 55)*base; 
          
            // incrementing base by power 
            base = base*16; 
        } 
    } 
      
    return dec_val; 
}

char *strlwr(char *s)
{
	 char *str;
	 str = s;
	 while(*str != '\0')
	 {
		if(*str >= 'A' && *str <= 'Z') {
		 *str += 'a'-'A';
		}
		str++;
	 }
	 return s;
}
#define REMOVE_LEN 12
#define DISK_INDEX 10
//#define CYGWIN
#define LINUX
int main(int argc, char *argv[])
{
	FILE *fp = NULL; 
	FILE *fw = NULL;
	//FILE *fd = NULL;
	int i = 0;
	char strLine[MAX_LINE];
	printf("argc = %d\r\n",argc);
	if(argc>0){
		for(i =0;i<argc;i++){
			printf("index %d name=%s\r\n",i,argv[i]);
		}
	}
	char *temp_buf = (char *)malloc(1024);
	char disk_value = 0;
	unsigned int index[64] = {0};
	unsigned int size[64] = {0};
	unsigned int buffer[16] = {0};
	char file_name[1024] = {0};
	char str[64]={0};
	char sensor_config_file_name[1024] = {0};
	char sensor_combine_file_name[1024] = {0};
	char write_path[1024]={0};
	
	char *ptr = NULL;
	int diff = 0;
	unsigned char count = 0;
	unsigned int file_index = 0;
	unsigned int file_size = 0;
	int size_total = 0;
	
	if(argc >=3){
#ifdef CYGWIN
		memset(temp_buf,0,1024);
		sprintf(temp_buf,"%s",argv[1]);//SENSOR CONFIG PATH
		disk_value = temp_buf[DISK_INDEX];
		sprintf(sensor_config_file_name,"%c://%s",disk_value,temp_buf+REMOVE_LEN);
#else
		sprintf(sensor_config_file_name,"%s",argv[1]);
#endif
		if((fp = fopen(sensor_config_file_name,"r")) == NULL){
			perror(sensor_config_file_name);
			if(temp_buf)
				free(temp_buf);
			//getchar();
			return -1;
		}else{
#ifdef CYGWIN
			memset(temp_buf,0,1024);
			sprintf(temp_buf,"%s",argv[2]);//SENSOR COMBINE PATH
			sprintf(sensor_combine_file_name,"%c://%s",disk_value,temp_buf+REMOVE_LEN);
#else
			sprintf(sensor_combine_file_name,"%s",argv[2]);
#endif
			printf("sensor_combine_file_name = %s\r\n",sensor_combine_file_name);
		}
	}else{
		printf("The command is wrong\r\n");
		if(temp_buf)
			free(temp_buf);
		//getchar();
		return -1;
	}
	sprintf(write_path,"%s%s",sensor_combine_file_name,"isp.bin");
	if((fw = fopen(write_path,"wb")) == NULL)
	{
		perror(write_path);
		//getchar();
		if(fp)
			fclose(fp);
		if(temp_buf)
			free(temp_buf);
		return -1;
	}
	fseek(fw,HEADER_SIZE,SEEK_SET);
	while (!feof(fp))									
	{
		memset(strLine,0,sizeof(strLine));
		fgets(strLine,MAX_LINE,fp);
		memset(str,0,sizeof(str));
		for(i =0;i<strlen(strLine);i++){
			if(strLine[i] == '\n'|| strLine[i]<32)
				strLine[i]=0;
		}
		printf("%s \r\n",strLine);
		ptr == NULL;
		ptr = strstr(strLine,",");
		if(ptr== NULL)
			continue;
		diff = ptr-strLine;
		for(i =0;i<diff;i++)
			str[i]=strLine[i];
		index[count] =  hexadecimalToDecimal(str);//atoi(str);
		printf("%s %x\r\n",str,hexadecimalToDecimal(str));
		file_index = index[count];
		ptr = strstr(strLine,"_")+1;
		memset(file_name,0,sizeof(file_name));
		sprintf(file_name,"%sisp_%s.bin",sensor_combine_file_name,strlwr(ptr));
		file_size = fwite_isp_bin(file_name,fw);
		size[count] = file_size;
		size_total+=file_size;
#ifdef ENABLE_SWAP_ISP
		buffer[count*2] = swap_int32(file_index);//Index
		buffer[count*2+1] = swap_int32(HEADER_SIZE+size_total-file_size);//Offset
#else
		buffer[count*2] = file_index;//Index
		buffer[count*2+1] = HEADER_SIZE+size_total-file_size;//Offset
#endif
		count++;
	}
	unsigned char *ptr_value =(unsigned char *)buffer;
	fseek(fw,0,SEEK_SET);
	fwrite(ptr_value,1,64,fw);
	
	printf("ISP Combine finish\r\n");
	if(fp)
		fclose(fp);
	if(fw)
		fclose(fw);
	if(temp_buf)
		free(temp_buf);
	//getchar();
	
	return 0; 
}