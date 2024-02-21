#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;

//استراکت پلیر که اطلاعات اسم و امتیاز پلیر ها رو نگه می داره
struct Player
{
    string name;
    int score;
};

ofstream ScoreBoard;
int score = 0;
int NumberOfPlayTimes = -1;
string LeaderBoard;
string MenuLeaderBoard;
int WinFlag = 1;
Player newPlayer[100];

//یه تابع بابل سورت که جدول امتیازات رو بر اساس امتیاز بازیکن ها مرتب می کنه
void SortLeaderBoard(int n)
{
    bool Swapped;
    for (int i = 0; i < n - 1; i++) {
        Swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            //اگه امتیاز یک بازیکن بیشتر از اون یکی باشه، جای استراکت ها رو عوض میکنه
            if (newPlayer[j].score > newPlayer[j + 1].score)
            {
                swap(newPlayer[j], newPlayer[j + 1]);
                Swapped = true;
            }
        }
        if (Swapped == false)
        {
            break;
        }
    }
}

//وقتی دکمه ی بالا زده میشه، این تابع همه ی خونه ها رو بالا میبره
void MoveUp(int Number[4][4])
{
    int Row, Col, TopRow, MovCol;

    for (Col = 0; Col < 4; Col++)
    {
        TopRow = 0;
        MovCol = Col;

        for (Row = 1; Row < 4; Row++)
        {
            //اگه یه خونه خالی باشه، بالا برده نمیشه
            if (Number[Row][Col] != 0)
            {
                //فقط اگه خونه ی بالا خالی باشه، یا با خودش برابر باشه، میتونه بالا برده بشه
                if (Number[Row-1][Col] == 0 || Number[Row-1][Col] == Number[Row][Col])
                {
                    //اگه هر دو تا خونه با هم برابر بودن، خونه ی بالایی رو دو برابر میکنه و خونه ی پایینی رو صفر میکنه
                    if (Number[TopRow][MovCol] == Number[Row][Col])
                    {
                        score += Number[Row][Col];
                        Number[TopRow][MovCol] *= 2;
                        Number[Row][Col] = 0;
                    }
                    else
                    {
                        //اگه خونه ی بالایی صفر بود، جای دو تا خونه رو عوض میکنه
                        if (Number[TopRow][MovCol] == 0)
                        {
                            Number[TopRow][MovCol] = Number[Row][Col];
                            Number[Row][Col] = 0;
                        }
                        //اگه خونه ی بالایی صفر نبود و یه عدد بود، هر دوی اونها بالا برده میشن، پس فعلا این یکی رو بالا میبره
                        else
                        {
                            Number[++TopRow][MovCol] = Number[Row][Col];
                            Number[Row][Col] = 0;
                        }
                    }
                }
                else TopRow++;
            }
        }
    }
}

//وقتی دکمه ی پایین زده میشه، این تابع همه ی خونه ها رو پایین میبره
void MoveDown(int Number[4][4])
{
    int Row, Col, BottomRow, MovCol;

    for (Col = 0; Col < 4; Col++)
    {
        BottomRow = 3;
        MovCol = Col;

        for (Row = 2; Row >= 0; Row--)
        {
            //اگه یه خونه خالی باشه، پایین برده نمیشه
            if (Number[Row][Col] != 0)
            {
                //فقط اگه خونه ی پایین خالی باشه، یا با خودش برابر باشه، میتونه پایین برده بشه
                if (Number[Row+1][Col] == 0 || Number[Row+1][Col] == Number[Row][Col])
                {
                    //اگه هر دو تا خونه با هم برابر بودن، خونه ی پایینی رو دو برابر میکنه و خونه ی بالایی رو صفر میکنه
                    if (Number[BottomRow][MovCol] == Number[Row][Col])
                    {
                        score += Number[Row][Col];
                        Number[BottomRow][MovCol] *= 2;
                        Number[Row][Col] = 0;
                    }
                    else
                    {
                        //اگه خونه ی پایینی صفر بود، جای دو تا خونه رو عوض میکنه
                        if (Number[BottomRow][MovCol] == 0)
                        {
                            Number[BottomRow][MovCol] = Number[Row][Col];
                            Number[Row][Col] = 0;
                        }
                        //اگه خونه ی پایینی صفر نبود و یه عدد بود، هر دوی اونها پایین برده میشن، پس فعلا این یکی رو پایین میبره
                        else
                        {
                            Number[--BottomRow][MovCol] = Number[Row][Col];
                            Number[Row][Col] = 0;
                        }
                    }
                }
                else BottomRow--;
            }
        }
    }
}

