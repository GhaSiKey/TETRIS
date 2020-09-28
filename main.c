#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")
#define FrameX 13
#define FrameY 3
#define Frame_height 20
#define Frame_width 18

int i,j,Temp,Temp1,Temp2;
int a[80][80] = {0};//0,1,2  1�з��飬 0�޷��飬 2��ʾ��Ϸ�߿�
int b[4];  //1�з��飬 0�޷���
struct Tetris
{
    int x;
    int y;
    int flag;
    int next;
    int speed;
    int number;
    int socre;
    int level;
};

HANDLE hOut;

//��������
void music_1()
{
	PlaySound("lian.wav",NULL,SND_FILENAME | SND_ASYNC);
	return 0;
}
//SND_FILENAME��ʾpszSound����ָ�������ļ�����pszSound������ָ����Դ���ڴ����֡�ϵͳ���ֵȵȣ���
//SND_ASYNC�����첽��ʽ����������PlaySound�����ڿ�ʼ���ź��������أ�
////SND_SYNC��ͬ�������������ڲ������PlaySound�����ŷ��أ�
//SND_LOOPһ�����ظ�����������������SND_ASYNC��־һ��ʹ�á�
//E:\\from_C\\C_code\\music\\lian.wav
void music_2()
{
	PlaySound("1757.wav",NULL,SND_FILENAME | SND_ASYNC|SND_LOOP);
	return 0;
}
void music_3()
{
	PlaySound("yinxiao.wav",NULL,SND_FILENAME | SND_ASYNC);
	return 0;
}
void music_4()
{
	PlaySound("8865.wav",NULL,SND_FILENAME | SND_ASYNC);
	return 0;
}

