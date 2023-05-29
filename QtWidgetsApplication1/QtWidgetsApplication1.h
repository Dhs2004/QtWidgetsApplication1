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
#define jump_speed 30.0//��ֱ����ĳ�ʼ�ٶȣ�δ��ֵǰ��
#define WIDTH 1024
#define HEIGHT 640
//#define Gravity 5.0//���������ٶ�
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
    void keyPressEvent(QKeyEvent* event) override;  // ��д�����¼�������
    void keyReleaseEvent(QKeyEvent* event);
    void timeOut();

    //��c++��Ŀ�п��������Ĳ��ֺ���
    //���� qt �Ĺ��캯������GameControl 
   // void play();
   //  play���������ҵĹ��캯�� 
   //
    //��Ϸ������к���
    void CenterInitGraph();
    //ClearRange��������������ض����򣬿���ʵ������ȼ��ܡ�Ҳ����ʵ����Ϸ�������Ż���
    //void clearRange(int x, int y, int width, int height);
    //���溯��
    void Interface(wchar_t* text);
    //����ѡ��չʾ����
    void DHS_DISPLAY();




private:
    directions direction01;//����1 ��������
    directions direction02;//����2 ��������
    Ui::QtWidgetsApplication1Class ui;
    QLabel* characterLabel;
    int characterX;//��ɫ��X����
    int characterY;
    int characterY0;//��ʼy ������y����
    QTimer* moveTimer;//��ʱ��


    bool choice = 2;//ģʽѡ�� Ĭ��Ϊ˫����Ϸ


    //����ʱ��
    QTimer* jumpTimer;
    //���䶨ʱ��
   //QTimer* downTimer;
    QMovie* characterMovie;
    QLabel* label;

    QLabel* healthLabel;   // Ѫ����ǩ
    QProgressBar* healthBar;   // Ѫ��
    QLabel* energyLabel;   // ��������ǩ
    QProgressBar* energyBar;   // ������
    double energyValue;   // ����ֵ
    double healthValue;   // Ѫ��ֵ


    double vy = jump_speed;
    double gravity = 2.5;
    //double jumpHeight=0;



    QMovie* attackMovie;   // ��������
    QMovie* jumpMovie;//��Ծ����

    bool isAttacking = false;   // �Ƿ����ڹ���
    // bool isLanded = true;//�ж��Ƿ����
     //bool isJumping = false;//�ж��Ƿ���Ծ
     //ǰ������
    QMovie* forwardMovie;
    //�¶׶���
    QMovie* crouchMovie;

    //���˶���
    QMovie* backwardMovie;




    QMovie* entranceMovie;//��������


    QMovie* crouchAttack;
    bool cantmove;   // �Ƿ�����ƶ�
    QMovie* skill0;//����0


    bool iscrouch;





    void skillFinished()
    {
        // ���ܶ���������ϣ����Խ�����������

        // �ָ��������ƶ��Ȳ���
        // ...

        // ���ñ�־λΪfalse����ʾ�����ͷ����
        cantmove = false;
    }
    QMetaObject::Connection connection;

    void showup();
    void castSkill1();
    //{
    //    // ���ñ�־λΪ true����ʾ�����ͷż���
    //    cantmove = true;

    //    // ��ͣ�����������繥�����ƶ�
    //    // ...

    //    // ���ż��ܶ���
    //    characterLabel->clear();
    //    characterLabel->setMovie(skill0);
    //    skill0->start();

    //    // ��ȡ���ܶ�����֡��
    //    int totalFrames = skill0->frameCount();

    //    // ���� frameChanged �źŵ��ۺ���
    //    connect(skill0, &QMovie::frameChanged, this, [this, totalFrames]() {
    //        // ��ȡ��ǰ֡��
    //        int currentFrame = skill0->currentFrameNumber();

    //        // �ж��Ƿ�ﵽ��֡��
    //        if (currentFrame == totalFrames - 1) {
    //            // ����������һ�飬ֹͣ���ܶ���
    //            skillFinished();
    //        }
    //        });
    //}


};