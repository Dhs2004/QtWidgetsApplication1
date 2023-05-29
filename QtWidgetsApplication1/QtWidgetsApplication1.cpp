
#include "QtWidgetsApplication1.h"


QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    DHS_DISPLAY();
    switch (choice)
    {
        //��������ģʽ
    case(1):
    {


    }

    //����˫��ģʽ
    case(2): {

        closegraph();
        // ������ɫ�� QMovie ����
        QFileInfo fileInfo("chara_pic_or_gif/bashen/zhanli.gif");
        QString absolutePath = fileInfo.absoluteFilePath();
        characterMovie = new QMovie(absolutePath);
        //��׽�����¼�
        installEventFilter(this);
        // ������ɫ�� QLabel ����
        characterLabel = new QLabel(this);
        this->setFixedSize(m_width, m_height);
        characterLabel->setGeometry(150, 450, 300, 300); // ���ó�ʼλ�úʹ�С
        characterLabel->setMovie(characterMovie);






        // �ڹ��캯�����ʼ��������...


        // ������ɫ�ĳ�������
        //QMovie* entranceMovie;
        entranceMovie = new QMovie("chara_pic_or_gif/bashen/chuchang.gif");

        //�Ƿ�����ƶ�
        cantmove = false;
        //�Ƿ��
        iscrouch = false;
        // ������������
        showup();





        // �� characterLabel ָ�븳ֵΪ������ QLabel ����
        this->characterLabel = characterLabel;

        // ��ʼ�� characterX ����Ϊ��ɫ�ĳ�ʼ x ����
        characterX = characterLabel->x();
        // ��ʼ�� characterY0 ����Ϊ��ɫ�ĳ�ʼ y ���� 
        characterY0 = characterLabel->y();
        characterY = characterLabel->y();
        direction01 = directions::none;
        direction02 = directions::none;
        // ������ʱ��
        moveTimer = new QTimer(this);
        jumpTimer = new QTimer(this);
        // ����ÿ֡ 16 ����
        moveTimer->setInterval(16);
        jumpTimer->setInterval(22);
        //downTimer->setInterval(16);
        // �����źźͲ�
        connect(moveTimer, &QTimer::timeout, this, &QtWidgetsApplication1::timeOut);
        connect(jumpTimer, &QTimer::timeout, this, &QtWidgetsApplication1::timeOut);
        //connect(downTimer, &QTimer::timeout, this, &QtWidgetsApplication1::timeOut);
        // ������ʼ������...

        // ��ʼ���Ž�ɫ�Ķ���
        characterMovie->start();

        // ����Ѫ����ǩ��Ѫ���ؼ�
        healthLabel = new QLabel("Health:", this);
        healthLabel->setGeometry(10, 10, 50, 20);
        healthBar = new QProgressBar(this);
        healthBar->setGeometry(70, 10, 100, 20);

        // ������������ǩ���������ؼ�
        energyLabel = new QLabel("Energy:", this);
        energyLabel->setGeometry(10, 40, 50, 20);
        energyBar = new QProgressBar(this);
        energyBar->setGeometry(70, 40, 100, 20);

        // ��ʼ��Ѫ��������ֵ
        healthValue = 100;
        energyValue = 100;
        // ����Ѫ��������������ֵ
        healthBar->setValue(healthValue);    // ����ʵ��Ѫ��ֵ���и���
        energyBar->setValue(energyValue);  // ����ʵ������ֵ���и���



        // ����������������
        attackMovie = new QMovie("chara_pic_or_gif/bashen/zhangong.gif");
        //noMovie = new QMovie(" ");
        // ��ʼ������״̬
        isAttacking = false;

        //��Ծ����
        jumpMovie = new QMovie("chara_pic_or_gif/bashen/zhitiao.gif");

        //�¶׶���
        crouchMovie = new QMovie("chara_pic_or_gif/bashen/xiadun.gif");
        //�¶׹���
        crouchAttack = new QMovie("chara_pic_or_gif/bashen/dungong.gif");

        //ǰ������
        forwardMovie = new QMovie("chara_pic_or_gif/bashen/qianjin.gif");
        //���˶���
        backwardMovie = new QMovie("chara_pic_or_gif/bashen/houtui.gif");
        //����0����
        skill0 = new QMovie("chara_pic_or_gif/bashen/skill0.gif");


    }

    }

}