//وقتی دکمه ی چپ زده میشه، این تابع همه ی خونه ها رو سمت چپ میبره
void MoveLeft(int Number[4][4])
{
    int Row, Col, MovRow, RightCol;

    for (Row = 0; Row < 4; Row++)
    {
        MovRow = Row;
        RightCol = 0;

        for (Col = 1; Col < 4; Col++)
        {
            //اگه یه خونه خالی باشه، سمت چپ برده نمیشه
            if (Number[Row][Col] != 0)
            {
                //فقط اگه خونه ی سمت چپ خالی باشه، یا با خودش برابر باشه، میتونه سمت چپ برده بشه
                if (Number[Row][Col-1] == 0 || Number[Row][Col-1] == Number[Row][Col])
                {
                    //اگه هر دو تا خونه با هم برابر بودن، خونه ی سمت چپی رو دو برابر میکنه و خونه ی سمت راستی رو صفر میکنه
                    if (Number[MovRow][RightCol] == Number[Row][Col])
                    {
                        score += Number[Row][Col];
                        Number[MovRow][RightCol] *= 2;
                        Number[Row][Col] = 0;
                    }
                    else
                    {
                        //اگه خونه ی سمت چپی صفر بود، جای دو تا خونه رو عوض میکنه
                        if (Number[MovRow][RightCol] == 0)
                        {
                            Number[MovRow][RightCol] = Number[Row][Col];
                            Number[Row][Col] = 0;
                        }
                        //اگه خونه ی سمت چپی صفر نبود و یه عدد بود، هر دوی اونها به چپ برده میشن، پس فعلا این یکی رو به چپ میبره
                        else
                        {
                            Number[MovRow][++RightCol] = Number[Row][Col];
                            Number[Row][Col] = 0;
                        }
                    }
                }
                else RightCol++;
            }
        }
    }
}

//وقتی دکمه ی راست زده میشه، این تابع همه ی خونه ها رو سمت راست میبره
void MoveRight(int Number[4][4])
{
    int Row, Col, MovRow, LeftCol;

    for(Row = 0; Row < 4; Row++)
    {
        MovRow = Row;
        LeftCol = 3;

        for (Col = 2; Col >= 0; Col--)
        {
            //اگه یه خونه خالی باشه، سمت راست برده نمیشه
            if (Number[Row][Col] != 0)
            {
                //فقط اگه خونه ی سمت راست خالی باشه، یا با خودش برابر باشه، میتونه سمت راست برده بشه
                if(Number[Row][Col+1] == 0 || Number[Row][Col+1] == Number[Row][Col])
                {
                    //اگه هر دو تا خونه با هم برابر بودن، خونه ی سمت راستی رو دو برابر میکنه و خونه ی سمت چپی رو صفر میکنه
                    if (Number[MovRow][LeftCol] == Number[Row][Col])
                    {
                        score += Number[Row][Col];
                        Number[MovRow][LeftCol] *= 2;
                        Number[Row][Col] = 0;
                    }
                    else
                    {
                        //اگه خونه ی سمت راستی صفر بود، جای دو تا خونه رو عوض میکنه
                        if (Number[MovRow][LeftCol] == 0)
                        {
                            Number[MovRow][LeftCol] = Number[Row][Col];
                            Number[Row][Col] = 0;
                        }
                        //اگه خونه ی سمت راستی صفر نبود و یه عدد بود، هر دوی اونها به راست برده میشن، پس فعلا این یکی رو به راست میبره
                        else
                        {
                            Number[MovRow][--LeftCol] = Number[Row][Col];
                            Number[Row][Col] = 0;
                        }
                    }
                }
                else LeftCol--;
            }
        }
    }
}

//بعد از هر حرکت، این تابع به صورت تصادفی یکی از خونه ها رو دو یا چهار میزاره
void AddBlock(int Number[4][4])
{
    int Row, Col;
    srand(time(0));

    while(1)
    {
        //یک عدد تصادفی برای سطر و یک عدد تصادفی برای ستون انتخاب میکنه و مود به چهار میزنه
        Row = rand() % 4;
        Col = rand() % 4;

        //اگه خونه ی انتخاب شده صفر بود، عدد رو جایگذاری میکنه
        if (Number[Row][Col] == 0)
        {
            //یه عدد رندوم میگیره و مود به چهار میزنه
            int Rand = rand() % 4;
            //اگه صفر بود، عدد جایگذاری شده چهار میشه
            if (Rand == 0)
            {
                Number[Row][Col] = 4;
            }
            //اگه نبود، عدد جایگذاری شده دو میشه. اینجوری احتمال دو اومدن سه برابر چهار اومدن میشه
            else
            {
                Number[Row][Col] = 2;
            }
            break;
        }
    }
}

