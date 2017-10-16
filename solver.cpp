#include<iostream>
#include<algorithm>
#include<vector>
#include<utility>

using namespace std;

struct Block {
	char mat[5][5];
	char pat[5][5];
	int v, w, h, c, u;

	Block(char m[5][5],int hh,int ww,int cc) {
		u = 0;
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				mat[i][j] = m[i][j];
				if(m[i][j] == 'x') {
					u++;
				}
			}
		}
		h = hh;
		w = ww;
		c = cc;
		make();
	}

	void rotate() {
		for(int i = 0; i < 5; i++) {
			for(int j = i+1; j < 5; j++) {
				swap(mat[i][j],mat[j][i]);
			}
		}
		for(int j = 0; j < 2; j++) {
			for(int i = 0; i < 5; i++) {
				swap(mat[i][j],mat[i][4-j]);
			}
		}
		swap(w,h);
		make();
	}

	void make() {
		int tr = 6, tc = 6, br = -1, bc = -1;

		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				if(mat[i][j] == 'x') {
					tr = min(tr,i);
					tc = min(tc,j);
					br = max(br,i);
					bc = max(bc,j);
				}
			}
		}

		for(int i = tr; i <= br; i++) {
			for(int j = tc; j <= bc; j++) {
				pat[i-tr][j-tc] = mat[i][j];
			}
		}
	}

	void print() {
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				cout << mat[i][j] << " ";
			}
			cout << "\n";
		}
	}

	void printPat() {
		for(int i = 0; i < h; i++) {
			for(int j = 0; j < w; j++) {
				cout << pat[i][j] << " ";
			}
			cout << "\n";
		}
	}
};

struct Grid {
	int w,h;
	char mat[20][20];

	Grid(int hh,int ww) {
		h = hh;
		w = ww;
		for(int i = 0; i < h; i++) {
			for(int j = 0; j < w; j++)  {
				mat[i][j] = 'x';
			}
		}
	}

	void print() {
		for(int i = 0; i < h; i++) {
			for(int j = 0; j < w; j++) {
				cout << mat[i][j] << " ";
			}
			cout << "\n";
		}
	}

	void color(Block &b,int si,int sj,bool t=0) {
		int h = b.h;
		int w = b.w;
		int c = b.c;

		for(int i = si; i < si+h; i++) { 
			for(int j = sj; j < sj+w; j++) {
				if(b.pat[i-si][j-sj] == 'x') {
					if(t == 0) {
						mat[i][j] = c+'a';
					} else {
						mat[i][j] = 'x';
					}
				}
			}
		}
	}
};

vector< pair<int,int> > bruteforce(Grid &g,Block &b) {
	vector< pair<int,int> > occ;
	for(int i = 0; i < g.h-b.h+1; i++) {
		for(int j = 0; j < g.w-b.w+1; j++) {
			for(int ii = 0; ii < b.h; ii++) {
				for(int jj = 0; jj < b.w; jj++) {
					if(b.pat[ii][jj] == 'x' && g.mat[i+ii][j+jj] != b.pat[ii][jj]) {
						goto no;
					}
				}
			}
			occ.push_back(make_pair(i,j));
no:;

		}
	}
	return occ;
}

bool solve(vector<Block> &blocks,Grid &g,int t,int cur=0) {
	if(t == 0) {
		g.print();
		return true;
	}
	for(int c = 0; c < 4; c++) {
		vector< pair<int,int> > occ = bruteforce(g,blocks[cur]);
		for(int i = 0; i < (int) occ.size(); i++) {
			g.color(blocks[cur],occ[i].first,occ[i].second);
			if(solve(blocks,g,t-blocks[cur].u,cur+1)) {
				return true;
			}
			g.color(blocks[cur],occ[i].first,occ[i].second,1);
		}
		blocks[cur].rotate();
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,m,h,w,b;
	char mat[5][5];
	vector<Block> blocks;

	cin >> n >> m;

	Grid g(n,m);

	cin >> b;

	for(int i = 0; i < b; i++) {
		cin >> h >> w;
		for(int j = 0; j < 5; j++) {
			for(int k = 0; k < 5; k++) {
				cin >> mat[j][k];
			}
		}
		blocks.push_back(Block(mat,h,w,i));
	}
	if(solve(blocks,g,n*m)) {
		return 0;
	}
	cout << "unable to find solution" << "\n";
	return 0;
}