// // ������ɫ�� QMovie ����
// QFileInfo fileInfo("D:\\360downloads\\QtWidgetsApplication1\\chara_pic_or_gif\\cao_chara1\\a01[2].gif"); 
// QString absolutePath = fileInfo.absoluteFilePath();
// characterMovie = new QMovie(absolutePath); 
// //��׽�����¼�
// installEventFilter(this);
// // ������ɫ�� QLabel ����
// characterLabel = new QLabel(this);
// this->setFixedSize(m_width, m_height);
// characterLabel->setGeometry(150, 450,300,300); // ���ó�ʼλ�úʹ�С
// characterLabel->setMovie(characterMovie);

// // �� characterLabel ָ�븳ֵΪ������ QLabel ����
// this->characterLabel = characterLabel; 

// // ��ʼ�� characterX ����Ϊ��ɫ�ĳ�ʼ x ����
// characterX = characterLabel->x(); 
// // ��ʼ�� characterY0 ����Ϊ��ɫ�ĳ�ʼ y ���� 
// characterY0 = characterLabel->y();

// direction = directions::none;

// // ������ʱ��
// moveTimer = new QTimer(this);
// jumpTimer = new QTimer(this);
//// ����ÿ֡ 16 ����
// jumpTimer->setInterval(16); 
// // �����źźͲ�
// connect(moveTimer, &QTimer::timeout, this, &QtWidgetsApplication1::timeOut);
// connect(jumpTimer, &QTimer::timeout, this, &QtWidgetsApplication1::timeOut);
// 
// // ������ʼ������...

// // ��ʼ���Ž�ɫ�Ķ���
// characterMovie->start();


void QtWidgetsApplication1::keyPressEvent(QKeyEvent* event)
{
    if (cantmove) { return; }

    if (event->key() == Qt::Key_A)
    {
        // ���� A ���������ƶ�

        direction01 = directions::left;
        if (!moveTimer->isActive()) {
            moveTimer->start(16);      // ����ÿ֡ 16 ����
        }
        // ���ý�ɫ�Ķ���
        if (!jumpTimer->isActive())
        {
            characterLabel->clear();
            characterLabel->setMovie(backwardMovie);
            backwardMovie->start();
        }
    }
    else if (event->key() == Qt::Key_S)
    {

        // ���� S �����¶�
        iscrouch = true;
        direction01 = directions::none;
        if (!moveTimer->isActive()) {
            moveTimer->start(16);
        }
        // ���ý�ɫ�Ķ���
        if (!jumpTimer->isActive())
        {
            characterLabel->clear();
            characterLabel->setMovie(crouchMovie);
            crouchMovie->start();
        }

    }
    else if (event->key() == Qt::Key_D)
    {
        // ���� D ���������ƶ�
        direction01 = directions::right;
        if (!moveTimer->isActive()) {
            moveTimer->start(16);
        }
        // ���ý�ɫ�Ķ���
        if (!jumpTimer->isActive())
        {
            characterLabel->clear();
            characterLabel->setMovie(forwardMovie);
            forwardMovie->start();
        }




    }

    else if (event->key() == Qt::Key_J)
    {
        // ����J�������й�������

        if (iscrouch) {
            moveTimer->stop();
            jumpTimer->stop();
            isAttacking = true;
            characterMovie->stop();
            // ��ն�����ǩ����
            characterLabel->clear();
            // �л�Ϊ��������
            characterLabel->setMovie(crouchAttack);
            crouchAttack->start();

        }
        else if (!isAttacking)
        {

            isAttacking = true;

            characterMovie->stop();
            if (!jumpTimer->isActive())
            {
                moveTimer->stop();
            }
            // ��ն�����ǩ����

            characterLabel->clear();

            // �л�Ϊ��������

            characterLabel->setMovie(attackMovie);

            attackMovie->start();
        }
    }

    else if (event->key() == Qt::Key_U)
    {
        // ����U��������skill0����
        //------------------------------------------------------------------------------------------
        mciSendStringA("open resources/music/2308.mp3 alias BGM", 0, 0, 0);
        mciSendStringA("play BGM ", 0, 0, 0);
        castSkill1();
       /* mciSendStringA("close BGM", 0, 0, 0);*/


    }

    else if (event->key() == Qt::Key_Space)
    {
        // �����ɫ�ڵ����ϣ�������Ծ
        if (characterY == characterY0)
        {
            // ���ý�ɫ�Ķ���
            characterLabel->clear();
            characterLabel->setMovie(jumpMovie);
            jumpMovie->start();

            // ������Ծ������ٶ�
            direction02 = directions::up;
            vy = jump_speed;
            // ������Ծ��ʱ��
            jumpTimer->start(22);
        }


    }
    /*else if (event->type() == QEvent::KeyRelease) {
       if (event->key() == Qt::Key_A || event->key() == Qt::Key_D) {
           moveTimer->stop();
           direction = directions::none;
       }
   }*/
   // ���½�ɫ��λ��

   //QLabel* characterLabel = this->characterLabel; 
   //characterLabel->move(characterX, characterY);

   // ���ø�����¼�������
    QMainWindow::keyPressEvent(event);
}

