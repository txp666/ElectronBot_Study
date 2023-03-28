#include "robot.h"

void Robot::UpdateServoAngle(Robot::JointStatus_t &_joint, float _angleSetPoint)
{
    if (_angleSetPoint >= _joint.angleMin && _angleSetPoint <= _joint.angleMax)
    {
        auto *b = (unsigned char *)(&_angleSetPoint);

        i2cTxData[0] = 0x01;
        for (int i = 0; i < 4; i++)
            i2cTxData[i + 1] = *(b + i);

        TransmitAndReceiveI2cPacket(_joint.id);

        _joint.angle = *(float *)(i2cRxData + 1);
    }
}

void Robot::UpdateServoAngle(Robot::JointStatus_t &_joint)
{
    auto *b = (unsigned char *)&(_joint.angle);

    i2cTxData[0] = 0x11;

    TransmitAndReceiveI2cPacket(_joint.id);

    _joint.angle = *(float *)(i2cRxData + 1);
}

void Robot::SetJointEnable(Robot::JointStatus_t &_joint, bool _enable)
{
    i2cTxData[0] = 0xff;
    i2cTxData[1] = _enable ? 1 : 0;

    TransmitAndReceiveI2cPacket(_joint.id);

    _joint.angle = *(float *)(i2cRxData + 1);
}

void Robot::TransmitAndReceiveI2cPacket(uint8_t _id)
{
    // 发送数据
    Wire.beginTransmission(_id);
    for (int i = 0; i < 5; i++)
    {
        Wire.write(i2cTxData[i]);
    }
    byte txError = Wire.endTransmission();
    while (txError != 0)
    {
        delay(5); // 重试间隔
        Wire.beginTransmission(_id);
        for (int i = 0; i < 5; i++)
        {
            Wire.write(i2cTxData[i]);
        }
        txError = Wire.endTransmission();
    }

    // 接收数据
    byte bytesRead = 0;
    while (bytesRead != 5)
    {
        bytesRead = Wire.requestFrom(_id, 5);
        delay(5); // 重试间隔
    }

    for (int i = 0; i < bytesRead; i++)
    {
        i2cRxData[i] = Wire.read();
    }
}



void Robot::SetJointTorqueLimit(Robot::JointStatus_t &_joint, float _percent)
{
    if (_percent >= 0 && _percent <= 1)
    {
        auto *b = (unsigned char *)(&_percent);

        i2cTxData[0] = 0x26;
        for (int i = 0; i < 4; i++)
            i2cTxData[i + 1] = *(b + i);

        TransmitAndReceiveI2cPacket(_joint.id);

        _joint.angle = *(float *)(i2cRxData + 1);

        vTaskDelay(500); // wait servo reset
    }
}

void Robot::SetJointId(Robot::JointStatus_t &_joint, uint8_t _id)
{
    i2cTxData[0] = 0x21;
    i2cTxData[1] = _id;

    TransmitAndReceiveI2cPacket(_joint.id);

    _joint.angle = *(float *)(i2cRxData + 1);

    vTaskDelay(500); // wait servo reset
}

void Robot::SetJointInitAngle(Robot::JointStatus_t &_joint, float _angle)
{
    float sAngle = _joint.inverted ? (_angle - _joint.modelAngelMin) /
                                             (_joint.modelAngelMax - _joint.modelAngelMin) *
                                             (_joint.angleMin - _joint.angleMax) +
                                         _joint.angleMax
                                   : (_angle - _joint.modelAngelMin) /
                                             (_joint.modelAngelMax - _joint.modelAngelMin) *
                                             (_joint.angleMax - _joint.angleMin) +
                                         _joint.angleMin;

    if (sAngle >= _joint.angleMin && sAngle <= _joint.angleMax)
    {
        auto *b = (unsigned char *)(&_angle);

        i2cTxData[0] = 0x27;
        for (int i = 0; i < 4; i++)
            i2cTxData[i + 1] = *(b + i);

        TransmitAndReceiveI2cPacket(_joint.id);

        _joint.angle = *(float *)(i2cRxData + 1);

        vTaskDelay(500); // wait servo reset
    }
}

