#ifndef SCREENCONTROLTEST_H
#define SCREENCONTROLTEST_H

//include ScreenControl
#include "screencontrol.h"

class ScreenControlTest
{
public:
    ScreenControlTest();
    ScreenControlTest(QDesktopWidget *desktop);
    void SetWindowTest();//测试窗口设置
private:
    ScreenControl m_screencontrol;
};

#endif // SCREENCONTROLTEST_H
