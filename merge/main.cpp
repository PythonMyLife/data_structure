#include <iostream>
#include <fstream>
using namespace std;

void merge(const char *in1, const char *in2, const char *out)
{
    ifstream inf1, inf2;
    int num1, num2, num3;
    ofstream outf;
    inf1.open(in1);
    inf2.open(in2);
    outf.open(out);

    inf1 >> num1;
    inf2 >> num2;
    num3 = num1 < num2 ? num1 : num2;
    outf << num3 << " ";

    while(!inf1.eof() && !inf2.eof()){
        if(num1 < num2){
            inf1 >> num1;
        }else {
            inf2 >> num2;
        }

        num3 = num1 < num2 ? num1 : num2;
        outf << num3 << " ";
    }

    num3 = num1 < num2 ? num2 : num1;

    while(!inf1.eof()){
        inf1 >> num1;
        num2 = num1 < num3 ? num1 : num3;
        outf << num2 << " ";
    }

    while(!inf2.eof()){
        inf2 >> num1;
        num2 = num1 < num3 ? num1 : num3;
        outf << num2 << " ";
    }

    num2 = num1 < num3 ? num3 :num1;
    outf << num2 << " ";

    inf1.close();
    inf2.close();
    outf.close();
}

int main()
{
    char * in1 = "1.txt";
    char * in2 = "2.txt";
    char * out = "out.txt";
    cout << "finish merge!" << endl;
    merge(in1, in2, out);
    return 0;
}
