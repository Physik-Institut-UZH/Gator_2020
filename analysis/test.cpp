#include <stdio.h>
#include <stdlib.h>
#include "isotopes.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int test (string bla, int events)
{
	if (U238) cout<<"test U238\n";
	if (U186) cout<<"test U186\n";
	if (U235) cout<<"test !U235\n";

	cout<<" hello "<<events<<bla<<endl;
	return 0;

}
