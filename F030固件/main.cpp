#include <cmath>
#include "common_inc.h"
#include "screen.h"
#include "robot.h"


Robot electron(&hspi1, &hi2c1);
float jointSetPoints[6];
bool isEnabled = false;
/* Thread Definitions -----------------------------------------------------*/

/* Timer Callbacks -------------------------------------------------------*/


/* Default Entry -------------------------------------------------------*/

void Main(void)
{

    HAL_Delay(2000);
    electron.lcd->Init(Screen::DEGREE_0);
    electron.lcd->SetWindow(0, 239, 0, 239);

    int n=6;
    electron.joint[n].angleMin = 0;
    electron.joint[n].angleMax = 180;
    electron.joint[n].angle = 0;
    electron.joint[n].modelAngelMin = -90;
    electron.joint[n].modelAngelMax = 90;
    electron.SetJointEnable(electron.joint[n], true);

    while (1)
    {
        for (int i = -90; i < 90; i += 1)
        {
            float angle = i;
            electron.UpdateJointAngle(electron.joint[n], angle);

            HAL_Delay(20);
        }
        for (int i = 90; i > -90; i -= 1)
        {
            float angle = i;
            electron.UpdateJointAngle(electron.joint[n], angle);

            HAL_Delay(20);
        }
    }

}



extern "C"
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi)
{
    electron.lcd->isBusy = false;
}