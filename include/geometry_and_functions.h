#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

void check_matlist(string sim_dir);
int build_geo(string samplename,string sim_dir);
bool itExists(string dirName_in);
string checkfunction(string data_dir, string samplefilename);
void printsummary(string s_dir, string samplename, string GATORDIR_summary);