//����������ɫ
int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
    return 0;
}
//����������ʾλ��
 void goto_xy(int x,int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

//��ӭ�����ϵı���
void title()
{
    color(15);
    goto_xy(24,3);
    printf(" �� �� ˹ �� �� ( �� �� �S )");

    color(11);
    goto_xy(18,5);
    printf("��");//�ѹ��������ռ������x����λ��
    goto_xy(18,6);
    printf("����");
    goto_xy(18,7);
    printf("��");//T��

    color(14);
    goto_xy(26,6);
    printf("����");
    goto_xy(28,7);
    printf("����");//Z��

    color(10);
    goto_xy(36,6);
    printf("����");
    goto_xy(36,7);
    printf("����");//������

    color(13);
    goto_xy(45,5);
    printf("��");
    goto_xy(45,6);
    printf("��");
    goto_xy(45,7);
    printf("��");
    goto_xy(45,8);
    printf("��");//����

    color(12);
    goto_xy(55,6);
    printf("��");
    goto_xy(51,7);
    printf("������");//7��
}

//�˵�˵��
void information()
{
    goto_xy(66,11);
    color(12);
   printf("music.ver:��ҰԴ ��");
    goto_xy(65,19);
    color(5);
    printf("GhaSiKey ������");
}

//�˵�ѡ��
void welcome()
{
    music_1();
    int i,j = 1;
    int n;
    color(14);//�߿���ɫ
    for(i = 9;i <= 20;i++)//Y������ֵ (15,9)(60,9)(15,20)(60,20)
    {
        for(j = 15;j <= 60;j++)//x������ֵ
        {
            goto_xy(j,i);
            if(i ==9 || i == 20)
            {
                printf("==");
            }
            else if(j == 15 || j == 59)
            {
                printf("||");
            }
        }
    }

    color(12);//�˵�������ɫ
    goto_xy(25,12);
    printf("1.��ʼ��Ϸ");
    goto_xy(40,12);
    printf("2.����˵��");
    goto_xy(25,17);
    printf("3.��Ϸ����");
    goto_xy(40,17);
    printf("4.�˳�");

    //�˵�ѡ��
    goto_xy(21,22);
    color(3);
    printf("��ѡ��[1��2��3��4]��[ ]\b\b");//����˺󵽷�����
    color(14);
    scanf("%d",&n);
    switch(n)
    {
    case 1:
        music_3();
        system("cls");//c��������Ļ����
        //music_2();
        DrawGameframe();//����Ϸ���
        Gameplay();
        break;
    case 2:
        printf("�д���һ��������");
        Sleep(1000);
        break;
    case 3:
        printf("�д���һ��������");
        Sleep(1000);
        break;
    case 4:
        exit(0);
        break;
    default:
        printf("error");
    }
}

//������Ϸ����
void DrawGameframe()
{
    goto_xy(FrameX+Frame_width-7,FrameY-2);
    color(11);
    printf("����˹���飨���꣩");

//�� �� ��
//�� �� ��
//�� �� ��
    color(12);
    goto_xy(FrameX,FrameY);
    printf("��");
    goto_xy(FrameX+2*Frame_width-2,FrameY);
    printf("��");
    goto_xy(FrameX,FrameY+Frame_height);
    printf("��");
    goto_xy(FrameX+2*Frame_width-2,FrameY+Frame_height);
    printf("��");
    for(i = 1;i<2*Frame_width-2;i++)
    {
        goto_xy(FrameX+i,FrameY);
        printf("��");//�Ϻ��
    }
    for(i = 1;i<2*Frame_width-2;i++)
    {
        goto_xy(FrameX+i,FrameY+Frame_height);
        printf("��");//�º��
        a[FrameX+i][FrameY+Frame_height]=2;
    }
    for(i = 1;i<Frame_height;i++)
    {
        goto_xy(FrameX,FrameY+i);
        printf("��");//������
        a[FrameX][FrameY+i]=2;
    }
    for(i = 1;i<Frame_height;i++)
    {
        goto_xy(FrameX+2*Frame_width-2,FrameY+i);
        printf("��");//������
        a[FrameX+2*Frame_width-2][FrameY+i]=2;
    }

    //�Ҳ���ʾ
    color(2);
    goto_xy(FrameX+2*Frame_width+3,FrameY+7);
    printf("**********");
    goto_xy(FrameX+2*Frame_width+3,FrameY+13);
    printf("**********");
    color(3);
    goto_xy(FrameX+2*Frame_width+13,FrameY+7);
    printf("��һ���ַ���");

    //���½ǰ���˵��
    color(14);
    goto_xy(FrameX+2*Frame_width+3,FrameY+18);
    printf("Esc:�˳���Ϸ");
    goto_xy(FrameX+2*Frame_width+3,FrameY+20);
    printf("��������ת");
    goto_xy(FrameX+2*Frame_width+3,FrameY+22);
    printf("�ո���ͣ��Ϸ");
}

//��������˹����
void MakeTetris(struct Tetris *tetris)
{
    a[tetris->x][tetris->y] = b[0];
    switch(tetris->flag)
    {
    case 1://���ӷ��� ���Ŀ������½ǡ� �� 1 2
        //                          �� �� 0 3
        {
            color(14);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x+2][tetris->y-1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        }
    case 2://����  �� �� �� �� 1 0 2 3
        {
            color(11);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x+2][tetris->y] = b[2];
            a[tetris->x+4][tetris->y] = b[3];
            break;
        }
    case 3://   �� 1
        //      �� 0
        //      �� 2
        //      �� 3
        {
            color(11);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x][tetris->y+2] = b[3];
            break;
        }
    case 4://
        //    �� �� �� 1 0 2
        //      ��     3
        {
            color(13);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x+2][tetris->y] = b[2];
            a[tetris->x][tetris->y+1] = b[3];
            break;
        }
    case 5://  ��   1
        //   �� �� 3 0
        //     ��   2
        {
            color(13);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x-2][tetris->y] = b[3];
            break;
        }
    case 6://  ��       1
        //   �� �� ��   2 0 3
        {
            color(13);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x-2][tetris->y] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        }
    case 7://  ��     1
        //     �� ��   0 3
        //     ��     2
        {
            color(13);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        }
    case 8://    �� ��      1 0
        //         �� ��      2 3
        {
            color(12);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x+2][tetris->y+1] = b[3];
            break;
        }
    case 9://    ��       1
        //     �� ��     2 0
        //     ��       3
        {
            color(12);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x-2][tetris->y] = b[2];
            a[tetris->x-2][tetris->y+1] = b[3];
            break;
        }
    case 10://    �� ��    0 3
        //      �� ��    1 2
        {
            color(10);
            a[tetris->x-2][tetris->y+1] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        }
    case 11:// ��        1
        //     �� ��      0 2
        //       ��        3
        {
            color(10);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x+2][tetris->y] = b[2];
            a[tetris->x+2][tetris->y+1] = b[3];
            break;
        }
    case 12://��  ��  3 2
        //       ��    0
        //       ��    1
        {
            color(15);
            a[tetris->x][tetris->y+1] = b[1];
            a[tetris->x][tetris->y-1] = b[2];
            a[tetris->x-2][tetris->y-1] = b[3];
            break;
        }
    case 13://    ��         2
        //    �� �� ��     1 0 3
        {
            color(15);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x+2][tetris->y-1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        }
    case 14://   ��    1
        //       ��    0
        //       �� ��  2 3
        {
            color(15);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x+2][tetris->y+1] = b[3];
            break;
        }
    case 15://   �� �� ��     1 0 3
        //       ��         2
        {
            color(15);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x-2][tetris->y+1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        }
    case 16://   ��  ��  2 3
        //       ��     0
        //       ��     1
        {
            color(9);
            a[tetris->x][tetris->y+1] = b[1];
            a[tetris->x][tetris->y-1] = b[2];
            a[tetris->x+2][tetris->y-1] = b[3];
            break;
        }
    case 17://   �� �� ��     1 0 3
        //           ��         2
        {
            color(9);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x+2][tetris->y+1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        }
    case 18://   ��   1
        //       ��   0
        //     �� ��  3 2
        {
            color(9);
            a[tetris->x][tetris->y-1] = b[1];
            a[tetris->x][tetris->y+1] = b[2];
            a[tetris->x-2][tetris->y+1] = b[3];
            break;
        }
    case 19://��         2
        //    �� �� ��     1 0 3
        {
            color(9);
            a[tetris->x-2][tetris->y] = b[1];
            a[tetris->x-2][tetris->y-1] = b[2];
            a[tetris->x+2][tetris->y] = b[3];
            break;
        }
    }
}

