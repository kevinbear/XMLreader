#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <cstring>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
//FILE *read = fopen("2007_000033.xml","r+");
//FILE *write = fopen("2007_000033.txt", "w+");
//char *temp = NULL;
long fileToStr(char *fileName, int *sizePtr);
char *innerText(char *storest, char *pfile, char *beginMark, char *endMark);
int innerText_num(char *storest, char *pfile, char *beginMark, char *endMark);
int strcount(char *inpustr,char* comstr);
//int main()
//{
//
//	temp = (char *)malloc(sizeof(char)*1500);
//	memset(temp,'\0',1500);
//	fread(temp,1,sizeof(char)*1500,read);
//	fwrite(temp,sizeof(char),sizeof(char)*1500,write);
//	puts("job finish");
//	system("pause");
//	return 0;
//}
char *beginStart;
char *beginEnd;
char *endStart;
static char *xml = NULL;
static char *xxx = NULL;
int main(int argc, char *argv[]) 
{
	int filecount =67 ,year=2009,i=0;
	char filename[100];
	char imagename[100];
	char name[20], bndbox[10],w[5],h[5],xMax[5],xMin[5],yMax[5],yMin[5];
	int xmin, xmax, ymin, ymax, width, height,bboxcount;
	Mat framei, frameo;

	while (1)
	{	
		//year = 2007;
		//std::cout << "-------1231-------" << std::endl;
		//std::cout << "year=" << year << " " << "filecount=" << filecount << std::endl;
		/*讀取檔名*/
		if (filecount >=0 && filecount <=9 )
		{
			//std::cout << "111111111111" << std::endl;
			//std::cout << "year="<< year <<" "<<"filecount="<<filecount<< std::endl;
			sprintf(filename, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\Annotations\\%d_00000%d.xml", year, filecount);
			sprintf(imagename, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\JPEGImages\\%d_00000%d.jpg", year, filecount);
			FILE *file = fopen(filename, "rb");
			filecount++;
			if (file == NULL) continue;

			printf("filename=%s\n", filename);
			fseek(file, 0, SEEK_END);
			long sizel = ftell(file);
			rewind(file);
			xml = (char*)malloc(sizel + 1);
			xxx = (char*)malloc(sizel + 1);
			fread(xml, sizel, 1, file);
			xxx = xml;
			bboxcount = strcount(xxx, "<bndbox>");//計算bndbox數量讓後續讀檔動作停止使用
			//system("pause");
		}
		if (filecount >=10 && filecount <=99)
		{
			//std::cout << "111111111111" << std::endl;
			//std::cout << "year="<< year <<" "<<"filecount="<<filecount<< std::endl;
			sprintf(filename, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\Annotations\\%d_0000%d.xml",year, filecount);
			sprintf(imagename, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\JPEGImages\\%d_0000%d.jpg",year, filecount);
			FILE *file = fopen(filename, "rb");
			filecount++;
			if (file == NULL) continue;

			printf("filename=%s\n", filename);
			fseek(file, 0, SEEK_END);
			long sizel = ftell(file);
			rewind(file);
			xml = (char*)malloc(sizel + 1);
			xxx = (char*)malloc(sizel + 1);
			fread(xml, sizel, 1, file);
			xxx = xml;
			bboxcount = strcount(xxx, "<bndbox>");//計算bndbox數量讓後續讀檔動作停止使用
			//system("pause");
		}
		else if (filecount > 99 && filecount <= 999)
		{
			//std::cout << "22222222222" << std::endl;
			//std::cout << "year=" << year << " " << "filecount=" << filecount << std::endl;
			sprintf(filename, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\Annotations\\%d_000%d.xml", year, filecount);
			sprintf(imagename, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\JPEGImages\\%d_000%d.jpg", year, filecount);
			FILE *file = fopen(filename, "rb");
			filecount++;
			if (file == NULL) continue;
			printf("filename=%s\n", filename);
			fseek(file, 0, SEEK_END);
			long sizel = ftell(file);
			rewind(file);
			xml = (char*)malloc(sizel + 1);
			xxx = (char*)malloc(sizel + 1);
			fread(xml, sizel, 1, file);
			xxx = xml;
			bboxcount = strcount(xxx, "<bndbox>");//計算bndbox數量讓後續讀檔動作停止使用
			//system("pause");
		}
		else if (filecount > 999 && filecount <= 9999)
		{
			//std::cout << "3333333333" << std::endl;
			//std::cout << "year=" << year << " " << "filecount=" << filecount << std::endl;
			sprintf(filename, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\Annotations\\%d_00%d.xml", year, filecount);
			sprintf(imagename, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\JPEGImages\\%d_00%d.jpg", year, filecount);
			FILE *file = fopen(filename, "rb");
			filecount++;
			if (file == NULL) continue;
			printf("filename=%s\n", filename);
			fseek(file, 0, SEEK_END);
			long sizel = ftell(file);
			rewind(file);
			xml = (char*)malloc(sizel + 1);
			xxx = (char*)malloc(sizel + 1);
			fread(xml, sizel, 1, file);
			xxx = xml;
			bboxcount = strcount(xxx, "<bndbox>");//計算bndbox數量讓後續讀檔動作停止使用
			//system("pause");
		}
		if (filecount >= 9999)//增加年分
		{
			year++;
			filecount = 0;
			i = 0;
			continue;
		}
		if (year > 20010) break; //結束條件
		
		/*切割圖黨內樣本*/
		while (1)
		{
			printf("bboxcount=%d\n",bboxcount);
			if (i >= bboxcount)
				break;
			innerText(name, xml, "<name>", "<");
			printf("name=%s\n", name);

			xmax = innerText_num(xMax, xml, "<xmax>", "<");
			xmin = innerText_num(xMin, xml, "<xmin>", "<");
			ymax = innerText_num(yMin, xml, "<ymax>", "<");
			ymin = innerText_num(yMin, xml, "<ymin>", "<");
			
			printf("xmin=%d xmax=%d ymin=%d ymax=%d\n", xmin, xmax, ymin, ymax);
			framei = imread(imagename, -1);
			//printf("%s\n",imagename);
			//system("pause");
			frameo = framei(cvRect(xmin, ymin, xmax - xmin, ymax - ymin));
			char imgname[100];
			if (filecount >=0 && filecount <= 9)
				sprintf(imgname, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\samplefile\\%d_00000%d_out%s%d.jpg", year, filecount - 1, name, i);
			if (filecount >= 10 && filecount <= 99)
				sprintf(imgname, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\samplefile\\%d_0000%d_out%s%d.jpg",year, filecount-1, name, i);
			if (filecount > 99 && filecount <= 999)
				sprintf(imgname, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\samplefile\\%d_000%d_out%s%d.jpg", year, filecount-1, name, i);
			if (filecount > 999 && filecount <= 9999)
				sprintf(imgname, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\samplefile\\%d_00%d_out%s%d.jpg", year, filecount-1, name, i);
			imwrite(imgname, frameo);
			printf("------------------\n");
			i++;
		}
		i = 0;
	}
	//free(xml);
	system("pause");
	return 0;
}

// 檔案輸出入 
/*long fileToStr(char *fileName, int *sizePtr)
{
	printf("fileName=%s\n", fileName);
	FILE *file = fopen(fileName, "rb");
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);
	char *buffer = (char*)malloc(size + 1);
	fread(buffer, size, 1, file);
	fclose(file);
	printf("size=%d",size);
	system("pause");
	return size;
}*/

char *innerText(char *storest, char *pfile, char *beginMark, char *endMark) 
{
	beginStart = strstr(pfile, beginMark); //尋找與設定(beginMark)相同的文字位置指標
	if (beginStart == NULL) return NULL;

	beginEnd = beginStart + strlen(beginMark);//將指標移動至(beginMark)尾端
	endStart = strstr(beginEnd, endMark);
	if (endStart < 0) return NULL;

	int len = endStart - beginEnd;
	strncpy(storest, beginEnd, len);
	storest[len] = '\0';
	//printf("beginStart=%p beginEnd=%p endStart=%p\n", beginStart, beginEnd, endStart);
}
int innerText_num(char *storest, char *pfile, char *beginMark, char *endMark)
{
	int num;
	beginStart = strstr(pfile, beginMark); //尋找與設定(beginMark)相同的文字位置指標
	if (beginStart == NULL) return NULL;

	beginEnd = beginStart + strlen(beginMark);//將指標移動至(beginMark)尾端

	endStart = strstr(beginEnd, endMark);
	if (endStart < 0) return NULL;

	int len = endStart - beginEnd;
	strncpy(storest, beginEnd, len);
	storest[len] = '\0';
	num=atoi(storest);
	//printf("beginStart=%p beginEnd=%p endStart=%p\n",beginStart,beginEnd,endStart);
	xml = endStart;
	return num;
}
int strcount(char *inpustr,char *comstr)
{
	char *tempstr;
	int cou=0;
	while (1)
	{
		tempstr=strstr(inpustr, comstr);
		printf("tempstr=%p inpustr=%p comstr=%p cou=%d\n", tempstr, inpustr, comstr, cou);
		if (tempstr == NULL) break;
		cou++;
		inpustr=tempstr+strlen(comstr);
	}
	return cou;
}