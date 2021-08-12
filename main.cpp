#include <iostream>
#include <fstream>
using namespace std;




struct block
{
 int item[10];
 bool used[10];
 int horizontal[3][10];
 int vertical [3][10];

 int nusd=9;
};

struct square
{
    bool filled;
    bool possible[10];
    bool checked[10];
    int nrpos=9;
    int present;


};

struct sudoku
{
    int sqrsfill;

 int rows[9][10];
 int colls[9][10];
    block table[3][3];
    square gtb[9][9];

};
sudoku gm;


void clear_rc(int n)
{
for(int s=0;s<10;s++)
for (int i=0;i<n;i++)
    {
        gm.colls[i][s]=0;
        gm.rows[i][s]=0;
    }
}


void clear_hvector(int n,int s)
{

    for(int i=0;i<3;i++)
for(int j=0;j<3;j++)
{
    for(int line=0;line<3;line++)
    gm.table[i][j].horizontal[line][s]=0;

}

}


void check_horizontal(int n)
{


    for(int s=1;s<10;s++)
{
clear_hvector(n,s);

for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
{
    if(!gm.gtb[i][j].possible[s])
   gm.table[i/3][j/3].horizontal[i-(i/3)*3][s]++;

}

for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
{
    if(gm.table[i/3][j/3].horizontal[i-(i/3)*3][s]==1)
   gm.table[i/3][j/3].horizontal[i-(i/3)*3][s]=0;

}


}




}

void clear_vvector(int n, int s)
{


    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            for(int row=0;row<3;row++)
             gm.table[i][j].vertical[row][s]=0;

    }
}


void check_vertical(int n)
{

    for(int s=1;s<10;s++)
    {
        clear_vvector(n,s);

        for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
{
    if(!gm.gtb[i][j].possible[s])
   gm.table[i/3][j/3].vertical[j-(j/3)*3][s]++;

}

for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
{
    if(gm.table[i/3][j/3].vertical[j-(j/3)*3][s]==1)
   gm.table[i/3][j/3].vertical[j-(j/3)*3][s]=0;

}



    }

}


void clear_item(int n)
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        for(int s=1;s<10;s++)
        if(gm.table[i][j].item[s]!=9)gm.table[i][j].item[s]=0;


}



void set(int x,int y,int n)
{

for(int i=0;i<n;i++)
{
    gm.gtb[y][x].possible[gm.gtb[i][x].present]=true;
    gm.gtb[y][x].possible[gm.gtb[y][i].present]=true;

}




int st=0, inm=0;
for(int i=1;i<10;i++)
   {


    if(gm.table[y/3][x/3].used[i])
    {
        gm.gtb[y][x].possible[i]=true;
    }

    if(gm.gtb[y][x].possible[i])
        {gm.table[y/3][x/3].item[i]++;
         gm.rows[y][i]++;
         gm.colls[x][i]++;
        }




 }








}

int set2(int x,int y,int  n)
{
int ok=0;
for(int k=1;k<10;k++)
        if((!gm.gtb[y][x].possible[k] && gm.table[y/3][x/3].item[k]==8  && !gm.gtb[y][x].filled)||(!gm.gtb[y][x].possible[k] && gm.rows[y][k]==8 && !gm.gtb[y][x].filled) || (!gm.gtb[y][x].possible[k] && gm.colls[x][k]==8 && !gm.gtb[y][x].filled) )
    {

        gm.table[y/3][x/3].used[k];
        for(int i=(y/3)*3;i<(y/3)*3+3;i++)
        {
            for(int j=(x/3)*3;j<(x/3)*3+3;j++)
                gm.gtb[i][j].possible[k]=true;
        }
        for(int s=1;s<10;s++)
            gm.gtb[y][x].possible[s]=true;
        gm.gtb[y][x].present=k;
        gm.sqrsfill++;
        gm.gtb[y][x].filled=true;
        ok=1;
    }



    return ok;


}

void setvh(int n){

for(int nmb=1;nmb<10;nmb++)
for(int i=0;i<3;i++)
for(int j=0;j<3;j++)
{
    for(int row=0;row<3;row++)
        if(gm.table[i][j].horizontal[row][nmb]==9-gm.table[i][j].item[nmb] && gm.table[i][j].horizontal[row][nmb]>1)
    {



        for(int nx=0;nx<n;nx++)
        {
            if(nx<j*3||nx>j*3+2)
            {
                gm.gtb[i*3+row][nx].possible[nmb]=true;
            }
        }
    }
for(int col=0;col<3;col++)
    if(gm.table[i][j].vertical[col][nmb]==9-gm.table[i][j].item[nmb] && gm.table[i][j].vertical[col][nmb]>1)
{
    for(int ny=0;ny<n;ny++)
    {
    if(ny<i*3||ny>i*3+2)
       gm.gtb[ny][j*3+col].possible[nmb]=true;

    }

}


}







}

void show(int n)
{
    for(int i=0;i<n;i++)
    {for(int j=0;j<n;j++)
          cout<<gm.gtb[i][j].present<<" ";
          cout<<endl;
    }
}


int main()
{

ifstream game("game.txt");
ofstream solve("solve.txt");

int n=0;
game>>n;
n=n*n;

for(int i=0;i<n;i++)
{
    for(int j =0;j<n;j++)
    {   int nr=0;
        game>>nr;
        gm.gtb[i][j].present=nr;
        if(nr!=0)
            {gm.gtb[i][j].filled=true;
             for(int rt=1;rt<10;rt++)
             {
                 gm.table[i/3][j/3].item[rt]++;
           gm.gtb[i][j].possible[rt]=true;

             }

 gm.sqrsfill++;
            }
        else
            gm.gtb[i][j].filled=false;
        gm.table[i/3][j/3].used[nr]=true;


    }

}

while(gm.sqrsfill!=81)
{
clear_item(n);
clear_rc(n);

    for(int i=0;i<n;i++)
{
    for(int j =0;j<n;j++)
    {

      set(j,i,n);





    }



}


check_horizontal(n);
check_vertical(n);
setvh(n);



int ok=0;
for(int i=0;i<n && ok==0;i++)
for(int j =0;j<n && ok==0;j++)
   ok=set2(j,i,n);


show(n);
cout<<endl;



}





for(int i=0;i<n;i++)
{
    for(int j =0;j<n;j++)
    {
 solve<<gm.gtb[i][j].present<<" ";
    }
    solve<<endl;

}

solve.close();
game.close();
    return 0;
}
