#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<easyx.h>
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00
#include<graphics.h>
#include <mmSystem.h>//播放音乐的头文件
#include<string>
#include "vlc/vlc.h"  // libVLC header
#include <shellscalingapi.h>		// 引用头文件
#pragma comment(lib, "shcore.lib")


// 设置 DPI 感知级别的函数
void setDpiAwareness() {
    // 设置 DPI 感知级别为 PROCESS_PER_MONITOR_DPI_AWARE
    SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

}

// 在静态全局变量的构造函数中调用设置 DPI 感知级别的函数
struct DpiAwarenessInitializer {
    DpiAwarenessInitializer() {
        setDpiAwareness();
    }
};

// 定义一个静态全局变量，程序启动时会自动调用其构造函数
static DpiAwarenessInitializer dpiAwarenessInitializer;

#define X GetSystemMetrics(SM_CXSCREEN)
#define Y GetSystemMetrics(SM_CYSCREEN)
#define X0 1536
#define Y0 864
#define K X/X0
double text_x = 620 * K, text_y = 420 * K,
shang1_l = 465.6 * K, shang1_r = 605.6 * K, shang_u = 75.2 * K, shang_d = 28 * K,
shang2_l = 628.8 * K, shang2_r = 753 * K,
shang3_l = 776.8 * K, shang3_r = 916.8 * K,
shang4_l = 931.2 * K, shang4_r = 1072 * K,
xia1_l = 917 * K, xia1_r = 1193 * K, xia_u = 837 * K, xia_d = 776 * K,
xia2_l = 1213 * K, xia2_r = 1491 * K,
jiantou1_l = 46.4 * K, jiantou1_r = 74.4 * K, jiantou_u = 450.4 * K, jiantou_d = 414.4 * K,
jiantou2_l = 1463.2 * K, jiantou2_r = 1491.2 * K,
yuanshishu_x = 1210 * K, yuanshishu_y = 27 * K, yuanshidaxiao = 24 * K,
jiuchanshu_x = 1377 * K,
zhong_x = 704 * K,
sanup = 148.2 * K,
siup = 79 * K,
wuup = 59.2 * K,
tiao_x = 116 * K,
santiao_y = 574.4 * K,
sitiao_y = 698.85 * K,
wutiao_y = 742 * K,

chushiweizhi = 184.8 * K,
tuichu_l = 1452 * K, tuichu_r = 1498 * K, tuichu_u = 17 * K, tuichu_d = 63 * K,

dgshuzi_l = 380 * 0.8 * K, dgshuzi_u = 750 * 0.8 * K,  
dgshuzi2_l = 1307 * 0.8 * K, dgshuzi2_u = 740 * 0.8 * K,
dgdaxiao = 28 * K,
dinggui_l = 281 * K, dinggui_r = 411 * K, dinggui_d = 630 * K, dinggui_u = 500 * K,
dgtc_l = 1226 * K, dgtc_r = 1255 * K, dgtc_d = 182 * K, dgtc_u = 149 * K,
dg1l_l = 1139 * 0.8 * K, dg1l_r = 1265 * 0.8 * K, dg1l_d = 548 * 0.8 * K, dg1l_u = 359 * 0.8 * K,
dg1r_l = 1305 * 0.8 * K, dg1r_r = 1430 * 0.8 * K, dg1r_d = 548 * 0.8 * K, dg1r_u = 359 * 0.8 * K,
dgqd_l = 1098 * 0.8 * K, dgqd_r = 1470 * 0.8 * K, dgqd_d = 866 * 0.8 * K, dgqd_u = 803 * 0.8 * K,
dgtsqx_l = 571 * 0.8 * K, dgtsqx_r = 942 * 0.8 * K, dgtsqx_u = 726 * 0.8 * K, dgtsqx_d = 790 * 0.8 * K,
dgtsqr_l = 980 * 0.8 * K, dgtsqr_r = 1350 * 0.8 * K, dgtsqr_u = 726 * 0.8 * K, dgtsqr_d = 790 * 0.8 * K;

int xy;
void XY() {
    // 设置 DPI 感知级别为 PROCESS_PER_MONITOR_DPI_AWARE
    if (fabs(X*1.0 / Y - 1.6) <= 0.001)xy =(int) (Y - X / 16.0 * 9) / 2.0;
    else xy = 0;
}

// 在静态全局变量的构造函数中调用设置 DPI 感知级别的函数
struct XYZ {
    XYZ() {
        XY();
    }
};

static XYZ p;

#pragma comment(lib,"winmm.lib")//加载库文件
#pragma comment(lib,"libvlc.lib")
#pragma comment(lib,"libvlccore.lib")
#define N1 358
using namespace std;
int f1[2000][2] = { 0 };//第一行依次为0-三星武器，1-四星武器，2-四星角色，3-五星up角色,4-五星常驻角色
int f2[2000][2] = { 0 };
char dzm[128];
IMAGE bak;

IMAGE img0; IMAGE img1; IMAGE img2; IMAGE img3; IMAGE img4; IMAGE img5; IMAGE img6; IMAGE img7; IMAGE img8; IMAGE img9;
void Card_drawing_animation(char name[100]) {
    // Initialize EasyX graphics window
    initgraph(X, Y, SHOWCONSOLE);
    HWND hwnd1 = GetHWnd();
    SetWindowLong(hwnd1, GWL_STYLE, GetWindowLong(hwnd1, GWL_STYLE) - WS_CAPTION);
    // Get the window handle of the EasyX window
    HWND hwnd = GetHWnd();
    
    libvlc_instance_t* inst;
    libvlc_media_t* m;
    libvlc_media_player_t* mp;
    inst = libvlc_new(NULL, NULL);
    char filename[1024];
    sprintf_s(filename, "src\\%s.mp4", name);
    //sprintf_s(filename, "http://moshang.zicp.fun:8088//src//%s.mp4", name);
    //播放本地文件
    m = libvlc_media_new_path(inst, filename);
    //m = libvlc_media_new_location(inst, filename);
    mp = libvlc_media_player_new_from_media(m);
    libvlc_media_release(m);
    libvlc_media_player_play(mp);
    // Set the HWND where the media player should render its video output
    libvlc_media_player_set_hwnd(mp, hwnd);
    
   
    
    _sleep(6400);
    
    //Sleep(libvlc_media_player_get_length(mp) - 600);
    libvlc_media_player_stop(mp);
    // Release the media player and libVLC instance
    libvlc_media_player_release(mp);
    libvlc_release(inst);
    // Close the EasyX graphics window

}



void Sound(int a) {
    char filename[50];char name[50];
    libvlc_instance_t* inst;
    inst = libvlc_new(NULL, NULL);
    switch (a) {
    case 1:sprintf_s(name, "draw_cards_button");break;
    case 2:sprintf_s(name, "picture_merge");break;
    case 3:sprintf_s(name, "quit_button");break;
    case 4:sprintf_s(name, "side_switch");break;
    case 5:sprintf_s(name, "up_switch");break;
    case 6:sprintf_s(name, "dinggui_enter");break;
    case 7:sprintf_s(name, "dinggui_switch");break;
    case 8:sprintf_s(name, "dinggui_confirm");break;
    case 9:sprintf_s(name, "dinggui_click");break;
    case 10:sprintf_s(name, "dinggui_enter2");break;
    case 11:sprintf_s(name, "dinggui_quit");break;
    case 12:sprintf_s(name, "quxiaodinggui");break;
    }
    sprintf_s(filename, "src\\%s.mp3", name);
    //播放本地文件
   
    libvlc_media_player_play(libvlc_media_player_new_from_media(libvlc_media_new_path(inst, filename)));

}

