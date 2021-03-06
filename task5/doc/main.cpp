
#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>


void recogniseStickersByThreshold(cv::Mat image, std::vector<std::vector<cv::Point>> &stickers) {
    cv::Mat image_hsv;
    std::vector< std::vector<cv::Point> > contours;
    cv::cvtColor(image, image_hsv, cv::COLOR_BGR2HSV ); 
    cv::Mat tmp_img(image.size(), CV_8U);
    cv::inRange(image_hsv, cv::Scalar(100, 100, 100), cv::Scalar(255, 255, 255), tmp_img);
    cv::dilate(tmp_img,tmp_img,cv::Mat(), cv::Point(-1,-1), 3);
    cv::erode(tmp_img,tmp_img,cv::Mat(), cv::Point(-1,-1), 1);
    cv::findContours(tmp_img, stickers, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    for (uint i = 0; i<contours.size(); i++) {
        cv::Mat sticker;
        cv::Rect rect=cv::boundingRect(contours[i]);
        image(rect).copyTo(sticker);
        cv::rectangle(image, rect, cv::Scalar(0, 250, 0), 2);
        stickers.push_back(sticker); 
    }
}

bool cmpPointX(const cv::Point &a, const cv::Point &b) {
    return a.x < b.x;
}

bool cmpPointY(const cv::Point &a, const cv::Point &b) {
    return a.y < b.y;
}

cv::Point newGain(cv::Point oldGain, cv::Point measurement, cv::Point &target) {
    target += oldGain;
    std::cout << target << "\n";
    return oldGain + (1/3) * (measurement - target);
}

cv::Point estimate(cv::Point prediction, cv::Point measurement) {
    return 0.6 * prediction + 0.4 * measurement;
}

int main() {
    using namespace cv;
    using namespace std;

    cout << "start" << endl;
    VideoCapture cap("./project/temp.mp4");
    if ( !cap.isOpened() ) return -1;
    namedWindow("MyVideo",cv::WindowFlags::WINDOW_AUTOSIZE); 

    std::vector<std::vector<cv::Point>> stickers;
    cv::Point gain1(1, 1);
    cv::Point gain2(1, 1);
    cv::Point prediction1(1, 1);
    cv::Point prediction2(1, 1);
    bool start = true;
    while(1) {
        Mat frame;
        bool bSuccess = cap.read(frame); 
        if (!bSuccess) {
            cout << "Cannot read the frame from video file" << endl;
            break;
        }

        recogniseStickersByThreshold(frame, stickers);
        
        if (start)
        {
            auto st = stickers.front();
            cv::Point sticker1; 
            sticker1.x = (*min_element(st.begin(), st.end(), cmpPointX)).x;
            sticker1.y = (*min_element(st.begin(), st.end(), cmpPointY)).y;
            prediction1 = sticker1;
            cv::Point sticker2; 
            sticker2.x = (*max_element(st.begin(), st.end(), cmpPointX)).x;
            sticker2.y = (*max_element(st.begin(), st.end(), cmpPointY)).y;
            prediction2 = sticker2;
            start = false;
        }
        
        for (auto st : stickers)
        {
            cv::Point sticker1; 
            sticker1.x = (*min_element(st.begin(), st.end(), cmpPointX)).x;
            sticker1.y = (*min_element(st.begin(), st.end(), cmpPointY)).y;
            cv::Point sticker2; 
            sticker2.x = (*max_element(st.begin(), st.end(), cmpPointX)).x;
            sticker2.y = (*max_element(st.begin(), st.end(), cmpPointY)).y;
            cv::rectangle(frame, Rect(sticker1, sticker2),cv::Scalar(0,250,0),2);
            
            gain1 = newGain(gain1, sticker1, prediction1);
            gain2 = newGain(gain2, sticker2, prediction2);
            
            prediction1 = estimate(prediction1, sticker1);
            prediction2 = estimate(prediction2, sticker2);
            cv::rectangle(frame, Rect(prediction1 + gain1, prediction2 +gain2),cv::Scalar(250,0,0),2);
            break;
        }

        imshow("MyVideo", frame); 
        if(waitKey(30) == 27) {
            break;
        }
    }
    return 0;
}
