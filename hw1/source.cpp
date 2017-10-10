#include <vector>
#include <stdio.h>
#include <map>
#include <stack>
#include <utility>
#include <queue>
#define pi pair<int, int>
using namespace std;

int main ()
{
    FILE *in, *out;
    in = fopen("input.txt", "r");
    out = fopen("2015_17271.out", "w");
    int t;
    fscanf(in, "%d\n", &t);
    while(t--)
    {
        stack<char> cal;
        stack<pi> reg;
        queue<char> Queue;
        map<pair<int, char>, vector<int> > m;
        char rexp[5], exp[100], file[100];
        int sidx = 0;
        int visited[100] = {};
        fscanf(in, "%s %s %s", rexp, exp, file);
        //printf("%s %s %s", rexp, exp, file);
        for (int i = 0; exp[i] != 0; i++)
        {
            char cur = exp[i];
            if (cur == '0' || cur == '1')
                Queue.push(cur);
            else if (cur == ')')
            {
                Queue.push(cal.top());
                cal.pop();
            }
            else if (cur != '(')
                cal.push(cur);
        }
        while (!Queue.empty())
        {
            char front = Queue.front();
            if (front == '0' || front == '1')
            {
                m[make_pair(sidx, front)].push_back(sidx + 1);
                reg.push(make_pair(sidx, sidx + 1));
                sidx += 2;
            }
            else if (front == '+')
            {
                pi a = reg.top();
                reg.pop();
                pi b = reg.top();
                reg.pop();
                m[make_pair(sidx, 'e')].push_back(a.first);
                m[make_pair(sidx, 'e')].push_back(b.first);
                m[make_pair(a.second, 'e')].push_back(sidx + 1);
                m[make_pair(b.second, 'e')].push_back(sidx + 1);
                reg.push(make_pair(sidx, sidx + 1));
                sidx += 2;
            }
            else if (front == '*')
            {
                pi p = reg.top();
                reg.pop();
                m[make_pair(p.second, 'e')].push_back(p.first);
                m[make_pair(sidx, 'e')].push_back(p.first);
                m[make_pair(p.second, 'e')].push_back(sidx + 1);
                m[make_pair(sidx, 'e')].push_back(sidx + 1);
                reg.push(make_pair(sidx, sidx + 1));
                sidx += 2;
            }
            else if (front == '.')
            {
                pi b = reg.top();
                reg.pop();
                pi f = reg.top();
                reg.pop();
                m[make_pair(f.second, 'e')].push_back(b.first);
                reg.push(make_pair(f.first, b.second));
            }
            //printf("%c", Queue.front());
            Queue.pop();
        }
    }
}
