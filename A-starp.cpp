#include <bits/stdc++.h>
using namespace std;

#define inf              1000000007
#define forex(i,a,b)     for(int i=a;i<b;i++)
#define forin(i,a,b)     for(int i=a;i<=b;i++)
#define maxm(a,b)        ((a)>(b) ? (a) : (b))
#define minm(a,b)        ((a)>(b) ? (b) : (a))

typedef pair<int, int> Pair;

typedef pair<int, pair<int, int>> Ppair;

struct cell{
    //To store the co-ordinates of parent cell, 
    //F-value, G-value and H-value
    //G-value = distance moved from starting
    //H-value = Heuristic value
    //F-value = sum pf G and H value
    int rowp, colp, f, g, h;
};

int hvalue(Pair end, int row, int col)
{
    //calculates H-value = sum of absolute difference between the 
    // x and y co-ordinates of present cell and end cell
    return abs(end.first - row)+abs(end.second - col);
}

bool isvalid(int n, int m, int row, int col)
{
    // Returns true if the co-ordinate lies inside the grid
    return ((row >= 0) && (row < n) && (col >= 0) && (col < m));
}

void path(int n, int m, vector<vector<cell>>& cellinfo, Pair end)
{
    int row = end.first, col = end.second;

    stack<Pair> ans;

    while (!(cellinfo[row][col].rowp == row && cellinfo[row][col].colp == col))
    {
        ans.push(make_pair(row, col));
        int trow = cellinfo[row][col].rowp;
        int tcol = cellinfo[row][col].colp;
        row = trow;
        col = tcol;
    }

    ans.push(make_pair(row, col));

    cout<<"[";
    while(!ans.empty())
    {
        Pair p = ans.top();
        ans.pop();
        cout<<"("<<p.first<<", "<<p.second<<")";
        if (ans.size()==0)
            cout<<"]";
        else    
            cout<<", ";
    }

    return;
}

