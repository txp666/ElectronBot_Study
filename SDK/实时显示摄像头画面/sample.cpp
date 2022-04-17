#include "electron_low_level.h"

using namespace cv;


int main()
{
    ElectronLowLevel robot;

    if (robot.Connect())
        printf("Robot connected!\n");
    else
    {
        printf("Connect failed!\n");
        getchar();
        return 0;
    }

   // VideoCapture video("D:\\txp\\Recent\\ElectronBot\\3.Software\\SDK\\ElectronBotSDK-LowLevel\\happy.mp4");
    VideoCapture video(0);
    Mat frame;
    uint8_t extraData[32];
    float jointAngles[6];
    float jointAngleSetPoints[6];

    int t = 10;

    while (1)
    {
        video >> frame;
        if (frame.empty())
        {
            // video.set(CV_CAP_PROP_POS_FRAMES, 0);
            // continue;
            break;
        }
        transpose(frame,frame);
        flip(frame, frame, 0);// 0 ÉÏÏÂ·­×ª
        robot.SetImageSrc(frame);
        waitKey(50);

       // robot.SetJointAngles(0, 0, 0, 0, 0, 0, false);
        robot.Sync();
       // robot.GetJointAngles(jointAngles);

        //printf("%f,%f,%f,%f,%f,%f\n",
        //    jointAngles[0], jointAngles[1], jointAngles[2],
        //    jointAngles[3], jointAngles[4], jointAngles[5]);
    }

   // robot.Disconnect();
   //printf("Robot Disconnected.\n");


    getchar();
    return 0;
}

