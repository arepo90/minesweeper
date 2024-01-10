#include <bits/stdc++.h>
using namespace std;
#define N 10
#define M 2

/*
        ╔═══╦═══╦═══╦═══╦═══╗
        ║>1<║ 0 ║ 0 ║ 0 ║ 0 ║
        ╠═══╬═══╬═══╬═══╬═══╣
        ║ 1 ║ 0 ║ 0 ║ 0 ║ 0 ║
        ╠═══╬═══╬═══╬═══╬═══╣
        ║ 1 ║ 0 ║ 0 ║ 0 ║ 0 ║
        ╠═══╬═══╬═══╬═══╬═══╣
        ║ 1 ║ 0 ║ 0 ║ 0 ║ 0 ║
        ╠═══╬═══╬═══╬═══╬═══╣
        ║ 1 ║ 0 ║ 0 ║ 0 ║ 0 ║
        ╚═══╩═══╩═══╩═══╩═══╝
*/

vector<pair<int, int>> dirs_diag = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}, dirs_cross = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
vector<vector<pair<int, bool>>> mp;
set<pair<int, int>> flags;
int valid_flags = 0, total_flags = 0;

void populate(){
    srand(time(0));
    vector<pair<int, bool>> temp;
    for(int i = 0; i < N; i++){
        temp.push_back({0, false});
    }
    for(int i = 0; i < N; i++){
        mp.push_back(temp);
    }
    set<pair<int, int>> s;
    for(int i = 0; i < M; i++){
        int x = rand() % N, y = rand() % N;
        if(s.count({x, y}) > 0) i--;
        else{
            s.insert({x, y});
            mp[y][x].first = -1;
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(mp[i][j].first == -1) continue;
            for(int k = 0; k < 8; k++){
                int cx = j + dirs_diag[k].first, cy = i + dirs_diag[k].second;
                if(cx >= 0 && cx < N && cy >= 0 && cy < N && mp[cy][cx].first == -1) mp[i][j].first++;
            }
        }
    }
}


void draw(int x, int y, bool mode = false){
    system("clear");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i == 0 && j == 0) cout << "╔═══";
            else if(j == 0) cout << "╠═══";
            else if(i == 0) cout << "╦═══";
            else cout << "╬═══";
            if(i == 0 && j == N-1) cout << "╗\n";
            else if(j == N-1) cout << "╣\n";
        }
        for(int j = 0; j < N; j++){
            cout << "║" << ((i == y && j == x) ? ">" : " ");
            if(mp[i][j].second) cout << (mp[i][j].first == 0 ? " " : (mode && mp[i][j].first == -1 ? "X" : to_string(mp[i][j].first)));
            else{
                bool check = true;
                for(auto it = flags.begin(); it != flags.end(); it++){
                    if(i == it->second && j == it->first){
                        cout << '!';
                        check = false;
                    }
                }
                if(check) cout << '+';
            }
            cout << (i == y && j == x ? "<" : " ");
            if(j == N-1) cout << "║\n";
        }
    }
    for(int i = 0; i < N; i++){
        if(i == 0) cout << "╚═══";
        else if(i == N-1) cout << "╩═══╝\n";
        else cout << "╩═══";
    }
}

void bfs(int x, int y){
    queue<pair<int, int>> q;
    q.push({x, y});
    mp[y][x].second = true;
    while(!q.empty()){
        int cx = q.front().first, cy = q.front().second;
        q.pop();
        mp[cy][cx].second = true;
        if(mp[cy][cx].first != mp[y][x].first) continue;
        for(int i = 0; i < 8; i++){
            int xx = cx + dirs_diag[i].first, yy = cy + dirs_diag[i].second;
            if(xx >= 0 && xx < N && yy >= 0 && yy < N && !mp[yy][xx].second) q.push({xx, yy});
        }
    }
}

void end_game(bool win){
    if(win){
        cout << "\nGanaste let's go\n";
    }
    else{
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(mp[i][j].first == -1){
                    mp[i][j].second = true;
                }
            }
        }
        draw(-1, -1, true);
        cout << "\nPerdiste xd\n";
    }
}

int main(){
    populate();
    int cx = 0, cy = 0;
    while(1){
        draw(cx, cy);
        char op; cin >> op;
        switch(op){
            case 'w':
                cy = max(0, cy-1);
                break;
            case 'a':
                cx = max(0, cx-1);
                break;
            case 's':
                cy = min(N-1, cy+1);
                break;
            case 'd':
                cx = min(N-1, cx+1);
                break;
            case 'q':
                if(mp[cy][cx].first == -1){
                    end_game(false);
                    return 0;
                }
                else if(mp[cy][cx].first == 0) bfs(cx, cy);
                else mp[cy][cx].second = true;
                break;
            case 'e':
                if(mp[cy][cx].second) continue;
                else if(flags.find({cx, cy}) == flags.end()){
                    flags.insert({cx, cy});
                    total_flags++;
                    if(mp[cy][cx].first == -1) valid_flags++;
                    if(total_flags == valid_flags && valid_flags == M){
                        end_game(true);
                        return 0;
                    }
                }
                else{
                    flags.erase({cx, cy}); 
                    total_flags--;
                    if(mp[cy][cx].first == -1) valid_flags--; 
                }
                break;
            default:
                break;
        }
    }
    draw(0, 0);
    return 0;
}
