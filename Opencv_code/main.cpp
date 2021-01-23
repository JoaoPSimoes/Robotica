#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string> 
#include"ImageProc.h"

using namespace cv;
using namespace std;

Mat corrigir_distorcao(Mat t,Mat frame);

Mat frame;
Mat direito;
Mat B_gray;
Mat mesa_gray;
Mat copo_gray;
Mat R_gray;
Mat segm_mesa;
Mat segm_copo;
Mat binary;
Mat labels;
Mat binary_copo;
Mat temp;
Mat out;
Mat blurred;
coordinates centroid;
list<coordinates> listacentros;

int h_upper_mesa = 88;
int h_lower_mesa = 52;
int s_upper_mesa = 255;
int s_lower_mesa = 40;
int v_upper_mesa = 255;
int v_lower_mesa = 40;

int h_upper_copo = 255;
int h_lower_copo = 0;
int s_upper_copo = 110;
int s_lower_copo = 20;
int v_upper_copo = 168;
int v_lower_copo = 20;

int max_labels = 0;

int main(int argc, char** argv)
{
	/*
	VideoCapture cap("http://192.168.1.169:4747/video"); // open the default camera
	if (!cap.isOpened()) { // check if we succeeded
		cout << "couldn't open camera" << endl;
		return -1;
	}
	*/
	
	 //para debugging
	frame = imread("D:/copo2.jpg");  //localização da imagem
	if (frame.empty()) {  //se o sistema não carregar a imagem
		cout << "Cannot load file" << endl;
		return -1;
	}
	

	namedWindow("frame", 1);
	namedWindow("final", 1);
	namedWindow("mesa", 1);
	namedWindow("copo", 1);
	//namedWindow("segm_mesa", 1);
	//namedWindow("segm_copo", 1);
	//namedWindow("g_binary", 1);
	//namedWindow("binary", 1);

	createTrackbar("h_up", "segm_mesa", &h_upper_mesa, 255);
	createTrackbar("h_low", "segm_mesa", &h_lower_mesa, 255);
	createTrackbar( "s_up", "segm_mesa", &s_upper_mesa, 255);
	createTrackbar( "s_low", "segm_mesa", &s_lower_mesa, 255);
	createTrackbar( "v_up", "segm_mesa", &v_upper_mesa, 255);
	createTrackbar( "v_low", "segm_mesa", &v_lower_mesa, 255);

	createTrackbar("h_up", "segm_copo", &h_upper_copo, 255);
	createTrackbar("h_low", "segm_copo", &h_lower_copo, 255);
	createTrackbar("s_up", "segm_copo", &s_upper_copo, 255);
	createTrackbar("s_low", "segm_copo", &s_lower_copo, 255);
	createTrackbar("v_up", "segm_copo", &v_upper_copo, 255);
	createTrackbar("v_low", "segm_copo", &v_lower_copo, 255);


	while (true) {
		//cap >> frame; // get a new frame from camera
		GaussianBlur(frame, blurred, Size(3, 3), 0);

		segm_mesa = VCPI_Segmenta_Cor(blurred,h_lower_mesa,h_upper_mesa,s_lower_mesa,s_upper_mesa,v_lower_mesa,v_upper_mesa);	//efetuar a binarização da imagem segundo um dado threshold
		
		mesa_gray = vcpi_rgb_to_gray(segm_mesa);

		binary = vcpi_gray_to_binary(vcpi_rgb_to_gray(segm_mesa), 1, 255);
		binary = vcpi_binary_open(binary, 5, Oito, 5, Oito);


		temp = vcpi_get_max_blob_area(vcpi_binary_blob_improved_labelling(binary));     //filtrar blobs com tamanho inferior a um determinado numero de pixeis
		temp = vcpi_gray_negative(vcpi_get_max_blob_area(vcpi_binary_blob_improved_labelling(vcpi_gray_negative(temp))));
		segm_mesa = apply_mask(frame, temp);

		direito = corrigir_distorcao(temp,frame);

		segm_copo = VCPI_Segmenta_Cor(direito, h_lower_copo, h_upper_copo, s_lower_copo, s_upper_copo, v_lower_copo, v_upper_copo);	//efetuar a binarização da imagem segundo um dado threshold
		
		binary_copo = vcpi_gray_to_binary(vcpi_rgb_to_gray(segm_copo), 1, 255);
		binary_copo = vcpi_binary_close(binary_copo, 5, Oito, 7, Oito);

		segm_copo = apply_mask(direito, binary_copo);

		labels = vcpi_binary_blob_improved_labelling(binary_copo);
		binary_copo = vcpi_filter_blob_area(labels, 200);
		labels = vcpi_binary_blob_improved_labelling(binary_copo);

		max_labels = 0;
		
		for (uint i = 0; i < labels.cols * labels.rows; i++) {
			max_labels = labels.data[i] > max_labels ? labels.data[i] : max_labels;
		}

		coordenadas cent_copo = vcpi_blob_centroid(find_replace_value(labels, 1, 255));
		//cout << "Img size pixels X: " << direito.cols << "  Y: " << direito.rows<<endl;
		//cout << "Pixel pos copo X: " << cent_copo.x << "    Y: " << cent_copo.y << "  Area: "<< cent_copo.area <<endl;
		uint pos_copo_y =(uint) round((500.0f / (float)direito.rows)*cent_copo.y);
		uint pos_copo_x =(uint) round((430.0f / (float)direito.cols)*cent_copo.x);
		cout << "Millimetros copo X: " << pos_copo_x << "  Y: " << pos_copo_y << endl;


		
		out = find_apply_created(direito, find_create_with(vcpi_draw_circle_centroid(find_replace_value(labels, 1, 255)), 255, 40, 40, 255));

		if (frame.cols > 0 && frame.rows > 0) {
			imshow("frame", frame);
			//imshow("segm_mesa", mesa_gray);
			//imshow("segm_copo", copo_gray);
			imshow("mesa", segm_mesa);
			imshow("copo", segm_copo);
			//imshow("binary_copo", binary_copo);
			imshow("final", out);

		}
		waitKey(1);
	} 
	
	return 0;
}

