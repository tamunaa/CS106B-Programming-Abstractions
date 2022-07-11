/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
#include "pqueue.h"
#include <vector>
using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */

const int dirsX[] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dirsY[] = {1, -1, 0, 0, 1, -1, 1, -1};

void reverse(Vector<Loc>& path){
	for(int i = 0; i < ((int)path.size())/2; i++){
		swap(path[i],path[(int)path.size() - 1 - i]);
	}
}

void findPath(Loc start, Loc end, Vector<Vector<Loc>>& pers, Vector<Loc>& path){
	Loc curLoc = end;

	while(curLoc != start){
		path.push_back(curLoc);
		curLoc = pers[curLoc.row][curLoc.col];
	}
	path.push_back(curLoc);
	reverse(path);	
}

bool isVal(Loc l, int r, int c){
	return (l.row >= 0 && l.col >= 0 && l.row <r && l.col < c);
}


Vector<Loc> shortestPath(Loc start, Loc end,Grid<double>& world, 
						 double costFn(Loc from, Loc to, Grid<double>& world), double heuristic(Loc start, Loc end, Grid<double>& world)) {
	//shevinaxavt ferebs
	// -1 == GRAY; 0 == YELLOW; 1 == GREEN;
	Vector<Vector<int>> colors(world.numRows(), Vector<int>(world.numCols(), -1));
	//shevinaxavt mandzilebs
	Vector<Vector<double>> dis(world.numRows(), Vector<double>(world.numCols(), INT_MAX));
	//shevinaxavt mshoblebs
	Vector<Vector<Loc>> pers(world.numRows(), Vector<Loc>(world.numCols()));
	
	Vector<Loc> path;

	TrailblazerPQueue<Loc> qu;

	//chavadgot sawyisi lokacia
	qu.enqueue(start, 0);
	dis[start.row][start.col] = 0;
	colors[start.row][start.col] = 0;
	colorCell(world, start, YELLOW);

	while(qu.size() != 0){
		Loc cur = qu.dequeueMin();
		colors[cur.row][cur.col] = 1;
		colorCell(world, cur, GREEN);
		if(cur == end)break;
		
		for(int i = 0; i < 8; i++){
			int nrow = cur.row + dirsX[i];
			int ncol = cur.col + dirsY[i];
			Loc neibLoc = makeLoc(nrow, ncol);
			//tu gavcdit sazgvrebs
			if(!isVal(neibLoc, world.numRows(), world.numCols()))continue;
			// tu ukve gvaqvs manamde minimaluri sizrdzis gza
			//if(colors[nrow][ncol] == 1)continue;
			

			//davtvalot ra jdeba gza tu cur idan gadavalt
			double cost = dis[cur.row][cur.col] + costFn(cur, neibLoc, world);

			//tu nacrisferia chavamatot
			if(colors[nrow][ncol] == -1){
				qu.enqueue(neibLoc, cost + heuristic(neibLoc, end, world));
				dis[nrow][ncol] = cost;
				colors[nrow][ncol] = 0;
				pers[nrow][ncol] = cur;
				colorCell(world, neibLoc, YELLOW);

			}else if(colors[nrow][ncol] == 0){//tu yvitelia, ganviaxlot prioriteti tu ase naklebi jdeba
				if(dis[nrow][ncol] < cost)continue;
				
				qu.decreaseKey(neibLoc, cost+ heuristic(neibLoc, end, world));
				dis[nrow][ncol] = cost;
				pers[nrow][ncol] = cur;
				
			}
		}
	}
	findPath(start, end, pers, path);
	//cout << "gamovidaa" << endl;
	
	if(path.size() == 0)error("shortestPath is not implemented yet.");
    
	return path;
}

struct edge{
	Loc a;
	Loc b;
};


void fillqu(PriorityQueue<Edge>& qu, int r, int c){
	int dx[] = {1, 0};
	int dy[] = {0, 1};
	
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			Loc cur = makeLoc(i, j);

			for(int t = 0; t < 2; t++){
				int nx = i + dx[t];
				int ny = j + dy[t];
				Loc neib = makeLoc(nx, ny);
				if(!isVal(neib, r, c)){
					continue;
				}
				
				Edge p; p.start = cur; p.end = neib;
				double n = randomReal(0, 1);
				qu.enqueue(p, n);
			}
		}
	}
}

vector<int> parent;
vector<int> sz;

int count = 0;

void make_set(int v){
	parent[v] = v;
	sz[v] = 1;
    count++;
}

int find_set(int v){
	if(v == parent[v])return v;
	return parent[v] = find_set(parent[v]);
}

Set<Edge> createMaze_vesrion1(int numRows, int numCols) {
	int len = numRows * numCols;
	parent.resize(len, -1);
	sz.resize(len, 0);
	count = 0;
	
	for(int i = 0; i < len; i++){
		make_set(i);
	}

	PriorityQueue<Edge> qu;
	fillqu(qu, numRows, numCols);
	Set<Edge> ans;	

	while(count > 1){
		Edge a = qu.dequeue();

		Loc first = a.start;
		Loc sec = a.end;

		int num1 = first.row * numCols + first.col;
		int num2 = sec.row * numCols + sec.col;
			
		int per1 = find_set(num1);
		int per2 = find_set(num2);

		if(per1 != per2){
			count--;
			if(sz[per1] < sz[per2])swap(per1, per2);
			parent[per2] = per1;
            sz[per1] += sz[per2];
			ans.insert(a);
		}
	}

	if(ans.size() == 0)error("createMaze is not implemented yet.");
    return ans;
}

Set<Edge> createMaze_vesrion2(int numRows, int numCols){
	map<Loc, bool> vis;
	map<Loc, Loc> per;
	PriorityQueue<Loc> qu;
	Set<Edge> ans;
	//chavagdot random wvero
	
	int startX = randomInteger(0, numRows - 1);
	int startY = randomInteger(0, numCols - 1);
	Loc ll = makeLoc(startX, startY);
	vis[ll] = true;
	for(int i = 0; i < 4; i++){
		int nr = startX + dirsX[i];
		int nc = startY + dirsY[i];
		Loc l = makeLoc(nr, nc);
		if(nr >= 0 && nr < numRows && nc >= 0 && nc < numCols){
			qu.enqueue(l,randomReal(0, 1));
			per[l] = ll;
		}
	}
	
	while(qu.size() != 0){
		Loc cur = qu.dequeue();
		vis[cur] = true;

		Edge edg; edg.end = cur; edg.start = per[cur];
		ans.insert(edg);

		for(int i = 0; i < 4; i++){
			int nr = cur.row + dirsX[i];
			int nc = cur.col + dirsY[i];
			Loc l = makeLoc(nr, nc);
			if(nr >= 0 && nr < numRows && nc >= 0 && nc < numCols){
				if(vis[l])continue;
				
				if(vis[l])continue;

				qu.enqueue(l,randomReal(0, 1));
				per[l] = cur;
			}
		}
		while(qu.size() != 0 && vis[qu.peek()])qu.dequeue();
	}
	
	return ans;
}

Set<Edge> createMaze(int numRows, int numCols){

	return createMaze_vesrion1(numRows, numCols);
}
