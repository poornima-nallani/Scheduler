#include<bits/stdc++.h>
using namespace std;
class process
{
public:
int id;
int initialQueue;
int arrivalTime;
int burstTime;
int c_time;
int first_run;
    process(int id1,int initialQueue1,int arrivalTime1,int burstTime1)
    {
        id=id1;
        initialQueue=initialQueue1;
        arrivalTime=arrivalTime1;
        burstTime=burstTime1;
        c_time=0;
        first_run=-1;
    }
};
bool arrivalsort( const process* x ,const process* y)
{
	if(x->arrivalTime < y->arrivalTime)
		return true;
	else
		return false;
}
bool burstsort( const process* x ,const process* y)
{
	if(x->burstTime < y->burstTime)
		return true;
	else
		return false;
}
bool idsort( const process* x ,const process* y)
{
	return x->id < y->id;
}

int main(int argc, char * argv[])
{
    int timeQuantum = atoi(argv[1]);
    int timeThreshold = atoi(argv[2]);
    ifstream inputFile(argv[3]);
    ofstream outputFile(argv[4]);
    int id, initialQueue, arrivalTime, burstTime;
    vector<process*>v1;
    while (inputFile >> id >> initialQueue >> arrivalTime >> burstTime) 
    {
        process * p= new process(id,initialQueue,arrivalTime,burstTime);
        v1.push_back(p);
    }
    sort(v1.begin(),v1.end(),arrivalsort);
    int curr_time=0;
    int p=0;
    float tot_time=0;
    float total=0;
    queue<process*>q1,q2,q3,q4;
    process *p_run=NULL;
    int r=0;
    int used=0;
    int complete=0;
    vector<process *>v11,v22,v33,v44;
        for(int i=0;i<v1.size();i++)
        {
            if(v1[i]->arrivalTime==0)
            {
                int x=v1[i]->initialQueue;
                if(x==4) v44.push_back(v1[i]);
                else if(x==3) v33.push_back(v1[i]);
                else if(x==2) v22.push_back(v1[i]);
                else if(x==1) v11.push_back(v1[i]);
            }
        }
        
        sort(v11.begin(),v11.end(),idsort);
        sort(v22.begin(),v22.end(),idsort);  
        sort(v33.begin(),v33.end(),idsort);
        sort(v44.begin(),v44.end(),idsort);
        for(int i=0;i<v11.size();i++) q1.push(v11[i]);
        for(int i=0;i<v22.size();i++) q2.push(v22[i]);
        for(int i=0;i<v33.size();i++) q3.push(v33[i]);
        for(int i=0;i<v44.size();i++) q4.push(v44[i]);
        v11.clear();v22.clear();v33.clear();v44.clear();
    while(complete<v1.size())
    {
        if(!q3.empty())
        {
            vector<process *>v;
            queue<process*>q33=q3;
            while(!q33.empty())
            {
                process * pr=q33.front();
                v.push_back(pr);
                q33.pop();
            }
            map<process*,int>f;
            for(int i=0;i<v.size();i++)
            {
                if((curr_time-(v[i]->arrivalTime))%timeThreshold==0 && curr_time != v[i]->arrivalTime)
                {
                    v44.push_back(v[i]);
                    f[v[i]]=1;
                }
            }
            queue<process*>q11;
            while(!q3.empty())
            {
                if(f[q3.front()]!=1)
                {
                    q11.push(q3.front());
                }
                q3.pop();
            }
            q3=q11;
        }
        if(!q2.empty())
        {
            process * p =q2.front();
            // int flag=0;
            vector<process *>v;
            queue<process*>q33=q2;
            while(!q33.empty())
            {
                process * pr=q33.front();
                v.push_back(pr);
                q33.pop();
            }
            sort(v.begin(),v.end(),burstsort);
            map<process*,int>f;
            for(int i=0;i<v.size();i++)
            {
                if((curr_time-(v[i]->arrivalTime))%timeThreshold==0)
                {
                    v33.push_back(v[i]);
                    f[v[i]]=1;
                }
            }
            queue<process*>q11;
            while(!q2.empty())
            {
                if(f[q2.front()]==0)
                {
                    q11.push(q2.front());
                }
                q2.pop();
            }
            q2=q11;
        }
        if(!q1.empty())
        {
            process * p =q1.front();
            vector<process *>v;
            queue<process*>q33=q1;
            while(!q33.empty())
            {
                process * pr=q33.front();
                v.push_back(pr);
                q33.pop();
            }
            map<process*,int>f;
            for(int i=0;i<v.size();i++)
            {
                if((curr_time-(v[i]->arrivalTime))%timeThreshold==0)
                {
                    v22.push_back(v[i]);
                    f[v[i]]=1;
                }
            }
            queue<process*>q11;
            while(!q1.empty())
            {
                if(f[q1.front()]==0)
                {
                    q11.push(q1.front());
                }
                q1.pop();
            }
            q1=q11;
        }
        if((r==1||r==2||r==3)&&p_run!=NULL)
        {
            if(p_run->burstTime== curr_time - (p_run->first_run)) 
            {
                p_run->c_time=curr_time;
                total=curr_time;
                complete++;
                int TAT=curr_time-p_run->arrivalTime;
                tot_time+=TAT;
                outputFile<<"ID: "<<p_run->id<<"; Orig. Level: "<<p_run->initialQueue<<"; Final Level: "<<r<<" ; Comp. Time(ms): "<<curr_time<<" ;TAT (ms):"<<TAT<<endl;
                p_run=NULL;
            }
        }
        else if(r==4&&p_run!=NULL)
        { 
                if(used==p_run->burstTime)
                {
                    p_run->c_time=curr_time;
                    complete++;
                    int TAT=curr_time-p_run->arrivalTime;
                    total=curr_time;
                    tot_time+=TAT;
                    outputFile<<"ID:"<<" "<<p_run->id<<"; Orig. Level:"<<" "<<p_run->initialQueue<<"; Final Level:"<<" "<<r<<" "<<"; Comp. Time(ms):"<<" "<<curr_time<<" "<<";TAT (ms):"<<TAT<<endl;
                    p_run=NULL;
                    used=0;
                }
                else if(used==timeQuantum)
                {
                    p_run->burstTime-=used;
                        process* p1=NULL;
                        if(!q4.empty()||!v44.empty())
                        {
                            v44.push_back(p_run);
                            p_run=NULL;
                            used=0;
                        }               
                        else used=1;
                }
                else used++;
        }
        for(int i=0;i<v1.size();i++)
        {
            if(v1[i]->arrivalTime==curr_time&&curr_time!=0)
            {
                int x=v1[i]->initialQueue;
                if(x==4) v44.push_back(v1[i]);
                else if(x==3) v33.push_back(v1[i]);
                else if(x==2) v22.push_back(v1[i]);
                else if(x==1) v11.push_back(v1[i]);
            }
        }
        
        sort(v11.begin(),v11.end(),idsort);
        sort(v22.begin(),v22.end(),idsort);  
        sort(v33.begin(),v33.end(),idsort);
        sort(v44.begin(),v44.end(),idsort);
        for(int i=0;i<v11.size();i++) q1.push(v11[i]);
        for(int i=0;i<v22.size();i++) q2.push(v22[i]);
        for(int i=0;i<v33.size();i++) q3.push(v33[i]);
        for(int i=0;i<v44.size();i++) q4.push(v44[i]);
        v11.clear();v22.clear();v33.clear();v44.clear();
         if(!q4.empty())
        {
            process* p=q4.front();
            if(p_run==NULL)
            {
                p_run=p;
                if(p_run->first_run==-1) p_run->first_run=curr_time;
                q4.pop();
                r=4;
                used++;
            }
        }
        else if(!q3.empty())
        {
            if(p_run==NULL)
            {
                    r=3;
                    vector<process *> v;
                    while(!q3.empty())
                    {
                        v.push_back(q3.front());
                        q3.pop();
                    }
                    for(int i=0;i<v.size();i++)
                    {
                        q3.push(v[i]);
                    }
                    p_run=q3.front();
                    q3.pop();
                   if(p_run->first_run==-1) p_run->first_run=curr_time;
            }
        }
        else if(!q2.empty())
        {
            if(p_run==NULL)
            {
                    r=2;
                    vector<process *> v;
                    while(!q2.empty())
                    {
                        v.push_back(q2.front());
                        q2.pop();
                    }
                    for(int i=0;i<v.size();i++)
                    {
                        q2.push(v[i]);
                    }
                    p_run=q2.front();
                    q2.pop();
                    if(p_run->first_run==-1) p_run->first_run=curr_time;
            }
        }
        else if(!q1.empty())
        {
            if(p_run==NULL)
            {
                r=1;
                p_run=q1.front();
                q1.pop();
                if(p_run->first_run==-1) p_run->first_run=curr_time;
            }
        }
        
        curr_time++;
    }
    float size= v1.size();
    float ATAT= tot_time/size*1.00;
    float Throughput=size/total*1000.0;
    outputFile<<"Mean Turnaround time:  "<<ATAT<<" (ms); Throughput:"<<Throughput<<" processes/sec"<<endl;
    
}