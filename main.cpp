#include <iostream>
#include <math.h>
#include <graphics.h>
#include <list>
#include <vector>
#include <iomanip> // làm tròn số đến 1 chữa số thập phân
using namespace std;

#define X_AXIS  30
#define Y_AXIS  100
#define epsilon 0.001
list <float> listGiaoDiem;

// VẼ TRỤC TỌA ĐỘ Oxy
void drawxy()
{
    initwindow(800,600);
    /* Draw the axis */
    int cx = getmaxx()/2, cy = getmaxy()/2;
    line(20, cy, getmaxx()-20, cy);
    line(cx, 20, cx, getmaxy()-20);
    outtextxy(cx, cy, "O");
    outtextxy(20, cy, "-30");
    outtextxy(getmaxx()-20, cy, "30");
    outtextxy(cx, 20, "100");
    outtextxy(cx, getmaxy()-20, "-100");

    }

// NHẬP HÀM
void nhapin_ham(int n, float a[]){
    for(int i=0;i<n+1;i++){
    cout<< "he co thu "<<(i+1)<<"= ";
    cin>> a[i];}
    cout<< "- Da thuc la: ";
    for(int i=0;i< n;i++){
    cout <<a[i]<<"*x^"<<(n-i)<<"+";}
    cout << a[n]<<endl;
}


// TÍNH GIÁ TRỊ CỦA HÀM TẠI x
float f(float x,int n, float a[]){
    float y=0;
    for(int i=n;i>=0;i--){
        y+=a[n-i]*pow(x,i);
    }
    return y;}
/*
// TÍNH GIÁ TRỊ ĐẠO HÀM TẠI x
float df(float x, int n, float  a[]){

    float y=0;
    for(int i=n-1;i>=0;i++){

        y+=a[n-1-i]*(i+1)*pow(x,i);
        }return y;
}
*/
// TÍNH NGUYÊN HÀM TẠI x
float F(float x, int n, float a[]){
    float y=0;
    for (int i=n; i>=0;i--){
        y+=a[n-i]*pow(x,i+1)/(i+1);
    }
    return y;
}

//VẼ ĐỒ THỊ
void veDoThi(int n,float a[],float direction, int t){
    setcolor(t);
//    setlinestyle(SOLID_LINE, 0, 2);
    float x = 0, y=0, px, py,cx = getmaxx()/2, cy = getmaxy()/2;

    while (x <= X_AXIS && x >= -X_AXIS) {
        /* Calculate y with given x */
        y=f(x,n,a);
        /* Calculate coordoninates to display */
        px = x * getmaxx()/(2* X_AXIS )+ getmaxx()/2;
        /* -cy because of origin point in window(top left corner) */
        py = -y * getmaxy() /(2*Y_AXIS)  + getmaxy()/2;
        /* in case boundaries are passed */
        if (py < 0 || py > getmaxy()) break;
        if (x == 0) // only for first loop
        moveto(px, py);
        /* Draw segment line */
        lineto(px, py);
        /* update CP */
        moveto(px, py);
        x=x+direction;
    }
}

//HIỆU HAI ĐA THỨC
float Hieu2DaThuc(float x, int n, int m, float A[], float B[])
{
	return f(x,n,A)-f(x,m,B);
}
//GIAO ĐIỂM HAI HÀM TRONG KHOẢNG (a,b)

void toado2ham (int n, int m, float A[], float B[], float a, float b){
    if(Hieu2DaThuc(a,n,m,A,B)==0){
        cout<< "Toa do giao diem la: ("<<a<<","<<f(a,n,A)<<")"<<endl;
        listGiaoDiem.push_back(a);
    }
    if(Hieu2DaThuc(a,n,m,A,B)*Hieu2DaThuc(b,n,m,A,B)<0){
            float c=(a+b)/2,E = fabs(b-a);
            while(E>epsilon){
            if(Hieu2DaThuc(a,n,m,A,B)*Hieu2DaThuc(c,n,m,A,B)<=0)
                b = c;
            else
                a = c;
            E = fabs(b -a);
            c = (b + a)/2;
        }
    cout<< "Toa do giao diem la: ("<<a<<","<<f(a,n,A)<<")"<<endl;
    listGiaoDiem.push_back(a);

    }
}


// TÍNH DIEN TICH
float dientich(int n, float A[]){


    int i;
    float y=0;
    vector <float> listGiao;
    listGiao.push_back(-50);
// TÍNH GIAO ĐIỂM VỚI TRỤC Ox
    for ( i=-50; i<51;i++) {
        if (f(i,n,A)==0) listGiao.push_back(i);
        if(f(i,n,A)*f(i+1,n,A)<0){
            float a=i, b=i+1,c=(a+b)/2,E = fabs(b-a);
            while(E>epsilon){
            if(f(a,n,A)*f(c,n,A)<=0)
                b = c;
            else
                a = c;
            E = fabs(b -a);
            c = (b + a)/2;
        }
    listGiao.push_back(a);
    }
   }
   listGiao.push_back(50);
   for(int i=0; i<listGiao.size()-1;i++){
        y=y+ fabs(F(listGiao[i],n,A)-F(listGiao[i+1],n,A));
   }

    return y;
}

// KIỂM TRA HAI ĐA THỨC CÓ BẰNG NHAU HAY KHÔNG
bool haiHamBangNhau(int n, int m, float A[], float B[]){
    bool flag=true;
    if(n==m){
        for (int i = 0;i < n+1; i++ )
        if(A[i] != B[i]){
            flag= false;
            break;
        }
    }
    else flag=false;
    return flag;
}


// HÀM MAIN
int main(){
    cout << "                  CHAO MUNG BAN DEN VOI CHUONG TRINH "<< endl;
    cout<<"____________________________________________________________________"<< endl;
    int n,m;
    cout<<"- Nhap bac ham thu nhat: ";
    cin>> n;
    float A[n];
    nhapin_ham(n,A);
    cout<<"- Nhap bac ham thu hai: ";
    cin>> m;
    float B[m];
    nhapin_ham(m,B);

 // IN TỌA ĐỘ GIAO ĐIỂM

    if(haiHamBangNhau(n,m,A,B)) cout<<" Hai ham trung nhau :) "<<endl;
    else{
        for(int i=-50; i<51;i++){
            toado2ham(n,m,A,B,i,i+1);
        }
        if(listGiaoDiem.empty()) cout<< "~~~~~Do thi hai ham khong giao nhau :( ~~~~~"<< endl;
    }

// IN DIỆN TÍCH GIAO VỚI TRỤC Ox
    cout<< "Dien tich cua ham thu nhat voi truc Ox (trong khoang -50<x<50): "<<dientich(n,A)<< endl;
    cout<< "Dien tich cua ham thu hai voi truc Ox (trong khoang -50<x<50): "<<dientich(m,B)<< endl;

// IN ĐỒ THỊ
    drawxy();
    veDoThi(n,A,0.005,2);
    veDoThi(n,A,-0.005,2);
    veDoThi(m,B,0.005,3);
    veDoThi(m,B,-0.005,3);
    getch();
    closegraph();
return 0;
}

 /*
    //hihihihhi
   while(fabs(f(a,n,A))>epsilon&& fabs(f(b,n,A))> epsilon&& (b-a)>epsilon){
            if(f(a,n,A)*f(c,n,A)<0) b=c;
            else a=c;
        }
        if(fabs(f(a,n,A))<=epsilon) listGiao.push_back(a);
        else listGiao.push_back(b); */
