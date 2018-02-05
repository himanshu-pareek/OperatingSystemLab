#include <bits/stdc++.h>
#include <time.h>
#include <fstream>

using namespace std;

float FCFS (int n, const vector < pair < float, float > > &job) {
    vector < pair < float, float > > jobDesc (job.begin (), job.end ());
    vector < float > finish;
    sort (jobDesc.begin (), jobDesc.end ());

    finish.push_back (jobDesc[0].second);

    int timeOfFinish = finish[0];
    for (int i = 1; i < n; i++) {
        timeOfFinish = max (timeOfFinish + jobDesc[i].second, jobDesc[i].first + jobDesc[i].second);
        finish.push_back (timeOfFinish);
    }

    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (finish[i] - jobDesc[i].first);
    }

    return sum / n;
}

float SJF (int n, const vector < pair < float, float > > &A) {
    vector < pair < float, float > > job (A.begin (), A.end ());
    priority_queue < pair < float, int > > q;
    priority_queue < pair < float, int > > p;

    int trt = 0;

    for (int i = 0; i < n; i++) {
        p.push (make_pair (-1 * job[i].first, i));
    }

    float time = 0;
    pair < float, int > temp1, temp2;

    do {
        if (!p.empty ()) {
            temp1 = p.top ();
            p.pop ();
            q.push (make_pair (-1 * (job[temp1.second].second), temp1.second));

            if (!p.empty ()) {
                temp2 = p.top ();
                while (temp2.first == temp1.first) {
                    p.pop ();
                    q.push (make_pair (-1 * (job[temp2.second].second), temp2.second));
                    if (p.empty ()) {
                        break;
                    }
                    temp2 = p.top ();
                }
            }
            time = -1 * temp1.first;
        }
        float en = (p.empty ()) ? (float ) INT_MAX : (-1 * (p.top().first));
        if (!q.empty ()) {
            temp1 = q.top ();
            while ((-1 * temp1.first) <= en - time) {
                q.pop ();
                time += -1 * temp1.first;
                trt += time - job[temp1.second].first;
                if (q.empty ()) {
                    break;
                }
                temp1 = q.top ();
            }
        }
        if (en > time && !q.empty ()) {
            temp1 = q.top ();
            q.pop ();
            temp1.first += en - time;
            time = en;
            q.push (temp1);
        }
    } while (!p.empty ());

    return trt / n;
}

float RR (int n, float quant, vector < pair < float, float> > &A) {
    vector < pair < float, float > > job (A.begin (), A.end ());
    priority_queue < pair < float, int > > p;
    int trt = 0;
    for (int i = 0; i < n; i++) {
        p.push (make_pair (-1 * job[i].first, i));
    }
    queue < pair < float, int > > q;
    float time = 0;
    pair < float, int > temp1, temp2;
    do {
        if(!q.empty()){
            temp1 = q.front();
            while(((-1 * temp1.first) <= quant)){
                q.pop ();
                time += -1 * temp1.first;
                trt += time - job[temp1.second].first;
                if (q.empty ()) {
                    break;
                }
                temp1 = q.front ();
            }
        }
        if (!p.empty ()) {
            temp1 = p.top ();
            while (-1 * temp1.first <= time) {
                p.pop ();
                q.push (make_pair (-1 * job[temp1.second].second, temp1.second));
                if(p.empty ()) {
                    break;
                }
                temp1 = p.top ();
            }
        }
        if (!q.empty ()) {
            temp1 = q.front ();
            if (-1 * temp1.first > quant) {
                q.pop ();
                temp1.first += quant;
                time += quant;
               // cout<<"job: "<<temp1.second<<"\tremaining  "<<-1*temp1.first<<"\ttime: "<<time<<endl;
                q.push (temp1);
            }
        }
    } while (!p.empty () || !q.empty ());

    return trt / n;
}

double ran_expo (double lambda) {
    double u;
    u = rand () / (RAND_MAX + 1.0);
    return -log (1 - u) / lambda;
}

int main (void) {
    int fcfs[3];
    int sjf[3];
    int rr1[3];
    int rr2[3];
    int rr3[3];
    int n[3];

    float av[15] = {0};

    n[0] = 10;
    n[1] = 50;
    n[2] = 100;
    int t = 10;

    ofstream output_file;
    output_file.open ("output.csv");
    output_file << "n = 10,fcfs,sjf,rr-1,ff-2,rr-5,n=50,fcfs,sjf,rr-1,rr-2,rr-5,n=100,fcfs,sjf,rr-1,rr-2,rr-5\n";

    while (t--) {
        srand (t * (unsigned) time (NULL));
        for (int j = 0; j < 3; j++) {
            vector < pair < float, float > > job;
            job.clear ();
            float arr, bur;
            double lam = 0.1;
            pair < float, float > p;
            arr = 0.000000;
            bur = rand () % 20 + 1;
            p = make_pair (arr, bur);
            job.push_back (p);
            for (int i = 0; i < n[j]; i++) {
                arr = ran_expo (lam) * lam * 10 / log (RAND_MAX + 1.0);
                bur = rand () % 20 + 1;
                p = make_pair (arr, bur);
                job.push_back (p);
            }
            fcfs[j]=FCFS(n[j],job);
            sjf[j]=SJF(n[j],job);
            rr1[j]=RR(n[j],1,job);
            rr2[j]=RR(n[j],2,job);
            rr3[j]=RR(n[j],5,job);
        }
        av[0] += fcfs[0];
        av[1] += sjf[0];
        av[2] += rr1[0];
        av[3] += rr2[0];
        av[4] += rr3[0];
        av[5] += fcfs[1];
        av[6] += sjf[1];
        av[7] += rr1[1];
        av[8] += rr2[1];
        av[9] += rr3[1];
        av[10] += fcfs[2];
        av[11] += sjf[2];
        av[12] += rr1[2];
        av[13] += rr2[2];
        av[14] += rr3[2];

        output_file<<","<<fcfs[0]<<","<<sjf[0]<<","<<rr1[0]<<","<<rr2[0]<<","<<rr3[0]<<",,"<<fcfs[1]<<","<<sjf[1]<<","<<rr1[1]<<","<<rr2[1]<<","<<rr3[1]<<",,"<<fcfs[2]<<","<<sjf[2]<<","<<rr1[2]<<","<<rr2[2]<<","<<rr3[2]<<"\n";
    }

    for (int i = 0; i < 15; i++) {
        av[i] = av[i] / 10;
    }

    output_file<<"\nAverage,"<<av[0]<<","<<av[1]<<","<<av[2]<<","<<av[3]<<","<<av[4]<<",,"<<av[5]<<","<<av[6]<<","<<av[7]<<","<<av[8]<<","<<av[9]<<",,"<<av[10]<<","<<av[11]<<","<<av[12]<<","<<av[13]<<","<<av[14]<<"\n";

    return 0;
}
