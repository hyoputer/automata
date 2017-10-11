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
        map<pair<int, char>, vector<int> > m; //nfa table '(state, alphabet)-> vector of dest state'
        char rexp[5], exp[100], file[100];
        int sidx = 0; // new state number
        fscanf(in, "%s %s %s", rexp, exp, file);
        for (int i = 0; exp[i] != 0; i++) //infix regex to postfix in queue
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
        while (!Queue.empty()) // make nfa table from postfix regex
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
            Queue.pop();
        }
        pi p = reg.top();
        int end = p.second;
        queue<int> res;
        queue<int> start;
        res.push(p.first);
        bool f = true;
        for (int i = 0; file[i] != 0; i++) //using BFS to run NFA
        {
            queue<int> empty;
            swap(res, start);
            swap(res, empty);
            char cur = file[i];
            int visited[100] = {};
            if (start.empty())
            {
                f = false;
                break;
            }
            while(!start.empty())
            {
                int cs = start.front();
                visited[cs] = 1;
                start.pop();
                vector<int> v = m[make_pair(cs, 'e')];
                for (int j = 0; j < v.size(); j++)
                {
                    if (visited[v[j]] != 0)
                        continue;
                    start.push(v[j]);
                }
                if (!m[make_pair(cs, cur)].empty())
                    res.push(m[make_pair(cs, cur)][0]);
            }
        }
        if (f)
        {
            int visited[100] = {};
            bool ff = false;
            while(!res.empty())
            {
                int cs = res.front();
                visited[cs] = 1;
                if (end == cs)
                {
                    ff = true;
                    break;
                }
                vector<int> v = m[make_pair(cs, 'e')];
                for (int j = 0; j < v.size(); j++)
                {
                    if (visited[v[j]] != 0)
                        continue;
                    res.push(v[j]);
                }
                res.pop();
            }
            if (!ff)
                f = false;
        }
        if (f)
            fprintf(out, "yes\n");
        else
            fprintf(out, "no\n");
    }
}
