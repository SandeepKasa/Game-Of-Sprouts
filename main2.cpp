#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 600
#define HEIGHT 600
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

using namespace std;

double arr[5000][4],temp[2],sph[1000][3],edge[50][100], box[50][200],uti[100][10],child[100][10],mid[100][10];
float color[3][3]={{1.0,1.0,1.0},{1.0,1.0,0.0},{0.0,1.0,0.0}};

int spind=0,boxind=0,ptr=0,pos,state=1,block=1,glo=0;
float r=10.0;
int z=0,flag=0,kas=0,tt,fl1=0,fl2=0,fl3=0,fl4=0,fl5=0,fl6=0,fl7=0,fl8=0;

void myPressedMove(int x,int y);
void init()
{
    glClearColor( 0.0, 0.0, 0.0, 1.0);
    glMatrixMode( GL_PROJECTION);
    gluOrtho2D(0.0,WIDTH,0.0,HEIGHT);
    memset(arr,0,5000);
    glPointSize(20.0);
}



void Disk( float x, float y)
{
    glColor3f(1.0,1.0,0.0);
    glBegin( GL_TRIANGLE_FAN );
    glVertex2f( x, y );
    for(float i = 0; i <= 2 * PI + 0.1; i += 0.1 )
    {
        glVertex2f( x + sin( i ) * r, y + cos( i ) * r );
    }
    glEnd();
}

float getOpenGLX(int x)
{
    double ox = x/ (double)WIDTH*(WIDTH);
    return ox;
}
float getOpenGLY(int y)
{
    double oy = (1 - y/ (double) HEIGHT)*HEIGHT;
    return oy;
}

void drawLines(int i)
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(arr[i][0],arr[i][1]);
    glVertex2f(arr[i+1][0],arr[i+1][1]);
    glEnd();
}

void drawLine(int x,int y,int w,int z)
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(x,y);
    glVertex2f(w,z);
    glEnd();
}

void addValue(int x,int y)
{
    arr[z][0]=getOpenGLX(x);
    arr[z][1]=getOpenGLY(y);
    z++;
}


void myDisplay()
{
    glClear( GL_COLOR_BUFFER_BIT);
    if(pos==1 && glo==0)
    {
        z=0;
        sph[13][2]=1;
        arr[z][0]=sph[0][0], arr[z][1]=sph[0][1];
        z++;
        arr[z][0]=sph[13][0], arr[z][1]=sph[13][1];
        z++;
        arr[z][0]=sph[13][0], arr[z][1]=sph[13][1];
        z++;
        arr[z][0]=sph[1][0], arr[z][1]=sph[1][1];
        z++;
        glo=1;
    }

    
    for(int jj=0 ; jj<spind ;jj++)
    {
        if(sph[jj][2]==1)
        {
            Disk(sph[jj][0],sph[jj][1]);
            if(jj==2)
            {
                drawLine(sph[2][0],sph[2][1],325,450);
                drawLine(sph[0][0],sph[0][1],325,450);
                drawLine(sph[2][0],sph[2][1],275,450);
                drawLine(sph[0][0],sph[0][1],275,450);
            }
            if(jj==7)
            {
                drawLine(sph[7][0],sph[7][1],325,150);
                drawLine(sph[1][0],sph[1][1],325,150);
                drawLine(sph[7][0],sph[7][1],275,150);
                drawLine(sph[1][0],sph[1][1],275,150);
            }
        }
    }
    if(z%2==0)
    {
        for(int i=0;i<z;i=i+2)
            drawLines(i);
    }
    else
    {
        for(int i=0;i<z-1;i=i+2)
            drawLines(i);
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0,0.0,0.0);
        glVertex2f(arr[z-1][0],arr[z-1][1]);
        glVertex2f(temp[0],temp[1]);
        glEnd();
        
    }
    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}


