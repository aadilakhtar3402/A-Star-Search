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
    //To store the co-ordinates of parent cell, F-value.
    //F-value = distance moved from starting
    vector<vector<int>> rowp;
    vector<vector<int>> colp;
    int f;
};

bool isvalid(int n, int m, int row, int col)
{
    // Returns true if the co-ordinate lies inside the grid
    return ((row >= 0) && (row < n) && (col >= 0) && (col < m));
}

void display(const stack<Pair>* ans)
{
    stack<Pair> out(*ans);
    Pair p;
    cout<<"[";
    while(!out.empty())
    {
        p = out.top();
        cout<<"("<<p.first<<", "<<p.second<<")";
        if (out.size()!=1)
            cout<<", ";
        out.pop();
    }
    cout<<"]\n";

}

void path(int n, int m, vector<vector<cell>>& cellinfo, Pair end,stack<Pair>* ans)
{

    (*ans).push(end);
    int row = end.first, col = end.second;

    Pair p;
    
    if (cellinfo[row][col].rowp[1][1] == row && cellinfo[row][col].colp[1][1] == col)
    {
        display(ans);
    }

    //checking if the cell is north of parent cell

    if (cellinfo[row][col].rowp[2][1] != -1 && cellinfo[row][col].colp[2][1] != -1)
    {
        p = make_pair(cellinfo[row][col].rowp[2][1], cellinfo[row][col].colp[2][1]); 
        path(n, m, cellinfo, p, ans);
    }

    //checking if the cell is north-east of parent cell

    if (cellinfo[row][col].rowp[2][0] != -1 && cellinfo[row][col].colp[2][0] != -1)
    {
        p = make_pair(cellinfo[row][col].rowp[2][0], cellinfo[row][col].colp[2][0]); 
        path(n, m, cellinfo, p, ans);
    }

    //checking if the cell is east of parent cell

    if (cellinfo[row][col].rowp[1][0] != -1 && cellinfo[row][col].colp[1][0] != -1)
    {
        p = make_pair(cellinfo[row][col].rowp[1][0], cellinfo[row][col].colp[1][0]); 
        path(n, m, cellinfo, p, ans);
    }

    //checking if the cell is south-east of parent cell

    if (cellinfo[row][col].rowp[0][0] != -1 && cellinfo[row][col].colp[0][0] != -1)
    {
        p = make_pair(cellinfo[row][col].rowp[0][0], cellinfo[row][col].colp[0][0]); 
        path(n, m, cellinfo, p, ans);
    }

    //checking if the cell is south of parent cell

    if (cellinfo[row][col].rowp[0][1] != -1 && cellinfo[row][col].colp[0][1] != -1)
    {
        p = make_pair(cellinfo[row][col].rowp[0][1], cellinfo[row][col].colp[0][1]); 
        path(n, m, cellinfo, p, ans);
    }

    //checking if the cell is south-west of parent cell

    if (cellinfo[row][col].rowp[0][2] != -1 && cellinfo[row][col].colp[0][2] != -1)
    {
        p = make_pair(cellinfo[row][col].rowp[0][2], cellinfo[row][col].colp[0][2]); 
        path(n, m, cellinfo, p, ans);
    }

    //checking if the cell is west of parent cell

    if (cellinfo[row][col].rowp[1][2] != -1 && cellinfo[row][col].colp[1][2] != -1)
    {
        p = make_pair(cellinfo[row][col].rowp[1][2], cellinfo[row][col].colp[1][2]); 
        path(n, m, cellinfo, p, ans);
    }

    //checking if the cell is north-west of parent cell

    if (cellinfo[row][col].rowp[2][2] != -1 && cellinfo[row][col].colp[2][2] != -1)
    {
        p = make_pair(cellinfo[row][col].rowp[2][2], cellinfo[row][col].colp[2][2]); 
        path(n, m, cellinfo, p, ans);
    }

    (*ans).pop();

    return;
}