void QtWidgetsApplication1::keyReleaseEvent(QKeyEvent* event)
{

    if (cantmove) {
        moveTimer->stop();
        jumpTimer->stop();
        //direction = directions::none;
        return;
    }

    if (event->key() == Qt::Key_A || event->key() == Qt::Key_D || event->key() == Qt::Key_S)
    {
        // �ɿ� A �� D ����ֹͣ�ƶ�
        moveTimer->stop();
        //jumpTimer->stop();
        //downTimer->start();
        direction01 = directions::none;
        // ���ý�ɫ�Ķ���
        characterLabel->clear();
        characterLabel->setMovie(characterMovie);
        characterMovie->start();
        // forwardMovie->stop();
        // backwardMovie->stop();
    }




    //�ɿ��ո�ʱ
    else if (event->key() == Qt::Key_Space)
    {
        if (characterY < characterY0 && vy>0)
        {

        };

        if (characterY >= characterY0 && vy >= jump_speed)
        {
            jumpTimer->stop();
            direction02 = directions::none;
            vy = 0;

        }


    }
    else if (event->key() == Qt::Key_J)
    {
        // �ɿ� J ����ֹͣ����
        if (iscrouch) {
            isAttacking = false;
            characterLabel->clear();
            characterLabel->setMovie(crouchMovie);
            characterMovie->start();
        }

        else if (isAttacking) {
            isAttacking = false;
            // attackMovie->stop();
            characterLabel->clear();
            characterLabel->setMovie(characterMovie);
            characterMovie->start();
        }

    }
    else if (event->key() == Qt::Key_S)
    {
        //isAttacking = false;
        attackMovie->stop();
        characterLabel->clear();
        characterLabel->setMovie(characterMovie);
        characterMovie->start();
    }
    // ���ø�����¼�������
    QMainWindow::keyReleaseEvent(event);
}