void myMouseStat(int button,int state,int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(!flag)
        {
            flag=1;
            addValue(x,y);
            fl1=0,fl2=0,fl3=0;
            fl4=0 , fl5=0 , fl6=0,fl7=0,fl8=0;
            temp[0]=getOpenGLX(x);
            temp[1]=getOpenGLY(y);
        }
        
    }
    else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if(flag)
        {
            int i,j,x,te=0,te1=0,out=0,flka=0;
            for(i=0;i<spind;i++)
            {
                if(pow(sph[i][0]-arr[z-1][0],2)+pow(sph[i][1]-arr[z-1][1],2)<=pow(r,2) && sph[i][2]==1)
                {
                    
                    for(j=0;j<spind;j++)
                    {
                        if(pow(sph[j][0]-temp[0],2)+pow(sph[j][1]-temp[1],2)<=pow(r,2) && sph[j][2]==1)
                        {
                            arr[z-1][0]=sph[i][0] , arr[z-1][1]=sph[i][1];
                            z++;
                            arr[z-1][0]=sph[j][0] , arr[z-1][1]=sph[j][1];
                            if(i==j && i==0)
                                sph[2][2]=1;
                            if(i==j && i==1)
                                sph[7][2]=1;
                            int cv=0;
                            for(x=0;x<100;x++)
                            {
                                if((mid[x][0]==i && mid[x][1]==j) || (mid[x][1]==i && mid[x][0]==j))
                                {
                                    if((i==0 && j==1) || (i==1 && j==0))
                                    {
                                        if(fl5==1)
                                        {
                                            cv=mid[15][2] ;
                                            break;
                                        }
                                        else if(fl6==1)
                                        {
                                            cv=mid[16][2];
                                            break;
                                        }
                                        else if(fl4==1)
                                        {
                                            cv=mid[14][2];
                                            break;
                                        }
                                        
                                    }
                                    else if((i==0 && j==2) || (i==2 && j==0))
                                    {
                                        if(fl1==1)
                                        {
                                            cv=mid[3][2] ;
                                            break;
                                        }
                                        else if(fl2==1)
                                        {
                                            cv=mid[2][2];
                                            break;
                                        }
                                    }
                                    else if((i==1 && j==15) || (i==15 && j==1))
                                    {
                                        if(fl8==1)
                                        {
                                            cv=19;
                                            break;
                                        }
                                        else if(fl7==1)
                                        {
                                            cv=20;
                                            break;
                                        }
                                    }

                                    else
                                    {
                                        cv=mid[x][2];
                                        break;
                                    }
                                }
                            }
                            z=z-2;
                            sph[cv][2]=1;
                            //cout<<"cv"<<cv<<endl ;
                            arr[z][0]=sph[i][0], arr[z][1]=sph[i][1];
                            z++;
                            if(cv!=2 && cv!=7)
                            {
                            arr[z][0]=sph[cv][0],arr[z][1]=sph[cv][1];
                            arr[z+1][0]=sph[cv][0],arr[z+1][1]=sph[cv][1];
                            z=z+2;
                            }
                            arr[z][0]=sph[j][0], arr[z][1]=sph[j][1];
                            z++;
                            te=1;
                            int temp1[200],tv,rt;
                            for(tv=0;tv<200;tv++)
                                temp1[tv]=-1;
                            for(tv=1;tv<=46;tv++)
                            {
                                flka=0;
                                for(rt=0;rt<200;rt++)
                                {
                                    if(box[tv][rt]==-1 && box[tv][rt+1]==-1)
                                        break;
                                    else
                                        temp1[rt]=box[tv][rt];
                                }
                              
                                int wa=0;
                                for(wa=0;wa<200;wa=wa+3)
                                {
                                    if(temp1[wa+1]==-1)
                                        break;
                                }
                                int a,b;
                                for(a=0;a<z;a=a+2)
                                {
                                    int c,d,e;
                                    for(e=0;e<spind;e++)
                                    {
                                        if(arr[a][0]==sph[e][0] && arr[a][1]==sph[e][1])
                                        {
                                            c=e;
                                           
                                        }
                                        if(arr[a+1][0]==sph[e][0] && arr[a+1][1]==sph[e][1])
                                        {
                                            d=e;
                                           
                                        }
                                    }
                                    for(b=0;b<wa;b=b+3)
                                    {
                                        if((temp1[b]==c && temp1[b+1]==d) || (temp1[b]==d && temp1[b+1]==c))
                                        {
                                            temp1[b]=-1,temp1[b+1]=-1;
                                            flka=1;
                                            break;
                                        }
                                        else
                                        {
                                            flka=0;
                                            
                                        }
                                        
                                    }
                                    if(flka==0)
                                        break;
                                    
                                }
                                int count=0;
                                if(flka==1)
                                {
                                    for(a=0;a<wa;a++)
                                    {
                                        if(temp1[a]==-1)
                                            count+=1;
                                    }
                                }
                                int qw=0;
                                for(a=wa;a<200;a++)
                                {
                                    if(box[tv][a]!=-1)
                                    {
                                        int re=box[tv][a];
                                        if(sph[re][2]==0)
                                            qw=1;
                                    }
                                }
                                
                                for(a=0;a<200;a++)
                                    temp1[a]=-1;
                                
                                if(count==wa && qw==0 && flka!=0)
                                {
                                    te1=1;
                                    break;
                                }
                                
                            }
                       //     cout<<"tv111 "<<tv<<endl;

                            if(te1==0)
                            {
                                if(z<=4)
                                    z=0;
                                else
                                    z=z-4;
                                sph[cv][2]=0;
                                int aaa;
                                if(pos==0)
                                    aaa=2;
                                else
                                    aaa=1;
                                cout<<"Player"<<" "<<aaa<<" "<<"won the game\n";
                                exit(0);


                            }
                            else
                            {
                             //   cout<<"tv"<<tv<<endl;
                                myDisplay();
                                cin.ignore();
                                int tr=child[tv][0],max=uti[tr][1-pos],a,bel=tr;
                                if(tr==-1)
                                {
                                    int aaa;
                                    out=1;
                                    cout<<"GAME OVER"<<endl;
                                    if(pos==0)
                                    aaa=1;
                                    else
                                    aaa=2;
                                    cout<<"Player"<<" "<<aaa<<" "<<"won the game\n";
                                    exit(0);
                                    break;
                                }
                                for(a=0;a<10;a++)
                                {
                                    tr=child[tv][a];
                                    if(max<uti[tr][1-pos])
                                    {
                                        max=uti[tr][1-pos];
                                        bel=tr;
                                    }
                                }
                         //       cout<<"bel"<<bel<<endl;
                                for(tr=0;tr<5000;tr++)
                                    for(a=0;a<4;a++)
                                        arr[tr][a]=-1;
                                int wa=0;
                                for(wa=0;wa<200;wa=wa+3)
                                {
                                    if(box[bel][wa+1]==-1)
                                        break;
                                }
                                for(a=0;a<1000;a++)
                                {
                                    if(a==2 && sph[a][2]==1)
                                        continue;
                                    else if (a==7 && sph[a][7]==1)
                                        continue;
                                    sph[a][2]=0;
                                }
                                z=0;
                                
                                for(a=0;a<wa;a=a+3)
                                {
                                    int it=box[bel][a];
                                    arr[z][0]=sph[it][0], arr[z][1]=sph[it][1];
                                    z++;
                                    sph[it][2]=1;
                                    int it1=box[bel][a+1];
                                    arr[z][0]=sph[it1][0], arr[z][1]=sph[it1][1];
                                    z++;
                                    sph[it1][2]=1;
                          //          cout<<it<<" w "<<it1<<endl;
                                    if(it==it1 && it==0)
                                        sph[2][2]=1;
                                    if(it==it1 && it==1)
                                        sph[7][2]=1;
                                    
                                }
                                
                                for(a=wa;a<200;a++)
                                {
                                    if(box[bel][a]!=-1)
                                    {
                                        int it=box[bel][a];
                                        sph[it][2]=1;
                                    }
                                }
                                out=1;
                            /*  tr=child[bel][0];
                                if(tr==-1)
                                {
                                    out=1;
                                    cout<<"GAME OVER"<<endl;
                               //     cout<<"Entered";
                                    cout<<"Player2 won the game\n";
                                    cin.ignore();
                                    exit(0);
                                    break;
                                }*/
                                
                            }
                            if(out==1)
                                break;
                            
                        }
                    }
                    if(out==1)
                        break;
                }
            }
            if(te==0)
                z--;
            flag=0;
        }
    }
}


