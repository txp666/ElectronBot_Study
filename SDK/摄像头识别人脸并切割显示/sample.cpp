#include "electron_low_level.h"
#include <opencv/cv.h> 
#include <opencv/highgui.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
int FaceShow();
void DetectFace(Mat, Mat);
CascadeClassifier faceCascade;
ElectronLowLevel robot;

int main()
{
	if (robot.Connect())
		printf("Robot connected!\n");
	else
	{
		printf("Connect failed!\n");
		getchar();
		return 0;
	}

	uint8_t extraData[32];

	while (1)
	{
		if (!FaceShow()) {
			break;
		};
	}

	getchar();
	return 0;
}
int FaceShow() {
	VideoCapture cap;
	if (!cap.open(0)) {
		cout << "����ͷ��ʧ��!!" << endl;
		return 0;
	}
	//�滻Ϊ�Լ���opencv��
	if (!faceCascade.load("D:\\SoftWare\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt2.xml")) {
		cout << "������⼶��������û�ҵ�����" << endl;
		return 0;
	}
	Mat img, imgGray;
	int fps = 60;
	while (true) {
		cap >> img;
		transpose(img, img);
		flip(img, img, 0);
		cvtColor(img, imgGray, CV_BGR2GRAY);
		equalizeHist(imgGray, imgGray);//ֱ��ͼ���Ȼ�
		DetectFace(img, imgGray);
		waitKey(1000 / fps);
	}
	return 1;
}
void DetectFace(Mat img, Mat imgGray) {


	Mat faceROI;
	namedWindow("src", WINDOW_AUTOSIZE);
	namedWindow("output", WINDOW_AUTOSIZE);
	vector<Rect> faces, eyes;
	faceCascade.detectMultiScale(imgGray, faces, 1.2, 3, 0, Size(100, 100));

	if (faces.size() > 0) {
		for (size_t i = 0; i < faces.size(); i++) {
			Rect roi;
			roi.x = faces[static_cast<int>(i)].x + 2;
			roi.y = faces[static_cast<int>(i)].y + 2;
			roi.width = faces[static_cast<int>(i)].width - 2;
			roi.height = faces[static_cast<int>(i)].height - 2;
			//�������ڵĸ���Ȥ����
			faceROI = img(roi);
			rectangle(img, faces[static_cast<int>(i)], Scalar(0, 255, 0), 1, 8, 0);
		
			//������ͼ��Ĵ�Сͳһ����Ϊ240*240
			resize(faceROI, faceROI, Size(240, 240));

			}
		}
		
	if (!faceROI.empty())
	{
		imshow("output", faceROI);
		robot.SetImageSrc(faceROI);
		robot.Sync();
	}
	else {
		robot.SetImageSrc("NoFace.jpg");//û�м�⵽����//ͼƬҪ���빤��
		robot.Sync();
	}
	imshow("src", img);
	
}