void QtWidgetsApplication1::timeOut()
{


    //// ���ݷ���ı�����
    //switch (direction) {
    //case directions::left:
    //    characterX -= m_speed;
    //    break;
    //case directions::right:
    //    characterX += m_speed;
    //    break;
    //case directions::up:
    //    characterY -= m_speed;
    //    break;
        //characterY -= vy;
       // vy += jump_speed;
        // �ж��Ƿ�ﵽ��ߵ㣬��������л�Ϊ�½��׶�
        //if (vy <= 0) {
      //      direction = directions::down;
      //      vy = 0;
      //  }
      //  break;
    //case directions::down:
    //    vy += Gravity;
    //    characterY += vy;
    //    // �ж��Ƿ񴥵أ��������ֹͣ��Ծ
    //    if (characterY >= characterY0) {
    //        characterY = characterY0;
    //        // ���½�ɫ��λ��
    //        characterLabel->move(characterX, characterY);
    //        jumpTimer->stop();
    //        direction = directions::none;
    //    }
        // ������Ҫ����������ٶ�
       //break;

        // ������������...


        //characterLabel->move(characterX, characterY);
        // ��������Ƿ�Խ��

            // ���ݷ���ı�����
    switch (direction01) {
    case directions::left:
    {
        characterX -= m_speed;
        break;

    }
    case directions::right:
    {
        characterX += m_speed;
        break;
    }

    // case directions::down: {
    //     // ����ʱ���´�ֱ�ٶ�
    //     
    //     vy -= jump_speed;
    //     // �ж��Ƿ񴥵أ��������ֹͣ��Ծ
    //     if (characterY >= jumpHeight) {
    //         characterY = jumpHeight;
    //         vy = 0.0;
    //         jumpTimer->stop();
    //         direction = directions::none;
    //         // ��¼����״̬
    ////         isLanded = true;
    //     }
    //     // ������Ҫ����������ٶ�
    //     break; 
    // }
    default:
        break; // ����default��֧
    }

    switch (direction02)
    {
    case directions::up:
    {
        // ���´�ֱ�ٶȺ�λ��
        vy -= gravity;
        characterY -= vy;
        // �����ɫ��أ�ֹͣ��Ծ
        if (characterY >= characterY0)
        {
            characterY = characterY0;
            jumpTimer->stop();
            // ���ý�ɫ�Ķ���
            characterLabel->clear();
            characterLabel->setMovie(characterMovie);
            characterMovie->start();
            direction02 = directions::none;
        }

        break;
    }

    default:
        break; // ����default��֧
    }
    // ���´�ֱλ��
    //characterY += vy;
    // ��������Ƿ�Խ��
    if (characterX < 0) characterX = 0;
    if (characterX > m_width - 100) characterX = m_width - 100;
    if (characterY < 0) characterY = 0;
    if (characterY > m_height - 300) characterY = m_height - 300;
    // �ƶ���ɫ��ǩ
    characterLabel->move(characterX, characterY);
    //����Ѫ�� ������

    healthBar->setValue(healthValue);    // ����ʵ��Ѫ��ֵ���и���
    energyBar->setValue(energyValue);  // ����ʵ������ֵ���и���

}



void QtWidgetsApplication1::showup()
{
    // ���ñ�־λΪ true����ʾ���ڶ��������ƶ�
    cantmove = true;



    // ���ż��ܶ���
   
    characterLabel->clear();
    characterLabel->setMovie(entranceMovie);
    entranceMovie->start();
   

    // ��ȡ���ܶ�����֡��
    int totalFrames = entranceMovie->frameCount();

    // ���� frameChanged �źŵ��ۺ���
    connection = connect(entranceMovie, &QMovie::frameChanged, this, [this, totalFrames]() {
        // ��ȡ��ǰ֡��
        int currentFrame = entranceMovie->currentFrameNumber();

        // �ж��Ƿ�ﵽ��֡��
        if (currentFrame == totalFrames - 1) {
            // ����������һ�飬ֹͣ���ܶ���
            cantmove = false;
            characterLabel->clear();
            characterLabel->setMovie(characterMovie);
            characterMovie->start();

            disconnect(connection);
        }
        });
}


