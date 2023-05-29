#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include<QKeyEvent>
#include<QLabel>
#include<QMovie>
#include<QFileInfo>
#include<QTimer>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<graphics.h>
#include<mmsystem.h>
#include<algorithm>
#include <iostream>
#include <chrono>
#include<Windows.h>
#include<QShortcut>
#include<qdebug.h>
#include <QProgressBar>
#define m_width 1000
#define m_height 750
#define m_speed 5
#define jump_speed 30.0//垂直方向的初始速度（未赋值前）
#define WIDTH 1024
#define HEIGHT 640
//#define Gravity 5.0//拟重力加速度
//#define max_jump_height 200
#pragma comment(lib,"winmm.lib")
enum class directions {
    none,
    left,
    right,
    up,
    down
};
class QtWidgetsApplication1 : public QMainWindow
{

    Q_OBJECT

public:


    QtWidgetsApplication1(QWidget* parent = nullptr);
    ~QtWidgetsApplication1();
    void keyPressEvent(QKeyEvent* event) override;  // 重写键盘事件处理函数
    void keyReleaseEvent(QKeyEvent* event);
    void timeOut();

    //从c++项目中拷贝出来的部分函数
    //利用 qt 的构造函数当作GameControl 
   // void play();
   //  play函数就是我的构造函数 
   //
    //游戏界面居中函数
    void CenterInitGraph();
    //ClearRange函数，用于清空特定区域，可以实现隐身等技能。也可以实现游戏背景的优化。
    //void clearRange(int x, int y, int width, int height);
    //界面函数
    void Interface(wchar_t* text);
    //功能选择展示函数
    void DHS_DISPLAY();




private:
    directions direction01;//方向1 控制左右
    directions direction02;//方向2 控制上下
    Ui::QtWidgetsApplication1Class ui;
    QLabel* characterLabel;
    int characterX;//角色的X坐标
    int characterY;
    int characterY0;//初始y 即地面y坐标
    QTimer* moveTimer;//定时器


    bool choice = 2;//模式选择 默认为双人游戏


    //跳起定时器
    QTimer* jumpTimer;
    //下落定时器
   //QTimer* downTimer;
    QMovie* characterMovie;
    QLabel* label;

    QLabel* healthLabel;   // 血条标签
    QProgressBar* healthBar;   // 血条
    QLabel* energyLabel;   // 能量条标签
    QProgressBar* energyBar;   // 能量条
    double energyValue;   // 能量值
    double healthValue;   // 血量值


    double vy = jump_speed;
    double gravity = 2.5;
    //double jumpHeight=0;



    QMovie* attackMovie;   // 攻击动画
    QMovie* jumpMovie;//跳跃动画

    bool isAttacking = false;   // 是否正在攻击
    // bool isLanded = true;//判断是否落地
     //bool isJumping = false;//判断是否跳跃
     //前进动画
    QMovie* forwardMovie;
    //下蹲动画
    QMovie* crouchMovie;

    //后退动画
    QMovie* backwardMovie;




    QMovie* entranceMovie;//开场动画


    QMovie* crouchAttack;
    bool cantmove;   // 是否可以移动
    QMovie* skill0;//技能0


    bool iscrouch;





    void skillFinished()
    {
        // 技能动画播放完毕，可以进行其他操作

        // 恢复攻击和移动等操作
        // ...

        // 设置标志位为false，表示技能释放完成
        cantmove = false;
    }
    QMetaObject::Connection connection;

    void showup();
    void castSkill1();
    //{
    //    // 设置标志位为 true，表示正在释放技能
    //    cantmove = true;

    //    // 暂停其他动作，如攻击和移动
    //    // ...

    //    // 播放技能动画
    //    characterLabel->clear();
    //    characterLabel->setMovie(skill0);
    //    skill0->start();

    //    // 获取技能动画的帧数
    //    int totalFrames = skill0->frameCount();

    //    // 连接 frameChanged 信号到槽函数
    //    connect(skill0, &QMovie::frameChanged, this, [this, totalFrames]() {
    //        // 获取当前帧数
    //        int currentFrame = skill0->currentFrameNumber();

    //        // 判断是否达到总帧数
    //        if (currentFrame == totalFrames - 1) {
    //            // 动画播放完一遍，停止技能动画
    //            skillFinished();
    //        }
    //        });
    //}


};