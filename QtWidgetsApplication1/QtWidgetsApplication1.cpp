
#include "QtWidgetsApplication1.h"


QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    DHS_DISPLAY();
    switch (choice)
    {
        //启动单人模式
    case(1):
    {


    }

    //启动双人模式
    case(2): {

        closegraph();
        // 创建角色的 QMovie 对象
        QFileInfo fileInfo("chara_pic_or_gif/bashen/zhanli.gif");
        QString absolutePath = fileInfo.absoluteFilePath();
        characterMovie = new QMovie(absolutePath);
        //捕捉键盘事件
        installEventFilter(this);
        // 创建角色的 QLabel 对象
        characterLabel = new QLabel(this);
        this->setFixedSize(m_width, m_height);
        characterLabel->setGeometry(150, 450, 300, 300); // 设置初始位置和大小
        characterLabel->setMovie(characterMovie);






        // 在构造函数或初始化函数中...


        // 创建角色的出场动画
        //QMovie* entranceMovie;
        entranceMovie = new QMovie("chara_pic_or_gif/bashen/chuchang.gif");

        //是否可以移动
        cantmove = false;
        //是否蹲
        iscrouch = false;
        // 启动出场动画
        showup();





        // 将 characterLabel 指针赋值为创建的 QLabel 对象
        this->characterLabel = characterLabel;

        // 初始化 characterX 变量为角色的初始 x 坐标
        characterX = characterLabel->x();
        // 初始化 characterY0 变量为角色的初始 y 坐标 
        characterY0 = characterLabel->y();
        characterY = characterLabel->y();
        direction01 = directions::none;
        direction02 = directions::none;
        // 创建定时器
        moveTimer = new QTimer(this);
        jumpTimer = new QTimer(this);
        // 假设每帧 16 毫秒
        moveTimer->setInterval(16);
        jumpTimer->setInterval(22);
        //downTimer->setInterval(16);
        // 连接信号和槽
        connect(moveTimer, &QTimer::timeout, this, &QtWidgetsApplication1::timeOut);
        connect(jumpTimer, &QTimer::timeout, this, &QtWidgetsApplication1::timeOut);
        //connect(downTimer, &QTimer::timeout, this, &QtWidgetsApplication1::timeOut);
        // 其他初始化操作...

        // 开始播放角色的动画
        characterMovie->start();

        // 创建血条标签和血条控件
        healthLabel = new QLabel("Health:", this);
        healthLabel->setGeometry(10, 10, 50, 20);
        healthBar = new QProgressBar(this);
        healthBar->setGeometry(70, 10, 100, 20);

        // 创建能量条标签和能量条控件
        energyLabel = new QLabel("Energy:", this);
        energyLabel->setGeometry(10, 40, 50, 20);
        energyBar = new QProgressBar(this);
        energyBar->setGeometry(70, 40, 100, 20);

        // 初始化血量和能量值
        healthValue = 100;
        energyValue = 100;
        // 更新血条和能量条的数值
        healthBar->setValue(healthValue);    // 根据实际血量值进行更新
        energyBar->setValue(energyValue);  // 根据实际能量值进行更新



        // 创建攻击动画对象
        attackMovie = new QMovie("chara_pic_or_gif/bashen/zhangong.gif");
        //noMovie = new QMovie(" ");
        // 初始化攻击状态
        isAttacking = false;

        //跳跃动画
        jumpMovie = new QMovie("chara_pic_or_gif/bashen/zhitiao.gif");

        //下蹲动画
        crouchMovie = new QMovie("chara_pic_or_gif/bashen/xiadun.gif");
        //下蹲攻击
        crouchAttack = new QMovie("chara_pic_or_gif/bashen/dungong.gif");

        //前进动画
        forwardMovie = new QMovie("chara_pic_or_gif/bashen/qianjin.gif");
        //后退动画
        backwardMovie = new QMovie("chara_pic_or_gif/bashen/houtui.gif");
        //技能0动画
        skill0 = new QMovie("chara_pic_or_gif/bashen/skill0.gif");


    }

    }

}