void tiaoweisy() {
    ExMessage msg;
    int ii = 1;

    while (ii) {
        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= tuichu_l && msg.x <= tuichu_r && msg.y >= tuichu_u + xy && msg.y <= tuichu_d + xy) {
                    ii = 0;
                    Sound(3);
                }
                break;
            default:
                break;
            }
        }
    }

}
int fx1(int x) {
    int y;
    if (x <= 73)y = 60;
    else if (x > 73 && x < 90)y = -43740 + x * 600;
    else y = 10000;
    return y;

}
int gx1(int x) {
    int y;
    if (x <= 8)y = 510;
    else if (x == 9)y = 5610;
    else y = 10000;
    return y;
}
int fx2(int x) {//用于产生五星武器抽取概率，输入为第几抽，输出与从1到10000的产生随机数比较得出概率
    int y;
    if (x <= 62)y = 70;
    else if (x > 62 && x <= 73)y = -43330 + x * 700;
    else if (x > 73 && x < 80)y = -17780 + x * 350;
    else y = 10000;
    return y;
}
int gx2(int x) {//用于产生四星武器抽取概率，其他同上
    int y;
    if (x <= 7)y = 600;
    else if (x == 8)y = 6600;
    else y = 10000;
    return y;
}
void upwxjs(int* np, int* xz) {//1
    if (*xz == 1)cout << "阿蕾奇诺";
    else if (*xz == 2)cout << "林尼";
    if (*np == 1) {

        Sound(2);
        putimage(0, xy, &bak);
        sprintf_s(dzm, "src\\4.6上\\upwxjs\\%d.jpg", *xz);
        loadimage(&img1, dzm, tiao_x, wutiao_y + xy);
        _sleep(100);
        putimage(zhong_x, wuup + xy, &img1);
        int ii = 1;
        tiaoweisy();

    }
}
int czwxjs(int* np) {//1
    int a;
    using namespace std;
    a = rand() % 6 + 1;
    if (*np == 1) {
        Sound(2);
        putimage(0, xy, &bak);
        sprintf_s(dzm, "src\\4.6上\\czwxjs\\%d.jpg", a);
        loadimage(&img1, dzm, tiao_x, wutiao_y + xy);
        _sleep(100);
        putimage(zhong_x, wuup + xy, &img1);
        tiaoweisy();
    }

    switch (a) {
    case 1:cout << "提纳里"; break;//
    case 2:cout << "刻晴"; break;//
    case 3:cout << "莫娜"; break;//
    case 4:cout << "七七"; break;//
    case 5:cout << "迪卢克"; break;//
    case 6:cout << "琴"; break;//
    }
    return a;
}
int sxjs(int* np) {//3
    int a;
    a = rand() % 3 + 1;

    if (*np == 1) {
        Sound(2);
        putimage(0, xy, &bak);
        sprintf_s(dzm, "src\\4.6上\\sxjs\\%d.jpg", a);
        loadimage(&img2, dzm, tiao_x, sitiao_y + xy);
        _sleep(100);
        putimage(zhong_x, siup + xy, &img2);
        tiaoweisy();
    }
    switch (a) {
    case 1:cout << "香菱"; break;//
    case 2:cout << "菲米尼"; break;//
    case 3:cout << "琳妮特"; break;//
    }
    return  a;
}
int sxwp(int* np) {//44
    int a;
    a = rand() % 51 + 1;
    if (*np == 1) {
        Sound(2);
        putimage(0, xy, &bak);
        sprintf_s(dzm, "src\\4.6上\\sxwp\\%d.jpg", a);
        loadimage(&img3, dzm, tiao_x, sitiao_y + xy);
        _sleep(100);
        putimage(zhong_x, siup + xy, &img3);
        tiaoweisy();

    }
    switch (a) {
    case 1:cout << "祭礼弓"; break;//
    case 2:cout << "西风猎弓"; break;//
    case 3:cout << "弓藏"; break;//
    case 4:cout << "绝弦"; break;//
    case 5:cout << "昭心"; break;//
    case 6:cout << "流浪乐章"; break;//
    case 7:cout << "西风大剑"; break;//
    case 8:cout << "祭礼残章"; break;//
    case 9:cout << "西风秘典"; break;//
    case 10:cout << "匣里灭辰"; break;//
    case 11:cout << "祭礼大剑"; break;//
    case 12:cout << "祭礼剑"; break;//
    case 13:cout << "西风长枪"; break;//
    case 14:cout << "雨裁"; break;//
    case 15:cout << "钟剑"; break;//
    case 16:cout << "匣里龙吟"; break;//
    case 17:cout << "笛剑"; break;
    case 18:cout << "西风剑"; break;//
    case 19:cout << "米卡"; break;
    case 20:cout << "迪奥娜"; break;//
    case 21:cout << "砂糖"; break;//
    case 22:cout << "鹿野院平藏"; break;//
    case 23:cout << "五郎"; break;//
    case 24:cout << "托马"; break;//
    case 25:cout << "辛焱"; break;//
    case 26:cout << "班尼特"; break;//
    case 27:cout << "诺艾尔"; break;//
    case 28:cout << "菲谢尔"; break;//
    case 29:cout << "雷泽"; break;//
    case 30:cout << "罗莎莉亚"; break;//
    case 31:cout << "珐露珊"; break;//
    case 32:cout << "坎蒂丝"; break;//
    case 33:cout << "凝光"; break;//
    case 34:cout << "云堇"; break;//
    case 35:cout << "九条裟罗"; break;//
    case 36:cout << "早柚"; break;//
    case 37:cout << "烟绯"; break;//
    case 38:cout << "柯莱"; break;//
    case 39:cout << "重云"; break;//
    case 40:cout << "北斗"; break;//
    case 41:cout << "莱依拉"; break;//
    case 42:cout << "行秋"; break;//
    case 43:cout << "瑶瑶"; break;//
    case 44:cout << "芭芭拉"; break;//
    case 45:cout << "多莉"; break;//
    case 46:cout << "久岐忍"; break;//
    case 47:cout << "嘉明"; break;//
    case 48:cout << "夏沃蕾"; break;//
    case 49:cout << "夏洛蒂"; break;//
    case 50:cout << "琦良良"; break;//
    case 51:cout << "卡维"; break;//
    }
    return a;
}
int saxwq(int* np) {//1 2
    using namespace std;
    int a;
    a = rand() % 13 + 1;
    if (*np == 1) {
        Sound(2);
        putimage(0, xy, &bak);
        sprintf_s(dzm, "src\\4.6上\\saxwq\\%d.jpg", a);
        loadimage(&img4, dzm, tiao_x, santiao_y + xy);
        _sleep(100);
        putimage(zhong_x, sanup + xy, &img4);
        tiaoweisy();



    }
    switch (a) {
    case 1:cout << "弹弓"; break;
    case 2:cout << "鸦羽弓"; break;
    case 3:cout << "讨龙英杰谭"; break;
    case 4:cout << "黑缨枪"; break;
    case 5:cout << "沐浴龙血的剑"; break;
    case 6:cout << "飞天御剑"; break;
    case 7:cout << "冷刃"; break;
    case 8:cout << "神射手之誓"; break;
    case 9:cout << "翡玉法球"; break;
    case 10:cout << "魔导绪论"; break;
    case 11:cout << "以理服人"; break;
    case 12:cout << "铁影阔剑"; break;
    case 13:cout << "黎明神剑"; break;
    }
    return a;
}
int czwxwq(int* np) {//2
    int a;
    a = rand() % 10 + 1;
    if (*np == 1) {
        Sound(2);
        putimage(0, xy, &bak);
        sprintf_s(dzm, "src\\4.6上\\czwxwq\\%d.jpg", a);
        loadimage(&img1, dzm, tiao_x, wutiao_y + xy);
        _sleep(100);
        putimage(zhong_x, wuup + xy, &img1);
        tiaoweisy();
    }
    switch (a) {
    case 1:cout << "阿莫斯之弓"; break;//
    case 2:cout << "天空之翼"; break;//
    case 3:cout << "四风原典"; break;//
    case 4:cout << "天空之卷"; break;//
    case 5:cout << "和璞鸢"; break;//
    case 6:cout << "天空之脊"; break;//
    case 7:cout << "狼的末路"; break;//
    case 8:cout << "天空之傲"; break;//
    case 9:cout << "天空之刃"; break;//
    case 10:cout << "风鹰剑"; break;
    }
    return a;
}
int wwsxwp(int* np) {//为四星未提升概率武器或角色，目的与三星武器区分，函数用于产生四星武器//2
    int a;
    a = rand() % 50 + 1;
    if (*np == 1) {
        Sound(2);
        putimage(0, xy, &bak);
        sprintf_s(dzm, "src\\4.6上\\wwsxwp\\%d.jpg", a);
        loadimage(&img3, dzm, tiao_x, sitiao_y + xy);
        _sleep(100);
        putimage(zhong_x, siup + xy, &img3);
        tiaoweisy();


    }
    switch (a) {
    case 1:cout << "莱依拉"; break;
    case 2:cout << "多莉"; break;//
    case 3:cout << "久岐忍"; break;//
    case 4:cout << "鹿野院平藏"; break;//
    case 5:cout << "五郎"; break;//
    case 6:cout << "托马"; break;//
    case 7:cout << "辛焱"; break;//
    case 8:cout << "迪奥娜"; break;//
    case 9:cout << "诺艾尔"; break;//
    case 10:cout << "菲谢尔"; break;//
    case 11:cout << "雷泽"; break;//
    case 12:cout << "罗莎莉亚"; break;//
    case 13:cout << "珐露珊"; break;//
    case 14:cout << "坎蒂丝"; break;//
    case 15:cout << "柯莱"; break;//
    case 16:cout << "云堇"; break;//
    case 17:cout << "九条裟罗"; break;//
    case 18:cout << "早柚"; break;//
    case 19:cout << "烟绯"; break;//
    case 20:cout << "砂糖"; break;//
    case 21:cout << "重云"; break;//
    case 22:cout << "班尼特"; break;//
    case 23:cout << "香菱"; break;//
    case 24:cout << "芭芭拉"; break;//
    case 25:cout << "北斗"; break;//
    case 26:cout << "凝光"; break;//
    case 27:cout << "行秋"; break;//
    case 28:cout << "瑶瑶"; break;//
    case 29:cout << "钟剑"; break;
    case 30:cout << "绝弦"; break;
    case 31:cout << "西风剑"; break;
    case 32:cout << "西风长枪"; break;
    case 33:cout << "流浪乐章"; break;
    case 34:cout << "祭礼剑"; break;
    case 35:cout << "雨裁"; break;
    case 36:cout << "西风秘典"; break;
    case 37:cout << "祭礼大剑"; break;
    case 38:cout << "西风大剑"; break;//
    case 39:cout << "匣里龙吟"; break;
    case 40:cout << "笛剑"; break;
    case 41:cout << "祭礼弓"; break;
    case 42:cout << "弓藏"; break;
    case 43:cout << "祭礼残章"; break;
    case 44:cout << "夏沃蕾"; break;
    case 45:cout << "夏洛蒂"; break;
    case 46:cout << "菲米尼"; break;
    case 47:cout << "琳妮特"; break;
    case 48:cout << "琦良良"; break;
    case 49:cout << "卡维"; break;
    case 50:cout << "嘉明"; break;
    }
    return a;
}
int wwsxwq(int* np) {//为四星提升概率武器//2
    int a;
    a = rand() % 5 + 1;
    if (*np == 1) {
        Sound(2);
        putimage(0, xy, &bak);
        sprintf_s(dzm, "src\\4.6上\\wwsxwq\\%d.jpg", a);
        loadimage(&img3, dzm, tiao_x, sitiao_y + xy);
        _sleep(100);
        putimage(zhong_x, siup + xy, &img3);
        tiaoweisy();


    }
    switch (a) {
    case 1:cout << "昭心"; break;
    case 2:cout << "便携动力锯"; break;
    case 3:cout << "匣里灭辰"; break;
    case 4:cout << "船坞长剑"; break;
    case 5:cout << "西风猎弓"; break;
    }
    return a;
}
int czsxjs(int* np) {//27 24函数名为四星角色的首字母，通过输入指针x(x所指数据含义：若*x=0,表示接下来的四星角色可能不是概率提升的四星角色；若*x=1,表示接下来的四星角色为概率提升的四星角色)，此函数用于产生四星角色
    int a;
    a = rand() % 38 + 1;
    if (*np == 1) {
        Sound(2);
        putimage(0, xy, &bak);
        sprintf_s(dzm, "src\\4.6上\\czsxjs\\%d.jpg", a);
        loadimage(&img1, dzm, tiao_x, sitiao_y + xy);
        _sleep(100);
        putimage(zhong_x, siup + xy, &img1);
        tiaoweisy();
    }
    switch (a) {
    case 1:cout << "莱依拉"; break;
    case 2:cout << "多莉"; break;
    case 3:cout << "久岐忍"; break;
    case 4:cout << "鹿野院平藏"; break;
    case 5:cout << "五郎"; break;
    case 6:cout << "托马"; break;
    case 7:cout << "辛焱"; break;
    case 8:cout << "迪奥娜"; break;
    case 9:cout << "诺艾尔"; break;
    case 10:cout << "菲谢尔"; break;
    case 11:cout << "雷泽"; break;
    case 12:cout << "罗莎莉亚"; break;
    case 13:cout << "珐露珊"; break;
    case 14:cout << "坎蒂丝"; break;
    case 15:cout << "凝光"; break;
    case 16:cout << "云堇"; break;
    case 17:cout << "九条裟罗"; break;
    case 18:cout << "早柚"; break;
    case 19:cout << "烟绯"; break;
    case 20:cout << "砂糖"; break;
    case 21:cout << "重云"; break;
    case 22:cout << "北斗"; break;
    case 23:cout << "香菱"; break;
    case 24:cout << "行秋"; break;
    case 25:cout << "瑶瑶"; break;
    case 26:cout << "班尼特"; break;
    case 27:cout << "柯莱"; break;
    case 28:cout << "芭芭拉"; break;
    case 29:cout << "安柏"; break;
    case 30:cout << "凯亚"; break;
    case 31:cout << "丽莎"; break;
    case 32:cout << "夏沃蕾"; break;//
    case 33:cout << "夏洛蒂"; break;
    case 34:cout << "菲米尼"; break;
    case 35:cout << "琳妮特"; break;
    case 36:cout << "琦良良"; break;
    case 37:cout << "卡维"; break;
    case 38:cout << "嘉明"; break;
    }
    return a;
}
int czsxwq(int* np) {//函数名为四星武器的缩写，其中多一个i，目的与三星武器区分，函数用于产生四星武器
    int a;
    a = rand() % 18 + 1;
    if (*np == 1) {
        Sound(2);
        putimage(0, xy, &bak);
        sprintf_s(dzm, "src\\4.6上\\czsxwq\\%d.jpg", a);
        loadimage(&img1, dzm, tiao_x, sitiao_y + xy);
        _sleep(100);
        putimage(zhong_x, siup + xy, &img1);
        tiaoweisy();

    }
    switch (a) {
    case 1:cout << "祭礼弓"; break;
    case 2:cout << "西风猎弓"; break;
    case 3:cout << "弓藏"; break;
    case 4:cout << "绝弦"; break;
    case 5:cout << "昭心"; break;
    case 6:cout << "流浪乐章"; break;
    case 7:cout << "西风大剑"; break;
    case 8:cout << "祭礼残章"; break;
    case 9:cout << "西风秘典"; break;
    case 10:cout << "匣里灭辰"; break;
    case 11:cout << "祭礼大剑"; break;
    case 12:cout << "祭礼剑"; break;
    case 13:cout << "西风长枪"; break;
    case 14:cout << "雨裁"; break;
    case 15:cout << "钟剑"; break;
    case 16:cout << "匣里龙吟"; break;
    case 17:cout << "笛剑"; break;
    case 18:cout << "西风剑"; break;
    }
    return a;
}

