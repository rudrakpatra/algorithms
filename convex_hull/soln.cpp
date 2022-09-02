#include <bits/stdc++.h>
using namespace std;

//some of the code is untested ,  but it should work
//if you have any question , please ask

//80% code is written using github copliot 


//this function is untested
int getAngle(pair<int,int> ptA,pair<int,int> ptB,pair<int,int> ptC){
    //get the angle pt1,ptB,ptC with ptB as the vertex
    int x1 = ptB.first - ptA.first;
    int y1 = ptB.second - ptA.second;
    int x2 = ptB.first - ptC.first;
    int y2 = ptB.second - ptC.second;
    int dot = x1*x2 + y1*y2;
    int det = x1*y2 - y1*x2;
    return atan2(det,dot);
}

//this function is tested
int eval(tuple<int,int,int> L,pair<int,int> pt){
    int a,b,c;
    tie(a,b,c)=L;
    return a*pt.first+b*pt.second+c;
}

//this function is tested
tuple<int,int,int> pointToLineEqn(pair<int,int> p1, pair<int,int> p2){
    //line equation is ax+by+c=0
    int a = p2.second - p1.second;
    int b = p1.first - p2.first;
    int c = p1.second* p2.first -p2.second*p1.first ;
    return make_tuple(a,b,c);
}

vector<pair<int,int>> soln(vector<pair<int,int>> p,int n){
    //base case
    if(n<=1){
        return p; 
    }
    //finding the bounding rectangle
    pair<int,int> left=p[0],right=p[0];
    pair<int,int> top=p[0],bottom=p[0];
    for(int i=0;i<n;i++){
        if(p[i].first<left.first){
            left=p[i];
        }
        if(p[i].first>right.first){
            right=p[i];
        }
        if(p[i].second<bottom.second){
            bottom=p[i];
        }
        if(p[i].second>top.second){
            top=p[i];
        }
    }
    //create the lines in cyclic order left, top right bottom
    tuple<int,int,int> L_lt=pointToLineEqn(left,top);
    tuple<int,int,int> L_tr=pointToLineEqn(top,right);
    tuple<int,int,int> L_rb=pointToLineEqn(right,bottom);
    tuple<int,int,int> L_bl=pointToLineEqn(bottom,left);

    //create the Regions
    vector<pair<int,int>> R_lt,R_tr,R_rb,R_bl;
    //for each point calc which region it belongs
    for(int i=0;i<n;i++){
        if(eval(L_lt,p[i])<0)
            R_lt.push_back(p[i]);
        else if(eval(L_tr,p[i])<0)
            R_tr.push_back(p[i]);
        else if(eval(L_rb,p[i])<0)
            R_rb.push_back(p[i]);
        else if(eval(L_bl,p[i])<0)
            R_bl.push_back(p[i]);
    }
    //the points inside the quadrilateral will be discarded
    //recursively call the function for each region
    vector<pair<int,int>> soln_lt=soln(R_lt,R_lt.size());
    vector<pair<int,int>> soln_tr=soln(R_tr,R_tr.size());
    vector<pair<int,int>> soln_rb=soln(R_rb,R_rb.size());
    vector<pair<int,int>> soln_bl=soln(R_bl,R_bl.size());


    //merge the solutions
    vector<pair<int,int>> soln_main;
    int current=0;
    //start with left
    soln_main.push_back(left);
    //we enter R_lt
    //we start and end
    int start=0,end=0;
    int clk_angle=getAngle(top,left,top);
    int cclk_angle=getAngle(left,top,left);
    for(int i=0;i<soln_lt.size();i++){
        if (getAngle(top,left,soln_lt[i])>clk_angle){
            clk_angle=getAngle(top,left,soln_lt[i]);
            start=i;
        }
        if (getAngle(soln_lt[i],top,left)>cclk_angle){
            cclk_angle=getAngle(soln_lt[i],top,left);
            end=i;
        }
    }
    //finally push the elements in soln_lt from start to end in main soln
    for(int i=start;i<end;i++){
        soln_main.push_back(soln_lt[i]);
    }
    //push top
    soln_main.push_back(top);
    //we enter R_tr
    //we start and end
    start=0,end=0;
    clk_angle=getAngle(right,top,right);
    cclk_angle=getAngle(top,right,top);
    for(int i=0;i<soln_tr.size();i++){
        if (getAngle(right,top,soln_tr[i])>clk_angle){
            clk_angle=getAngle(right,top,soln_tr[i]);
            start=i;
        }
        if (getAngle(soln_tr[i],top,right)>cclk_angle){
            cclk_angle=getAngle(soln_tr[i],top,right);
            end=i;
        }
    }
    //finally push the elements in soln_tr from start to end in main soln
    for(int i=start;i<end;i++){
        soln_main.push_back(soln_tr[i]);
    }
    //push right
    soln_main.push_back(right);
    //we enter R_rb
    //we start and end
    start=0,end=0;
    clk_angle=getAngle(bottom,right,bottom);
    cclk_angle=getAngle(right,bottom,right);
    for(int i=0;i<soln_rb.size();i++){
        if (getAngle(bottom,right,soln_rb[i])>clk_angle){
            clk_angle=getAngle(bottom,right,soln_rb[i]);
            start=i;
        }
        if (getAngle(soln_rb[i],bottom,right)>cclk_angle){
            cclk_angle=getAngle(soln_rb[i],bottom,right);
            end=i;
        }
    }
    //finally push the elements in soln_rb from start to end in main soln
    for(int i=start;i<end;i++){
        soln_main.push_back(soln_rb[i]);
    }
    //push bottom
    soln_main.push_back(bottom);
    //we enter R_bl
    //we start and end
    start=0,end=0;
    clk_angle=getAngle(left,bottom,left);
    cclk_angle=getAngle(bottom,left,bottom);
    for(int i=0;i<soln_bl.size();i++){
        if (getAngle(left,bottom,soln_bl[i])>clk_angle){
            clk_angle=getAngle(left,bottom,soln_bl[i]);
            start=i;
        }
        if (getAngle(soln_bl[i],bottom,left)>cclk_angle){
            cclk_angle=getAngle(soln_bl[i],bottom,left);
            end=i;
        }
    }
    //finally push the elements in soln_bl from start to end in main soln
    for(int i=start;i<end;i++){
        soln_main.push_back(soln_bl[i]);
    }

    return soln_main;
}

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].first >> points[i].second;
    }

    vector<pair<int,int>> ans=soln(points, n);
    //print ans
    cout<<"the points are..."<<endl;

    pair<int,int> first_pt=ans[0];
    pair<int,int> last_pt=ans[0];
    
    cout<<last_pt.first<<","<<last_pt.second<<endl;
    for(int i=1;i<ans.size();i++){
        //if current point is same as last point or first point, then don't print
        if(last_pt.first!=ans[i].first || last_pt.second!=ans[i].second){
            if(first_pt.first!=ans[i].first || first_pt.second!=ans[i].second){
            cout<<ans[i].first<<","<<ans[i].second<<endl;
            last_pt=ans[i];
            }
        }
    }
    return 0;
}