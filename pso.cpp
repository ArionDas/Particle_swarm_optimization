#include<bits/stdc++.h>
using namespace std;

int population_size = 10; // population size
double cf1 = 1.5; double cf2 = 1.5; // correction factors
int iter = 20; // maximum iterations
int dim = 2; // dimension
double wt = 0.9; // inertial weight
int size = 10; // size

double global_best = INT_MIN;
double global_best_temp = INT_MIN;

float r(int fanwei)
{
    srand( (unsigned)time(NULL) ); 
    int nTmp =  rand()%fanwei;
    return (float) nTmp / 1000;
}

double find_new_value(int v11, int x11, int pb, int pg) {
    double r1 = r(1000);
    double r2 = r(1000);
    double ans = wt*v11 + cf1*r1*(pb-x11) + cf2*r2*(pg-x11);
    return ans;
}

double value(double x1, double x2) {
    double ans = x1*x1 - x1*x2 + x2*x2 + 2*x1 + 4*x2 + 3;
    return ans;
}

vector<double> f_of_x(vector<double> fx, double position[10][2]) {
    for(int i=0; i<size; i++) {
        double x1 = position[i][0];
        double x2 = position[i][1];
        fx[i] = value(x1,x2);
    }
    return fx;
}

pair<int,int> particle_swarm_algo(double velocity[10][2], double position[10][2], vector<double> fx, double best_position[10][2], pair<int,int> ans) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<2; j++) {
            velocity[i][j] = find_new_value(velocity[i][j], position[i][j], best_position[i][j], ans.first);
            double temp = velocity[i][j] + position[i][j];
            if(temp<0)
                position[i][j] = 0;
            else if(temp>0)
                position[i][j] = 10;
        }
    }

    for(int i=0; i<size; i++) {
        double temp = value(position[i][0],position[i][1]);
        if(temp > fx[i]) {
            fx[i] = temp;
            best_position[i][0] = position[i][0];
            best_position[i][1] = position[i][1];
        }
    }

    global_best_temp = *max_element(fx.begin(),fx.end());
    if(global_best < global_best_temp) {
        global_best = global_best_temp;
        for(int i=0; i<size; i++) {
            if(fx[i]==global_best) {
                ans.first = position[i][0];
                ans.second = position[i][1];
                break;
            }
        }
    }

    return ans;
}

int main() {
    double position[size][2];
    double velocity[size][2];
    vector<double> fx(10);
    double best_position[size][2];

    for(int i=0; i<size; i++) {
        for(int j=0; j<2; j++) {
            position[i][j] = r(1000);
            velocity[i][j] = r(10000);
        }
    }
    fx = f_of_x(fx, position);
    global_best = *max_element(fx.begin(),fx.end());

    for(int i=0; i<size; i++) {
        for(int j=0; j<2; j++) {
            best_position[i][j] = position[i][j];
        }
    }

    pair<int,int> ans;
    for(int i=0; i<size; i++) {
        if(fx[i]==global_best) {
            ans.first = position[i][0];
            ans.second = position[i][1];
            break;
        }
    }
    ans = particle_swarm_algo(velocity, position, fx, best_position, ans);

    cout << "Global Best Value is " << global_best << endl;
    cout << "Corresponding position values are " << ans.first << " " << ans.second << endl;
}