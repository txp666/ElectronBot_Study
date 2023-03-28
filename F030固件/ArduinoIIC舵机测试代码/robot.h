#ifndef ELECTRONBOT_FW_ROBOT_H
#define ELECTRONBOT_FW_ROBOT_H

#include <Wire.h>
#include<Arduino.h>
#define ANY 0

class Robot
{
public:
    Robot()

    {
        joint[ANY] = JointStatus_t(0, -180, 180, 90);
        joint[1] = JointStatus_t(1, 10, 80, 0, -15, 15, true);
        joint[2] = JointStatus_t(2, -34, 10, 0, 0, 30, false);
        joint[3] = JointStatus_t(3, -16, 147, 0, -20, 180, false);
        joint[4] = JointStatus_t(4, 130, 190, 0, 0, 30, true);
        joint[5] = JointStatus_t(5, 10, 160, 0, -20, 180, true);
        joint[6] = JointStatus_t(6, 0, 180, 0, -90, 90, false);
    };
    /********* Need to adjust parameters for specific hardware *********/

    struct JointStatus_t
    {
        uint8_t id;
        float angleMin;
        float angleMax;
        float angle;
        float modelAngelMin;
        float modelAngelMax;
        bool inverted;

        JointStatus_t()
            : id(0), angleMin(0), angleMax(0), angle(0), modelAngelMin(0), modelAngelMax(0), inverted(false)
        {
        }

        JointStatus_t(uint8_t id, float angleMin, float angleMax, float angle, float modelAngelMin = 0, float modelAngelMax = 0, bool inverted = false)
            : id(id), angleMin(angleMin), angleMax(angleMax), angle(angle), modelAngelMin(modelAngelMin), modelAngelMax(modelAngelMax), inverted(inverted)
        {
        }
    };

    JointStatus_t joint[7];

    void init(uint8_t sda_pin, uint8_t scl_pin);

    void SetJointId(JointStatus_t &_joint, uint8_t _id);
    void SetJointKp(JointStatus_t &_joint, float _value);
    void SetJointKi(JointStatus_t &_joint, float _value);
    void SetJointKv(JointStatus_t &_joint, float _value);
    void SetJointKd(JointStatus_t &_joint, float _value);
    void SetJointEnable(JointStatus_t &_joint, bool _enable);
    void SetJointInitAngle(JointStatus_t &_joint, float _angle);
    void SetJointTorqueLimit(JointStatus_t &_joint, float _percent);

    void UpdateServoAngle(JointStatus_t &_joint);
    void UpdateServoAngle(JointStatus_t &_joint, float _angleSetPoint);
    void UpdateJointAngle(JointStatus_t &_joint);
    void UpdateJointAngle(JointStatus_t &_joint, float _angleSetPoint);

private:
    uint8_t sda_pin;
    uint8_t scl_pin;

    uint8_t i2cRxData[8];
    uint8_t i2cTxData[8];

    void TransmitAndReceiveI2cPacket(uint8_t _id);
};

#endif // ELECTRONBOT_FW_ROBOT_H
