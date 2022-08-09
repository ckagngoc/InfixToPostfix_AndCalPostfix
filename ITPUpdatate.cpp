#include <stdio.h>

void xuly(){
    int k = 0;
    int dem = 0;
    int a = 1;
    int b = 0;
    int c = 0;
    int d = 0;
    for(a = 1;a<10;a++){
        for(b = 0;b<10;b++){
            for(c = 0;c<10;c++){
                for(int d = 0;d<10;d++){
                    if((a+b+c+d)%3 == 0){
                        if(k = 0) printf("so nho nhat thoa man la: %d%d%d%d",a,b,c,d);
                        k = 1;
                        dem++;
                    }
                }
            }
        }
    }
    printf("So cac so thoa man la: %d",dem);
}


int main(){
    xuly();
    return 0;
}