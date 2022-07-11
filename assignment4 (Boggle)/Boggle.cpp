/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "Set.h"
using namespace std;

/* Constants */
Lexicon lex;
const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

bool canGetWord(Vector<Vector<char>>& grid, Vector<Vector<bool>>& vis, string word, int ind, int row, int col);
void rollTheCubes(Vector<Vector<char>>& grid);
void generateStandartBoard(Vector<Vector<char>>& grid);
bool isWordOnTheGrid(Vector<Vector<char>>& grid, string str);
void playersTurn(Vector<Vector<char>>& grid, Vector<string>& playersWords);
void findAllWords(Vector<Vector<char>>& grid, Set<string>& words);
void game();

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();

/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
	lex.addWordsFromFile("EnglishWords.dat");
    welcome();
    giveInstructions();
	game();	
    return 0;
}

void getRandomSides(Vector<Vector<char>>& grid){
	int ind = 0;
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[0].size(); j++){
			string str = STANDARD_CUBES[ind];
			int r = randomInteger(0, str.size()-1);
			char randChar = str.at(r);
			grid[i][j] = randChar;
			ind++;
		}
	}
}
void swap(Vector<Vector<char>>& grid){
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[0].size(); j++){
			int randomNum = randomInteger(0, grid.size() * grid[0].size()-1);
			int col = randomNum % grid[0].size();
			int row = randomNum / grid[0].size();

			char tmp = grid[i][j];
			grid[i][j] = grid[row][col];
			grid[row][col] = tmp;
		}
	}
}

void rollTheCubes(Vector<Vector<char>>& grid){
	// jer avirchiot characterebi da mere davsvapot
	getRandomSides(grid);
	// davsvapot
	swap(grid);
}

void drawGrid(Vector<Vector<char>>& grid){
	drawBoard(grid.size(), grid[0].size());
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[0].size(); j++){
			labelCube(i, j, grid[i][j]);
		}
	}
}
void generateStandartBoard(Vector<Vector<char>>& grid){
	rollTheCubes(grid);
	drawGrid(grid);
}



bool contains(Vector<string> vec, string str){
	for(int i = 0; i < vec.size(); i++){
		if(vec[i] == str)return true;
	}
	return false;
}

void unhighlight(Vector<Vector<char>>& grid){
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[0].size(); j++){
			highlightCube(i,j, false);
		}
	}
}
void playersTurn(Vector<Vector<char>>& grid, Vector<string>& playersWords){
	while(true){
		string str = getLine();
		if(str == "")break;
		if(str.size() < 4){
			cout << "the length is less then 4 " << endl;
			continue;
		}
		if(contains(playersWords, str)){
			cout << "you have alrady found this word " << endl;
			continue;
		}
		str = toUpperCase(str);
		// cota upiratesoba ;dd
		/*
		if(!lex.contains(str)){
			cout << "it's not a valid english word "<< endl; 
			continue;
		}
		*/
		bool canFind = isWordOnTheGrid(grid, str);
		if(!canFind){
			cout << "this word cannot be found on this board" << endl;
			continue;
		}
		playersWords.push_back(str);
		recordWordForPlayer(str, HUMAN);
		pause(117);
		unhighlight(grid);
	}
}
const int dirsX[8] = {1, 1, 1, 0, 0, -1, -1, -1};
const int dirsY[8] = {1,-1, 0, 1, -1, 1, -1, 0};
void rec(Vector<Vector<char>>& grid, Set<string>& words, Vector<Vector<bool>>& vis, string p, int row, int col){
	if(lex.contains(p) && p.size() >= 4){
		words.add(p);
	}
	if(row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size())return;
	if(!lex.containsPrefix(p) || vis[row][col])return;
	
	p += grid[row][col];
	for(int i = 0; i < 8; i++){
		int nr = row + dirsX[i];
		int nc = col + dirsY[i];
		vis[row][col] = true;
		rec(grid, words, vis, p, nr, nc);
		vis[row][col] = false;
	}
}

void findAllWords(Vector<Vector<char>>& grid, Set<string>& words){
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[0].size(); j++){
			Vector<Vector<bool>> vis(grid.size(), Vector<bool>(grid[0].size(), false));
			rec(grid, words, vis, "", i, j);
		}
	}
}
void filterWords(Set<string>& words, Vector<string>& playersWords){
	for(int i = 0; i < playersWords.size(); i++){
		words -= playersWords[i];
	}
}
void showCompsWords(Set<string>& words){
	foreach(string s in words){
		recordWordForPlayer(s, COMPUTER);
	}
}
bool askToPlayAgain(){
	string ans = getLine("wanna play again? (write yes or no) ");
	if(toLowerCase(ans) == "no")return false;
	return true;
}
void fillGrid(Vector<Vector<char>>& grid, string line){
	int ind = 0;
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[0].size(); j++){
			grid[i][j] = line[ind];
			ind++;
		}
	}
}
void game(){
	int size = 4;
	Vector<Vector<char>> grid(size, Vector<char>(size));
	string ans = getLine("wanna enter your grid ? (say yes or no) ");
	if(ans == "no"){
		generateStandartBoard(grid);
	}else{
		string line;
		while(line.size() != 16){
			line = getLine("enter string of letters of length 16 ");
		}
		line = toUpperCase(line);
		fillGrid(grid, line);
		drawGrid(grid);
	}
	
	Vector<string> playersWords;
	Set<string> words;
	findAllWords(grid, words);

	playersTurn(grid, playersWords);
	// uzeris gamocnobili sityvebi rom agar chavtvalot
	filterWords(words, playersWords);
	showCompsWords(words);

	if(askToPlayAgain())game();
}
/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */
void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}
/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */
void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

bool canGetWord(Vector<Vector<char>>& grid, Vector<Vector<bool>>& vis, string word, int ind, int row, int col){
	if(ind == word.size())return true;
	if(row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size())return false;
	if(word[ind] != grid[row][col] || vis[row][col])return false;
	for(int i = 0; i < 8; i++){
		int nr = row + dirsX[i];
		int nc = col + dirsY[i];
		vis[row][col] = true;
		highlightCube(row,col, true);
		if(canGetWord(grid, vis, word, ind + 1, nr, nc))return true;
		highlightCube(row,col, false);
		vis[row][col] = false;
	}
}
bool isWordOnTheGrid(Vector<Vector<char>>& grid, string str){
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[0].size(); j++){
			Vector<Vector<bool>> vis(grid.size(), Vector<bool>(grid[0].size()));
			if(canGetWord(grid, vis, str,0,i, j))return true;
		}
	}
	return false;
}
