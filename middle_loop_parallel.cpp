#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int dist[2048][2048];
int n;

int main()
{
    int size = 2048;
    int num = 7;
    string s = "./testcase/";
    int x = size;
    string mp;
    while(x > 0)
    {
        mp += (char)(x%10 + '0');
        x = x/10;
    }
    reverse(mp.begin(),mp.end());
    s += mp;
    string t = ".txt";
    for(int yy = 0;yy < num;yy++)
    {
        int intinf = 1e4;

        string nam;
        string nam1;
        
        nam += s;
        nam += "/input";
        nam += (char)(yy/10 + '0');
        nam += (char)(yy%10 + '0');
        nam += t;

        nam1 += s;
        nam1 += "/output";
        nam1 += (char)(yy/10 + '0');
        nam1 += (char)(yy%10 + '0');
        nam1 += t;
    
        fstream fin,fout;
        fin.open(nam);
        fout.open(nam1);

        fin >> n;
        for(int i = 0;i<n;i++)
            for(int j = 0;j<n;j++)
                fin >> dist[i][j];

        double start = omp_get_wtime();
        for(int k = 0;k<n;k++)
        {
            #pragma omp parallel for num_threads(4) 
            for(int i = 0;i<n;i++)
            {
                #pragma omp simd
                for(int j = 0;j<n;j++)
                {
                    dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
                }
            }
        }
        double end = omp_get_wtime();
        double duration = (end - start)*1000;

        int x;
        for(int i = 0;i<n;i++)
        {
            for(int j = 0;j<n;j++)
            {
                fout >> x;
                if(dist[i][j] != x)
                {
                    cout << "FAILED " << duration <<" ms"<< '\n';
                    return 0;
                }
            }
        }
        cout << "PASSED " << duration <<" ms" << '\n';
        
        
        fin.close();
        fout.close();
    }

    return 0;
}