// // 创建角色的 QMovie 对象
// QFileInfo fileInfo("D:\\360downloads\\QtWidgetsApplication1\\chara_pic_or_gif\\cao_chara1\\a01[2].gif"); 
// QString absolutePath = fileInfo.absoluteFilePath();
// characterMovie = new QMovie(absolutePath); 
// //捕捉键盘事件
// installEventFilter(this);
// // 创建角色的 QLabel 对象
// characterLabel = new QLabel(this);
// this->setFixedSize(m_width, m_height);
// characterLabel->setGeometry(150, 450,300,300); // 设置初始位置和大小
// characterLabel->setMovie(characterMovie);

// // 将 characterLabel 指针赋值为创建的 QLabel 对象
// this->characterLabel = characterLabel; 

// // 初始化 characterX 变量为角色的初始 x 坐标
// characterX = characterLabel->x(); 
// // 初始化 characterY0 变量为角色的初始 y 坐标 
// characterY0 = characterLabel->y();

// direction = directions::none;

// // 创建定时器
// moveTimer = new QTimer(this);
// jumpTimer = new QTimer(this);
//// 假设每帧 16 毫秒
// jumpTimer->setInterval(16); 
// // 连接信号和槽
// connect(moveTimer, &QTimer::timeout, this, &QtWidgetsApplication1::timeOut);
// connect(jumpTimer, &QTimer::timeout, this, &QtWidgetsApplication1::timeOut);
// 
// // 其他初始化操作...

// // 开始播放角色的动画
// characterMovie->start();


void QtWidgetsApplication1::keyPressEvent(QKeyEvent* event)
{
    if (cantmove) { return; }

    if (event->key() == Qt::Key_A)
    {
        // 按下 A 键，向左移动

        direction01 = directions::left;
        if (!moveTimer->isActive()) {
            moveTimer->start(16);      // 假设每帧 16 毫秒
        }
        // 设置角色的动画
        if (!jumpTimer->isActive())
        {
            characterLabel->clear();
            characterLabel->setMovie(backwardMovie);
            backwardMovie->start();
        }
    }
    else if (event->key() == Qt::Key_S)
    {

        // 按下 S 键，下蹲
        iscrouch = true;
        direction01 = directions::none;
        if (!moveTimer->isActive()) {
            moveTimer->start(16);
        }
        // 设置角色的动画
        if (!jumpTimer->isActive())
        {
            characterLabel->clear();
            characterLabel->setMovie(crouchMovie);
            crouchMovie->start();
        }

    }
    else if (event->key() == Qt::Key_D)
    {
        // 按下 D 键，向右移动
        direction01 = directions::right;
        if (!moveTimer->isActive()) {
            moveTimer->start(16);
        }
        // 设置角色的动画
        if (!jumpTimer->isActive())
        {
            characterLabel->clear();
            characterLabel->setMovie(forwardMovie);
            forwardMovie->start();
        }




    }

    else if (event->key() == Qt::Key_J)
    {
        // 按下J键，进行攻击动画

        if (iscrouch) {
            moveTimer->stop();
            jumpTimer->stop();
            isAttacking = true;
            characterMovie->stop();
            // 清空动画标签内容
            characterLabel->clear();
            // 切换为攻击动画
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
            // 清空动画标签内容

            characterLabel->clear();

            // 切换为攻击动画

            characterLabel->setMovie(attackMovie);

            attackMovie->start();
        }
    }

    else if (event->key() == Qt::Key_U)
    {
        // 按下U键，进行skill0动画
        //------------------------------------------------------------------------------------------
        mciSendStringA("open resources/music/2308.mp3 alias BGM", 0, 0, 0);
        mciSendStringA("play BGM ", 0, 0, 0);
        castSkill1();
       /* mciSendStringA("close BGM", 0, 0, 0);*/


    }

    else if (event->key() == Qt::Key_Space)
    {
        // 如果角色在地面上，才能跳跃
        if (characterY == characterY0)
        {
            // 设置角色的动画
            characterLabel->clear();
            characterLabel->setMovie(jumpMovie);
            jumpMovie->start();

            // 设置跳跃方向和速度
            direction02 = directions::up;
            vy = jump_speed;
            // 启动跳跃定时器
            jumpTimer->start(22);
        }


    }
    /*else if (event->type() == QEvent::KeyRelease) {
       if (event->key() == Qt::Key_A || event->key() == Qt::Key_D) {
           moveTimer->stop();
           direction = directions::none;
       }
   }*/
   // 更新角色的位置

   //QLabel* characterLabel = this->characterLabel; 
   //characterLabel->move(characterX, characterY);

   // 调用父类的事件处理函数
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
        // 松开 A 或 D 键，停止移动
        moveTimer->stop();
        //jumpTimer->stop();
        //downTimer->start();
        direction01 = directions::none;
        // 设置角色的动画
        characterLabel->clear();
        characterLabel->setMovie(characterMovie);
        characterMovie->start();
        // forwardMovie->stop();
        // backwardMovie->stop();
    }




    //松开空格时
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
        // 松开 J 键，停止攻击
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
    // 调用父类的事件处理函数
    QMainWindow::keyReleaseEvent(event);
}