//��ӡ����˹����
void PrintTetris(struct Tetris *tetris)
{
    for(i=0;i<4;i++)
    {
        b[i]=1;
    }
    MakeTetris(tetris);
    for(i=tetris->x-2;i<=tetris->x+4;i+=2)
    {
        for(j=tetris->y-1;j<=tetris->y+2;j++)
        {
            if(a[i][j]==1&&j>FrameY)
            {
                goto_xy(i,j);
                printf("��");
            }
        }
    }

    //��ӡ�˵���Ϣ
    goto_xy(FrameX+2*Frame_width+3,FrameY+1);
    color(4);
    printf("level: ");
    color(12);
    printf("%d",tetris->level);

    goto_xy(FrameX+2*Frame_width+3,FrameY+3);
    color(4);
    printf("score: ");
    color(12);
    printf("%d",tetris->socre);

    goto_xy(FrameX+2*Frame_width+3,FrameY+5);
    color(4);
    printf("speed: ");
    color(12);
    printf("%dms",tetris->speed);
}

//�ж��Ƿ���ƶ�
int ifMove(struct Tetris *tetris)
{
   if(a[tetris->x][tetris->y] != 0)
   {
       return 0;
   }
   else
   {
       if(tetris->flag ==1&&(a[tetris->x][tetris->y-1]==0&&a[tetris->x+2][tetris->y-1]==0&&a[tetris->x+2][tetris->y]==0)||
          tetris->flag ==2&&(a[tetris->x-2][tetris->y]==0&&a[tetris->x+2][tetris->y]==0&&a[tetris->x+4][tetris->y]==0)||
          tetris->flag ==3&&(a[tetris->x][tetris->y-1]==0&&a[tetris->x][tetris->y+1]==0&&a[tetris->x][tetris->y+2]==0)||
          tetris->flag ==4&&(a[tetris->x-2][tetris->y]==0&&a[tetris->x+2][tetris->y]==0&&a[tetris->x][tetris->y+1]==0)||
          tetris->flag ==5&&(a[tetris->x-2][tetris->y]==0&&a[tetris->x][tetris->y-1]==0&&a[tetris->x][tetris->y+1]==0)||
          tetris->flag ==6&&(a[tetris->x-2][tetris->y]==0&&a[tetris->x][tetris->y-1]==0&&a[tetris->x+2][tetris->y]==0)||
          tetris->flag ==7&&(a[tetris->x][tetris->y-1]==0&&a[tetris->x+2][tetris->y]==0&&a[tetris->x][tetris->y+1]==0)||
          tetris->flag ==8&&(a[tetris->x-2][tetris->y]==0&&a[tetris->x][tetris->y+1]==0&&a[tetris->x+2][tetris->y+1]==0)||
          tetris->flag ==9&&(a[tetris->x][tetris->y-1]==0&&a[tetris->x-2][tetris->y]==0&&a[tetris->x-2][tetris->y+1]==0)||
          tetris->flag ==10&&(a[tetris->x+2][tetris->y]==0&&a[tetris->x][tetris->y+1]==0&&a[tetris->x-2][tetris->y+1]==0)||
          tetris->flag ==11&&(a[tetris->x][tetris->y-1]==0&&a[tetris->x+2][tetris->y]==0&&a[tetris->x+2][tetris->y+1]==0)||
          tetris->flag ==12&&(a[tetris->x-2][tetris->y-1]==0&&a[tetris->x][tetris->y-1]==0&&a[tetris->x][tetris->y+1]==0)||
          tetris->flag ==13&&(a[tetris->x-2][tetris->y]==0&&a[tetris->x+2][tetris->y]==0&&a[tetris->x+2][tetris->y-1]==0)||
          tetris->flag ==14&&(a[tetris->x][tetris->y-1]==0&&a[tetris->x][tetris->y+1]==0&&a[tetris->x+2][tetris->y+1]==0)||
          tetris->flag ==15&&(a[tetris->x-2][tetris->y]==0&&a[tetris->x-2][tetris->y+1]==0&&a[tetris->x+2][tetris->y]==0)||
          tetris->flag ==16&&(a[tetris->x][tetris->y+1]==0&&a[tetris->x][tetris->y-1]==0&&a[tetris->x+2][tetris->y-1]==0)||
          tetris->flag ==17&&(a[tetris->x-2][tetris->y]==0&&a[tetris->x+2][tetris->y]==0&&a[tetris->x+2][tetris->y+1]==0)||
          tetris->flag ==18&&(a[tetris->x][tetris->y-1]==0&&a[tetris->x][tetris->y+1]==0&&a[tetris->x-2][tetris->y+1]==0)||
          tetris->flag ==19&&(a[tetris->x-2][tetris->y-1]==0&&a[tetris->x-2][tetris->y]==0&&a[tetris->x+2][tetris->y]==0))
        {
            return 1;
        }
   }
   return 0;
}