void search(string* grid, int n, int m, Pair start, Pair end)
{
    //stores True if the cell has been visited
    bool closed[n][m];
    memset(closed, false, sizeof(closed));

    int i, j;

    int shortestf = inf;
    //to store the f value of shortest path

    vector<vector<cell>> cellinfo( n , vector<cell> (m));
    //stores all the info about a cell
    //initialising all values f, g, h with inf
    //and parents as (-1, -1) 

    vector<int> a(3,-1); 

    forex(i,0,n)
    {
        forex(j,0,m)
        {
            forex(k,0,3)
            {
                cellinfo[i][j].rowp.push_back(a);
                cellinfo[i][j].colp.push_back(a);
            }
            cellinfo[i][j].f = inf;
        }
    }

    //putting value of f =0 for start so it is chosen first
    i = start.first, j = start.second;
    cellinfo[i][j].rowp[1][1] = i;
    cellinfo[i][j].colp[1][1] = j;
    cellinfo[i][j].f = 0;

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

        int fnew;

        //          NW    N    NE       for cell (i, j)    next cell            parent cell
        //           \    |    /                           N  - (i-1, j)         (2, 1)
        //            \   |   /                            NE - (i-1, j+1)       (2, 0)
        //             \  |  /                             E  - (i, j+1)         (1, 0)
        //       W -----  O  ----- E                       SE - (i+1, j+1)       (0, 0)
        //             /  |  \                             S  - (i+1, j)         (0, 1)
        //            /   |   \                            SW - (i+1, j-1)       (0, 2)
        //           /    |    \                           W  - (i, j-1)         (1, 2)
        //          SW    S    SE                          NW - (i-1, j-1)       (2, 2)

       //going north i.e. to cell(i-1,j)

        if (isvalid(n, m, i-1, j) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i-1][j] == 'E')
            {
                
                reached = true;
                //if the new f value is shorter than shortestf then only print the path
                if (cellinfo[i][j].f + 1 <= shortestf)
                {
                    cellinfo[i-1][j].rowp[2][1] = i;
                    cellinfo[i-1][j].colp[2][1] = j;
                    shortestf = cellinfo[i][j].f + 1;
                }
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i-1][j] == false && grid[i-1][j]=='O')
            {
                fnew = cellinfo[i][j].f + 1;

                if (cellinfo[i-1][j].f == inf || cellinfo[i-1][j].f >= fnew)
                {
                    open.push(make_pair(fnew, make_pair(i-1, j)));

                    cellinfo[i-1][j].rowp[2][1] = i;
                    cellinfo[i-1][j].colp[2][1] = j;
                    cellinfo[i-1][j].f = fnew;
                } 
            }
        }
        
        //going north-east i.e. to cell(i-1,j+1)

        if (isvalid(n, m, i-1, j+1) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i-1][j+1] == 'E')
            {
                
                reached = true;
                if (cellinfo[i][j].f + 1 <= shortestf)
                {
                    cellinfo[i-1][j+1].rowp[2][0] = i;
                    cellinfo[i-1][j+1].colp[2][0] = j;
                    shortestf = cellinfo[i][j].f + 1;
                }
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i-1][j+1] == false && grid[i-1][j+1]=='O')
            {
                fnew = cellinfo[i][j].f + 1;

                if (cellinfo[i-1][j+1].f == inf || cellinfo[i-1][j+1].f >= fnew)
                {
                    open.push(make_pair(fnew, make_pair(i-1, j+1)));

                    cellinfo[i-1][j+1].rowp[2][0] = i;
                    cellinfo[i-1][j+1].colp[2][0] = j;
                    cellinfo[i-1][j+1].f = fnew;
                } 
            }
        } 

        //going east i.e. to cell(i,j+1)

        if (isvalid(n, m, i, j+1) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i][j+1] == 'E')
            {
                
                reached = true;
                if (cellinfo[i][j].f + 1 <= shortestf)
                {
                    cellinfo[i][j+1].rowp[1][0] = i;
                    cellinfo[i][j+1].colp[1][0] = j;
                    shortestf = cellinfo[i][j].f + 1;
                }
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i][j+1] == false && grid[i][j+1]=='O')
            {
                fnew = cellinfo[i][j].f + 1;

                if (cellinfo[i][j+1].f == inf || cellinfo[i][j+1].f >= fnew)
                {
                    open.push(make_pair(fnew, make_pair(i, j+1)));

                    cellinfo[i][j+1].rowp[1][0] = i;
                    cellinfo[i][j+1].colp[1][0] = j;
                    cellinfo[i][j+1].f = fnew;
                } 
            }
        } 

        //going south-east i.e. to cell(i+1,j+1)

        if (isvalid(n, m, i+1, j+1) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i+1][j+1] == 'E')
            {
               
                reached = true;
                if (cellinfo[i][j].f + 1 <= shortestf)
                {
                    cellinfo[i+1][j+1].rowp[0][0] = i;
                    cellinfo[i+1][j+1].colp[0][0] = j;
                    shortestf = cellinfo[i][j].f + 1;
                }
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i+1][j+1] == false && grid[i+1][j+1]=='O')
            {
                fnew = cellinfo[i][j].f + 1;

                if (cellinfo[i+1][j+1].f == inf || cellinfo[i+1][j+1].f >= fnew)
                {
                    open.push(make_pair(fnew, make_pair(i+1, j+1)));

                    cellinfo[i+1][j+1].rowp[0][0] = i;
                    cellinfo[i+1][j+1].colp[0][0] = j;
                    cellinfo[i+1][j+1].f = fnew;
                } 
            }
        } 

        //going south i.e. to cell(i+1,j)

        if (isvalid(n, m, i+1, j) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i+1][j] == 'E')
            {
                
                reached = true;
                if (cellinfo[i][j].f + 1 <= shortestf)
                {
                    cellinfo[i+1][j].rowp[0][1] = i;
                    cellinfo[i+1][j].colp[0][1] = j;
                    shortestf = cellinfo[i][j].f + 1;
                }
                //else return;
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i+1][j] == false && grid[i+1][j]=='O')
            {
                fnew = cellinfo[i][j].f + 1;

                if (cellinfo[i+1][j].f == inf || cellinfo[i+1][j].f >= fnew)
                {
                    open.push(make_pair(fnew, make_pair(i+1, j)));

                    cellinfo[i+1][j].rowp[0][1] = i;
                    cellinfo[i+1][j].colp[0][1] = j;
                    cellinfo[i+1][j].f = fnew;
                } 
            }
        } 

        //going south-west i.e. to cell(i+1,j-1)

        if (isvalid(n, m, i+1, j-1) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i+1][j-1] == 'E')
            {
                
                reached = true;
                if (cellinfo[i][j].f + 1 <= shortestf)
                {
                    cellinfo[i+1][j-1].rowp[0][2] = i;
                    cellinfo[i+1][j-1].colp[0][2] = j;
                    shortestf = cellinfo[i][j].f + 1;
                }
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i+1][j-1] == false && grid[i+1][j-1]=='O')
            {
                fnew = cellinfo[i][j].f + 1;

                if (cellinfo[i+1][j-1].f == inf || cellinfo[i+1][j-1].f >= fnew)
                {
                    open.push(make_pair(fnew, make_pair(i+1, j-1)));

                    cellinfo[i+1][j-1].rowp[0][2]= i;
                    cellinfo[i+1][j-1].colp[0][2] = j;
                    cellinfo[i+1][j-1].f = fnew;
                } 
            }
        } 

        //going west i.e. to cell(i,j-1)

        if (isvalid(n, m, i, j-1) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i][j-1] == 'E')
            {
                
                reached = true;
                if (cellinfo[i][j].f + 1 <= shortestf)
                {
                    cellinfo[i][j-1].rowp[1][2] = i;
                    cellinfo[i][j-1].colp[1][2] = j;
                    shortestf = cellinfo[i][j].f + 1;
                }
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i][j-1] == false && grid[i][j-1]=='O')
            {
                fnew = cellinfo[i][j].f + 1;

                if (cellinfo[i][j-1].f == inf || cellinfo[i][j-1].f >= fnew)
                {
                    open.push(make_pair(fnew, make_pair(i, j-1)));

                    cellinfo[i][j-1].rowp[1][2] = i;
                    cellinfo[i][j-1].colp[1][2] = j;
                    cellinfo[i][j-1].f = fnew;
                } 
            }
        }

        //going north-west i.e. to cell(i-1,j-1)

        if (isvalid(n, m, i-1, j-1) == true)
        {
            //if the next cell is ending point, store its parents and return
            if (grid[i-1][j-1] == 'E')
            {
                
                reached = true;
                if (cellinfo[i][j].f + 1 <= shortestf)
                {
                    cellinfo[i-1][j-1].rowp[2][2] = i;
                    cellinfo[i-1][j-1].colp[2][2] = j;
                    shortestf = cellinfo[i][j].f + 1;
                }
            }

            //if the cell has not been placed in open and and 
            //newf is less than before update it and place it in open
            else if (closed[i-1][j-1] == false && grid[i-1][j-1]=='O')
            {
                fnew = cellinfo[i][j].f + 1;

                if (cellinfo[i-1][j-1].f == inf || cellinfo[i-1][j-1].f >= fnew)
                {
                    open.push(make_pair(fnew, make_pair(i-1, j-1)));

                    cellinfo[i-1][j-1].rowp[2][2] = i;
                    cellinfo[i-1][j-1].colp[2][2] = j;
                    cellinfo[i-1][j-1].f = fnew;
                } 
            }
        }  
    }
  
    if (reached == false) cout<<"no possible path\n";
    else 
    {
        stack<Pair> ans;
        path(n, m, cellinfo, end, &ans);
    }

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