void QtWidgetsApplication1::timeOut()
{


    //// 根据方向改变坐标
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
        // 判断是否达到最高点，如果是则切换为下降阶段
        //if (vy <= 0) {
      //      direction = directions::down;
      //      vy = 0;
      //  }
      //  break;
    //case directions::down:
    //    vy += Gravity;
    //    characterY += vy;
    //    // 判断是否触地，如果是则停止跳跃
    //    if (characterY >= characterY0) {
    //        characterY = characterY0;
    //        // 更新角色的位置
    //        characterLabel->move(characterX, characterY);
    //        jumpTimer->stop();
    //        direction = directions::none;
    //    }
        // 根据需要调整跳起的速度
       //break;

        // 其他方向的情况...


        //characterLabel->move(characterX, characterY);
        // 检查坐标是否越界

            // 根据方向改变坐标
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
    //     // 下落时更新垂直速度
    //     
    //     vy -= jump_speed;
    //     // 判断是否触地，如果是则停止跳跃
    //     if (characterY >= jumpHeight) {
    //         characterY = jumpHeight;
    //         vy = 0.0;
    //         jumpTimer->stop();
    //         direction = directions::none;
    //         // 记录触地状态
    ////         isLanded = true;
    //     }
    //     // 根据需要调整跳起的速度
    //     break; 
    // }
    default:
        break; // 加上default分支
    }

    switch (direction02)
    {
    case directions::up:
    {
        // 更新垂直速度和位置
        vy -= gravity;
        characterY -= vy;
        // 如果角色落地，停止跳跃
        if (characterY >= characterY0)
        {
            characterY = characterY0;
            jumpTimer->stop();
            // 设置角色的动画
            characterLabel->clear();
            characterLabel->setMovie(characterMovie);
            characterMovie->start();
            direction02 = directions::none;
        }

        break;
    }

    default:
        break; // 加上default分支
    }
    // 更新垂直位置
    //characterY += vy;
    // 检查坐标是否越界
    if (characterX < 0) characterX = 0;
    if (characterX > m_width - 100) characterX = m_width - 100;
    if (characterY < 0) characterY = 0;
    if (characterY > m_height - 300) characterY = m_height - 300;
    // 移动角色标签
    characterLabel->move(characterX, characterY);
    //加载血条 能量条

    healthBar->setValue(healthValue);    // 根据实际血量值进行更新
    energyBar->setValue(energyValue);  // 根据实际能量值进行更新

}



