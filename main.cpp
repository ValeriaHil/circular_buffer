#include <iostream>
#include "circular_buffer.h"

using namespace std;

int main() {
//    circ_buff<int> buff;
//    circ_buff<int>::iterator const j = buff.begin();
//    j == j;
//    circ_buff<int>::const_iterator k = buff.begin();
//    std::cout << (buff.begin() != k) << std::endl;
//
//    circ_buff<int> const &buff_ref = buff;
//    buff_ref.begin();
//
//    circ_buff<int>::iterator m;
//    m++;
//
//    for (int i = 1; i <= 100; i++) {
//        buff.push_front(i);
//    }
//    for (int i = 5; i <= 100; i++) {
//        buff.push_front\\(i);
////        buff.erase(buff.end() - 2);
//    }

    circ_buff<int> d;
    for (int i = 0; i < 10; ++i) {
        d.push_back(i);
    }
    const circ_buff<int> d3(d);
    d.erase(d.erase(d.begin()));
    d[4] = 100;
    cerr << *d.begin() << endl;
    cerr << *(d.begin() + 1) << endl;
    cerr << *(d.begin() + 2) << endl;
    cerr << *(d.begin() + 3) << endl;
    auto it = d.end();
    it -= 2;
    d.insert(d.erase(it), 321);
    cerr << endl;
    cerr << "!!!!!\n";
    for (auto it = d.begin(); it != d.end(); ++it) {
        cerr << *it << endl;
    }
    cerr << endl;
    circ_buff<int> d2;
    d2 = d;
    d.clear();
    for (auto it = d.begin(); it != d.end(); ++it) {
        cerr << *it << endl;
    }
    cerr << endl;
    for (auto it = d2.begin(); it != d2.end(); ++it) {
        cerr << *it << endl;
    }
    cerr << endl;
    for (auto it = d3.begin(); it != d3.end(); ++it) {
        cerr << *it << endl;
    }
    cerr << endl;
    cerr << *(d3.rbegin()) << endl;
    circ_buff<int>::const_iterator re = d3.end();
    --re;
    cerr << *re << endl;
    circ_buff<int>::const_iterator re2 = d3.end();
    --re2;
    cerr << (re == re2);
    circ_buff<int> a;
    cerr << "\n&&&&&&&&&&&\n";
    for (int i = 0; i < 5; ++i) {
        a.push_back(i);
    }
    for (int i = 5; i < 100; ++i) {
        a.push_back(i);
        auto r = a.begin();
        a.erase(a.begin() + 1);
    }
    //0 96 97 98 99
    cerr << endl;
    for (auto i = a.begin(); i != a.end(); ++i) {
        cerr << *i << " ";
    }
    circ_buff<int> c;
    c.push_back(6);
    c.push_back(7);
    circ_buff<int>::iterator ncon = c.begin();
    circ_buff<int>::const_iterator con = c.begin();
    cerr << "!!!!!\n";
    cerr << endl << (con == ncon )<< endl;
    cerr << endl << (ncon == con)<< endl;
    circ_buff<int> test;
    cerr << "^^^^^^^^^^\n";
    cerr << (test.begin() == test.end()) << endl;
    cerr << (test.rbegin() == test.rend()) << endl;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    cerr << *(test.end() - 1);

    return 0;
}