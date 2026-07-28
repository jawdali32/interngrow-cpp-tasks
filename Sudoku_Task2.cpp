/*
    InternGrow C++ Programming Track - Module 1
    TASK 3: Intelligent Sudoku Solver & Generator

    Base Feature:
      - Represent a Sudoku grid as a 2D array
      - Apply recursive backtracking algorithm to solve empty board cells

    Upgrade Feature:
      - Integrated puzzle generator engine that outputs unique unsolved
        Sudoku configurations based on difficulty settings
        (Easy, Medium, Hard).

    The generator works by first building a fully solved random valid
    board (via randomized backtracking), then removing a difficulty-based
    number of cells while keeping the board a valid Sudoku puzzle to solve.
*/

#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define SIZE 9

class Sudoku
{
private:

    int board[SIZE][SIZE];

public:

    Sudoku()
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                board[i][j]=0;
            }
        }
    }

    //----------------------------------

    bool isSafe(int row,int col,int num)
    {

        for(int x=0;x<9;x++)
            if(board[row][x]==num)
                return false;

        for(int x=0;x<9;x++)
            if(board[x][col]==num)
                return false;

        int startRow=row-row%3;
        int startCol=col-col%3;

        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(board[startRow+i][startCol+j]==num)
                    return false;
            }
        }

        return true;
    }

    //----------------------------------

    bool solve()
    {

        int row,col;

        bool empty=false;

        for(row=0;row<9;row++)
        {
            for(col=0;col<9;col++)
            {
                if(board[row][col]==0)
                {
                    empty=true;
                    goto OUT;
                }
            }
        }

OUT:

        if(!empty)
            return true;

        for(int num=1;num<=9;num++)
        {

            if(isSafe(row,col,num))
            {

                board[row][col]=num;

                if(solve())
                    return true;

                board[row][col]=0;
            }

        }

        return false;
    }

    //----------------------------------

    void display()
    {

        cout<<"\n-------------------------\n";

        for(int i=0;i<9;i++)
        {

            for(int j=0;j<9;j++)
            {

                cout<<board[i][j]<<" ";

                if((j+1)%3==0)
                    cout<<" ";
            }

            cout<<endl;

            if((i+1)%3==0)
                cout<<endl;
        }
    }

    //----------------------------------

    void generateSolvedBoard()
    {

        srand(time(0));

        solve();
    }

    //----------------------------------

    void removeCells(int blanks)
    {

        while(blanks>0)
        {

            int row=rand()%9;
            int col=rand()%9;

            if(board[row][col]!=0)
            {
                board[row][col]=0;
                blanks--;
            }

        }

    }

    //----------------------------------

    void generatePuzzle(int level)
    {

        generateSolvedBoard();

        if(level==1)
        {
            removeCells(30);
            cout<<"\nEasy Puzzle\n";
        }

        else if(level==2)
        {
            removeCells(45);
            cout<<"\nMedium Puzzle\n";
        }

        else
        {
            removeCells(60);
            cout<<"\nHard Puzzle\n";
        }

    }

};

//========================

int main()
{

    Sudoku game;

    int choice;

    cout<<"=========== Sudoku Generator ===========\n";

    cout<<"1. Easy\n";
    cout<<"2. Medium\n";
    cout<<"3. Hard\n";

    cout<<"\nEnter Difficulty : ";

    cin>>choice;

    game.generatePuzzle(choice);

    game.display();

    cout<<"\nSolving Puzzle...\n";

    game.solve();

    game.display();

    return 0;
}