void QtWidgetsApplication1::castSkill1()
{
    // ���ñ�־λΪ true����ʾ�����ͷż���
    cantmove = true;

    // ��ͣ�����������繥�����ƶ�
    // ...

    // ���ż��ܶ���
    characterLabel->clear();
    characterLabel->setMovie(skill0);
    skill0->start();

    // ��ȡ���ܶ�����֡��
    int totalFrames = skill0->frameCount();

    // ���� frameChanged �źŵ��ۺ���
    connection = connect(skill0, &QMovie::frameChanged, this, [this, totalFrames]() {
        // ��ȡ��ǰ֡��
        int currentFrame = skill0->currentFrameNumber();

        // �ж��Ƿ�ﵽ��֡��
        if (currentFrame == totalFrames - 1) {
            // ����������һ�飬ֹͣ���ܶ���
            cantmove = false;
            characterLabel->clear();
            characterLabel->setMovie(characterMovie);
            skill0->stop();
            disconnect(connection);
        }
        });
}



















void QtWidgetsApplication1::CenterInitGraph()
{
    // ��ȡ��Ļ�ֱ���
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // ����initgraph���ڵĴ�С
    int width = WIDTH;
    int height = HEIGHT;

    // ����initgraph����Ӧ�ó�������Ļ�����λ��
    int x = (screenWidth - width) / 2;
    int y = (screenHeight - height) / 2;

    // ��ʼ��ͼ�ν��棬���������ƶ����������λ��
    initgraph(width, height);
    HWND hwnd = GetHWnd();
    SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void QtWidgetsApplication1::Interface(wchar_t* text)
{

    //����ע�͵������ǵ�����ʾ���ڣ������Ƿ�ʹ�ã��ɸ���ʵ�����������
    /*HWND hwnd;
    hwnd = GetHWnd();
    int is_ok = MessageBox(hwnd, _T(""), _T("��ʾ"), MB_OK);
    flushmessage(EM_MOUSE);*/
    initgraph(1024, 640, NOCLOSE | NOMINIMIZE);
    IMAGE img;
    CenterInitGraph();
    loadimage(&img, _T("E:\\MVandP\\p\\th.jpg"), 1024, 640);
    putimage(0, 0, &img);
    wchar_t Arr[] = _T("�˳���Ϸ");
    setlinecolor(YELLOW);
    settextcolor(BLACK);
    settextstyle(25, 0, _T("����"));
    setbkmode(TRANSPARENT);
    wchar_t arr[50] = { 0 };
    wcscpy_s(arr, text);
    fillroundrect(300, 200, 400 + textwidth(arr), 300 + textheight(arr), 50, 50);
    outtextxy(350, 250, arr);
    setlinecolor(YELLOW);
    settextcolor(BLACK);
    settextstyle(25, 0, _T("����"));
    setbkmode(TRANSPARENT);
    fillroundrect(600, 200, 700 + textwidth(Arr), 300 + textheight(Arr), 50, 50);
    outtextxy(650, 250, Arr);
    MOUSEMSG msg;
    int a = 1;
    GetMouseMsg();
    while (a)
    {

        if (MouseHit())
        {
            msg = GetMouseMsg();
            switch (msg.uMsg)
            {
            case WM_LBUTTONDOWN:
                if (msg.x > 300 && msg.x < 400 + textwidth(arr) && msg.y>200 && msg.y < 300 + textheight(arr))
                {
                    closegraph();
                    a = 0;
                    break;
                }
                else if (msg.x > 600 && msg.x < 700 + textwidth(Arr) && msg.y>200 && msg.y < 300 + textheight(Arr))
                {
                    cleardevice();
                    settextcolor(WHITE);
                    outtextxy(0, 0, _T("���������Ӻ��˳�"));
                    Sleep(3000);
                    closegraph();
                    exit(0);
                }
            default:
                break;
            }
        }
    }


}

void QtWidgetsApplication1::DHS_DISPLAY()
{

    {
        initgraph(WIDTH, HEIGHT);
        CenterInitGraph();
        loadimage(0, _T("resources/chara_pic/interface.jpg"), WIDTH, HEIGHT);//��������ʱ���������ͼƬ����ȻͼƬ���Ը��ġ�
        //��ť״̬ͼ
        IMAGE MenuBtn01, MenuBtn11, MenuBtn00, MenuBtn10;
        loadimage(&MenuBtn00, _T("resources/chara_pic/MenuBtn00.png"), 725, 75);
        loadimage(&MenuBtn01, _T("resources/chara_pic/MenuBtn01.png"), 725, 75);
        loadimage(&MenuBtn10, _T("resources/chara_pic/MenuBtn10.png"), 725, 80);
        loadimage(&MenuBtn11, _T("resources/chara_pic/MenuBtn11.png"), 725, 80);
        mciSendStringA("open resources/music/WHU��.mp3 alias BGM", 0, 0, 0);
        mciSendStringA("play BGM ", 0, 0, 0);

        //������
        MOUSEMSG msg;
        GetMouseMsg();
        bool MenuStatus = true;
        while (MenuStatus)
        {
           
            if (MouseHit())
            {
                msg = GetMouseMsg();
                //ʵ�����������ť����ť��ʽ�ı�
                switch (msg.uMsg)
                {
                case WM_MOUSEMOVE:

                    if (msg.x > 150 && msg.x < 875 && msg.y>435 && msg.y < 510)
                    {
                        putimage(150, 435, &MenuBtn01);
                        putimage(150, 540, &MenuBtn10);
                    }
                    else if (msg.x > 150 && msg.x < 875 && msg.y>540 && msg.y < 620)
                    {
                        putimage(150, 540, &MenuBtn11);
                        putimage(150, 435, &MenuBtn00);
                    }
                    else
                    {
                        putimage(150, 435, &MenuBtn00);
                        putimage(150, 540, &MenuBtn10);
                    }
                    break;

                    //ʵ���������ť����ת����Ϸ����
                case WM_LBUTTONDOWN:

                    if (msg.x > 150 && msg.x < 875 && msg.y>435 && msg.y < 510)
                    {
                        cleardevice();
                        closegraph();
                        choice = 1;
                        mciSendStringA("close BGM ", 0, 0, 0);
                        //������Ϸ��ť
                    }
                    else if (msg.x > 150 && msg.x < 875 && msg.y>540 && msg.y < 620)
                    {
                        cleardevice();
                        closegraph();
                        choice = 2;
                        mciSendStringA("close BGM ", 0, 0, 0);
                        //������Ϸ��ť
                    }
                    MenuStatus = false;
                    break;
                }
            }
        }
    }
}

void victory()
{
    initgraph(1024, 640, SHOWCONSOLE);
    IMAGE VICTORY;
    loadimage(&VICTORY, _T("C:\\Users\\86156\\Documents\\Tencent Files\\1973570506\\FileRecv\\QtWidgetsApplication1\\resources\\chara_pic\\BASHENAN.jpeg"), 1024, 640);
    putimage(0, 0, &VICTORY);
    /*settextcolor(YELLOW);
    setlinecolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(60, 40, _T("����"));
    wchar_t text[50] = _T("�����ֻ��ʤ����");
    outtextxy(512 - textwidth(text)/2, 320 - textheight(text)/2, text);*/
    Sleep(5000);
    closegraph();
}
void fail()
{
    initgraph(1024, 640, SHOWCONSOLE);
    IMAGE FAIL;
    loadimage(&FAIL, _T("C:\\Users\\86156\\Documents\\Tencent Files\\1973570506\\FileRecv\\QtWidgetsApplication1\\resources\\chara_pic\\CAOTIJING.jpg"), 1024, 640);
    putimage(0, 0, &FAIL);
    /*settextcolor(YELLOW);
    setlinecolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(60, 40, _T("����"));
    wchar_t text[50] = _T("���������ʤ����");
    outtextxy(512 - textwidth(text) / 2, 320 - textheight(text) / 2, text);
    Sleep(5000);*/
    Sleep(5000);
    closegraph();
}


QtWidgetsApplication1::~QtWidgetsApplication1()
{}