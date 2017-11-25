#include <vector>
#include <iostream>
#include <map>
#include <stack>
#include <utility>
#include <queue>
#include <string>
#define pi pair<int, int>
using namespace std;

void printauto (string s, stack<char> Stack, queue<string> &q) //print process and push in queue
{
  string ap;
  while(Stack.size() != 1)
  {
    ap += Stack.top();
    Stack.pop();
  }
  q.push("=> " + s + ap);
}

int main ()
{
  string input;
  stack<char> Stack; 
  queue<string> pqueue; // save calculation process 
  bool correct = true;
  cin >> input;
  input += '#';
  Stack.push('#');
  Stack.push('E');
  string s = "";
  pqueue.push("E");
  for (int i = 0; i < input.length(); i++)
  {
    switch (input[i])
    {
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'x':
      case 'y':
      case 'z':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
        while (Stack.top() != input[i]) // numbers and english alphabet
        {
          switch (Stack.top()) //check top of stack
          {
            case 'E':
              Stack.pop();
              Stack.push('e');
              Stack.push('T');
              printauto(s, Stack, pqueue);
              break;
            case 'T':
              Stack.pop();
              Stack.push('t');
              Stack.push('F');
              printauto(s, Stack, pqueue);
              break;
            case 'F':
              Stack.pop();
              Stack.push('A');
              printauto(s, Stack, pqueue);
              break;
            case 'A':
              Stack.pop();
              Stack.push(input[i]);
              printauto(s, Stack, pqueue);
              break;
            default:
              correct = false;
          }
          if (!correct) // if not in parsing table
          {
            i = input.length();
            break;
          }
        }
        s += input[i];
        Stack.pop(); 
        break;
      case '+':
      case '-':
        while (Stack.top() != input[i])
        {
          switch (Stack.top())
          {
            case 'e':
              Stack.push('T');
              Stack.push(input[i]);
              printauto(s, Stack, pqueue);
              break;
            case 't':
              Stack.pop();
              printauto(s, Stack, pqueue);
              break;
            default:
              correct = false;
          }
          if (!correct)
          {
            i = input.length();
            break;
          }
        }
        s += input[i];
        Stack.pop();
        break;
      case '*':
      case '/':
        while (Stack.top() != input[i])
        {
          switch (Stack.top())
          {
            case 't':
              Stack.push('F');
              Stack.push(input[i]);
              printauto(s, Stack, pqueue);
              break;
            default:
              correct = false;
          }
          if (!correct)
          {
            i = input.length();
            break;
          }
        }
        s += input[i];
        Stack.pop();
        break;
      case '(':
        while (Stack.top() != input[i])
        {
          switch (Stack.top())
          {
            case 'E':
              Stack.pop();
              Stack.push('e');
              Stack.push('T');
              printauto(s, Stack, pqueue);
              break;
            case 'T':
              Stack.pop();
              Stack.push('t');
              Stack.push('F');
              printauto(s, Stack, pqueue);
              break;
            case 'F':
              Stack.pop();
              Stack.push(')');
              Stack.push('E');
              Stack.push('(');
              printauto(s, Stack, pqueue);
              break;
            default:
              correct = false;
          }
          if (!correct)
          {
            i = input.length();
            break;
          }
        }
        s += input[i];
        Stack.pop();
        break;
      case ')':
        while (Stack.top() != input[i])
        {
          switch (Stack.top())
          {
            case 'e':
              Stack.pop();
              printauto(s, Stack, pqueue);
              break;
            case 't':
              Stack.pop();
              printauto(s, Stack, pqueue);
              break;
            default:
              correct = false;
          }
          if (!correct)
          {
            i = input.length();
            break;
          }
        }
        s += input[i];
        Stack.pop();
        break;
      case '#':
        while (Stack.top() != input[i])
        {
          switch (Stack.top())
          {
            case 'e':
              Stack.pop();
              printauto(s, Stack, pqueue);
              break;
            case 't':
              Stack.pop();
              printauto(s, Stack, pqueue);
              break;
            default:
              correct = false;
          }
          if (!correct)
          {
            i = input.length();
            break;
          }
        }
        Stack.pop();
        break;
    }
  }
  if (!Stack.empty()) //check stack
    correct = false;
  if (correct)
  {
    cout << "Yes" << endl;
    while(!pqueue.empty())
    {
      cout << pqueue.front() << endl;
      pqueue.pop();
    }
  }
  else {
    cout << "No" << endl;
  }
}
