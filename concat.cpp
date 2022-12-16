
#include "util.h"

#include "color.h"
#include "surface_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>
#include <fstream>
// Include the string library
#include <string>
using namespace std;

void test()
{
    ofstream of_a("file13.ppm",  ios_base::binary |  ios_base::app);
    
//     for(int i=4; i>=0; i--
    
    ifstream if_6("header.ppm",    ios_base::binary);
    string nfile = "proc_"+to_string(0)+".ppm";
    cout << nfile << endl;
    ifstream if_0(nfile,  ios_base::binary);
    ifstream if_1("proc_1.ppm",  ios_base::binary);
    ifstream if_2("proc_2.ppm",  ios_base::binary);
    ifstream if_3("proc_3.ppm",  ios_base::binary);
    ifstream if_4("proc_4.ppm",  ios_base::binary);
//     ifstream if_5("proc_5.ppm",  ios_base::binary);
    
    of_a.seekp(0,  ios_base::end);
//     of_a  << if_4.rdbuf() << if_3.rdbuf() << if_2.rdbuf() << if_1.rdbuf() << if_0.rdbuf();
    of_a << if_4.rdbuf();
    of_a << if_3.rdbuf();
    of_a << if_2.rdbuf();
    of_a << if_1.rdbuf();
    of_a << if_0.rdbuf();

}

int main(int argc, char *argv []) 
{
    for(int i=100; i>=0; --i)
    {
        string fname1 = "proc_" + to_string(i) + ".ppm";
        ifstream in1(fname1);
        ofstream outFile("outfile.ppm", ios::app);
        string line;
        int count =1;
        while(getline(in1, line))
        {
            outFile << line << '\n';
            count++;
        }
    }
    
}