void QtWidgetsApplication1::showup()
{
    // 设置标志位为 true，表示正在动画不能移动
    cantmove = true;



    // 播放技能动画
   
    characterLabel->clear();
    characterLabel->setMovie(entranceMovie);
    entranceMovie->start();
   

    // 获取技能动画的帧数
    int totalFrames = entranceMovie->frameCount();

    // 连接 frameChanged 信号到槽函数
    connection = connect(entranceMovie, &QMovie::frameChanged, this, [this, totalFrames]() {
        // 获取当前帧数
        int currentFrame = entranceMovie->currentFrameNumber();

        // 判断是否达到总帧数
        if (currentFrame == totalFrames - 1) {
            // 动画播放完一遍，停止技能动画
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
    // 设置标志位为 true，表示正在释放技能
    cantmove = true;

    // 暂停其他动作，如攻击和移动
    // ...

    // 播放技能动画
    characterLabel->clear();
    characterLabel->setMovie(skill0);
    skill0->start();

    // 获取技能动画的帧数
    int totalFrames = skill0->frameCount();

    // 连接 frameChanged 信号到槽函数
    connection = connect(skill0, &QMovie::frameChanged, this, [this, totalFrames]() {
        // 获取当前帧数
        int currentFrame = skill0->currentFrameNumber();

        // 判断是否达到总帧数
        if (currentFrame == totalFrames - 1) {
            // 动画播放完一遍，停止技能动画
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
    // 获取屏幕分辨率
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // 计算initgraph窗口的大小
    int width = WIDTH;
    int height = HEIGHT;

    // 计算initgraph窗口应该出现在屏幕中央的位置
    int x = (screenWidth - width) / 2;
    int y = (screenHeight - height) / 2;

    // 初始化图形界面，并将窗口移动到计算出的位置
    initgraph(width, height);
    HWND hwnd = GetHWnd();
    SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void QtWidgetsApplication1::Interface(wchar_t* text)
{

    //下面注释的内容是弹出提示窗口，至于是否使用，可根据实际情况而定。
    /*HWND hwnd;
    hwnd = GetHWnd();
    int is_ok = MessageBox(hwnd, _T(""), _T("提示"), MB_OK);
    flushmessage(EM_MOUSE);*/
    initgraph(1024, 640, NOCLOSE | NOMINIMIZE);
    IMAGE img;
    CenterInitGraph();
    loadimage(&img, _T("E:\\MVandP\\p\\th.jpg"), 1024, 640);
    putimage(0, 0, &img);
    wchar_t Arr[] = _T("退出游戏");
    setlinecolor(YELLOW);
    settextcolor(BLACK);
    settextstyle(25, 0, _T("楷体"));
    setbkmode(TRANSPARENT);
    wchar_t arr[50] = { 0 };
    wcscpy_s(arr, text);
    fillroundrect(300, 200, 400 + textwidth(arr), 300 + textheight(arr), 50, 50);
    outtextxy(350, 250, arr);
    setlinecolor(YELLOW);
    settextcolor(BLACK);
    settextstyle(25, 0, _T("楷体"));
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
                    outtextxy(0, 0, _T("将在三秒钟后退出"));
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
        loadimage(0, _T("resources/chara_pic/interface.jpg"), WIDTH, HEIGHT);//这里我暂时引用了你的图片，当然图片可以更改。
        //按钮状态图
        IMAGE MenuBtn01, MenuBtn11, MenuBtn00, MenuBtn10;
        loadimage(&MenuBtn00, _T("resources/chara_pic/MenuBtn00.png"), 725, 75);
        loadimage(&MenuBtn01, _T("resources/chara_pic/MenuBtn01.png"), 725, 75);
        loadimage(&MenuBtn10, _T("resources/chara_pic/MenuBtn10.png"), 725, 80);
        loadimage(&MenuBtn11, _T("resources/chara_pic/MenuBtn11.png"), 725, 80);
        mciSendStringA("open resources/music/WHU！.mp3 alias BGM", 0, 0, 0);
        mciSendStringA("play BGM ", 0, 0, 0);

        //鼠标监听
        MOUSEMSG msg;
        GetMouseMsg();
        bool MenuStatus = true;
        while (MenuStatus)
        {
           
            if (MouseHit())
            {
                msg = GetMouseMsg();
                //实现鼠标悬浮按钮，按钮样式改变
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

                    //实现鼠标点击按钮，跳转到游戏界面
                case WM_LBUTTONDOWN:

                    if (msg.x > 150 && msg.x < 875 && msg.y>435 && msg.y < 510)
                    {
                        cleardevice();
                        closegraph();
                        choice = 1;
                        mciSendStringA("close BGM ", 0, 0, 0);
                        //单人游戏按钮
                    }
                    else if (msg.x > 150 && msg.x < 875 && msg.y>540 && msg.y < 620)
                    {
                        cleardevice();
                        closegraph();
                        choice = 2;
                        mciSendStringA("close BGM ", 0, 0, 0);
                        //多人游戏按钮
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
    settextstyle(60, 40, _T("宋体"));
    wchar_t text[50] = _T("八神庵获得胜利！");
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
    settextstyle(60, 40, _T("宋体"));
    wchar_t text[50] = _T("草雉京获得胜利！");
    outtextxy(512 - textwidth(text) / 2, 320 - textheight(text) / 2, text);
    Sleep(5000);*/
    Sleep(5000);
    closegraph();
}


QtWidgetsApplication1::~QtWidgetsApplication1()
{}