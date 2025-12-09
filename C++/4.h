#pragma once
#include <iostream>
#include <climits>
using namespace std;

const int MAX_POS = 10100;
const int MAX_V = 200;
const int INF = INT_MAX;

struct State {
    int pos, v, steps;
    State(int p, int vel, int s) : pos(p), v(vel), steps(s) {}
};

void path();
