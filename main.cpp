using namespace std;
#include<cstdlib>
#include<time.h>
#include<iostream>

int main(){
    cout << "hi" << endl;
    srand(time(0));
    const int upperLimitOfInt = 1.84467441E19;
    int randomInt = rand();
    int testInt = 3147;
    int powerOfTwo = 0;

while (testInt <= upperLimitOfInt){
    powerOfTwo++;
    int multiplier = 2;
    for (int i = 1; i <= powerOfTwo; i++){
        multiplier *= 2;
        cout << multiplier << endl;
    }
    testInt *= multiplier;
    //cout << testInt << endl;
}

    return 0;
}