void search(string* grid, int n, int m, Pair start, Pair end)
{
    //stores True if the cell has been visited
    bool closed[n][m];
    memset(closed, false, sizeof(closed));

    int i, j;

    vector<vector<cell>> cellinfo( n , vector<cell> (m));
    //stores all the info about a cell
    //initialising all values f, g, h with inf
    //and parents as -1,-1 

    forex(i,0,n)
    {
        forex(j,0,m)
        {
            cellinfo[i][j].rowp = -1;
            cellinfo[i][j].colp = -1;
            cellinfo[i][j].f = inf;
            cellinfo[i][j].g = inf;
            cellinfo[i][j].h = inf;
        }
    }

    //putting value of f =0 for start so it is chosen first
    i = start.first, j = start.second;
    cellinfo[i][j].rowp = i;
    cellinfo[i][j].colp = j;
    cellinfo[i][j].f = 0;
    cellinfo[i][j].g = 0;
    cellinfo[i][j].h = 0;

    priority_queue<Ppair, vector<Ppair>, greater<Ppair> > open;
    //stores  cell which is to be explored

    open.push(make_pair(0,make_pair(i,j)));

    bool reached = false;

    while(!open.empty())
    {
        Ppair p = open.top();

        //removing the cell from open
        open.pop();

        i = p.second.first, j = p.second.second;
        closed[i][j] = true;

        int fnew, gnew, hnew;

        //          NW    N    NE       for cell (i, j)    next cell          
        //           \    |    /                           N  - (i-1, j)      
        //            \   |   /                            NE - (i-1, j+1)       
        //             \  |  /                             E  - (i, j+1)         
        //       W -----  O  ----- E                       SE - (i+1, j+1)       
        //             /  |  \                             S  - (i+1, j)         
        //            /   |   \                            SW - (i+1, j-1)      
        //           /    |    \                           W  - (i, j-1)         
        //          SW    S    SE                          NW - (i-1, j-1)       

       //going north i.e. to cell(i-1,j)

        if (isvalid(n, m, i-1, j) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i-1][j] == 'E')
            {
                cellinfo[i-1][j].rowp = i;
                cellinfo[i-1][j].colp = j;
                path(n, m, cellinfo, end);
                reached = true;
                return;
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i-1][j] == false && grid[i-1][j]=='O')
            {
                gnew = cellinfo[i][j].g + 1;
                hnew = hvalue(end, i-1, j);
                fnew = gnew + hnew;

                if (cellinfo[i-1][j].f == inf || cellinfo[i-1][j].f > fnew)
                {
                    open.push(make_pair(fnew, make_pair(i-1, j)));

                    cellinfo[i-1][j].rowp = i;
                    cellinfo[i-1][j].colp = j;
                    cellinfo[i-1][j].f = fnew;
                    cellinfo[i-1][j].g = gnew;
                    cellinfo[i-1][j].h = hnew;
                } 
            }
        }
        
        //going north-east i.e. to cell(i-1,j+1)

        if (isvalid(n, m, i-1, j+1) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i-1][j+1] == 'E')
            {
                cellinfo[i-1][j+1].rowp = i;
                cellinfo[i-1][j+1].colp = j;
                path(n, m, cellinfo, end);
                reached = true;
                return;
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i-1][j+1] == false && grid[i-1][j+1]=='O')
            {
                gnew = cellinfo[i][j].g + 1;
                hnew = hvalue(end, i-1, j+1);
                fnew = gnew + hnew;

                if (cellinfo[i-1][j+1].f == inf || cellinfo[i-1][j+1].f > fnew)
                {
                    open.push(make_pair(fnew, make_pair(i-1, j+1)));

                    cellinfo[i-1][j+1].rowp = i;
                    cellinfo[i-1][j+1].colp = j;
                    cellinfo[i-1][j+1].f = fnew;
                    cellinfo[i-1][j+1].g = gnew;
                    cellinfo[i-1][j+1].h = hnew;
                } 
            }
        } 

        //going east i.e. to cell(i,j+1)

        if (isvalid(n, m, i, j+1) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i][j+1] == 'E')
            {
                cellinfo[i][j+1].rowp = i;
                cellinfo[i][j+1].colp = j;
                path(n, m, cellinfo, end);
                reached = true;
                return;
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i][j+1] == false && grid[i][j+1]=='O')
            {
                gnew = cellinfo[i][j].g + 1;
                hnew = hvalue(end, i, j+1);
                fnew = gnew + hnew;

                if (cellinfo[i][j+1].f == inf || cellinfo[i][j+1].f > fnew)
                {
                    open.push(make_pair(fnew, make_pair(i, j+1)));

                    cellinfo[i][j+1].rowp = i;
                    cellinfo[i][j+1].colp = j;
                    cellinfo[i][j+1].f = fnew;
                    cellinfo[i][j+1].g = gnew;
                    cellinfo[i][j+1].h = hnew;
                } 
            }
        } 

        //going south-east i.e. to cell(i+1,j+1)

        if (isvalid(n, m, i+1, j+1) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i+1][j+1] == 'E')
            {
                cellinfo[i+1][j+1].rowp = i;
                cellinfo[i+1][j+1].colp = j;
                path(n, m, cellinfo, end);
                reached = true;
                return;
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i+1][j+1] == false && grid[i+1][j+1]=='O')
            {
                gnew = cellinfo[i][j].g + 1;
                hnew = hvalue(end, i+1, j+1);
                fnew = gnew + hnew;

                if (cellinfo[i+1][j+1].f == inf || cellinfo[i+1][j+1].f > fnew)
                {
                    open.push(make_pair(fnew, make_pair(i+1, j+1)));

                    cellinfo[i+1][j+1].rowp = i;
                    cellinfo[i+1][j+1].colp = j;
                    cellinfo[i+1][j+1].f = fnew;
                    cellinfo[i+1][j+1].g = gnew;
                    cellinfo[i+1][j+1].h = hnew;
                } 
            }
        } 

        //going south i.e. to cell(i+1,j)

        if (isvalid(n, m, i+1, j) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i+1][j] == 'E')
            {
                cellinfo[i+1][j].rowp = i;
                cellinfo[i+1][j].colp = j;
                path(n, m, cellinfo, end);
                reached = true;
                return;
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i+1][j] == false && grid[i+1][j]=='O')
            {
                gnew = cellinfo[i][j].g + 1;
                hnew = hvalue(end, i+1, j);
                fnew = gnew + hnew;

                if (cellinfo[i+1][j].f == inf || cellinfo[i+1][j].f > fnew)
                {
                    open.push(make_pair(fnew, make_pair(i+1, j)));

                    cellinfo[i+1][j].rowp = i;
                    cellinfo[i+1][j].colp = j;
                    cellinfo[i+1][j].f = fnew;
                    cellinfo[i+1][j].g = gnew;
                    cellinfo[i+1][j].h = hnew;
                } 
            }
        } 

        //going south-west i.e. to cell(i+1,j-1)

        if (isvalid(n, m, i+1, j-1) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i+1][j-1] == 'E')
            {
                cellinfo[i+1][j-1].rowp = i;
                cellinfo[i+1][j-1].colp = j;
                path(n, m, cellinfo, end);
                reached = true;
                return;
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i+1][j-1] == false && grid[i+1][j-1]=='O')
            {
                gnew = cellinfo[i][j].g + 1;
                hnew = hvalue(end, i+1, j-1);
                fnew = gnew + hnew;

                if (cellinfo[i+1][j-1].f == inf || cellinfo[i+1][j-1].f > fnew)
                {
                    open.push(make_pair(fnew, make_pair(i+1, j-1)));

                    cellinfo[i+1][j-1].rowp = i;
                    cellinfo[i+1][j-1].colp = j;
                    cellinfo[i+1][j-1].f = fnew;
                    cellinfo[i+1][j-1].g = gnew;
                    cellinfo[i+1][j-1].h = hnew;
                } 
            }
        } 

        //going west i.e. to cell(i,j-1)

        if (isvalid(n, m, i, j-1) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i][j-1] == 'E')
            {
                cellinfo[i][j-1].rowp = i;
                cellinfo[i][j-1].colp = j;
                path(n, m, cellinfo, end);
                reached = true;
                return;
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i][j-1] == false && grid[i][j-1]=='O')
            {
                gnew = cellinfo[i][j].g + 1;
                hnew = hvalue(end, i, j-1);
                fnew = gnew + hnew;

                if (cellinfo[i][j-1].f == inf || cellinfo[i][j-1].f > fnew)
                {
                    open.push(make_pair(fnew, make_pair(i, j-1)));

                    cellinfo[i][j-1].rowp = i;
                    cellinfo[i][j-1].colp = j;
                    cellinfo[i][j-1].f = fnew;
                    cellinfo[i][j-1].g = gnew;
                    cellinfo[i][j-1].h = hnew;
                } 
            }
        }

        //going north-west i.e. to cell(i-1,j-1)

        if (isvalid(n, m, i-1, j-1) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i-1][j-1] == 'E')
            {
                cellinfo[i-1][j-1].rowp = i;
                cellinfo[i-1][j-1].colp = j;
                path(n, m, cellinfo, end);
                reached = true;
                return;
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i-1][j-1] == false && grid[i-1][j-1]=='O')
            {
                gnew = cellinfo[i][j].g + 1;
                hnew = hvalue(end, i-1, j-1);
                fnew = gnew + hnew;

                if (cellinfo[i-1][j-1].f == inf || cellinfo[i-1][j-1].f > fnew)
                {
                    open.push(make_pair(fnew, make_pair(i-1, j-1)));

                    cellinfo[i-1][j-1].rowp = i;
                    cellinfo[i-1][j-1].colp = j;
                    cellinfo[i-1][j-1].f = fnew;
                    cellinfo[i-1][j-1].g = gnew;
                    cellinfo[i-1][j-1].h = hnew;
                } 
            }
        }  
    }

    if (reached == false) cout<<"no possible path\n";

    return;
}




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    //First ine take two inputs n = no. of rows and m = no. of columns 
    //the next n lines take a string input   
    //each string is of length m

    int n,m; //n = no. of rows, m = no. of columns
    cin>>n>>m;
    string grid[n];
    forex(i,0,n)  cin>>grid[i];

    Pair start; //co-ordinates of starting point
    Pair end; //co-ordinates of ending point
    
    forex(i,0,n)
    {
        forex(j,0,m)
        {
            if (grid[i][j]=='S')
                start = make_pair(i,j);
            if (grid[i][j]=='E')
                end = make_pair(i,j);
        }
    }

    search(grid, n, m, start, end);

    return 0;
}