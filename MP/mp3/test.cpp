#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void Output(int val)
{
    cout << val << ' ';
}

int main() {

	vector<int> intvec;
    for (int i = 0; i < 10; i++)
        intvec.push_back(i);
    cout << "vect is" << endl;
    for_each(intvec.begin(), intvec.end(), Output);
    random_shuffle(intvec.begin(), intvec.end());
    cout << "change vector is" << endl;
    for_each(intvec.begin(), intvec.end(), Output);

}