int  main()
{
    
    int xz, * p, p1, * pn, * pp, g, bd_1, bd1_1, ljcs_1 = 0, fff_1 = 1, d_1, d1_1, a_1, a1_1, f_1, n, i1_1 = 1, i2_1, i3_1, ii = 1, x, F = 0, sl[10][2] = { 0 };
    double xbd_1 = 0, xbdbw_1 = 0, sum_1 = 0, sum1_1 = 0;
    p = &p1;
    pp = &xz;
    pn = &n;

    //IMAGE image1[N1]; IMAGE image2[N1]; IMAGE image3[N1]; IMAGE image4[N1]; IMAGE image5[N1];
    xz = 1;
    d_1 = 0;
    /*cout << "请输入当前最后一0现四星后出现三星的次数：\n";
    cin >> d1;*/
    d1_1 = 0;
    i2_1 = d_1 + 1; i3_1 = d1_1 + 1;
    /*cout << "当前是否有大保底？(有1,无0)\n";
    cin >> bd;*/
    bd_1 = 0;
    /*cout << "上个四星是武器(1)还是角色(0):\n";
    cin >> bd1;*/
    bd1_1 = 0;
    /*cout << "上个四星角色是(0)否(1)为获取概率提升角色：\n";
    cin >> p1;*/
    p1 = 0;

    int  dg = 3, d_2, d1_2, i1_2, i2_2, i3_2, bd_2, bd1_2, s, ljcs_2 = 0, a_2, a1_2, f_2, fff_2 = 1;
    double sum = 0, sum1_2 = 0, sum2_2 = 0;

    s = 0; d_2 = 0; d1_2 = 0; i2_2 = d_2 + 1; i3_2 = d1_2 + 1; bd_2 = 0; bd1_2 = 1;
    //s未抽中定规出5星次数
    int ys, fq, lq;
    cout << "请输入您的原石、粉球、蓝球数量：\n";
    cin >> ys >> fq >> lq;


    int  bd, bd1, ljcs = 0, fff = 1, d, d1, a, a1, f, i1, i2, i3;

    d = 0; d1 = 0; i2 = d + 1; i3 = d1 + 1; bd = 0; bd1 = 0;
    libvlc_instance_t* inst;
    inst = libvlc_new(0, NULL);
    libvlc_media_list_t* ml;
    libvlc_media_t* md;
    libvlc_media_list_player_t* mlp;
    ml = libvlc_media_list_new(inst);
    md = libvlc_media_new_path(inst, "src\\bkmusic.mp3");
    libvlc_media_list_add_media(ml, md);
    libvlc_media_release(md);
    mlp = libvlc_media_list_player_new(inst);
    libvlc_media_player_t* mp = libvlc_media_player_new(inst);
    libvlc_media_list_player_set_media_list(mlp, ml);
    libvlc_media_list_player_set_media_player(mlp, mp);
    libvlc_media_list_player_set_playback_mode(mlp, libvlc_playback_mode_loop);
    libvlc_media_list_player_play(mlp);
FLAG:

    initgraph(X, Y, SHOWCONSOLE);
    const char* fontPath = "src\\zh-cn.ttf"; // 替换为你的字体文件路径
    AddFontResource(fontPath);
    IMAGE img;
    HWND hwnd = GetHWnd();
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION); SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN), SWP_SHOWWINDOW);

    string z{ "  " }, ysc, fqc, lqc;
    if (ys >= 0 && ys < 10)ysc = z + z + z + to_string(ys) + z;
    else if (ys < 100)ysc = z + z + to_string(ys) + z;
    else if (ys < 10000)ysc = z + to_string(ys) + z;
    else ysc = to_string(ys) + z;
    LPCSTR str1 = ysc.c_str();

    if (fq >= 0 && fq < 10)fqc = z +  to_string(fq) + z;
    else fqc = to_string(fq) + z;
    LPCSTR str2 = fqc.c_str();

    if (lq >= 0 && lq < 10)lqc = z +  to_string(lq) + z;
    else lqc = to_string(lq) + z;
    LPCSTR str3 = lqc.c_str();

    ExMessage msg;
    
    //getchar();
    loadimage(&bak, "src\\4.6上\\tiaobeijing.jpg", X0 * K, Y0 * K);
    if (xz == 1)
        loadimage(&img, "src\\4.6上\\up阿蕾奇诺池.jpg", X0 * K, Y0 * K);
    else if (xz == 2)
        loadimage(&img, "src\\4.6上\\up林尼池.jpg", X0 * K, Y0 * K);
    else if (xz == 3)
        if (dg == 3)
            loadimage(&img, "src\\4.6上\\武器池.jpg", X0 * K, Y0 * K);
        else 
            loadimage(&img, "src\\4.6上\\武器池().jpg", X0 * K, Y0 * K);
    else if (xz == 4)
        loadimage(&img, "src\\4.6上\\常驻池.jpg", X0 * K, Y0 * K);
    putimage(0, xy, &img);
    if (xz == 3 && dg != 3) {
        settextcolor(RGB(243, 143, 0));
        setbkcolor(RGB(236, 229, 216));
        settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
        char z[100];
        sprintf(z, "    %d", s);
        outtextxy(dgshuzi_l, dgshuzi_u + xy, z);
        settextcolor(RGB(73, 83, 102));
        settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
        outtextxy(dgshuzi_l + yuanshidaxiao + 12 * K, dgshuzi_u + xy, "/2    ");
    }
    settextcolor(RGB(250, 251, 255));
    setbkcolor(RGB(81, 104, 124));
    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
    outtextxy(yuanshishu_x, yuanshishu_y + xy, str1);
    if (xz <= 3)outtextxy(jiuchanshu_x, yuanshishu_y + xy, str2);
    else outtextxy(jiuchanshu_x, yuanshishu_y + xy, str3);
    while (ii) {

        if (peekmessage(&msg, EM_MOUSE)) {

            if (msg.message == WM_LBUTTONDOWN)
            {


                if (msg.x >= xia1_l && msg.x <= xia1_r && msg.y >= xia_d + xy && msg.y <= xia_u + xy) {
                    n = 1;
                    if (fq >= 1 && xz <= 3)fq -= 1;
                    else if (lq >= 1 && xz == 4)lq -= 1;
                    else if (ys >= 160)ys -= 160;
                    else if (xz <= 3) {
                        closegraph();
                        cout << "缺乏原石(仅剩" << ys << "原石)，请输入增加的原石、粉球:\n";
                        int i, j;
                        cin >> i >> j;
                        ys += i; fq += j;
                        goto FLAG;
                    }
                    else {
                        closegraph();
                        cout << "缺乏原石(仅剩" << ys << "原石)，请输入增加的原石、蓝球:\n";
                        int i, j;
                        cin >> i >> j;
                        ys += i; lq += j;
                        goto FLAG;
                    }
                    ii = 0;
                    Sound(1);
                    
                }

                else if (msg.x >= xia2_l && msg.x <= xia2_r && msg.y >= xia_d + xy && msg.y <= xia_u + xy)
                {
                    n = 10;
                    if (fq >= 10 && xz <= 3)fq -= 10;
                    else if (fq * 160 + ys >= 1600 && xz <= 3) {
                        ys -= (1600 - fq * 160);
                        fq = 0;
                    }
                    else if (lq >= 10 && xz == 4)lq -= 10;
                    else if (lq * 160 + ys >= 1600 && xz == 4) {
                        ys -= (1600 - lq * 160);
                        lq = 0;
                    }
                    else if (xz <= 3) {
                        closegraph();
                        cout << "缺乏原石(仅剩" << ys << "原石和" << fq << "粉球)，请输入增加的原石和粉球:\n";
                        int i, j;
                        cin >> i >> j;
                        ys += i; fq += j;
                        goto FLAG;
                    }
                    else {
                        closegraph();
                        cout << "缺乏原石(仅剩" << ys << "原石和" << lq << "蓝球)，请输入增加的原石和蓝球:\n";
                        int i, j;
                        cin >> i >> j;
                        ys += i; lq += j;
                        goto FLAG;
                    }
                    ii = 0;
                    Sound(1);
                    
                }

                else if (msg.x >= tuichu_l && msg.x <= tuichu_r && msg.y >= tuichu_u + xy && msg.y <= tuichu_d + xy) {

                    Sound(3);

                    goto FLAG1;
                }

                //initgraph(X, Y, SHOWCONSOLE);
                /*IMAGE img;
                HWND hwnd = GetHWnd();
                SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION); SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN), SWP_SHOWWINDOW);
                */
                if (xz != 1 && msg.x >= shang1_l && msg.x <= shang1_r && msg.y >= shang_d + xy && msg.y <= shang_u + xy) {//上换卡池到阿蕾奇诺
                    xz = 1;

                    Sound(5);

                    loadimage(&img, "src\\4.6上\\up阿蕾奇诺池.jpg", X0 * K, Y0 * K);
                    putimage(0, xy, &img);

                    settextcolor(RGB(250, 251, 255));
                    setbkcolor(RGB(81, 104, 124));
                    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                    outtextxy(yuanshishu_x, yuanshishu_y + xy, str1);
                    outtextxy(jiuchanshu_x, yuanshishu_y + xy, str2);



                }
                else if (xz != 2 && msg.x >= shang2_l && msg.x <= shang2_r && msg.y >= shang_d + xy && msg.y <= shang_u + xy) {//上换卡池到林尼
                    xz = 2;

                    Sound(5);

                    loadimage(&img, "src\\4.6上\\up林尼池.jpg", X0 * K, Y0 * K);
                    putimage(0, xy, &img);

                    settextcolor(RGB(250, 251, 255));
                    setbkcolor(RGB(81, 104, 124));
                    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                    outtextxy(yuanshishu_x, yuanshishu_y + xy, str1);
                    outtextxy(jiuchanshu_x, yuanshishu_y + xy, str2);



                }
                else if (xz != 3 && msg.x >= shang3_l && msg.x <= shang3_r && msg.y >= shang_d + xy && msg.y <= shang_u + xy) {//上换卡池到武器
                    xz = 3;
                    Sound(5);
                    if (dg == 3) {
                        loadimage(&img, "src\\4.6上\\武器池.jpg", X0* K, Y0* K);
                        putimage(0, xy, &img);
                    }
                    else {
                        loadimage(&img, "src\\4.6上\\武器池().jpg", X0* K, Y0* K);
                        putimage(0, xy, &img);
                        settextcolor(RGB(243, 143, 0));
                        setbkcolor(RGB(236, 229, 216));
                        settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                        char z[100];
                        sprintf(z, "    %d", s);
                        outtextxy(dgshuzi_l, dgshuzi_u + xy, z);
                        settextcolor(RGB(73, 83, 102));
                        settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                        outtextxy(dgshuzi_l + yuanshidaxiao + 12 * K, dgshuzi_u + xy, "/2    ");
                    }
                    settextcolor(RGB(250, 251, 255));
                    setbkcolor(RGB(81, 104, 124));
                    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                    outtextxy(yuanshishu_x, yuanshishu_y + xy, str1);
                    outtextxy(jiuchanshu_x, yuanshishu_y + xy, str2);
                }
                else if (xz != 4 && msg.x >= shang4_l && msg.x <= shang4_r && msg.y >= shang_d + xy && msg.y <= shang_u + xy) {//上换卡池到常驻
                    xz = 4;

                    Sound(5);

                    loadimage(&img, "src\\4.6上\\常驻池.jpg", X0 * K, Y0 * K);
                    putimage(0, xy, &img);

                    settextcolor(RGB(250, 251, 255));
                    setbkcolor(RGB(81, 104, 124));
                    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                    outtextxy(yuanshishu_x+10, yuanshishu_y + xy, str1);
                    outtextxy(jiuchanshu_x, yuanshishu_y + xy, str3);

                }
                else if (xz == 3 && msg.x >= jiantou2_l && msg.x <= jiantou2_r && msg.y >= jiantou_d + xy && msg.y <= jiantou_u + xy) {//ce换卡池武器到常驻
                    xz = 4;

                    Sound(4);

                    loadimage(&img, "src\\4.6上\\常驻池.jpg", X0 * K, Y0 * K);
                    putimage(0, xy, &img);

                    settextcolor(RGB(250, 251, 255));
                    setbkcolor(RGB(81, 104, 124));
                    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                    outtextxy(yuanshishu_x + 10, yuanshishu_y + xy, str1);
                    outtextxy(jiuchanshu_x, yuanshishu_y + xy, str3);



                }

                else if (xz == 2 && msg.x >= jiantou2_l && msg.x <= jiantou2_r && msg.y >= jiantou_d + xy && msg.y <= jiantou_u + xy) {//ce换卡池林尼到武器
                    xz = 3;
                    Sound(4);
                    if (dg == 3) {
                        loadimage(&img, "src\\4.6上\\武器池.jpg", X0 * K, Y0 * K);
                        putimage(0, xy, &img);
                    }
                    else {
                        loadimage(&img, "src\\4.6上\\武器池().jpg", X0* K, Y0* K);
                        putimage(0, xy, &img);
                        settextcolor(RGB(243, 143, 0));
                        setbkcolor(RGB(236, 229, 216));
                        settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                        char z[100];
                        sprintf(z, "    %d", s);
                        outtextxy(dgshuzi_l, dgshuzi_u + xy, z);
                        settextcolor(RGB(73, 83, 102));
                        settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                        outtextxy(dgshuzi_l + yuanshidaxiao + 12 * K, dgshuzi_u + xy, "/2    ");
                    }
                    settextcolor(RGB(250, 251, 255));
                    setbkcolor(RGB(81, 104, 124));
                    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                    outtextxy(yuanshishu_x, yuanshishu_y + xy, str1);
                    outtextxy(jiuchanshu_x, yuanshishu_y + xy, str2);
                }
                else if (xz == 1 && msg.x >= jiantou2_l && msg.x <= jiantou2_r && msg.y >= jiantou_d + xy && msg.y <= jiantou_u + xy) {//ce换卡池阿蕾奇诺到林尼
                    xz = 2;

                    Sound(4);

                    loadimage(&img, "src\\4.6上\\up林尼池.jpg", X0 * K, Y0 * K);
                    putimage(0, xy, &img);

                    settextcolor(RGB(250, 251, 255));
                    setbkcolor(RGB(81, 104, 124));
                    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                    outtextxy(yuanshishu_x, yuanshishu_y + xy, str1);
                    outtextxy(jiuchanshu_x, yuanshishu_y + xy, str2);



                }
                else if (xz == 2 && msg.x >= jiantou1_l && msg.x <= jiantou1_r && msg.y >= jiantou_d + xy && msg.y <= jiantou_u + xy) {//侧换卡池林尼到阿蕾奇诺
                    xz = 1;

                    Sound(4);

                    loadimage(&img, "src\\4.6上\\up阿蕾奇诺池.jpg", X0 * K, Y0 * K);
                    putimage(0, xy, &img);

                    settextcolor(RGB(250, 251, 255));
                    setbkcolor(RGB(81, 104, 124));
                    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                    outtextxy(yuanshishu_x, yuanshishu_y + xy, str1);
                    outtextxy(jiuchanshu_x, yuanshishu_y + xy, str2);



                }
                else if (xz == 3 && msg.x >= jiantou1_l && msg.x <= jiantou1_r && msg.y >= jiantou_d + xy && msg.y <= jiantou_u + xy) {//侧换卡池武器到林尼
                    xz = 2;

                    Sound(4);

                    loadimage(&img, "src\\4.6上\\up林尼池.jpg", X0 * K, Y0 * K);
                    putimage(0, xy, &img);

                    settextcolor(RGB(250, 251, 255));
                    setbkcolor(RGB(81, 104, 124));
                    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                    outtextxy(yuanshishu_x, yuanshishu_y + xy, str1);
                    outtextxy(jiuchanshu_x, yuanshishu_y + xy, str2);



                }
                else if (xz == 4 && msg.x >= jiantou1_l && msg.x <= jiantou1_r && msg.y >= jiantou_d + xy && msg.y <= jiantou_u + xy) {//侧换卡池常驻到武器
                    xz = 3;
                    Sound(4);
                    if (dg == 3) {
                        loadimage(&img, "src\\4.6上\\武器池.jpg", X0* K, Y0* K);
                        putimage(0, xy, &img);
                    }
                    else {
                        loadimage(&img, "src\\4.6上\\武器池().jpg", X0* K, Y0* K);
                        putimage(0, xy, &img);
                        settextcolor(RGB(243, 143, 0));
                        setbkcolor(RGB(236, 229, 216));
                        settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                        char z[100];
                        sprintf(z, "    %d", s);
                        outtextxy(dgshuzi_l, dgshuzi_u + xy, z);
                        settextcolor(RGB(73, 83, 102));
                        settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                        outtextxy(dgshuzi_l + yuanshidaxiao + 12 * K, dgshuzi_u + xy, "/2    ");
                    }
                    settextcolor(RGB(250, 251, 255));
                    setbkcolor(RGB(81, 104, 124));
                    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                    outtextxy(yuanshishu_x, yuanshishu_y + xy, str1);
                    outtextxy(jiuchanshu_x, yuanshishu_y + xy, str2);
                }
                else if (xz == 3 && msg.x >= dinggui_l && msg.x <= dinggui_r && msg.y >= dinggui_u + xy && msg.y <= dinggui_d + xy) {//武器池定轨
                    if (dg == 3)Sound(6);
                    else Sound(10);
                    if (dg == 3) loadimage(&img, "src\\4.6上\\武器池1.jpg", X0 * K, Y0 * K);
                    else if (dg == 4) loadimage(&img, "src\\4.6上\\武器池11.jpg", X0 * K, Y0 * K);
                    else if (dg == 5) loadimage(&img, "src\\4.6上\\武器池21.jpg", X0 * K, Y0 * K);
                    putimage(0, xy, &img);
                    if (dg != 3) {
                        settextcolor(RGB(243, 143, 0));
                        setbkcolor(RGB(236, 229, 216));
                        settextstyle(dgdaxiao, 0, "SDK_SC_Web");
                        char z[100];
                        sprintf(z, "%d", s);
                        outtextxy(dgshuzi2_l, dgshuzi2_u + xy, z);
                        settextcolor(RGB(73, 83, 102));
                        settextstyle(dgdaxiao, 0, "SDK_SC_Web");
                        outtextxy(dgshuzi2_l + 18 * K, dgshuzi2_u + xy, "/2");
                    }
                    int xz2 = 1;
                    int x = 1;
                    ExMessage msg;
                    while (x) {
                        if (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN) {
                            if (msg.x >= dgtc_l && msg.x <= dgtc_r && msg.y >= dgtc_u + xy && msg.y <= dgtc_d + xy) {//退出定轨页面
                                Sound(11);
                                x = 0;
                                if (dg == 3) {
                                    loadimage(&img, "src\\4.6上\\武器池.jpg", X0* K, Y0* K);
                                    putimage(0, xy, &img);
                                }
                                else {
                                    loadimage(&img, "src\\4.6上\\武器池().jpg", X0* K, Y0* K);
                                    putimage(0, xy, &img);
                                    settextcolor(RGB(243, 143, 0));
                                    setbkcolor(RGB(236, 229, 216));
                                    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                                    char z[100];
                                    sprintf(z, "    %d", s);
                                    outtextxy(dgshuzi_l, dgshuzi_u + xy, z);
                                    settextcolor(RGB(73, 83, 102));
                                    settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                                    outtextxy(dgshuzi_l + yuanshidaxiao + 12 * K, dgshuzi_u + xy, "/2    ");
                                }
                                settextcolor(RGB(250, 251, 255));
                                setbkcolor(RGB(81, 104, 124));
                                settextstyle(yuanshidaxiao, 0, "SDK_SC_Web");
                                outtextxy(yuanshishu_x, yuanshishu_y + xy, str1);
                                outtextxy(jiuchanshu_x, yuanshishu_y + xy, str2);
                            }
                            else if (msg.x >= dg1l_l && msg.x <= dg1l_r && msg.y >= dg1l_u + xy && msg.y <= dg1l_d + xy) {//选择左边武器定规
                                Sound(7);
                                xz2 = 1;
                                if (dg == 3)loadimage(&img, "src\\4.6上\\武器池1.jpg", X0 * K, Y0 * K);
                                else if (dg == 4)loadimage(&img, "src\\4.6上\\武器池11.jpg", X0 * K, Y0 * K);
                                putimage(0, xy, &img);
                                if (dg != 3) {
                                    settextcolor(RGB(243, 143, 0));
                                    setbkcolor(RGB(236, 229, 216));
                                    settextstyle(dgdaxiao, 0, "SDK_SC_Web");
                                    char z[100];
                                    sprintf(z, "%d", s);
                                    outtextxy(dgshuzi2_l, dgshuzi2_u + xy, z);
                                    settextcolor(RGB(73, 83, 102));
                                    settextstyle(dgdaxiao, 0, "SDK_SC_Web");
                                    outtextxy(dgshuzi2_l + 18 * K, dgshuzi2_u + xy, "/2");
                                }
                            }
                            else if (msg.x >= dg1r_l && msg.x <= dg1r_r && msg.y >= dg1r_u + xy && msg.y <= dg1r_d + xy) {//选择右边武器定规
                                Sound(7);
                                xz2 = 2;
                                if (dg == 3)loadimage(&img, "src\\4.6上\\武器池2.jpg", X0 * K, Y0 * K);
                                else if (dg == 5)loadimage(&img, "src\\4.6上\\武器池21.jpg", X0 * K, Y0 * K);
                                putimage(0, xy, &img);
                                if (dg != 3) {
                                    settextcolor(RGB(243, 143, 0));
                                    setbkcolor(RGB(236, 229, 216));
                                    settextstyle(dgdaxiao, 0, "SDK_SC_Web");
                                    char z[100];
                                    sprintf(z, "%d", s);
                                    outtextxy(dgshuzi2_l, dgshuzi2_u + xy, z);
                                    settextcolor(RGB(73, 83, 102));
                                    settextstyle(dgdaxiao, 0, "SDK_SC_Web");
                                    outtextxy(dgshuzi2_l + 18 * K, dgshuzi2_u + xy, "/2");
                                }
                            }
                            else if (dg == 3 && xz2 == 1 && msg.x >= dgqd_l && msg.x <= dgqd_r && msg.y >= dgqd_u + xy && msg.y <= dgqd_d + xy) {//初始状态确认左边武器定轨
                                Sound(8);
                                dg = 4;
                                loadimage(&img, "src\\4.6上\\武器池11.jpg", X0* K, Y0* K);
                                putimage(0, xy, &img);
                                if (dg != 3) {
                                    settextcolor(RGB(243, 143, 0));
                                    setbkcolor(RGB(236, 229, 216));
                                    settextstyle(dgdaxiao, 0, "SDK_SC_Web");
                                    char z[100];
                                    sprintf(z, "%d", s);
                                    outtextxy(dgshuzi2_l, dgshuzi2_u + xy, z);
                                    settextcolor(RGB(73, 83, 102));
                                    settextstyle(dgdaxiao, 0, "SDK_SC_Web");
                                    outtextxy(dgshuzi2_l + 18 * K, dgshuzi2_u + xy, "/2");
                                }
                            }
                            else if (dg == 3 && xz2 == 2 && msg.x >= dgqd_l && msg.x <= dgqd_r && msg.y >= dgqd_u + xy && msg.y <= dgqd_d + xy) {//初始状态确认右边武器定轨
                                Sound(8);
                                dg = 5;
                                loadimage(&img, "src\\4.6上\\武器池21.jpg", X0 * K, Y0 * K);
                                putimage(0, xy, &img);
                                if (dg != 3) {
                                    settextcolor(RGB(243, 143, 0));
                                    setbkcolor(RGB(236, 229, 216));
                                    settextstyle(dgdaxiao, 0, "SDK_SC_Web");
                                    char z[100];
                                    sprintf(z, "%d", s);
                                    outtextxy(dgshuzi2_l, dgshuzi2_u + xy, z);
                                    settextcolor(RGB(73, 83, 102));
                                    settextstyle(dgdaxiao, 0, "SDK_SC_Web");
                                    outtextxy(dgshuzi2_l + 18 * K, dgshuzi2_u + xy, "/2");
                                }
                            }
                            else if (dg != 3 && msg.x >= dgqd_l && msg.x <= dgqd_r && msg.y >= dgqd_u + xy && msg.y <= dgqd_d + xy) {//取消定轨
                                Sound(12);
                                loadimage(&img, "src\\4.6上\\武器池0.jpg", X0 * K, Y0 * K);
                                putimage(0, xy, &img);//dgtsqx  dgtsqr
                                int y = 1;

                                ExMessage msg;
                                while (y) {
                                    if (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN) {
                                        if (msg.x >= dgtsqx_l && msg.x <= dgtsqx_r && msg.y >= dgtsqx_u + xy && msg.y <= dgtsqx_d + xy) {
                                            Sound(9);
                                            y = 0;
                                            if (dg == 4)loadimage(&img, "src\\4.6上\\武器池11.jpg", X0 * K, Y0 * K);
                                            else if (dg == 5)loadimage(&img, "src\\4.6上\\武器池21.jpg", X0 * K, Y0 * K);
                                            putimage(0, xy, &img);
                                            if (dg != 3) {
                                                settextcolor(RGB(243, 143, 0));
                                                setbkcolor(RGB(236, 229, 216));
                                                settextstyle(dgdaxiao, 0, "SDK_SC_Web");
                                                char z[100];
                                                sprintf(z, "%d", s);
                                                outtextxy(dgshuzi2_l, dgshuzi2_u + xy, z);
                                                settextcolor(RGB(73, 83, 102));
                                                settextstyle(dgdaxiao, 0, "SDK_SC_Web");
                                                outtextxy(dgshuzi2_l + 18 * K, dgshuzi2_u + xy, "/2");
                                            }
                                        }
                                        else if (msg.x >= dgtsqr_l && msg.x <= dgtsqr_r && msg.y >= dgtsqr_u + xy && msg.y <= dgtsqr_d + xy) {
                                            Sound(9);
                                            y = 0;
                                            loadimage(&img, "src\\4.6上\\武器池1.jpg", X0 * K, Y0 * K);
                                            putimage(0, xy, &img);
                                            s = 0;
                                            dg = 3;
                                        }
                                    }
                                }
                            }
                        }

                    }
                }




            }
        }

    }

    ii = 1;
    // _1 _2 _3
    srand((int)time(NULL));
    char name[100];
    int u;

    if (xz <= 2) {
        if (n == 1)  ljcs_1++;
        else if (n == 10)  ljcs_1 += 10;

        for (i1_1 = 1; i1_1 <= n; i1_1++, i2_1++, i3_1++) {//五星角色
            a_1 = rand() % 10000 + 1;
            a1_1 = rand() % 10000 + 1;
            g = 0;
            f_1 = 0;
            if (a_1 <= fx1(i2_1)) {
                f_1 = 1;
                i2_1 = 0;

                if (!bd_1) {
                    f1[i1_1 - n + ljcs_1 + d_1][0] = rand() % 2 + 3;//3不歪，4歪
                }
                else
                    f1[i1_1 - n + ljcs_1 + d_1][0] = 3;
            }
            else f_1 = 0;


            if ((a1_1 <= gx1(i3_1)) && f_1 == 0) {//四星物品
                g = 1;
                i3_1 = 0;
                if (!bd1_1)
                    f1[i1_1 - n + ljcs_1 + d_1][0] = rand() % 2 + 1;
                else
                    f1[i1_1 - n + ljcs_1 + d_1][0] = 2;	//2为四星提升概率角色角色，1为四星物品（含武器和未提升概率角色
            }
            else g = 0;


            if (n == 1 && !f_1 && !g) {//单抽三星///
                u = 1;
                
            }

            if (n == 1 && !f_1 && g) {//单抽四星
                u = 2;
                
            }

            if (n == 1 && f1[i1_1 - n + ljcs_1 + d_1][0] >= 3) {//单抽五星
                u = 3;
                
            }
            if (n == 1) {
                switch (u) {
                case 1:sprintf_s(name, "singleblue");break;
                case 2:sprintf_s(name, "singlepurple");break;
                case 3:sprintf_s(name, "singlegold");break;
                case 4:sprintf_s(name, "tenpurple");break;
                case 5:sprintf_s(name, "singlegold");break;
                }
                Card_drawing_animation(name);
            }
            if (f1[i1_1 - n + ljcs_1 + d_1][0] == 0) {

                cout << "角色池第" << i1_1 - n + ljcs_1 + d_1 << "次结果为：";
                f1[i1_1 - n + ljcs_1 + d_1][1] = saxwq(pn);
                cout << "\n";
            }
            else if (f1[i1_1 - n + ljcs_1 + d_1][0] == 2) {
                cout << "角色池第" << i1_1 - n + ljcs_1 + d_1 << "次结果为：";
                f1[i1_1 - n + ljcs_1 + d_1][1] = sxjs(pn);
                cout << '\n';
                bd1_1 = 0;
            }
            else if (f1[i1_1 - n + ljcs_1 + d_1][0] == 1) {
                cout << "角色池第" << i1_1 - n + ljcs_1 + d_1 << "次结果为：";
                f1[i1_1 - n + ljcs_1 + d_1][1] = sxwp(pn);
                cout << '\n';
                bd1_1 = 1;
            }
            else if (f1[i1_1 - n + ljcs_1 + d_1][0] == 3) {
                cout << "角色池第" << i1_1 - n + ljcs_1 + d_1 << "次结果为：";
                upwxjs(pn, pp);
                cout << '\n';

                bd_1 = 0;
                sum++;
                sum1_1++;
            }
            else if (f1[i1_1 - n + ljcs_1 + d_1][0] == 4) {
                cout << "角色池第" << i1_1 - n + ljcs_1 + d_1 << "次结果为：";
                f1[i1_1 - n + ljcs_1 + d_1][1] = czwxjs(pn);
                cout << '\n';
                sum++;
                bd_1 = 1;
            }

        }

        if (n == 10) {
            for (int k = 9, x = i1_1 - 1; x >= i1_1 - 10; x--, k--) {
                if (f1[x - n + ljcs_1 + d_1][0] >= 3)F = 1;
                sl[k][0] = f1[x - n + ljcs_1 + d_1][0];
                sl[k][1] = f1[x - n + ljcs_1 + d_1][1];
            }
            for (int i = 0; i < 10 - 1; i++) {
                for (int j = 0; j < 10 - i - 1; j++) {
                    if (sl[j][0] < sl[j + 1][0]) {
                        int tmp1 = sl[j][0];
                        sl[j][0] = sl[j + 1][0];
                        sl[j + 1][0] = tmp1;
                        int tmp2 = sl[j][1];
                        sl[j][1] = sl[j + 1][1];
                        sl[j + 1][1] = tmp2;
                    }
                }
            }
        }
        if (F == 1) {//十连五星
            F = 0;
            u = 5;
            sprintf_s(name, "tengold");
            Card_drawing_animation(name);
            Sound(2);
            putimage(0, xy, &bak);
            // 
            for (int i = 0; i < 10; i++) {
                if (sl[i][0] == 4) {
                    sprintf_s(dzm, "src\\4.6上\\czwxjs\\%d.jpg", sl[i][1]);
                    loadimage(&img8, dzm, tiao_x, wutiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, wuup + xy, &img8);
                }
                else if (sl[i][0] == 3) {
                    sprintf_s(dzm, "src\\4.6上\\upwxjs\\%d.jpg", xz);
                    loadimage(&img9, dzm, tiao_x, wutiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, wuup + xy, &img9);
                }
                else if (sl[i][0] == 1) {
                    sprintf_s(dzm, "src\\4.6上\\sxwp\\%d.jpg", sl[i][1]);
                    loadimage(&img5, dzm, tiao_x, sitiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, siup + xy, &img5);
                }
                else if (sl[i][0] == 2) {
                    sprintf_s(dzm, "src\\4.6上\\sxjs\\%d.jpg", sl[i][1]);
                    loadimage(&img6, dzm, tiao_x, sitiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, siup + xy, &img6);
                }
                else if (sl[i][0] == 0) {
                    sprintf_s(dzm, "src\\4.6上\\saxwq\\%d.jpg", sl[i][1]);
                    loadimage(&img7, dzm, tiao_x, santiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, sanup + xy, &img7);
                }
            }
            tiaoweisy();

        }


        else if (n == 10) {//十连四星
            u = 4;
            sprintf_s(name, "tenpurple");
            Card_drawing_animation(name);
            Sound(2);

            putimage(0, xy, &bak);

            for (int i = 0; i < 10; i++) {
                if (sl[i][0] == 1) {
                    sprintf_s(dzm, "src\\4.6上\\sxwp\\%d.jpg", sl[i][1]);
                    loadimage(&img5, dzm, tiao_x, sitiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, siup + xy, &img5);
                }
                else if (sl[i][0] == 2) {
                    sprintf_s(dzm, "src\\4.6上\\sxjs\\%d.jpg", sl[i][1]);
                    loadimage(&img6, dzm, tiao_x, sitiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, siup + xy, &img6);
                }
                else if (sl[i][0] == 0) {
                    sprintf_s(dzm, "src\\4.6上\\saxwq\\%d.jpg", sl[i][1]);
                    loadimage(&img7, dzm, tiao_x, santiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, sanup + xy, &img7);
                }

            }
            tiaoweisy();



        }


    }

    // _2  
    else if (xz == 3) {
        if (n == 1)  ljcs_2++;
        else if (n == 10)  ljcs_2 += 10;

        for (i1_2 = 1; i1_2 <= n; i1_2++, i2_2++, i3_2++) {
            //sleep(1);
            a_2 = rand() % 10000 + 1;
            a1_2 = rand() % 10000 + 1;
            if (dg == 3)s = 0;
            if (a_2 <= fx2(i2_2)) {
                f_2 = 1;
                i2_2 = 0;
                if (s < 2 && bd_2 == 0) {
                    x = rand() % 8 + 1;
                    if (x <= 3)f1[i1_2 - n + ljcs_2 + d_2][0] = 4;//4为赤月之形
                    else if (x <= 6)f1[i1_2 - n + ljcs_2 + d_2][0] = 5;//5为最初的大魔术
                    else {
                        f1[i1_2 - n + ljcs_2 + d_2][0] = 3;//3为常驻五星武器
                        s++; bd_2++;
                    }
                    if (f1[i1_2 - n + ljcs_2 + d_2][0] == dg)s = 0;
                    else if (f1[i1_2 - n + ljcs_2 + d_2][0] != 3)s++;

                }
                else if (s == 2) {
                    f1[i1_2 - n + ljcs_2 + d_2][0] = dg;
                    s = 0;
                    bd_2 = 0;
                }
                else {
                    f1[i1_2 - n + ljcs_2 + d_2][0] = rand() % 2 + 4;
                    if (dg == f1[i1_2 - n + ljcs_2 + d_2][0]) {
                        s = 0;
                        bd_2 = 0;
                    }
                    else {
                        s++;
                        bd_2 = 0;
                    }
                }
            }
            else f_2 = 0;


            if ((a1_2 <= gx2(i3_2)) && f_2 == 0) {

                i3_2 = 0;
                if (!bd1_2) {
                    x = rand() % 4 + 1;
                    if (x == 1)f1[i1_2 - n + ljcs_2 + d_2][0] = 1;
                    else f1[i1_2 - n + ljcs_2 + d_2][0] = 2;
                }
                else
                    f1[i1_2 - n + ljcs_2 + d_2][0] = 2;	//2为提升概率武器，1为未提升概率武器或角色 
            }

            if (n == 1 && f1[i1_2 - n + ljcs_2 + d_2][0] == 0) {//单抽三星
                u = 1;
            }

            if (n == 1 && (f1[i1_2 - n + ljcs_2 + d_2][0] == 1 || f1[i1_2 - n + ljcs_2 + d_2][0] == 2)) {//单抽四星
                u = 2;
            }

            if (n == 1 && f1[i1_2 - n + ljcs_2 + d_2][0] >= 3) {//单抽五星
                u = 3;
            }
            if (n == 1) {
                switch (u) {
                case 1:sprintf_s(name, "singleblue");break;
                case 2:sprintf_s(name, "singlepurple");break;
                case 3:sprintf_s(name, "singlegold");break;
                case 4:sprintf_s(name, "tenpurple");break;
                case 5:sprintf_s(name, "singlegold");break;
                }
                Card_drawing_animation(name);
            }

            if (f1[i1_2 - n + ljcs_2 + d_2][0] == 0) {
                cout << "武器池第" << i1_2 - n + ljcs_2 + d_2 << "次结果为：";
                f1[i1_2 - n + ljcs_2 + d_2][1] = saxwq(pn);
                cout << "\n";
            }
            else if (f1[i1_2 - n + ljcs_2 + d_2][0] == 2) {
                cout << "武器池第" << i1_2 - n + ljcs_2 + d_2 << "次结果为：";
                f1[i1_2 - n + ljcs_2 + d_2][1] = wwsxwq(pn);
                cout << '\n';
                bd1_2 = 0;
            }
            else if (f1[i1_2 - n + ljcs_2 + d_2][0] == 1) {
                cout << "武器池第" << i1_2 - n + ljcs_2 + d_2 << "次结果为：";
                f1[i1_2 - n + ljcs_2 + d_2][1] = wwsxwp(pn);
                cout << '\n';
                bd1_2 = 1;
            }
            else if (f1[i1_2 - n + ljcs_2 + d_2][0] == 3) {
                sum++;
                cout << "武器池第" << i1_2 - n + ljcs_2 + d_2 << "次结果为：";
                f1[i1_2 - n + ljcs_2 + d_2][1] = czwxwq(pn);
                cout << '\n';
            }
            else if (f1[i1_2 - n + ljcs_2 + d_2][0] == 4) {
                sum++;
                sum1_2++;

                cout << "武器池第" << i1_2 - n + ljcs_2 + d_2 << "次结果为：赤月之形" << '\n';

                if (n == 1) {
                    Sound(2);
                    putimage(0, xy, &bak);
                    sprintf_s(dzm, "src\\4.6上\\upwxwq\\1.jpg");
                    loadimage(&img1, dzm, tiao_x, wutiao_y + xy);
                    _sleep(100);
                    putimage(zhong_x, wuup + xy, &img1);
                    tiaoweisy();




                }
            }
            else if (f1[i1_2 - n + ljcs_2 + d_2][0] == 5) {
                sum++;
                sum1_2++;

                cout << "武器池第" << i1_2 - n + ljcs_2 + d_2 << "次结果为：最初的大魔术" << '\n';
                if (n == 1) {
                    Sound(2);
                    putimage(0, xy, &bak);
                    sprintf_s(dzm, "src\\4.6上\\upwxwq\\2.jpg");
                    loadimage(&img1, dzm, tiao_x, wutiao_y + xy);
                    _sleep(100);
                    putimage(zhong_x, wuup + xy, &img1);
                    tiaoweisy();



                }
            }
        }


        if (n == 10) {
            for (int k = 9, x = i1_2 - 1; x >= i1_2 - 10; x--, k--) {
                if (f1[x - n + ljcs_2 + d_2][0] >= 3)F = 1;
                sl[k][0] = f1[x - n + ljcs_2 + d_2][0];
                sl[k][1] = f1[x - n + ljcs_2 + d_2][1];
            }
            for (int i = 0; i < 10 - 1; i++) {
                for (int j = 0; j < 10 - i - 1; j++) {
                    if (sl[j][0] < sl[j + 1][0]) {
                        int tmp1 = sl[j][0];
                        sl[j][0] = sl[j + 1][0];
                        sl[j + 1][0] = tmp1;
                        int tmp2 = sl[j][1];
                        sl[j][1] = sl[j + 1][1];
                        sl[j + 1][1] = tmp2;
                    }
                }
            }
        }
        if (F == 1) {//十连五星
            F = 0;
            u = 5;
            sprintf_s(name, "tengold");
            Card_drawing_animation(name);
            Sound(2);
            putimage(0, xy, &bak);

            for (int i = 0; i < 10; i++) {
                if (sl[i][0] == 4) {
                    sprintf_s(dzm, "src\\4.6上\\upwxwq\\1.jpg");
                    loadimage(&img1, dzm, tiao_x, wutiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, wuup + xy, &img1);
                }
                else if (sl[i][0] == 5) {
                    sprintf_s(dzm, "src\\4.6上\\upwxwq\\2.jpg");
                    loadimage(&img2, dzm, tiao_x, wutiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, wuup + xy, &img2);
                }
                else if (sl[i][0] == 3) {
                    sprintf_s(dzm, "src\\4.6上\\czwxwq\\%d.jpg", sl[i][1]);
                    loadimage(&img3, dzm, tiao_x, wutiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, wuup + xy, &img3);
                }
                else if (sl[i][0] == 1) {
                    sprintf_s(dzm, "src\\4.6上\\wwsxwp\\%d.jpg", sl[i][1]);
                    loadimage(&img4, dzm, tiao_x, sitiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, siup + xy, &img4);
                }
                else if (sl[i][0] == 2) {
                    sprintf_s(dzm, "src\\4.6上\\wwsxwq\\%d.jpg", sl[i][1]);
                    loadimage(&img5, dzm, tiao_x, sitiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, siup + xy, &img5);
                }
                else if (sl[i][0] == 0) {
                    sprintf_s(dzm, "src\\4.6上\\saxwq\\%d.jpg", sl[i][1]);
                    loadimage(&img7, dzm, tiao_x, santiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, sanup + xy, &img7);
                }
            }
            tiaoweisy();




        }


        else if (n == 10) {//十连四星
            F = 0;
            u = 4;
            sprintf_s(name, "tenpurple");
            Card_drawing_animation(name);
            Sound(2);
            putimage(0, xy, &bak);

            for (int i = 0; i < 10; i++) {
                if (sl[i][0] == 1) {
                    sprintf_s(dzm, "src\\4.6上\\wwsxwp\\%d.jpg", sl[i][1]);
                    loadimage(&img5, dzm, tiao_x, sitiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, siup + xy, &img5);
                }
                else if (sl[i][0] == 2) {
                    sprintf_s(dzm, "src\\4.6上\\wwsxwq\\%d.jpg", sl[i][1]);
                    loadimage(&img6, dzm, tiao_x, sitiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, siup + xy, &img6);
                }
                else if (sl[i][0] == 0) {
                    sprintf_s(dzm, "src\\4.6上\\saxwq\\%d.jpg", sl[i][1]);
                    loadimage(&img7, dzm, tiao_x, santiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, sanup + xy, &img7);
                }
            }
            tiaoweisy();



        }
    }
    else if (xz == 4) {
        if (n == 1)  ljcs++;
        else if (n == 10)  ljcs += 10;
        for (i1 = 1; i1 <= n; i1++, i2++, i3++) {
            //sleep(1);
            a = rand() % 10000 + 1;
            a1 = rand() % 10000 + 1;
            if (a <= fx1(i2)) {
                f = 1;
                i2 = 0;
                // 0为三星，1为四星武器，2为四星角色，3为五星武器，4为五星角色
                if (!bd)
                    f1[i1 - n + ljcs + d][0] = rand() % 2 + 3;
                else
                    f1[i1 - n + ljcs + d][0] = 4;
            }
            else f = 0;


            if ((a1 <= gx1(i3)) && f == 0) {
                g = 1;
                i3 = 0;
                if (!bd1)
                    f1[i1 - n + ljcs + d][0] = rand() % 2 + 1;
                else
                    f1[i1 - n + ljcs + d][0] = 2;
            }
            else g = 0;


            if (n == 1 && !f && !g) {//单抽三星
                u = 1;
            }

            if (n == 1 && !f && g) {//单抽四星
                u = 2;
            }

            if (n == 1 && f1[i1 - n + ljcs + d][0] >= 3) {//单抽五星
                u = 3;
            }
            if (n == 1) {
                switch (u) {
                case 1:sprintf_s(name, "singleblue");break;
                case 2:sprintf_s(name, "singlepurple");break;
                case 3:sprintf_s(name, "singlegold");break;
                case 4:sprintf_s(name, "tenpurple");break;
                case 5:sprintf_s(name, "singlegold");break;
                }
                Card_drawing_animation(name);
            }
            // 0为三星，1为四星武器，2为四星角色，3为五星武器，4为五星角色
            if (f1[i1 - n + ljcs + d][0] == 4) {
                cout << "常驻池第" << i1 - n + ljcs + d << "次结果为：";
                f1[i1 - n + ljcs + d][1] = czwxjs(pn);
                cout << '\n';
                bd1 = 0;
            }
            else if (f1[i1 - n + ljcs + d][0] == 3) {
                cout << "常驻池第" << i1 - n + ljcs + d << "次结果为：";
                f1[i1 - n + ljcs + d][1] = czwxwq(pn);
                cout << '\n';
                bd1 = 1;
            }
            else if (f1[i1 - n + ljcs + d][0] == 2) {
                cout << "常驻池第" << i1 - n + ljcs + d << "次结果为：";
                f1[i1 - n + ljcs + d][1] = czsxjs(pn);
                cout << '\n';


                bd = 0;
            }
            else if (f1[i1 - n + ljcs + d][0] == 1) {
                cout << "常驻池第" << i1 - n + ljcs + d << "次结果为：";
                f1[i1 - n + ljcs + d][1] = czsxwq(pn);
                cout << '\n';

            }
            else if (f1[i1 - n + ljcs + d][0] == 0) {
                cout << "常驻池第" << i1 - n + ljcs + d << "次结果为：";
                f1[i1 - n + ljcs + d][1] = saxwq(pn);
                cout << '\n';


            }
        }



        if (n == 10) {
            for (int k = 9, x = i1 - 1; x >= i1 - 10; x--, k--) {
                if (f1[x - n + ljcs + d][0] >= 3)F = 1;
                sl[k][0] = f1[x - n + ljcs + d][0];
                sl[k][1] = f1[x - n + ljcs + d][1];
            }
            for (int i = 0; i < 10 - 1; i++) {
                for (int j = 0; j < 10 - i - 1; j++) {
                    if (sl[j][0] < sl[j + 1][0]) {
                        int tmp1 = sl[j][0];
                        sl[j][0] = sl[j + 1][0];
                        sl[j + 1][0] = tmp1;
                        int tmp2 = sl[j][1];
                        sl[j][1] = sl[j + 1][1];
                        sl[j + 1][1] = tmp2;
                    }
                }
            }
        }
        if (F == 1) {//十连五星
            u = 5;
            sprintf_s(name, "tengold");
            Card_drawing_animation(name);
            Sound(2);

            putimage(0, xy, &bak);

            for (int i = 0; i < 10; i++) {// 0为三星，1为四星武器，2为四星角色，3为五星武器，4为五星角色
                if (sl[i][0] == 4) {
                    sprintf_s(dzm, "src\\4.6上\\czwxjs\\%d.jpg", sl[i][1]);
                    loadimage(&img8, dzm, tiao_x, wutiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, wuup + xy, &img8);
                }
                else if (sl[i][0] == 3) {
                    sprintf_s(dzm, "src\\4.6上\\czwxwq\\%d.jpg", sl[i][1]);
                    loadimage(&img9, dzm, tiao_x, wutiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, wuup + xy, &img9);
                }
                else if (sl[i][0] == 2) {
                    sprintf_s(dzm, "src\\4.6上\\czsxjs\\%d.jpg", sl[i][1]);
                    loadimage(&img5, dzm, tiao_x, sitiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, siup + xy, &img5);
                }
                else if (sl[i][0] == 1) {
                    sprintf_s(dzm, "src\\4.6上\\czsxwq\\%d.jpg", sl[i][1]);
                    loadimage(&img6, dzm, tiao_x, sitiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, siup + xy, &img6);
                }
                else if (sl[i][0] == 0) {
                    sprintf_s(dzm, "src\\4.6上\\saxwq\\%d.jpg", sl[i][1]);
                    loadimage(&img7, dzm, tiao_x, santiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, sanup + xy, &img7);
                }
            }
            tiaoweisy();




        }


        else if (n == 10) {//十连四星
            u = 4;
            sprintf_s(name, "tenpurple");
            Card_drawing_animation(name);
            Sound(2);
            putimage(0, xy, &bak);

            for (int i = 0; i < 10; i++) {
                if (sl[i][0] == 2) {
                    sprintf_s(dzm, "src\\4.6上\\czsxjs\\%d.jpg", sl[i][1]);
                    loadimage(&img5, dzm, tiao_x, sitiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, siup + xy, &img5);
                }
                else if (sl[i][0] == 1) {
                    sprintf_s(dzm, "src\\4.6上\\czsxwq\\%d.jpg", sl[i][1]);
                    loadimage(&img6, dzm, tiao_x, sitiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, siup + xy, &img6);
                }
                else if (sl[i][0] == 0) {
                    sprintf_s(dzm, "src\\4.6上\\saxwq\\%d.jpg", sl[i][1]);
                    loadimage(&img7, dzm, tiao_x, santiao_y + xy);
                    _sleep(70);
                    putimage(chushiweizhi + tiao_x * i, sanup + xy, &img7);
                }

            }
            tiaoweisy();



        }
    }
    //closegraph();
    cleardevice();
    goto FLAG;
FLAG1:
    return 0;
}

