#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define mqtt_host "localhost"
#define mqtt_port 1883
#include <mosquitto.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
#include <nlohmann/json.hpp>
using nlohmann::json;

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

struct Box {
    int x1, y1;
    int x2, y2;
    std::string name;
};

void to_json(json& j, const Box& p)
{
    j = json{
        { "vector1", {
            { "x", p.x1},
            { "y", p.y1}
            }
        },
        { "vector2", {
            { "x", p.x2 },
            { "y", p.y2 }
            }
        }, 
        { "name", p.name }
    };
}

using namespace cv;  
using namespace std;

int main() {
    
    int rc;
    struct mosquitto *mosq;

    mosq = mosquitto_new("pubisher-test", true, NULL);
    
    rc = mosquitto_connect(mosq, mqtt_host, mqtt_port, 60);
    if (rc != 0)
    {
        printf("Client could not connect to brocker! Error Code: %d\n", rc);
        mosquitto_destroy(mosq);
        return -1;
    }
    
    printf("We are now connected to the broker!\n");

    cout << "start" << endl;
    VideoCapture cap("temp.mp4");
    if ( !cap.isOpened() ) return -1;
    namedWindow("MyVideo",cv::WindowFlags::WINDOW_AUTOSIZE); 
    std::string name = "box";
    std::vector<std::vector<cv::Point>> stickers;
    while(1) {
        Mat frame;
        bool bSuccess = cap.read(frame); 
        if (!bSuccess) {
            cout << "Cannot read the frame from video file" << endl;
            break;
        }
        
        int i = 0;
        recogniseStickersByThreshold(frame, stickers);
        for (auto st : stickers)
        {
            Box box;

            cv::Point sticker1; 
            sticker1.x = (*min_element(st.begin(), st.end(), cmpPointX)).x;
            sticker1.y = (*min_element(st.begin(), st.end(), cmpPointY)).y;
            cv::Point sticker2; 
            sticker2.x = (*max_element(st.begin(), st.end(), cmpPointX)).x;
            sticker2.y = (*max_element(st.begin(), st.end(), cmpPointY)).y;
            cv::rectangle(frame, Rect(sticker1, sticker2),cv::Scalar(0,250,0),2);
 
            box.x1 = sticker1.x;
            box.y1 = sticker1.y;
            box.x2 = sticker2.x;
            box.y2 = sticker2.y;
            box.name = std::to_string(i++);

            json j { box };
            std::stringstream ss;
            std::string str;
            ss << j.dump();
            ss >> str;
            mosquitto_publish(mosq, NULL, "test/tl", str.size(), str.c_str(), 0, false);
            //std::cout << j.dump(4) << '\n';
        }

        imshow("MyVideo", frame); 
        if(waitKey(30) == 27) {
            break;
        }
    }
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);

    mosquitto_lib_cleanup();
    return 0;
}

/*
static int run = 1;

void handle_signal(int s) {
    run = 0;
}
void connect_callback(struct mosquitto *mosq, void *obj, int result) {
    printf("connect callback, rc=%d\n", result);
}
void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message
*message) {
    bool match = 0;
    printf("got message '%.*s' for topic '%s'\n", message->payloadlen, (char*) message->payload, message->topic);
    mosquitto_topic_matches_sub("/devices/wb-adc/controls/+", message->topic, &match);
    if (match) {
        printf("got message for ADC topic\n");
    }
}

int main(int argc, char *argv[]) {

    uint8_t reconnect = true;
    char clientid[24];
    struct mosquitto *mosq; int rc = 0;
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    mosquitto_lib_init();
    memset(clientid, 0, 24);
    snprintf(clientid, 23, "mysql_log_%d", getpid());
    mosq = mosquitto_new(clientid, true, 0);
    if (mosq){
        mosquitto_connect_callback_set(mosq, connect_callback);
        mosquitto_message_callback_set(mosq, message_callback);
        rc = mosquitto_connect(mosq, mqtt_host, mqtt_port, 60);
        mosquitto_subscribe(mosq, NULL, "/devices/wb-adc/controls/+", 0);
        while(run){
            rc = mosquitto_loop(mosq, -1, 1);
            if(run && rc){
                printf("connection error!\n");
                sleep(10);
                mosquitto_reconnect(mosq);
            }
        }
        mosquitto_destroy(mosq);
    }
    mosquitto_lib_cleanup();
    return rc;
}*/