void myPressedMove(int x,int y)
{
    if(flag)
    {
        temp[0]=getOpenGLX(x);
        temp[1]=getOpenGLY(y);
         if(temp[0]>325)
         {
         fl1=1;
         }
         else
             fl2=1;
        if(temp[0]<sph[15][0] && temp[0]>sph[13][0])
        {
            fl4=1;
        }
        else if(temp[0]>sph[15][0])
        {
            fl5=1;
        }
        else
        {
            fl6=1;
        }
        if(temp[1]>sph[15][1])
        {
            fl8=1;
        }
        else
            fl7=1;
        
    }
}



void myTimer(int t)
{
    glutTimerFunc(100,myTimer,0);
    myDisplay();
}

int main( int argc, char ** argv)
{
     srand(time(NULL));
     int ran = rand() % 2;
     if(ran==0)
     pos=0;
     else
     pos=1;
     
    if(pos==0)
     cout<<"You are player 1\n";
     else
     cout<<"You are player2\n";
    cout<<"Press 'Enter' for the other Player to play\n";
    int i,j;
    for(i=0;i<5000;i++)
        for(j=0;j<4;j++)
            arr[i][j]=-1;
    
    for(i=0;i<50;i++)
        for(j=0;j<200;j++)
            box[i][j]=-1;
    for(i=0;i<100;i++)
    {
        for(j=0;j<10;j++)
        {
            uti[i][j]=-1;
            child[i][j]=-1;
            mid[i][j]=-1;
        }
    }
    for(i=0;i<1000;i++)
    {
        for(j=0;j<3;j++)
        {
            sph[i][j]=-1;
        }
    }
    if(1)
    {
    //* Intializing mid array
    
                mid[0][0]=1,mid[0][1]=1,mid[0][2]=7;
                mid[1][0]=0,mid[1][1]=0,mid[1][2]=2;
                mid[2][0]=0,mid[2][1]=2,mid[2][2]=12;
                mid[3][0]=0,mid[3][1]=2,mid[3][2]=3;
                mid[4][0]=2,mid[4][1]=3,mid[4][2]=14;
                mid[5][0]=1,mid[5][1]=2,mid[5][2]=14;
                mid[6][0]=1,mid[6][1]=13,mid[6][2]=15;
                mid[7][0]=7,mid[7][1]=13,mid[7][2]=14;
                mid[8][0]=1,mid[8][1]=7,mid[8][2]=11;
                mid[9][0]=1,mid[9][1]=7,mid[9][2]=9;
                mid[10][0]=1,mid[10][1]=14,mid[10][2]=16;
                mid[11][0]=13,mid[11][1]=14,mid[11][2]=15;
                mid[12][0]=1,mid[12][1]=15,mid[12][2]=18;
                mid[13][0]=1,mid[13][1]=15,mid[13][2]=20;
                mid[14][0]=0,mid[14][1]=1,mid[14][2]=4;
                mid[15][0]=0,mid[15][1]=1,mid[15][2]=15;
                mid[16][0]=0,mid[16][1]=1,mid[16][2]=13;
                mid[17][0]=2,mid[17][1]=15,mid[17][2]=3;
                mid[18][0]=1,mid[18][1]=3,mid[18][2]=14;
                mid[19][0]=0,mid[19][1]=13,mid[19][2]=21;
                mid[20][0]=13,mid[20][1]=15,mid[20][2]=20;
                mid[21][0]=4,mid[21][1]=15,mid[21][2]=18;
                mid[22][0]=14,mid[22][1]=7,mid[22][2]=8;
                mid[23][0]=21,mid[23][1]=15,mid[23][2]=3;
                mid[24][0]=2,mid[24][1]=7,mid[24][2]=14;
                mid[25][0]=2,mid[25][1]=13,mid[25][2]=14;

                
                
                //* Initializing the child array
                
                child[1][0]=2,child[1][1]=3;
                child[2][0]=4,child[2][1]=5,child[2][2]=6,child[2][3]=7;
                child[3][0]=7,child[3][1]=8,child[3][2]=9;
                child[4][0]=10,child[4][1]=11;
                child[5][0]=11,child[5][1]=12,child[5][2]=13;
                child[6][0]=12;
                child[7][0]=13,child[7][1]=14,child[7][2]=15,child[7][3]=16;
                child[8][0]=16,child[8][1]=17;
                child[9][0]=17,child[9][1]=18;
                child[10][0]=19,child[10][1]=20;
                child[11][0]=20,child[11][1]=21,child[11][2]=22;
                child[12][0]=22,child[12][1]=23;
                child[13][0]=24,child[13][1]=25;
                child[14][0]=25,child[14][1]=26;
                child[15][0]=27,child[15][1]=28;
                child[16][1]=28,child[16][1]=29,child[16][2]=30;
                child[17][0]=31,child[17][1]=32,child[17][2]=33;
                child[18][0]=34,child[18][1]=35;
                child[19][0]=36;
                child[20][0]=37;
                child[21][0]=38;
                child[24][0]=39;
                child[25][0]=40;
                child[26][0]=41;
                child[27][0]=42;
                child[28][0]=43;
                child[29][0]=44;
                child[31][0]=45;
                child[32][0]=46;
                
                //* Initializing the utility array
                
                uti[2][0]=9,uti[2][1]=3;
                uti[3][0]=8,uti[3][1]=4;
                uti[4][0]=3,uti[4][1]=1;
                uti[5][0]=4,uti[5][1]=2;
                uti[6][0]=0,uti[6][1]=2;
                uti[7][0]=6,uti[7][1]=1;
                uti[8][0]=4,uti[8][1]=2;
                uti[9][0]=2,uti[9][1]=3;
                uti[10][0]=2,uti[10][1]=0;
                uti[11][0]=2,uti[11][1]=1;
                uti[12][0]=0,uti[12][1]=2;
                uti[13][0]=2,uti[13][1]=0;
                uti[14][0]=2,uti[14][1]=0;
                uti[15][0]=2,uti[15][1]=0;
                uti[16][0]=2,uti[16][1]=1;
                uti[17][0]=2,uti[17][1]=1;
                uti[18][0]=0,uti[18][1]=2;
                
                // * Initializing the sphere array
                
                sph[0][0] = 300.0  , sph[0][1] = 400.0,sph[0][2] = 1;
                sph[1][0] = 300.0  , sph[1][1] = 200.0,sph[1][2] = 1;
                sph[2][0] = 300.0  , sph[2][1] = 500.0,sph[2][2] = 0;
                sph[3][0] = 400.0  , sph[3][1] = 450.0,sph[3][2] = 0;
                sph[4][0] = 350.0  , sph[4][1] = 325.0,sph[4][2] = 0;
                sph[5][0] = 350.0  , sph[5][1] = 200.0,sph[5][2] = 0;
                sph[6][0] = 330.0  , sph[6][1] = 230.0,sph[6][2] = 0;
                sph[7][0] = 300.0  , sph[7][1] = 100.0,sph[7][2] = 0;
                sph[8][0] = 450.0  , sph[8][1] = 200.0,sph[8][2] = 0;
                sph[9][0] = 500.0  , sph[9][1] = 300.0,sph[9][2] = 0;
                sph[10][0]= 500.0  , sph[10][1]= 375.0,sph[10][2] = 0;
                sph[11][0]= 300.0  , sph[11][1]= 150.0,sph[11][2] = 0;
                sph[12][0]= 300.0  , sph[12][1]= 450.0,sph[12][2] = 0;
                sph[13][0]= 250.0  , sph[13][1]= 300.0,sph[13][2] = 0;
                sph[14][0]= 550.0  , sph[14][1]= 300.0,sph[14][2] = 0;
                sph[15][0]= 425.0  , sph[15][1]= 300.0,sph[15][2] = 0;
                sph[16][0]= 425.0  , sph[16][1]= 250.0,sph[16][2]=0;
                sph[17][0]= 400.0  , sph[17][1]= 125.0,sph[17][2]=0;
                sph[18][0]= 362.5  , sph[18][1]= 250.0,sph[18][2]=0;
                sph[19][0]= 340.0  , sph[19][1]= 280.0,sph[19][2]=0;
                sph[20][0]= 300.0  , sph[20][1]= 50.0,sph[20][2]=0;
                sph[21][0]= 300.0  , sph[21][1]= 550.0,sph[21][2]=0;
                spind=22;
                
                // * Initializing the box array
                ptr=1;
                box[1][0] = 0 , box[1][1] = -1 , box[1][2] = 1 ;
                ptr=2;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1  ;
                ptr=4;
                box[4][0] = 0 , box[4][1] = 0 , box[4][2] = -1 , box[4][3] = 0 , box[4][4] = 3 , box[4][5] = -1 , box[4][6] = 2 , box[4][7] = 3 ,  box[4][8] = -1 , box[4][9] = 1  ;
                box[10][0] = 0 , box[10][1] = 0 , box[10][2] = -1 , box[10][3] = 0 , box[10][4] = 3 , box[10][5] = -1 , box[10][6] = 2 , box[10][7] = 3 ,  box[10][8] = -1 , box[10][9] = 1 , box[10][10] = 4 , box[10][11] = -1 , box[10][12] = 3 , box[10][13]=4    ;
                box[19][0] = 0 , box[19][1] = 0 , box[19][2] = -1 , box[19][3] = 0 , box[19][4] = 3 , box[19][5] = -1 , box[19][6] = 2 , box[19][7] = 3 ,  box[19][8] = -1 , box[19][9] = 1 , box[19][10] = 4 , box[19][11] = -1 , box[19][12] = 3 , box[19][13]=4 , box[19][14]=-1 ,box[19][15]=1 , box[19][16]=5 , box[19][17]=-1 , box[19][18]=4 , box[19][19]=5 , box[19][20]=-1 ;
                ptr=36;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 0 , box[ptr][4] = 3 , box[ptr][5] = -1 , box[ptr][6] = 2 , box[ptr][7] = 3 ,  box[ptr][8] = -1 , box[ptr][9] = 1 , box[ptr][10] = 4 , box[ptr][11] = -1 , box[ptr][12] = 3 , box[ptr][13]=4 , box[ptr][14]=-1 ,box[ptr][15]=1 , box[ptr][16]=5 , box[ptr][17]=-1 , box[ptr][18]=4 , box[ptr][19]=5 , box[ptr][20]=-1 , box[ptr][21] = 1 , box[ptr][22] = 6 , box[ptr][23] = -1,box[ptr][24] = 5 , box[ptr][25] = 6 , box[ptr][26] = -1;
                ptr=5;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 1 ;
                ptr=11;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 0 , box[ptr][4] = 3 , box[ptr][5] = -1 , box[ptr][6] = 2 , box[ptr][7] = 3 ,  box[ptr][8] = -1 , box[ptr][9] = 1 , box[ptr][10]=1 ;
                ptr=20;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 0 , box[ptr][4] = 3 , box[ptr][5] = -1 , box[ptr][6] = 2 , box[ptr][7] = 3 ,  box[ptr][8] = -1 , box[ptr][9] = 1 , box[ptr][10]=1 ,box[ptr][11]=-1 ,  box[ptr][12] = 1 , box[ptr][13] = 14 , box[ptr][14] = -1 ,  box[ptr][15] = 3 , box[ptr][16] = 14 ;
                ptr=37;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 0 , box[ptr][4] = 3 , box[ptr][5] = -1 , box[ptr][6] = 2 , box[ptr][7] = 3 ,  box[ptr][8] = -1 , box[ptr][9] = 1 , box[ptr][10]=1 ,box[ptr][11]=-1 ,  box[ptr][12] = 1 , box[ptr][13] = 14 , box[ptr][14] = -1 ,  box[ptr][15] = 3 , box[ptr][16] = 14 , box[ptr][17]= -1 , box[ptr][18] = 7 , box[ptr][19] = 8 , box[ptr][20] = -1 , box[ptr][21] = 14 , box[ptr][22] = 8 ;
                ptr=21;
                int ii=0;
                box[ptr][ii++] = 0 , box[ptr][ii++] = 0 , box[ptr][ii++] = -1 , box[ptr][ii++] = 0 , box[ptr][ii++] = 3 , box[ptr][ii++] = -1 , box[ptr][ii++] = 2 , box[ptr][ii++] = 3 ,  box[ptr][ii++] = -1 , box[ptr][ii++] = 1 , box[ptr][ii++]=1 , box[ptr][ii++]=-1 , box[ptr][ii++] = 1 , box[ptr][ii++] = 9 , box[ptr][ii++] = -1 , box[ptr][ii++] = 7 , box[ptr][ii++] = 9   ;
                ptr=38;
                ii=0;
                box[ptr][ii++] = 0 , box[ptr][ii++] = 0 , box[ptr][ii++] = -1 , box[ptr][ii++] = 0 , box[ptr][ii++] = 3 , box[ptr][ii++] = -1 , box[ptr][ii++] = 2 , box[ptr][ii++] = 3 ,  box[ptr][ii++] = -1 , box[ptr][ii++] = 1 , box[ptr][ii++]=1 , box[ptr][ii++]=-1 , box[ptr][ii++] = 1 , box[ptr][ii++] = 9 , box[ptr][ii++] = -1 , box[ptr][ii++] = 7 , box[ptr][ii++] = 9 , box[ptr][ii++] = -1 , box[ptr][ii++] = 3 , box[ptr][ii++] = 10 , box[ptr][ii++] = -1  , box[ptr][ii++] = 9 , box[ptr][ii++] = 10  ;
                ptr=12;
                ii=0;
                box[ptr][ii++] = 0 , box[ptr][ii++] = 0 , box[ptr][ii++] = -1 , box[ptr][ii++] = 1 , box[ptr][ii++] = 1 , box[ptr][ii++] = -1 , box[ptr][ii++] = 0 , box[ptr][ii++] = 12 , box[ptr][ii++] = -1 , box[ptr][ii++] = 2 , box[ptr][ii++] = 12 ;
                ptr=22;
                ii=0;
                box[ptr][ii++] = 0 , box[ptr][ii++] = 0 , box[ptr][ii++] = -1 , box[ptr][ii++] = 1 , box[ptr][ii++] = 1 , box[ptr][ii++] = -1 , box[ptr][ii++] = 0 , box[ptr][ii++] = 3 , box[ptr][ii++] = -1 , box[ptr][ii++] = 2 , box[ptr][ii++] = 3 , box[ptr][ii++] = -1 ,box[ptr][ii++] = 1 , box[ptr][ii++] = 11 , box[ptr][ii++] = -1 ,box[ptr][ii++] = 7 , box[ptr][ii++] = 11;
                ptr=23;
                ii=0;
                box[ptr][ii++] = 0 , box[ptr][ii++] = 0 , box[ptr][ii++] = -1 , box[ptr][ii++] = 1 , box[ptr][ii++] = 1 , box[ptr][ii++] = -1 , box[ptr][ii++] = 0 , box[ptr][ii++] = 12 , box[ptr][ii++] = -1 , box[ptr][ii++] = 2 , box[ptr][ii++] = 12 , box[ptr][ii++] = -1 ,box[ptr][ii++] = 1 , box[ptr][ii++] = 11 , box[ptr][ii++] = -1 ,box[ptr][ii++] = 7 , box[ptr][ii++] = 11;
                ptr=6;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3]=0 , box[ptr][4]=12 , box[ptr][5]=-1 , box[ptr][6]=2 , box[ptr][7]= 12 , box[ptr][8]=-1, box[ptr][9] = 1  ;
                ptr=7;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 13  ;
                ptr=13;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 13 , box[ptr][8] = -1 ,box[ptr][9] = 1 , box[ptr][10] = 1 ;
                ptr=24;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 13 , box[ptr][8]=-1 ,  box[ptr][9] = 2, box[ptr][10] = 14 , box[ptr][11]=-1 ,  box[ptr][12] = 7 , box[ptr][13] = 14 , box[ptr][14] = -1 ,box[ptr][15] = 1 , box[ptr][16] = 1  ;
                ptr=39;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 13 , box[ptr][8]=-1 ,  box[ptr][9] = 2, box[ptr][10] = 14 , box[ptr][11]=-1 ,  box[ptr][12] = 7 , box[ptr][13] = 14 , box[ptr][14]=-1 , box[ptr][15] = 13, box[ptr][16] = 15 , box[ptr][17]=-1 , box[ptr][18] = 14, box[ptr][19] = 15 ,box[ptr][20] = -1 , box[ptr][21] = 1 , box[ptr][22] = 1  ;
                ptr=3;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13  ;
                ptr=14;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 13 , box[ptr][8]=-1, box[ptr][9] = 13 , box[ptr][10] = 14 , box[ptr][11] = -1, box[ptr][12] = 2 , box[ptr][13] = 14 ;
                ptr=25;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 13 , box[ptr][8]=-1, box[ptr][9] = 13 , box[ptr][10] = 14 , box[ptr][11] = -1, box[ptr][12] = 2 , box[ptr][13] = 14 , box[ptr][14] = -1 , box[ptr][15] = 1 , box[ptr][16] = 1;
                ptr=40;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 13 , box[ptr][8]=-1, box[ptr][9] = 13 , box[ptr][10] = 14 , box[ptr][11] = -1, box[ptr][12] = 2 , box[ptr][13] = 14 , box[ptr][14] = -1 , box[ptr][15] = 1 , box[ptr][16] = 1 ,box[ptr][17] = -1, box[ptr][18] = 7 , box[ptr][19] = 16 , box[ptr][20] = -1 , box[ptr][21] = 16 , box[ptr][22] = 14 ;
                ptr= 26;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 13 , box[ptr][8]=-1, box[ptr][9] = 13 , box[ptr][10] = 14 , box[ptr][11] = -1, box[ptr][12] = 2 , box[ptr][13] = 14 , box[ptr][14] = -1 , box[ptr][15]= 1 , box[ptr][16]=8 , box[ptr][17] = -1 , box[ptr][18] = 14 , box[ptr][19]=8;
                ptr=41;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 13 , box[ptr][8]=-1, box[ptr][9] = 13 , box[ptr][10] = 14 , box[ptr][11] = -1, box[ptr][12] = 2 , box[ptr][13] = 14 , box[ptr][14] = -1 , box[ptr][15]= 1 , box[ptr][16]=16 , box[ptr][17] = -1 , box[ptr][18] = 14 , box[ptr][19]=16 , box[ptr][20]=-1 , box[ptr][21]= 1 , box[ptr][22]=17 , box[ptr][23] = -1 , box[ptr][24] = 16 , box[ptr][25]=17;
                ptr=15;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 13  , box[ptr][8] = -1 , box[ptr][9]=2 , box[ptr][10]=14 , box[ptr][11]=-1 , box[ptr][12]=1 , box[ptr][13]=14  ;
                ptr=27;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 13  , box[ptr][8] = -1 , box[ptr][9]=2 , box[ptr][10]=14 , box[ptr][11]=-1 , box[ptr][12]=1 , box[ptr][13]=14 ,box[ptr][14]=-1 , box[ptr][15]=13, box[ptr][16]=15 ,box[ptr][17]=-1 , box[ptr][18]=14 , box[ptr][19]=15   ;
                ptr=42;
                box[ptr][0] = 0 , box[ptr][1] = 0 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 13  , box[ptr][8] = -1 , box[ptr][9]=2 , box[ptr][10]=14 , box[ptr][11]=-1 , box[ptr][12]=1 , box[ptr][13]=14 ,box[ptr][14]=-1 , box[ptr][15]=13, box[ptr][16]=15 ,box[ptr][17]=-1 , box[ptr][18]=14 , box[ptr][19]=15  , box[ptr][20] = -1 , box[ptr][21] = 1 , box[ptr][22] = 18 , box[ptr][23] = -1 , box[ptr][24] = 15  , box[ptr][25] = 18 ;
                ptr=8;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 21 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 21;
                ptr=16;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 1 , box[ptr][7] = 15 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 15, box[ptr][11] = -1 , box[ptr][12] = 0 , box[ptr][13] = 0 ;
                ptr=28;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 1 , box[ptr][7] = 15 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 15, box[ptr][11] = -1 , box[ptr][12] = 0 , box[ptr][13] = 0 , box[ptr][14] = -1 , box[ptr][15] = 15 , box[ptr][16] = 3 , box[ptr][17] = -1 , box[ptr][18] = 2 , box[ptr][19] = 3 ;
                ptr=43;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 1 , box[ptr][7] = 15 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 15, box[ptr][11] = -1 , box[ptr][12] = 0 , box[ptr][13] = 0 , box[ptr][14] = -1 , box[ptr][15] = 15 , box[ptr][16] = 3 , box[ptr][17] = -1 , box[ptr][18] = 2 , box[ptr][19] = 3 , box[ptr][20] = -1 , box[ptr][21] = 1 , box[ptr][22] = 14 , box[ptr][23] = -1 , box[ptr][24] = 3 , box[ptr][25] = 14 ;
                ptr=29;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 1 , box[ptr][7] = 15 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 15, box[ptr][11] = -1 , box[ptr][12] = 0 , box[ptr][13] = 0 , box[ptr][14] = -1 , box[ptr][15] = 1 , box[ptr][16] = 16 , box[ptr][17] = -1 , box[ptr][18] = 15 , box[ptr][19] = 16 ;
                ptr=44;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 1 , box[ptr][7] = 15 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 15, box[ptr][11] = -1 , box[ptr][12] = 0 , box[ptr][13] = 0 , box[ptr][14] = -1 , box[ptr][15] = 1 , box[ptr][16] = 16 , box[ptr][17] = -1 , box[ptr][18] = 15 , box[ptr][19] = 16 , box[ptr][20] = -1 , box[ptr][21] = 16 , box[ptr][22] = 3 , box[ptr][23] = -1 , box[ptr][24] = 2 , box[ptr][25] = 3 ;
                ptr=30;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 1 , box[ptr][7] = 15 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 15, box[ptr][11] = -1 , box[ptr][12] = 0 , box[ptr][13] = 0 , box[ptr][14] = -1 , box[ptr][15] = 1 , box[ptr][16] = 19 , box[ptr][17] = -1 , box[ptr][18] = 15 , box[ptr][19] = 19 ;
                ptr=17;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 21 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 21 ,  box[ptr][11] = -1 , box[ptr][12] = 1 , box[ptr][13] = 15 ,  box[ptr][14] = -1 , box[ptr][15] = 0 , box[ptr][16] = 15 ;
                ptr=31;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 21 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 21 ,  box[ptr][11] = -1 , box[ptr][12] = 1 , box[ptr][13] = 15 ,  box[ptr][14] = -1 , box[ptr][15] = 0 , box[ptr][16] = 15 , box[ptr][17] = -1 , box[ptr][18] = 15 , box[ptr][19] = 3 , box[ptr][20] = -1 , box[ptr][21] = 21 , box[ptr][22] = 3 ;
                ptr=45;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 21 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 21 ,  box[ptr][11] = -1 , box[ptr][12] = 1 , box[ptr][13] = 15 ,  box[ptr][14] = -1 , box[ptr][15] = 0 , box[ptr][16] = 15 , box[ptr][17] = -1 , box[ptr][18] = 15 , box[ptr][19] = 3 , box[ptr][20] = -1 , box[ptr][21] = 21 , box[ptr][22] = 3 , box[ptr][23] = -1 , box[ptr][24] = 1 , box[ptr][25] = 14 , box[ptr][26] = -1 , box[ptr][27] = 3 , box[ptr][28] = 14;
                ptr=32;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 21 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 21 ,  box[ptr][11] = -1 , box[ptr][12] = 1 , box[ptr][13] = 15 ,  box[ptr][14] = -1 , box[ptr][15] = 0 , box[ptr][16] = 15 ,  box[ptr][17] = -1 , box[ptr][18] = 1 , box[ptr][19] = 20 ,  box[ptr][20] = -1 , box[ptr][21] = 15 , box[ptr][22] = 20;
                ptr=46;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 21 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 21 ,  box[ptr][11] = -1 , box[ptr][12] = 1 , box[ptr][13] = 15 ,  box[ptr][14] = -1 , box[ptr][15] = 0 , box[ptr][16] = 15 ,  box[ptr][17] = -1 , box[ptr][18] = 1 , box[ptr][19] = 20 ,  box[ptr][20] = -1 , box[ptr][21] = 15 , box[ptr][22] = 20 , box[ptr][23] = -1 , box[ptr][24] = 21 , box[ptr][25] = 14,box[ptr][26] = -1 , box[ptr][27] = 20 , box[ptr][28] = 14;
                ptr=33;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 0 , box[ptr][7] = 21 , box[ptr][8] = -1, box[ptr][9] = 13 , box[ptr][10] = 21 ,  box[ptr][11] = -1 , box[ptr][12] = 1 , box[ptr][13] = 15 ,  box[ptr][14] = -1 , box[ptr][15] = 0 , box[ptr][16] = 15 ,  box[ptr][17] = -1 , box[ptr][18] = 1 , box[ptr][19] = 19 ,  box[ptr][20] = -1 , box[ptr][21] = 15 , box[ptr][22] = 19;
                ptr=9;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 1 , box[ptr][7] = 15 , box[ptr][8] = -1 , box[ptr][9] = 0 , box[ptr][10] = 15  ;
                ptr=18;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 1 , box[ptr][7] = 15 , box[ptr][8] = -1 , box[ptr][9] = 0 , box[ptr][10] = 15 ,  box[ptr][11] = -1 , box[ptr][12] = 0 , box[ptr][13] = 4 ,  box[ptr][14] = -1 , box[ptr][15] = 1 , box[ptr][16] = 4 ;
                ptr=34;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 1 , box[ptr][7] = 15 , box[ptr][8] = -1 , box[ptr][9] = 0 , box[ptr][10] = 15 ,  box[ptr][11] = -1 , box[ptr][12] = 0 , box[ptr][13] = 4 ,  box[ptr][14] = -1 , box[ptr][15] = 1 , box[ptr][16] = 4 ,  box[ptr][17] = -1 , box[ptr][18] = 13 , box[ptr][19] = 20 ,  box[ptr][20] = -1 , box[ptr][21] = 20 , box[ptr][22] = 15;
                ptr=35;
                box[ptr][0] = 0 , box[ptr][1] = 13 , box[ptr][2] = -1 , box[ptr][3] = 1 , box[ptr][4] = 13 , box[ptr][5] = -1 , box[ptr][6] = 1 , box[ptr][7] = 15 , box[ptr][8] = -1 , box[ptr][9] = 0 , box[ptr][10] = 15 ,  box[ptr][11] = -1 , box[ptr][12] = 0 , box[ptr][13] = 4 ,  box[ptr][14] = -1 , box[ptr][15] = 1 , box[ptr][16] = 4 ,  box[ptr][17] = -1 , box[ptr][18] = 1 , box[ptr][19] = 18 ,  box[ptr][20] = -1 , box[ptr][21] = 18 , box[ptr][22] = 15;
                
    }
    
    
    glutInit( &argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowPosition( 100, 100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Sprouts");
    init();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouseStat);
    glutMotionFunc(myPressedMove);
    glutTimerFunc(100,myTimer,0);
    glutMainLoop();
    
    return 0;
}