//این تابع برای نمایش دادن صفحه ی بازی، زمانی که تم انتخابی آبی-سبز هست، استفاده میشه
void DisplayBlueGreen(int Number[4][4])
{
    cout << "\n\n\t\t\t  \033[38;5;29mPress ESC anytime to quit the game";
    cout << "\n\n\n";
    int Row, Col;

    cout << "\t\t\t\t\033[38;5;29m\u2554\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2557\033[0m\n\t\t\t\t";
    for (Row = 0; Row < 3; Row++)
    {
        for (Col = 0; Col < 4; Col++)
        {
            if (Number[Row][Col] == 0){
                cout << "\033[38;5;29m\u2551\033[0m    ";
            }
            else if (Number[Row][Col] < 10)
            {
                if (Number[Row][Col] == 2)
                {
                    cout << "\033[38;5;29m\u2551\033[0m " << "\033[38;5;87m2\033[0m" << "  ";
                }
                if (Number[Row][Col] == 4)
                {
                    cout << "\033[38;5;29m\u2551\033[0m " << "\033[38;5;86m4\033[0m" << "  ";
                }
                if (Number[Row][Col] == 8)
                {
                    cout << "\033[38;5;29m\u2551\033[0m " << "\033[38;5;85m8\033[0m" << "  ";
                }
            }
            else if (Number[Row][Col] >= 10 && Number[Row][Col] < 100)
            {
                if (Number[Row][Col] == 16)
                {
                    cout << "\033[38;5;29m\u2551\033[0m " << "\033[38;5;84m16\033[0m" << " ";
                }
                if (Number[Row][Col] == 32)
                {
                    cout << "\033[38;5;29m\u2551\033[0m " << "\033[38;5;83m32\033[0m" << " ";
                }
                if (Number[Row][Col] == 64)
                {
                    cout << "\033[38;5;29m\u2551\033[0m " << "\033[38;5;82m64\033[0m" << " ";
                }
            }
            else if (Number[Row][Col] >= 100 && Number[Row][Col] < 1000)
            {
                if (Number[Row][Col] == 128)
                {
                    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << "\033[38;5;76m128\033[0m" << " ";
                }
                if (Number[Row][Col] == 256)
                {
                    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << "\033[38;5;77m256\033[0m" << " ";
                }
                if (Number[Row][Col] == 512)
                {
                    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << "\033[38;5;78m512\033[0m" << " ";
                }
            }
            else if (Number[Row][Col] >= 1000 && Number[Row][Col] < 10000)
            {
                if (Number[Row][Col] == 1024)
                {
                    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << "\033[38;5;79m1024\033[0m";
                }
                if (Number[Row][Col] == 2048)
                {
                    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << "\033[38;5;80m2048\033[0m";
                }
                if (Number[Row][Col] == 4096)
                {
                    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << "\033[38;5;81m4096\033[0m";
                }
            }
        }
        cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" <<endl;
        cout << "\t\t\t\t\033[38;5;29m\u2560\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2563\033[0m\n\t\t\t\t";
    }

    for (Col = 0; Col < 4; Col++)
        {
            if (Number[3][Col] == 0){
                cout << "\033[38;5;29m\u2551\033[0m    ";
            }
            else if (Number[3][Col] < 10)
            {
                if (Number[3][Col] == 2)
                {
                    cout << "\033[38;5;29m\u2551\033[0m " << "\033[38;5;87m2\033[0m" << "  ";
                }
                if (Number[3][Col] == 4)
                {
                    cout << "\033[38;5;29m\u2551\033[0m " << "\033[38;5;86m4\033[0m" << "  ";
                }
                if (Number[3][Col] == 8)
                {
                    cout << "\033[38;5;29m\u2551\033[0m " << "\033[38;5;85m8\033[0m" << "  ";
                }
            }
            else if (Number[3][Col] >= 10 && Number[3][Col] < 100)
            {
                if (Number[3][Col] == 16)
                {
                    cout << "\033[38;5;29m\u2551\033[0m " << "\033[38;5;84m16\033[0m" << " ";
                }
                if (Number[3][Col] == 32)
                {
                    cout << "\033[38;5;29m\u2551\033[0m " << "\033[38;5;83m32\033[0m" << " ";
                }
                if (Number[3][Col] == 64)
                {
                    cout << "\033[38;5;29m\u2551\033[0m " << "\033[38;5;82m64\033[0m" << " ";
                }
            }
            else if (Number[3][Col] >= 100 && Number[3][Col] < 1000)
            {
                if (Number[3][Col] == 128)
                {
                    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << "\033[38;5;76m128\033[0m" << " ";
                }
                if (Number[3][Col] == 256)
                {
                    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << "\033[38;5;77m256\033[0m" << " ";
                }
                if (Number[3][Col] == 512)
                {
                    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << "\033[38;5;78m512\033[0m" << " ";
                }
            }
            else if (Number[3][Col] >= 1000 && Number[3][Col] < 10000)
            {
                if (Number[3][Col] == 1024)
                {
                    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << "\033[38;5;79m1024\033[0m";
                }
                if (Number[3][Col] == 2048)
                {
                    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << "\033[38;5;80m2048\033[0m";
                }
                if (Number[3][Col] == 4096)
                {
                    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << "\033[38;5;81m4096\033[0m";
                }
            }
        }
    cout << "\033[38;5;29m\033[38;5;29m\u2551\033[0m\033[0m" << endl;
    cout << "\t\t\t\t\033[38;5;29m\u255A\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u255D\033[0m\n\t\t\t\t";
    cout << "\n\t\t\t\t      Score: " << score;
}