void Robot::SetJointKp(Robot::JointStatus_t &_joint, float _value)
{
    auto *b = (unsigned char *)(&_value);

    i2cTxData[0] = 0x22;
    for (int i = 0; i < 4; i++)
        i2cTxData[i + 1] = *(b + i);

    TransmitAndReceiveI2cPacket(_joint.id);

    _joint.angle = *(float *)(i2cRxData + 1);

    vTaskDelay(500); // wait servo reset
}

void Robot::SetJointKi(Robot::JointStatus_t &_joint, float _value)
{
    auto *b = (unsigned char *)(&_value);

    i2cTxData[0] = 0x23;
    for (int i = 0; i < 4; i++)
        i2cTxData[i + 1] = *(b + i);

    TransmitAndReceiveI2cPacket(_joint.id);

    _joint.angle = *(float *)(i2cRxData + 1);

    vTaskDelay(500); // wait servo reset
}

void Robot::SetJointKv(Robot::JointStatus_t &_joint, float _value)
{
    auto *b = (unsigned char *)(&_value);

    i2cTxData[0] = 0x24;
    for (int i = 0; i < 4; i++)
        i2cTxData[i + 1] = *(b + i);

    TransmitAndReceiveI2cPacket(_joint.id);

    _joint.angle = *(float *)(i2cRxData + 1);

    vTaskDelay(500); // wait servo reset
}

void Robot::SetJointKd(Robot::JointStatus_t &_joint, float _value)
{
    auto *b = (unsigned char *)(&_value);

    i2cTxData[0] = 0x25;
    for (int i = 0; i < 4; i++)
        i2cTxData[i + 1] = *(b + i);

    TransmitAndReceiveI2cPacket(_joint.id);

    _joint.angle = *(float *)(i2cRxData + 1);

    vTaskDelay(500); // wait servo reset
}

void Robot::UpdateJointAngle(Robot::JointStatus_t &_joint)
{
    UpdateServoAngle(_joint);

    float jAngle = _joint.inverted ? (_joint.angleMax - _joint.angle) /
                                             (_joint.angleMax - _joint.angleMin) *
                                             (_joint.modelAngelMax - _joint.modelAngelMin) +
                                         _joint.modelAngelMin
                                   : (_joint.angle - _joint.angleMin) /
                                             (_joint.angleMax - _joint.angleMin) *
                                             (_joint.modelAngelMax - _joint.modelAngelMin) +
                                         _joint.modelAngelMin;

    _joint.angle = jAngle;
}

void Robot::UpdateJointAngle(Robot::JointStatus_t &_joint, float _angleSetPoint)
{
    float sAngle = _joint.inverted ? (_angleSetPoint - _joint.modelAngelMin) /
                                             (_joint.modelAngelMax - _joint.modelAngelMin) *
                                             (_joint.angleMin - _joint.angleMax) +
                                         _joint.angleMax
                                   : (_angleSetPoint - _joint.modelAngelMin) /
                                             (_joint.modelAngelMax - _joint.modelAngelMin) *
                                             (_joint.angleMax - _joint.angleMin) +
                                         _joint.angleMin;

    UpdateServoAngle(_joint, sAngle);

    float jAngle = _joint.inverted ? (_joint.angleMax - _joint.angle) /
                                             (_joint.angleMax - _joint.angleMin) *
                                             (_joint.modelAngelMax - _joint.modelAngelMin) +
                                         _joint.modelAngelMin
                                   : (_joint.angle - _joint.angleMin) /
                                             (_joint.angleMax - _joint.angleMin) *
                                             (_joint.modelAngelMax - _joint.modelAngelMin) +
                                         _joint.modelAngelMin;

    _joint.angle = jAngle;
}
