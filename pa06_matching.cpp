#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

int RabinKarp(char* t, char* p){
    int length = strlen(p);
    int pValue = 0,tValue, idx = 0;
    for(int i = 0 ; i < length; i++){
        pValue += p[i]*pow(length,length-1-i);
    }
    for(int i = 0; i < strlen(t)-length+1; i++){
        tValue = 0;
        for(int j = 0; j < length; j++){
            tValue += t[i+j]*pow(length,length-1-j);
        }
        idx++;
        if(tValue == pValue){
            if(!strncmp(t+i, p, length)){
                idx = idx+length;
                break;
            }
        }
    }
    return idx;
}

int KMP(char* t, char* p){
    int idx= 0, temp;
    for(int i = 0; i < strlen(t); i++){
        temp = 0;
        for(int j =0; j < strlen(p); j++){
            if(t[i+j] == p[j]) idx++;
            else break;
            temp++;
        }
        idx++;
        if(temp == strlen(p)){
            idx--;
            break;
        }
    }
    return idx;
}
void case1(int *s, int *b, char* p){
    int length = strlen(p);
    int i = length;
    int j = length+1;
    b[i] = j;
    while(i > 0)
    {
        while( j <= length && p[i-1] != p[j-1]){
            if(s[j] == 0)
                s[j] = j-i;
            j = b[j];
        }
        i--;
        j--;
        b[i] = j;
    }
}
void case2(int *s, int *b, char*p){
    int j;
    j = b[0];
    for(int i = 0; i <= strlen(p); i++){
        if(s[i] ==0)
            s[i] = j;
        if(i == j)
            j= b[j];
    }
}
int Boyer(char* t, char* p){
    int tLen = strlen(t);
    int pLen = strlen(p);

    int shift = 0;
    int idx= 0;
    int *bpos = new int[pLen+1];
    int *s = new int[pLen+1];
    for(int i = 0; i < pLen+1; i++) s[i] = 0;
    case1(s,bpos,p);
    case2(s,bpos,p);
    while(shift <= tLen - pLen){
        int j = pLen-1;
        while(j >= 0 && p[j] == t[shift+j]){
            j--;
            idx++;
        }
        if(j != pLen-1 && j != 0){
            idx++;
        }
        if(j < 0){
            return  idx + pLen-1;
        }
        else {
            idx++;
            shift += s[j+1];
        }
    }
    return idx;
}

void bad(char* str, int size, int badChar[256]){
    int i ;
    for(i = 0; i < 256; i++)
        badChar[i] = -1;

    for(i = 0; i < size; i++)
        badChar[(int)str[i]] = i;
}
int search(char* t, char* p){
    int idx = 0;
    int m = strlen(p);
    int n = strlen(t);
    int badChar[256];
    bad(p,m,badChar);
    int s = 0;
    while(s <= (n-m)){
        int j = m-1;
        while(j >= 0 && p[j] == t[s+j]){
            j--;
        }
        if(j != m-1 && j != 0){
            idx++;
        }
        if(j < 0)
        {
            return  idx + m-1;
        }
        else{
            idx++;
            s += max(1, j - badChar[t[s + j]]);
        }
    }
    return -1;
}
int main() {
    char *t = new char[200],*p = new char[200];
    int count,cnt;
    cin >> count;
    for(int i = 0; i < count; i++){
        cin.ignore();
        char *temp = new char[81];
        if(i == 0){
            cin.getline(p,81);
        }
        else{
            cin.getline(temp,81);
            strcat(p,temp);
        }
        delete[] temp;
    }
    cin >> cnt;
    for(int i = 0; i < cnt; i++){
        cin.ignore();
        char *temp = new char[81];
        if(i == 0){
            cin.getline(t,81);
        }
        else{
            cin.getline(temp,81);
            strcat(t,temp);
        }
        delete[] temp;
    }
    int a =RabinKarp(t,p);
    int b = KMP(t,p);
    int c = search(t,p);

    int list[3];if(a != b && b != c && a != c){if( a < b && a < c) list[0] = 1;else if(b < a && b <c) list[0] = 2;else list[0] = 3;if(a > b && a > c) list[2] = 1;else if(b > a && b > c) list[2] = 2;else list[2] = 3;if(a > b && a< c) list[1] = 1;else if(b > a && b < c) list[1] =2;else if(c >a && c < b) list[1] =3;else if(a > c && a < b) list[1] =1;else if(b > c && b < a) list[1] = 2;else list[1] = 3;}else{if(a == b && a == c){list[0] = 0;list[1] = 0;list[2] = 0;}else if(a == b){if(b < c){list[0] = 0;list[1] = 0;list[2] = 3;}else{list[0] = 3;list[1] = 0;list[2] = 0;}}else if(a == c){if(c < b){list[0] = 0;list[1] = 0;list[2] = 2;}else{list[0] = 2;list[1] = 0;list[2] = 0;}}else if(b == c){if(c < a){list[0] = 0;list[1] = 0;list[2] = 1;}else{list[0] = 1;list[1] = 0;list[2] = 0;}}}for(int i = 0 ; i < 3; i++){cout << list[i] << " ";}
}