//این تابع برای نمایش دادن صفحه ی بازی، زمانی که تم انتخابی نارنجی-قرمز هست، استفاده میشه
void DisplayOrangeRed(int Number[4][4])
{
    cout << "\n\n\t\t\t  \033[38;5;130mPress ESC anytime to quit the game";
    cout << "\n\n\n";
    int Row, Col;

    cout << "\t\t\t\t\033[38;5;130m\u2554\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2557\033[0m\n\t\t\t\t";
    for (Row = 0; Row < 3; Row++)
    {
        for (Col = 0; Col < 4; Col++)
        {
            if (Number[Row][Col] == 0){
                cout << "\033[38;5;130m\u2551\033[0m    ";
            }
            else if (Number[Row][Col] < 10)
            {
                if (Number[Row][Col] == 2)
                {
                    cout << "\033[38;5;130m\u2551\033[0m " << "\033[38;5;226m2\033[0m" << "  ";
                }
                if (Number[Row][Col] == 4)
                {
                    cout << "\033[38;5;130m\u2551\033[0m " << "\033[38;5;220m4\033[0m" << "  ";
                }
                if (Number[Row][Col] == 8)
                {
                    cout << "\033[38;5;130m\u2551\033[0m " << "\033[38;5;214m8\033[0m" << "  ";
                }
            }
            else if (Number[Row][Col] >= 10 && Number[Row][Col] < 100)
            {
                if (Number[Row][Col] == 16)
                {
                    cout << "\033[38;5;130m\u2551\033[0m " << "\033[38;5;208m16\033[0m" << " ";
                }
                if (Number[Row][Col] == 32)
                {
                    cout << "\033[38;5;130m\u2551\033[0m " << "\033[38;5;202m32\033[0m" << " ";
                }
                if (Number[Row][Col] == 64)
                {
                    cout << "\033[38;5;130m\u2551\033[0m " << "\033[38;5;196m64\033[0m" << " ";
                }
            }
            else if (Number[Row][Col] >= 100 && Number[Row][Col] < 1000)
            {
                if (Number[Row][Col] == 128)
                {
                    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << "\033[38;5;160m128\033[0m" << " ";
                }
                if (Number[Row][Col] == 256)
                {
                    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << "\033[38;5;161m256\033[0m" << " ";
                }
                if (Number[Row][Col] == 512)
                {
                    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << "\033[38;5;125m512\033[0m" << " ";
                }
            }
            else if (Number[Row][Col] >= 1000 && Number[Row][Col] < 10000)
            {
                if (Number[Row][Col] == 1024)
                {
                    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << "\033[38;5;88m1024\033[0m";
                }
                if (Number[Row][Col] == 2048)
                {
                    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << "\033[38;5;89m2048\033[0m";
                }
                if (Number[Row][Col] == 4096)
                {
                    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << "\033[38;5;90m4096\033[0m";
                }
            }
        }
        cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" <<endl;
        cout << "\t\t\t\t\033[38;5;130m\u2560\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2563\033[0m\n\t\t\t\t";
    }

    for (Col = 0; Col < 4; Col++)
        {
            if (Number[3][Col] == 0){
                cout << "\033[38;5;130m\u2551\033[0m    ";
            }
            else if (Number[3][Col] < 10)
            {
                if (Number[3][Col] == 2)
                {
                    cout << "\033[38;5;130m\u2551\033[0m " << "\033[38;5;226m2\033[0m" << "  ";
                }
                if (Number[3][Col] == 4)
                {
                    cout << "\033[38;5;130m\u2551\033[0m " << "\033[38;5;220m4\033[0m" << "  ";
                }
                if (Number[3][Col] == 8)
                {
                    cout << "\033[38;5;130m\u2551\033[0m " << "\033[38;5;214m8\033[0m" << "  ";
                }
            }
            else if (Number[3][Col] >= 10 && Number[3][Col] < 100)
            {
                if (Number[3][Col] == 16)
                {
                    cout << "\033[38;5;130m\u2551\033[0m " << "\033[38;5;208m16\033[0m" << " ";
                }
                if (Number[3][Col] == 32)
                {
                    cout << "\033[38;5;130m\u2551\033[0m " << "\033[38;5;202m32\033[0m" << " ";
                }
                if (Number[3][Col] == 64)
                {
                    cout << "\033[38;5;130m\u2551\033[0m " << "\033[38;5;196m64\033[0m" << " ";
                }
            }
            else if (Number[3][Col] >= 100 && Number[3][Col] < 1000)
            {
                if (Number[3][Col] == 128)
                {
                    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << "\033[38;5;160m128\0330m" << " ";
                }
                if (Number[3][Col] == 256)
                {
                    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << "\033[38;5;161m256\0330m" << " ";
                }
                if (Number[3][Col] == 512)
                {
                    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << "\033[38;5;125m512\0330m" << " ";
                }
            }
            else if (Number[3][Col] >= 1000 && Number[3][Col] < 10000)
            {
                if (Number[3][Col] == 1024)
                {
                    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << "\033[38;5;88m1024\033[0m";
                }
                if (Number[3][Col] == 2048)
                {
                    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << "\033[38;5;89m2048\033[0m";
                }
                if (Number[3][Col] == 4096)
                {
                    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << "\033[38;5;90m4096\033[0m";
                }
            }
        }
    cout << "\033[38;5;130m\033[38;5;130m\u2551\033[0m\033[0m" << endl;
    cout << "\t\t\t\t\033[38;5;130m\u255A\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u255D\033[0m\n\t\t\t\t";
    cout << "\n\t\t\t\t      Score: " << score;
}

