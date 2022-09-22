//priority_queue 써야하는 문제
#include <iostream>
#include <string>
#include <vector>

#include <string.h>

using namespace std;
int dat[50001];
int visited[50001];
vector<vector<pair<int, int>>> path;
int summitflag = 0;
int ans = 0;
int newans = 0;
int anssummit = 0;
int start;
void dfs1(int now) {
   
    if (summitflag == 0 && dat[now] == 2) {
        summitflag = 1;
        anssummit = now;
        return;
    }

    if (summitflag == 1) {
        return;
    }

    for (auto a : path[now]) {
        if (summitflag == 0) {
            if (visited[a.first]) continue;
            if (dat[a.first]==1) continue;
            if (a.second > ans) {
                ans = a.second;
                visited[a.first] = 1;
                dfs1(a.first);
            }
            else {
                visited[a.first] = 1;
                dfs1(a.first);
            }
        }
        else {

        }
    }

}


void dfs2(int now) {
   
    if (dat[now] == 2) {
        if (ans > newans)
        {
            ans = newans;
            anssummit = now;
        }
        else if (ans == newans) {
            if (anssummit > now)
                anssummit = now;
        }

        return;
    }

    for (auto a : path[now]) {
        if (visited[a.first]) continue;
        if( dat[a.first]==1) continue;
        if (a.second > ans) {

        }

        else {
            visited[a.first] = 1;
            int mem = newans;
            if (a.second > newans)
                newans = a.second;
            dfs2(a.first);
            newans = mem;
            visited[a.first] = 0;
        }
    }

}


vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer;
    path.resize(n+1);
    for (int i = 0; i < paths.size(); i++) {
        path[paths[i][0]].push_back({ paths[i][1],paths[i][2] });
        path[paths[i][1]].push_back({ paths[i][0],paths[i][2] });
    }
    for (int i : gates) {
        dat[i] = 1;
    }
    for (int i : summits) {
        dat[i] = 2;
    }

    visited[gates[0]] = 1;
    dfs1(gates[0]);
    for (int i = 0; i < gates.size(); i++) {
        memset(visited, 0, sizeof(int) * 50001);
        newans = 0;
        visited[gates[i]] = 1;
        dfs2(gates[i]);
    }
    answer.push_back(anssummit);
    answer.push_back(ans);
    return answer;
}
