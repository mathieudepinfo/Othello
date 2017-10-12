#include <iostream>
#include <vector>

using namespace std;
int main(){

    /*for(int i(0);i<10;i++){
        i=i+10;
        cout<< i;
    }
    vector<int> v;
    int x=1;
    v.push_back(x);

    unsigned int a(40000000);
    unsigned short x=(unsigned short)a;
    cout<<a<<" "<<x<<"\n";
    */
    unsigned int x;
    srand (time(NULL));
    int seeds[8][8][2];
    for (int i(0);i<4;i++){

        for(int j(0);j<4;j++){
            for(int k(0);k<2;k++){
                x=(unsigned int)rand();
                seeds[i][j][k]=x;
                seeds[7-i][j][k]=x;
                seeds[7-i][7-j][k]=x;
                seeds[i][7-j][k]=x;
            }
        }
    }
    cout<<"{";
    for(int i(0);i<8;i++){
        cout<<"{";
        for(int j(0);j<8;j++){

                cout<<"{"<<seeds[i][j][0]<<","<< seeds[i][j][1]<<"},";
        }
        cout<<"}\n";
    }
    cout<<"}";
}