//این تابع برای نمایش دادن صفحه ی بازی، زمانی که تم انتخابی پیش فرض هست، استفاده میشه
void DisplayDefault(int Number[4][4])
{
    cout << "\n\n\t\t\t  \033[38;5;15mPress ESC anytime to quit the game";
    cout << "\n\n\n";
    int Row, Col;

    cout << "\t\t\t\t\033[38;5;15m\u2554\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2557\033[0m\n\t\t\t\t";
    for (Row = 0; Row < 3; Row++)
    {
        for (Col = 0; Col < 4; Col++)
        {
            if (Number[Row][Col] == 0){
                cout << "\033[38;5;15m\u2551\033[0m    ";
            }
            else if (Number[Row][Col] < 10)
            {
                if (Number[Row][Col] == 2)
                {
                    cout << "\033[38;5;15m\u2551\033[0m " << "\033[38;5;15m2\033[0m" << "  ";
                }
                if (Number[Row][Col] == 4)
                {
                    cout << "\033[38;5;15m\u2551\033[0m " << "\033[38;5;15m4\033[0m" << "  ";
                }
                if (Number[Row][Col] == 8)
                {
                    cout << "\033[38;5;15m\u2551\033[0m " << "\033[38;5;15m8\033[0m" << "  ";
                }
            }
            else if (Number[Row][Col] >= 10 && Number[Row][Col] < 100)
            {
                if (Number[Row][Col] == 16)
                {
                    cout << "\033[38;5;15m\u2551\033[0m " << "\033[38;5;15m16\033[0m" << " ";
                }
                if (Number[Row][Col] == 32)
                {
                    cout << "\033[38;5;15m\u2551\033[0m " << "\033[38;5;15m32\033[0m" << " ";
                }
                if (Number[Row][Col] == 64)
                {
                    cout << "\033[38;5;15m\u2551\033[0m " << "\033[38;5;15m64\033[0m" << " ";
                }
            }
            else if (Number[Row][Col] >= 100 && Number[Row][Col] < 1000)
            {
                if (Number[Row][Col] == 128)
                {
                    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << "\033[38;5;15m128\033[0m" << " ";
                }
                if (Number[Row][Col] == 256)
                {
                    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << "\033[38;5;15m256\033[0m" << " ";
                }
                if (Number[Row][Col] == 512)
                {
                    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << "\033[38;5;15m512\033[0m" << " ";
                }
            }
            else if (Number[Row][Col] >= 1000 && Number[Row][Col] < 10000)
            {
                if (Number[Row][Col] == 1024)
                {
                    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << "\033[38;5;15m1024\033[0m";
                }
                if (Number[Row][Col] == 2048)
                {
                    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << "\033[38;5;15m2048\033[0m";
                }
                if (Number[Row][Col] == 4096)
                {
                    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << "\033[38;5;15m4096\033[0m";
                }
            }
        }
        cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" <<endl;
        cout << "\t\t\t\t\033[38;5;15m\u2560\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2563\033[0m\n\t\t\t\t";
    }

    for (Col = 0; Col < 4; Col++)
        {
            if (Number[3][Col] == 0){
                cout << "\033[38;5;15m\u2551\033[0m    ";
            }
            else if (Number[3][Col] < 10)
            {
                if (Number[3][Col] == 2)
                {
                    cout << "\033[38;5;15m\u2551\033[0m " << "\033[38;5;15m2\033[0m" << "  ";
                }
                if (Number[3][Col] == 4)
                {
                    cout << "\033[38;5;15m\u2551\033[0m " << "\033[38;5;15m4\033[0m" << "  ";
                }
                if (Number[3][Col] == 8)
                {
                    cout << "\033[38;5;15m\u2551\033[0m " << "\033[38;5;15m8\033[0m" << "  ";
                }
            }
            else if (Number[3][Col] >= 10 && Number[3][Col] < 100)
            {
                if (Number[3][Col] == 16)
                {
                    cout << "\033[38;5;15m\u2551\033[0m " << "\033[38;5;15m16\033[0m" << " ";
                }
                if (Number[3][Col] == 32)
                {
                    cout << "\033[38;5;15m\u2551\033[0m " << "\033[38;5;15m32\033[0m" << " ";
                }
                if (Number[3][Col] == 64)
                {
                    cout << "\033[38;5;15m\u2551\033[0m " << "\033[38;5;15m64\033[0m" << " ";
                }
            }
            else if (Number[3][Col] >= 100 && Number[3][Col] < 1000)
            {
                if (Number[3][Col] == 128)
                {
                    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << "\033[38;5;15m128\033[0m" << " ";
                }
                if (Number[3][Col] == 256)
                {
                    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << "\033[38;5;15m256\033[0m" << " ";
                }
                if (Number[3][Col] == 512)
                {
                    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << "\033[38;5;15m512\033[0m" << " ";
                }
            }
            else if (Number[3][Col] >= 1000 && Number[3][Col] < 10000)
            {
                if (Number[3][Col] == 1024)
                {
                    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << "\033[38;5;15m1024\033[0m";
                }
                if (Number[3][Col] == 2048)
                {
                    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << "\033[38;5;15m2048\033[0m";
                }
                if (Number[3][Col] == 4096)
                {
                    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << "\033[38;5;15m4096\033[0m";
                }
            }
        }
    cout << "\033[38;5;15m\033[38;5;15m\u2551\033[0m\033[0m" << endl;
    cout << "\t\t\t\t\033[38;5;15m\u255A\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u255D\033[0m\n\t\t\t\t";
    cout << "\n\t\t\t\t      Score: " << score;
}