//�������˹���������ۼ�
void CleanTetris(struct  Tetris *tetris)
{
    for(i=0;i<4;i++)
    {
        b[i]=0;
    }
    MakeTetris(tetris);
    for(i=tetris->x-2;i<=tetris->x+4;i+=2)
    {
        for(j=tetris->y-1;j<=tetris->y+2;j++)
        {
            if(a[i][j]==0&&j>FrameY)
            {
                goto_xy(i,j);
                printf(" ");
            }
        }
    }
}

//ɾ������
void Del_Fullline(struct Tetris *tetris)
{//////////////////////////////////////
    int k,del_rows=0; //kĳ�з���ĸ�����rowsɾ�����������
  for(j=FrameY+Frame_height-1;j>=FrameY+1;j--)
    {
        k=0;
        for(i=FrameX+2;i<FrameX+2*Frame_width-2;i+=2)
        {
            if(a[i][j]==1)
            {
                k++;
                if(k==Frame_width-2)
                {
                    for(k=FrameX+2;k<FrameX+2*Frame_width-2;k+=2)
                    {
                        a[k][j]=0;
                        goto_xy(k,j);
                        printf(" ");//ɾ��
                    }
                    for(k=j-1;k>FrameY;k--)
                    {
                        for(i=FrameX+2;i<FrameX+2*Frame_width-2;i+=2)
                        {
                            if(a[i][k]==1)
                            {
                                a[i][k]=0;
                                goto_xy(i,k);
                                printf(" ");
                                a[i][k+1]=1;
                                goto_xy(i,k+1);
                                printf("��");
                            }
                        }
                    }//����
                    j++;
                    del_rows++;
                }
            }
        }
    }
    tetris->socre+=100*del_rows;
    if(del_rows>0&&(tetris->socre%1000==0||tetris->socre/1000>tetris->level-1))
    {
        tetris->speed-=20;
        tetris->level++;//ÿ1000������
    }
}

// �����������
void Flag(struct Tetris *tetris)
{
    tetris->number++;
    srand(time(NULL));//��ʼ�������
    if(tetris->number==1)
    {
        tetris->flag=rand()%19+1;
    }
    tetris->next=rand()%19+1;
}

