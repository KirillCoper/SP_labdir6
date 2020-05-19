#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

using namespace std;

static string str;
pthread_mutex_t m;
pthread_mutex_t n;

void *finder(void *arg)
{
        pthread_mutex_lock(&m);
        string s;
        string *s1=(string *)arg;
        cout << *s1 << endl;
        cout << str << endl;
        s = *s1;
        pthread_mutex_unlock(&m);
        pthread_mutex_lock(&n);
        if (s.find(str) < 1000) {
                cout << "Naideno v pozicii " << s.find(str) << endl;
        }
        else
        {
                cout << "Ne naideno" << endl;
        }
        pthread_mutex_unlock(&n);
        return 0;
}

#define NUM 7

int main()
{
        int ch=0;
        pthread_mutex_init(&m,NULL);
        pthread_mutex_init(&n,NULL);
        string s;
        string mas_string[NUM];
        pthread_t mas_str[NUM];
        ifstream file("/TEXT");
        while (getline(file, s))
        {
               mas_string[ch]=s;
               cout << mas_string[ch] << endl;
               ch++;
        }
        file.close();
        cout << "Vvedite slovo ili fragment" << endl;
        cin >> str;
        for(int i = 0; i < NUM; i++)
        {
                pthread_create(&mas_str[i],NULL,finder,(void *)&mas_string[i]);
        }
        for(int i = 0; i < NUM; i++)
        {
                pthread_join(mas_str[i],NULL);
        }
        return 0;
}

                        