Mat corrigir_distorcao(Mat src, Mat color) {

	if (src.empty() || color.empty()) {
		cout << "There is no image!" << endl;
		return src;
	}

	Mat edges;
	vector< Point2f > corners;

	Canny(src, edges, 0, 255, 3);
	goodFeaturesToTrack(edges, corners, 4,0.01,20);
	Point Q1;
	Point Q2;
	Point Q3;
	Point Q4;

	uint canto = 0;
	uint lado = 0;
	for (uint i = 0; i < 4; i++)
	{
		if (abs(corners[i].x - corners[i].y) < 200){
			if (canto == 0){
				Q1 = corners[i];
				canto = 1;
			}else{
				if (Q1.x > corners[i].x) {
					Q3 = Q1;
					Q1 = corners[i];
				}
				else {
					Q3 = corners[i];
				}
			}
			
		}
		else {

			if (lado == 0) {
				Q2 = corners[i];
				lado = 1;
			}
			else {
				if (Q2.x > Q2.y) {
					Q4 = corners[i];
				}
				else {
					Q4 = Q2;
					Q2 = corners[i];
				}
			}

		}
	}


	// compute the size of the card by keeping aspect ratio.
	double ratio = 0.86;
	double cardH = sqrt((Q3.x - Q2.x)*(Q3.x - Q2.x) + (Q3.y - Q2.y)*(Q3.y - Q2.y));//Or you can give your own height
	double cardW = ratio * cardH;
	Rect R(Q1.x, Q1.y, cardW, cardH);

	Point R1 = Point2f(0,0);
	Point R2 = Point2f( R.width, 0);
	Point R3 = Point2f(Point2f(R.width, R.height));
	Point R4 = Point2f(Point2f(0, R.height));

	std::vector<Point2f> quad_pts;
	std::vector<Point2f> squre_pts;

	quad_pts.push_back(Q1);
	quad_pts.push_back(Q2);
	quad_pts.push_back(Q3);
	quad_pts.push_back(Q4);

	squre_pts.push_back(R1);
	squre_pts.push_back(R2);
	squre_pts.push_back(R3);
	squre_pts.push_back(R4);


	Mat transmtx = getPerspectiveTransform(quad_pts, squre_pts);
	int offsetSize = 150;
	Mat transformed = Mat::zeros(R.height,R.width, CV_8UC3);
	warpPerspective(frame, transformed, transmtx, transformed.size());

	return transformed;
}



