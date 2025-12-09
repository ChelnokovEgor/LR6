#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <iomanip>  

using namespace std;

const int MAX_POS = 10001;
const int MAX_V = 10001;
const int INF = INT_MAX;

struct State {
    int pos, v, steps;
    State(int p, int vel, int s) : pos(p), v(vel), steps(s) {}
};

void path() {
    int K;
    cin >> K;
    vector<int> targets(K);
    for (int i = 0; i < K; ++i) {
        cin >> targets[i];
    }

    vector<vector<int>> dist(MAX_POS + 1, vector<int>(MAX_V + 1, INF));
    vector<vector<int>> from_pos(MAX_POS + 1, vector<int>(MAX_V + 1, -1));
    vector<vector<int>> from_v(MAX_POS + 1, vector<int>(MAX_V + 1, -1));


    queue<State> q;
    dist[1][0] = 0;
    q.push(State(1, 0, 0));

    int final_pos = -1, final_v = -1;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        int pos = cur.pos;
        int v = cur.v;
        int steps = cur.steps;

        if (dist[pos][v] != steps) continue;

        int idx = upper_bound(targets.begin(), targets.end(), pos) - targets.begin();
        if (idx == K) {
            final_pos = pos;
            final_v = v;
            break;
        }
        int next_target = targets[idx];

        for (int dv = -1; dv <= 1; ++dv) {
            int v_new = v + dv;
            if (v_new < 1 || v_new > MAX_V) continue;

            int next_pos = pos + v_new;
            if (next_pos > MAX_POS) continue;
            if (next_pos > next_target) continue;

            if (dist[next_pos][v_new] > steps + 1) {
                dist[next_pos][v_new] = steps + 1;
                from_pos[next_pos][v_new] = pos;
                from_v[next_pos][v_new] = v;
                q.push(State(next_pos, v_new, steps + 1));
            }
        }
    }



    // Восстановление пути
    vector<pair<int, int>> moves; 
    int pos = final_pos, v = final_v;

    while (pos != 1 || v != 0) {
        int prev_pos = from_pos[pos][v];
        int prev_v = from_v[pos][v];
        moves.push_back(make_pair(v, pos));
        pos = prev_pos;
        v = prev_v;
    }

    reverse(moves.begin(), moves.end());

    // Вывод шагов
    for (int i = 0; i < (int)moves.size(); ++i) {
        int step_num = i + 1;
        int speed = moves[i].first;
        int position = moves[i].second;
        cout << "ход " << step_num << " скорость " << speed << " позиция " << position << endl;
    }

    int ans = (int)moves.size();
    cout << ans << endl;
}