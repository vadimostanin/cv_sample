//============================================================================
// Name        : sample_cv.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <math.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	cout<<__LINE__<<endl;
	CvCapture *capture = cvCaptureFromCAM(CV_CAP_ANY);
	cout<<__LINE__<<endl;
	if( NULL == capture )
	{
		cout<<"Camera connect was failed"<<endl;
		return -1;
	}
	cout<<__LINE__<<endl;
	IplImage* image = 0;
	IplImage* dst=0;
	IplImage* color_dst=0;
	IplImage* gray = 0;
	IplImage* bin = 0;
	cout<<__LINE__<<endl;
	cvNamedWindow( "Source", 1 );
	cvNamedWindow( "Hough", 1 );
	while(true)
	{
		cout<<__LINE__<<endl;
		printf("capture=%p\n", capture);
		image = cvQueryFrame(capture);
		cout<<__LINE__<<endl;
		if(NULL == image)
		{
			cout<<"image_src is NULL"<<endl;
			return -1;
		}
		// создаём одноканальные картинки
		gray = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
		bin = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
		// клонируем
		dst = cvCloneImage(image);
		// окно для отображения картинки
		cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
		cvNamedWindow("binary",CV_WINDOW_AUTOSIZE);
		cvNamedWindow("contours",CV_WINDOW_AUTOSIZE);

		// преобразуем в градации серого
		cvCvtColor(image, gray, CV_RGB2GRAY);

		// преобразуем в двоичное
		cvInRangeS(gray, cvScalar(40), cvScalar(150), bin); // atoi(argv[2])

		CvMemStorage* storage = cvCreateMemStorage(0);
		CvSeq* contours=0;

		// находим контуры
		int contoursCont = 0;
		contoursCont = cvFindContours( bin, storage,&contours,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));

		// нарисуем контуры
		for(CvSeq* seq0 = contours;seq0!=0;seq0 = seq0->h_next){
				cvDrawContours(dst, seq0, CV_RGB(255,216,0), CV_RGB(0,0,250), 0, 1, 8); // рисуем контур
		}

		// показываем картинки
		cvShowImage("original",image);
		cvShowImage("binary", bin);
		cvShowImage("contours", dst);

		// ждём нажатия клавиши
		cvWaitKey(10);
	}
	cvDestroyAllWindows();
	cvReleaseCapture(&capture);
    return 0;
}