//این تابع چک میکنه که ببینه با حرکت انجام شده، صفحه ی بازی تغییری کرده یا نه
int Check(int Temp[4][4], int Number[4][4])
{
    int Bool = 1, Row, Col;
    for (Row = 0; Row < 4; Row++)
    {
        for (Col = 0; Col < 4; Col++)
        {
            //اگه ماتریس ها با هم فرق داشته باشن، تایید میکنه که تغییر کرده
            if(Temp[Row][Col] != Number[Row][Col])
            {
                Bool = 0;
                break;
            }
        }
    }
    return Bool;
}

//این تابع چک میکنه که آیا بازیکن برنده شده یا نه
int ChechWin(int Number[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //اگه عدد دو هزار و چهل و هشت توی صفحه ی بازی باشه، تایید میکنه که بازیکن برنده شده
            if (Number[i][j] == 2048)
            {
                return 1;
            }
        }
    }
    return 0;
}

//این تابع چک میکنه که آیا بازیکن حرکتی برای انجام داره یا بازی رو باخته و بازی تموم شده
int CheckOver(int Number[4][4])
{
    int Empty = 0, AddBlock = 0, Row, Col;
    for (Row = 0; Row < 4; Row++)
    {
        for (Col = 0; Col < 4; Col++)
        {
            //اگه هر کدوم از خونه ها خالی باشن، به معنی اینه که بازی ادامه داره
            if(Number[Row][Col] == 0)
            {
                Empty = 1;
                break;    
            }
        }
    }
            
    for (Row = 0; Row < 3; Row++)
    {
        for (Col = 0; Col < 3; Col++)
        {
            //اگه دو تا از خونه های کنار هم با هم برابر باشن، به معنی اینه که بازی ادامه داره
            if(Number[Row+1][Col] == Number[Row][Col] || Number[Row][Col+1] == Number[Row][Col])
            {
                AddBlock = 1;
                break;
            }
        }
    }

    //اگه هر کدوم از شرط ها برقرار باشه، تایید میکنه که بازی ادامه داره
    if (Empty || AddBlock)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//این تابع جدول امتیازات مرتب شده رو به صورت یک استرینگ در میاره و آماده ی نمایش میکنه
string FinalLeaderBoard()
{
    string FinalScoreBoard;
    //اول باید اطلاعات مربوط به بازیکن ها مرتب بشن
    SortLeaderBoard(NumberOfPlayTimes + 1);

    //اطلاعات رو از بزرگترین به کوچکترین داخل استرینگ قرار میده
    for (int i = NumberOfPlayTimes; i >= 0; i--)
    {
        FinalScoreBoard += "\n";
        FinalScoreBoard += newPlayer[i].name;
        FinalScoreBoard += "'s score is: ";
        FinalScoreBoard += to_string(newPlayer[i].score);
        FinalScoreBoard += "\n";
    }

    return FinalScoreBoard;
}

//تابع اصلی که عملیات ها و تابع ها همه در اون مدیریت میشه
int main()
{
    //یه پیغام لودینگ که صفحه ی بعدی رو برای رنگی نمایش دادن آماده کنه
    cout << "\n\n\n\n\t\t\t\t\t\tLoading...";
    system("cls");

    //یه صفحه ی شروه اولیه که با فشردن هر دکمه ای میره
    cout << "\n\n\n\n\t\t\t\t\t\033[38;5;29m\033[38;5;9m2\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;10m0\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;226m4\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;12m8 \033[0m\033[0m";
    cout << "\033[38;5;15m\033[38;5;15mGAME\033[0m\033[0m" <<endl;
    cout << "\n\n\n\t\t\t\tPress any key to continue";
    getch();
    system("cls");

    //منوی اصلی برنامه
    Menu:
    WinFlag = 1;

    cout << "\n\n\n\n\t\t\t\t\t\033[38;5;29m\033[38;5;9m2\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;10m0\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;226m4\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;12m8 \033[0m\033[0m";
    cout << "\033[38;5;15m\033[38;5;15mGAME\033[0m\033[0m" <<endl;
    cout << "\n\n\n\t\t\t\t1) New Game";
    cout << "\n\n\n\t\t\t\t2) Score Board";
    cout << "\n\n\n\t\t\t\t3) Exit";
    cout << "\n\n\n\t\t\t\tPress any key to continue";
    cout << "\n\n\t\t\t\tPress 2 to see scoreboard";
    cout << "\n\n\t\t\t\tPress 3 to leave the game";

    //اگه بازیکن در منو دکمه ی دو رو فشار بده، صفحه ی جدول امتیازات نمایش داده میشه
    int MenuInput = getch();
    if (MenuInput == 50)
    {
        system("cls");
        cout << "\n\n";
        printf("%s\n",MenuLeaderBoard.c_str());
        cout << "\n\n\n\t\t\t\tPress any key to continue";
        getch();
        system("cls");
        goto Menu;
    }
    //اگه بازیکن در منو دکمه ی سه رو فشار بده، جدول امتیازات تو یه فایل ذخیره میشه و بازی بسته میشه
    if (MenuInput == 51)
    {
        LeaderBoard = FinalLeaderBoard();
        ScoreBoard.open ("scoreboard.txt");
        ScoreBoard << LeaderBoard;
        return 0;
    }
    //اگه هر دکمه ی دیگه ای زده بشه، بازیکن به صفحه شروع بازی منتقل میشه

    //تو این صفحه بازیکن تم بازی رو انتخاب میکنه
    system("cls");
    cout << "\n\n\n\n\t\t\t\tChoose your theme: ";
    cout << "\n\n\n\t\t\t\t1) Default";
    cout << "\n\n\n\t\t\t\t\033[38;5;15m2) \033[38;5;75mBlue\033[38;5;15m-\033[38;5;76mGreen";
    cout << "\n\n\n\t\t\t\t\033[38;5;15m3) \033[38;5;202mOrange\033[38;5;15m-\033[38;5;196mRed";
    cout << "\n\n\n\t\t\t\t\033[38;5;15mPress any key to choose Default theme";

    int Theme;
    int ThemeInput = getch();
    //اگه بازیکن دکمه ی دو رو فشار بده، تم آبی-سبز انتخاب میشه
    if (ThemeInput == 50)
    {
        Theme = 1;
    }
    //اگه بازیکن دکمه ی سه رو فشار بده، تم نارنجی-قرمز انتخاب میشه
    else if (ThemeInput == 51)
    {
        Theme = 2;
    }
    //اگه هر دکمه ی دیگه ای رو فشار بده، تم پیش فرض انتخاب میشه
    else
    {
        Theme = 0;
    }

    //تعداد دفعات بازی اضافه میشه
    NumberOfPlayTimes++;
    system("cls");

    //اسم بازیکن رو دریافت و داخل استراکت مربوط به اون بازیکن ذخیره میکنه
    cout << "\n\n\n\n\t\t\t\tEnter your name: ";
    getline(cin, newPlayer[NumberOfPlayTimes].name);
    system("cls");

    //برای شروع بازی به دو نقطه ی تصادفی احتیاج داره، پس چهار عدد تصادفی میسازه
    int RandRow1, RandCol1, RandRow2, RandCol2, Row, Col;
    int Number[4][4] = {0}, Temp[4][4] = {0};

    //مود اعداد به چهار رو میگیره تا نقاط داخل صفحه نمایش داده بشه
    srand(time(0));
    RandRow1 = rand() % 4;
    RandCol1 = rand() % 4;
    
    //اگه نقاط انتخابی با هم برابر بودن، مختصات نقطه ی دوم رو تغییر میده
    while(1)
    {
        RandRow2 = rand() % 4;
        RandCol2 = rand() % 4;

        if(RandRow2 != RandRow1 && RandCol2 != RandCol1)
        {
            break;
        } 
    }

    //یک از نقاط رو دو و اون یکی رو چهار قرار میده
    Number[RandRow1][RandCol1] = 2;
    Number[RandRow2][RandCol2] = 4;

    //صفحه ی بازی رو بر اساس تم انتخابی نمایش میده
    if (Theme == 1)
    {
        DisplayBlueGreen(Number);
    }
    else if (Theme == 2)
    {
        DisplayOrangeRed(Number);
    }
    else if (Theme == 0)
    {
        DisplayDefault(Number);
    }
    
    int Input;
    while (1)
    {
        //ماتریس تمپ رو با صفحه ی فعلی بازی یکی میزاره
        for (Row = 0; Row < 4; Row++)
        {
            for (Col = 0; Col < 4; Col++)
            {
                Temp[Row][Col] = Number[Row][Col];
            }
        }

        //دکمه ی ورودی رو دریافت میکنه و یه دور صفحه ی ترمینال رو پاک میکنه
        Input = getch();
        system("cls");

        //اگه دکمه ی ورودی بالا یا دبلیو بود، تابع بالا بردن رو صدا میکنه
        if (Input == 72 || Input == 119)
        {
            MoveUp(Number);
        }

        //اگه دکمه ی ورودی پایین یا اس بود، تابع پایین بردن رو صدا میکنه
        if (Input == 80 || Input == 115)
        {
            MoveDown(Number);
        }

        //اگه دکمه ی ورودی چپ یا ای بود، تابع چپ بردن رو صدا میکنه
        if (Input == 75 || Input == 97)
        {
            MoveLeft(Number);
        }

        //اگه دکمه ی ورودی راست یا دی بود، تابع راست بردن رو صدا میکنه
        if (Input == 77 || Input == 100)
        {
            MoveRight(Number);
        }

        //اگه دکمه ی ورودی اسکیپ بود، از صفحه ی بازی خارج میشه
        if (Input == 27)
        {
            //امتیازی که تا الان بدست اومده رو داخل استراکت بازیکن ذخیره میکنه
            newPlayer[NumberOfPlayTimes].score = score;
            score = 0;

            //جدول های امتیازات رو تشکیل میده
            LeaderBoard = FinalLeaderBoard();
            MenuLeaderBoard = FinalLeaderBoard();

            cout << "\n\n\t\t\t\tPress any key to play again!";
            cout << "\n\n\t\t\t\tPress ESC to leave the Game!\n";
            Input = getch();

            //اگه دکمه ی ورودی اسکیپ بود، اطلاعات جدول امتیازات رو توی فایل ذخیره میکنه و بازی رو میبنده
            if (Input == 27)
            {
                ScoreBoard.open ("scoreboard.txt");
                ScoreBoard << LeaderBoard;
                break;
            }
            //اگه هر دکمه ی دیگه ای فشار داده بشه، صفحه ی ترمینال رو پاک میکنه و به منو برمیگرده
            else
            {
                system("cls");
                goto Menu;
            }
        }
        
        //اگه صفحه ی بازی با دکمه ی ورودی بازیکن تغییر کرد، تابع اضافه کردن رو صدا میکنه
        if(!Check(Temp, Number))
        {
            AddBlock(Number);
        }

        //صفحه ی بازی رو بر اساس تم انتخابی نمایش میده
        if (Theme == 1)
        {
            DisplayBlueGreen(Number);
        }
        else if (Theme == 2)
        {
            DisplayOrangeRed(Number);
        }
        else if (Theme == 0)
        {
            DisplayDefault(Number);
        }

        //اگه بازیکن به عدد دو هزار و چهل هشت رسیده باشه، این عملیات انجام میشه
        if (ChechWin(Number))
        {
            //فقط اگه این اولین باری باشه که به عدد دو هزار و چهل و هشت میرسه این کار انجام میشه
            if (WinFlag != 0)
            {
                cout << "\n\n\t\t\tCongratualtions! You have reached 2048\n";
                WinFlag = 0;
                cout << "\n\n\t\t\t    Press enter to continue playing\n";
                cout << "\n\t\t\t     Press any key to quit to menu\n\n\n";

                //اگه دکمه ی ورودی اسکیپ بود، به منوی بازی بر میگرده
                int WinInput = getch();
                if (WinInput != 13)
                {
                    system("cls");
                    goto Menu;
                }
            }
        }
        
        //اگه بازیکن حرکتی برای انجام دادن نداشته باشه، این عملیات انجام میشه
        if (!CheckOver(Number))
        {
            cout << "\n\n\t\t\t\t     GAME OVER!\n";

            //امتیازی که تا الان بدست اومده رو داخل استراکت بازیکن ذخیره میکنه
            newPlayer[NumberOfPlayTimes].score = score;
            score = 0;

            //جدول های امتیازات رو تشکیل میده
            MenuLeaderBoard = FinalLeaderBoard();
            LeaderBoard = FinalLeaderBoard();

            cout << "\n\n\t\t\t     Press any key to play again!";
            cout << "\n\n\t\t\t     Press ESC to leave the Game!\n";
            Input = getch();

            //اگه دکمه ی ورودی اسکیپ بود، اطلاعات جدول امتیازات رو توی فایل ذخیره میکنه و بازی رو میبنده
            if (Input == 27)
            {
                ScoreBoard.open ("scoreboard.txt");
                ScoreBoard << LeaderBoard;
                break;
            }
            //اگه هر دکمه ی دیگه ای فشار داده بشه، صفحه ی ترمینال رو پاک میکنه و به منو برمیگرده
            else
            {
                system("cls");
                goto Menu;
            }
        }    
    }
    return 0;
}