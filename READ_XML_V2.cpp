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
#define startyear 2007
#define endyear 2012

char* FIND_XML_budbox_name(char *storest, char *pfile, char *beginMark, char *endMark);
int FIND_XML_budbox_name_num(char *storest, char *pfile, char *beginMark, char *endMark);
int strcount(char *inpustr, char* comstr, char *p_xmin, char *p_xmax, char *p_ymin, char *p_ymax, char *p_xml);
char *budboxname = (char*)malloc(sizeof(char)*25);
char *beginStart;
char *beginEnd;
char *endStart;

typedef struct Postion
{
	char OBJname[25];
	int X_min;
	int X_max;
	int Y_min;
	int Y_max;
}POS;
POS test1[100];
static char *xml = NULL;
static char *xxx = NULL;
static char *p_xmin = NULL;
static char *p_xmax = NULL;
static char *p_ymin = NULL;
static char *p_ymax = NULL;
char name[20];
int main(int argc, char *argv[])
{
	int filecount = 724, year = 2011, i = 0;
	char filename[100];
	char imagename[100];
	char xMax[5], xMin[5], yMax[5], yMin[5];
	int xmin, xmax, ymin, ymax, bboxcount;
	Mat framei, frameo;

	while (1)
	{

		/*------------讀取檔名--start-----------*/
		//檔名尾數為0~9
		if (filecount >= 0 && filecount <= 9)
		{
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
			p_xmin = xml;
			p_xmax = xml;
			p_ymin = xml;
			p_ymax = xml;
			bboxcount = strcount(xxx, "</bndbox>",p_xmin,p_xmax,p_ymin,p_ymax,xml);//計算bndbox數量讓後續讀檔動作停止使用
		}
		//檔名尾數為10~99
		else if (filecount >= 10 && filecount <= 99)
		{
			sprintf(filename, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\Annotations\\%d_0000%d.xml", year, filecount);
			sprintf(imagename, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\JPEGImages\\%d_0000%d.jpg", year, filecount);
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
			p_xmin = xml;
			p_xmax = xml;
			p_ymin = xml;
			p_ymax = xml;
			//printf("xml=%p xxx=%p\n\n",xml,xxx);
			bboxcount = strcount(xxx, "</bndbox>", p_xmin, p_xmax, p_ymin, p_ymax,xml);//計算bndbox數量讓後續讀檔動作停止使用
		}
		//檔名尾數為100~999
		else if (filecount > 99 && filecount <= 999)
		{
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
			p_xmin = xml;
			p_xmax = xml;
			p_ymin = xml;
			p_ymax = xml;
			bboxcount = strcount(xxx, "</bndbox>", p_xmin, p_xmax, p_ymin, p_ymax,xml);//計算bndbox數量讓後續讀檔動作停止使用
		}
		//檔名尾數為1000~9999
		else if (filecount > 999 && filecount <= 9999)
		{
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
			p_xmin = xml;
			p_xmax = xml;
			p_ymin = xml;
			p_ymax = xml;
			bboxcount = strcount(xxx, "</bndbox>", p_xmin, p_xmax, p_ymin, p_ymax,xml);//計算bndbox數量讓後續讀檔動作停止使用
		}
		/*------------讀取檔名--end-----------*/

		//超過9999年分增加
		if (filecount >= 9999)//增加年分
		{
			year++;
			filecount = 0;
			i = 0;
			continue;
		}
		if (year >= 2012) break; //結束條件

		/*切割圖黨內樣本*/
		while (1)
		{
			printf("bboxcount=%d\n", bboxcount);
			if (i >= bboxcount)
				break;
			//FIND_XML_budbox_name(name, xml, "<name>", "<");
			printf("name=%s num=%d\n", test1[i].OBJname, i);

			/*xmax = FIND_XML_budbox_name_num(xMax, xml, "<xmax>", "<");
			xmin = FIND_XML_budbox_name_num(xMin, xml, "<xmin>", "<");
			ymax = FIND_XML_budbox_name_num(yMin, xml, "<ymax>", "<");
			ymin = FIND_XML_budbox_name_num(yMin, xml, "<ymin>", "<");*/

			printf("xmin=%d xmax=%d ymin=%d ymax=%d\n", test1[i].X_min, test1[i].X_max, test1[i].Y_min, test1[i].Y_max);
			framei = imread(imagename, -1);
			//printf("%s\n",imagename);
			//system("pause");
			frameo = framei(cvRect(test1[i].X_min, test1[i].Y_min, test1[i].X_max - test1[i].X_min, test1[i].Y_max - test1[i].Y_min));
			char imgname[100];
			if (filecount >= 0 && filecount <= 9)
				sprintf(imgname, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\samplefile\\%d_00000%d_out%s%d.jpg", year, filecount - 1, test1[i].OBJname, i);
			if (filecount >= 10 && filecount <= 99)
				sprintf(imgname, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\samplefile\\%d_0000%d_out%s%d.jpg", year, filecount - 1, test1[i].OBJname, i);
			if (filecount > 99 && filecount <= 999)
				sprintf(imgname, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\samplefile\\%d_000%d_out%s%d.jpg", year, filecount - 1, test1[i].OBJname, i);
			if (filecount > 999 && filecount <= 9999)
				sprintf(imgname, "C:\\Users\\es912\\Desktop\\fileread\\rf\\rf\\samplefile\\%d_00%d_out%s%d.jpg", year, filecount - 1, test1[i].OBJname, i);
			imwrite(imgname, frameo);
			printf("------------------\n");
			i++;
			//system("pause");
		}
		i = 0;
	}
	//free(xml);
	system("pause");
	return 0;
}

//尋找 xml中budbox的name
char* FIND_XML_budbox_name(char *storest, char *pfile, char *beginMark, char *endMark)
{
	beginStart = strstr(pfile, beginMark); //尋找與設定(beginMark)相同的文字位置指標
	if (beginStart == NULL) return NULL;

	beginEnd = beginStart + strlen(beginMark);//將指標移動至(beginMark)尾端
	endStart = strstr(beginEnd, endMark);
	
	if (endStart < 0) return NULL;
	
	int len = endStart - beginEnd;
	strncpy(storest, beginEnd, len);
	storest[len] = '\0';
	//printf("333namep=%p name=%s\n", storest, storest);
	//printf("beginStart=%p beginEnd=%p endStart=%p\n", beginStart, beginEnd, endStart);-**/                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
	//return storest;
}
//尋找 xml中budbox的 xmax xmin ymax ymin
int FIND_XML_budbox_name_num(char *storest, char *pfile, char *beginMark, char *endMark)
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
	num = atoi(storest);
	//printf("beginStart=%p beginEnd=%p endStart=%p\n",beginStart,beginEnd,endStart);
	xml = endStart;
	return num;
}
//計算budbox數量
int strcount(char *inpustr, char *comstr, char *p_xmin, char *p_xmax, char *p_ymin, char *p_ymax ,char *pxml)
{
	char *tempstr;
	char Maxx[5];
	char Minx[5];
	char Maxy[5];
	char Miny[5];
	int cou = 0;
	while (1)
	{
		FIND_XML_budbox_name(test1[cou].OBJname,pxml,"<name>","<");
		test1[cou].X_min = FIND_XML_budbox_name_num(Minx, p_xmin, "<xmin>", "<");
		test1[cou].X_max = FIND_XML_budbox_name_num(Maxx, p_xmax, "<xmax>", "<");
		test1[cou].Y_min = FIND_XML_budbox_name_num(Miny, p_ymin, "<ymin>", "<");
		test1[cou].Y_max = FIND_XML_budbox_name_num(Maxy, p_ymax, "<ymax>", "<");

		tempstr = strstr(inpustr, comstr);
		//printf("tempstr=%p inpustr=%p comstr=%p cou=%d\n", tempstr, inpustr, comstr, cou);
		//printf("test1[%d].Xmin=%d test1[%d].Xmax=%d test1[%d].Ymin=%d test1[%d].Ymax=%d\n", cou, test1[cou].X_min, cou, test1[cou].X_max, cou, test1[cou].Y_min, cou , test1[cou].Y_max);
		if (tempstr == NULL) break;

		inpustr = tempstr + strlen(comstr);
		p_xmin = inpustr;
		p_xmax = inpustr;
		p_ymin = inpustr;
		p_ymax = inpustr;
		pxml = inpustr;
		cou++;
	}
	//system("pause");
	return cou;
}