//��ʼ��Ϸ
void Gameplay()
{
    int n;
    struct Tetris t,*tetris = &t;
    char ch;
    tetris->number=0;
    tetris->speed=200;
    tetris->socre=0;
    tetris->level=1;
    while(1)
    {
        Flag(tetris);
        Temp=tetris->flag;//��ס��ǰ��������
        tetris->x=FrameX+2*Frame_width+6;
        tetris->y=FrameY+10;
        tetris->flag=tetris->next;//�����һ���������
        PrintTetris(tetris);
        tetris->x=FrameX+Frame_width;
        tetris->y=FrameY-1;
        tetris->flag=Temp;

        //�������� �ϣ�72   �£�80   ��75  �ң�77   �ո�32  esc��27
        while(1)
        {
            label:PrintTetris(tetris);
            Sleep(tetris->speed);
            CleanTetris(tetris);
            Temp1=tetris->x;
            Temp2=tetris->flag;
            if(kbhit())
               {
                 ch=getch();
                 if(ch==75)
                 {
                     music_3();//����������������������������������������������������������������������
                    tetris->x-=2;
                 }
                 if(ch==77)
                 {
                    music_3();//����������������������������������������������������������������������
                     tetris->x+=2;
                 }
                 if(ch==80)
                 {
                     music_3();//����������������������������������������������������������������������
                     if(ifMove(tetris)!=0)
                     {
                         tetris->y+=2;
                     }
                     if(ifMove(tetris)==0)
                     {
                         tetris->y=FrameY+Frame_height-2;
                     }
                 }
                 if(ch==72)
                 {
                     music_3();//����������������������������������������������������������������������
                     if(tetris->flag>=2&&tetris->flag<=3)
                     {
                         tetris->flag++;
                         tetris->flag%=2;
                         tetris->flag+=2;
                     }
                     if(tetris->flag>=4&&tetris->flag<=7)
                     {
                         tetris->flag++;
                         tetris->flag%=4;
                         tetris->flag+=4;
                     }
                     if(tetris->flag>=8&&tetris->flag<=9)
                     {
                         tetris->flag++;
                         tetris->flag%=2;
                         tetris->flag+=8;
                     }
                     if(tetris->flag>=10&&tetris->flag<=11)
                     {
                         tetris->flag++;
                         tetris->flag%=2;
                         tetris->flag+=10;
                     }
                     if(tetris->flag>=12&&tetris->flag<=15)
                     {
                         tetris->flag++;
                         tetris->flag%=4;
                         tetris->flag+=12;
                     }
                     if(tetris->flag>=16&&tetris->flag<=19)
                     {
                         tetris->flag++;
                         tetris->flag%=4;
                         tetris->flag+=16;
                     }
                 }
                 if(ch==32)
                 {
                     music_2();//����������������������������������������������������������������������
                     PrintTetris(tetris);
                goto_xy(5,7);
                printf("\n");
                color(11);
                printf("  �� ��\n");
                printf("  ��   ��\n");
                printf("  �� ��\n");
                printf("  ��\n");
                printf("  ��\n");
                printf("  ��\n");
                     while(1)
                     {
                         if(kbhit())
                         {
                            ch=getch();
                            if(ch==32)
                            {
                                goto_xy(5,7);
                printf("\n");
                printf("           \n");
                printf("           \n");
                printf("           \n");
                printf("     \n");
                printf("     \n");
                printf("     \n");
                             music_3();//����������������������������������������������������������������������
                                goto label;//tgoto��ת��䣬��ת��label���ڴ�����
                            }
                         }
                     }
                 }
                 if(ch==27)
                 {
                     system("cls");
                     memset(a,0,6400*sizeof(int));//��ʼ��
                     title();
                     welcome();
                 }
                 if(ifMove(tetris)==0)//�����޷������ײ�����
                 {
                     tetris->x=Temp1;
                     tetris->flag=Temp2;
                 }
                 else
                 {
                     goto label;
                 }
               }
               tetris->y++;
               if(ifMove(tetris)==0)
               {
                   tetris->y--;
                   PrintTetris(tetris);
                   Del_Fullline(tetris);
                   break;
               }
        }
        //��Ϸ��������
        for(i=tetris->y-2;i<tetris->y+2;i++)
        {
            if(i==FrameY)//�Ӵ�����
            {
                music_4();
                system("cls");
                goto_xy(29,7);
                printf("\n");
                color(12);
                printf("\t\t\t��������    ��      ��     �� ��      \n");
                printf("\t\t\t��          �� ��   ��     ��    ��        \n");
                printf("\t\t\t��������    ��  ��  ��     ��     ��      \n");
                printf("\t\t\t��          ��   �� ��     ��    ��      \n");
                printf("\t\t\t��������    ��      ��     �� ��      \n");
                goto_xy(17,18);
                color(14);
                printf("����һ��----------1");
                goto_xy(44,18);
                printf("�����²�----------2\n");
                int n;
                goto_xy(32,20);
                printf("ѡ��1/2����");
                color(11);
                scanf("%d",&n);
                switch(n)
                    {
                    case 1:
                        system("cls");
                        Replay(tetris);
                        break;
                    case 2:
                        exit(0);
                        break;
                    }
                }
            }
        tetris->flag=tetris->next;//�����һ������˹���鴰��
        tetris->x=FrameX+2*Frame_width+6;
        tetris->y=FrameY+10;
        CleanTetris(tetris);

    }
}

//���¿�ʼ��Ϸ
void Replay(struct Tetris *tetris)
{
        system("cls");
        memset(a,0,6400*sizeof(int));
        DrawGameframe();
        Gameplay();
}

int main()
{
    title();
    information();
    welcome();

}
