#include <bits/stdc++.h>
using namespace std;

double ytop(double xn, double y, double theta, double z)
{
    double ya = -(y + (tan(theta) * (z - xn)));
    // cout<< y<<" "<<z<<" "<<xn<<" "<<z-xn<<" "<<ya<<endl;
    return ya;
}

double bishop(double height, double phi, double c, double theta)
{
    // Assuming starting width  = 2 and starting height = 3
    phi *= 0.0174533, theta *= 0.0174533; // converting to radian
    double gamma = 20.00, x = 2, x1 = 2, y = 2, h = height, z, width, radius;
    bool stop = false;
    height += y;
    width = x;
    radius = sqrt(pow(height, 2) + pow(x, 2));
    width += sqrt(pow(radius, 2) - pow(y, 2));
    // cout<<height<<" "<<width; WORKS

    // Dividing it in parts of width 1 & calculating coordinates
    int n = floor(width);
    double width_last_block = width - floor(width) + 1;
    // cout<<n<<" "<<width_last_block<<"\n";
    vector<pair<double, double>> coord, meancoord;
    vector<double> yt, ht, wt(n), alpha, len, wca, wsa, malpha, term, b(n, 1), fs;
    b[n - 1] = width_last_block;

    // for(int i = 0; i < n; i++) {
    //     cout<<b[i]<<" ";
    // }  WORKS

    x *= -1;
    for (int i = 0; i < n; i++)
    {
        coord.push_back(make_pair(x++, -(sqrt(pow(radius, 2) - pow(x, 2)))));
    }
    coord.push_back(make_pair(x + width_last_block - 1, -(sqrt(pow(radius, 2) - pow(x + width_last_block - 1, 2)))));

    // for(int i = 0; i < coord.size(); i++) {
    //     cout<<coord[i].first<<" "<<coord[i].second<<endl;
    // } //WORKS
    z = (h * tan(theta)) - x1;
    // cout << z;
    double sigmaL = 0, sigmaWCA = 0, sigmaWSA = 0;
    for (int i = 0; i < n; i++)
    {
        meancoord.push_back(make_pair((coord[i].first + coord[i + 1].first) / 2, (coord[i].second + coord[i + 1].second) / 2));
        // cout << meancoord[i].second << endl;
        if (z > meancoord[i].first)
        {
            yt.push_back(ytop(meancoord[i].first, y, theta, z));
        }
        else if (z <= meancoord[i].first && !stop)
        {
            yt.push_back(-y);
        }
        // cout<<yt[i]<<endl;
        ht.push_back(yt[i] - meancoord[i].second);
        // cout<<ht[i]<<" "<<b[i]<<" "<<gamma<<endl;
        wt[i] = b[i] * gamma * ht[i];
        // cout<<wt[i]<<endl;
        alpha.push_back(asin((meancoord[i].first) / radius));
        len.push_back(double(b[i]) / double(cos(alpha[i])));
        sigmaL += len[i];
        wca.push_back(wt[i] * cos(alpha[i]));
        sigmaWCA += wca[i];
        wsa.push_back(wt[i] * sin(alpha[i]));
        sigmaWSA += wsa[i];
    }
    // cout<<sigmaWCA<<" "<<sigmaWSA;
    
    double FS = ((c * sigmaL) + (tan(phi) * sigmaWCA)) / sigmaWSA;
    // cout << c << " " << sigmaL << " " << tan(phi) << " " << sigmaWCA << " " << sigmaWSA << endl;
    cout << FS << endl;
    // cout<<FS<<endl;
    fs.push_back(FS);
    double FSnew = 0, i = 4, sigmaTerm = 0;
    while (abs(FSnew - FS) > 0.0001)
    {
        malpha.clear();
        term.clear();
        FS = fs.back();
        sigmaTerm = 0;
        for (int i = 0; i < n; i++)
        {
            malpha.push_back(cos(alpha[i]) + ((sin(alpha[i]) * tan(phi)) / FS));
            term.push_back((c + (wt[i] * tan(phi)) / malpha[i]));
            sigmaTerm += term[i];
            // cout<<malpha[i]<<" "<<term[i]<<endl;
        }
        // double sigmaTerm = accumulate(term.begin(), term.end(), 0);
        // cout<<sigmaTerm<<endl;
        FSnew = sigmaTerm / sigmaWSA;
        fs.push_back(FSnew);
        cout << FSnew << endl;
    }
    // return fs.back();
    return 0;
}

int main()
{
    // #ifndef ONLINE_JUDGE
    //     freopen("input.txt", "r", stdin);
    //     freopen("output.txt", "w", stdout);
    // #endif // ONLINE_JUDGE

    bishop(7,30, 10, 50);
}