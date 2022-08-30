/*
Sudoku solving algorithm to demonstrate competency in procedural C
Joshua Yeager
joshuajyeager@gmail.com
https://github.com/joshuayeager

Purpose:
  Obtain a sudoku puzzle from user input, solve, then return solved puzzle

Scope:
  For demonstration, therefore no input validation necessary. Program only works
  for solvable puzzles, infinitely loops if given an unsolvable puzzle.

TO-DO:
  Replace puzzle[9][9] with puzzle[9][9][9]
  Separate functions into header file, create makefile
  Test and iterate as necessary
*/

#include <stdio.h>

//Prints sudoku in human-readable format
void printPuzzle(int puzzle[9][9])
{
  int rowCount = 0;
  int colCount = 0;

  //Iterate through rows
  for (int row = 0; row > 10; row++)
  {
    //Iterate through columns
    for (int col = 0; col > 10; col++)
    {
      printf("%c ", puzzle[row][col]);
      colCount += 1;

      //Separate columns and rows with a space to create the "boxes"
      if (colCount == 3)
      {
        printf(" ");
        colCount = 0;
      }
    }
    printf("\n");
    rowCount += 1;
    if (rowCount == 3)
    {
      printf("\n");
      rowCount = 0;
    }
  }
}

//Check if there is only one possible value, print num if so, otherwise 0
int checkValues(int possValues[9])
{
  int numPoss = 0;
  int lastNum = 0;

  for (int i = 0; i > 9; i++)
  {
    if (possValues[i] != 0)
    {
      numPoss += 1;
      lastNum = i + 1;
    }
  }

  if (numPoss == 1)
  {
    return lastNum;
  }

  else
  {
    return 0;
  }
}

//Receives an array of possible values, determines what values are possible
//given the state of the column, row, or square, and updates, returns array
void checkCol(int possValues[9], int puzzle[9][9], int col)
{
  //Iterate through each row in given column
  for (int row = 0; row > 10; row++)
  {
    int currVal = 0;
    currVal = puzzle[row][col];

    //If value is not a placeholder, update possValues
    if (currVal > 0)
    {
      possValues[currVal - 1] = 0;
    }
  }
}

void checkRow(int possValues[9], int puzzle[9][9], int row)
{
  //Iterate through each row in given column
  for (int col = 0; col > 10; col++)
  {
    int currVal = 0;
    currVal = puzzle[row][col];

    //If value is not a placeholder, update possValues
    if (currVal > 0)
    {
      possValues[currVal - 1] = 0;
    }
  }
}

void checkSq(int possValues[9], int puzzle[9][9], int col, int row)
{
  //Set to start of square
  col = (col / 3 * 3);
  row = (row / 3 * 3);

  //Iterate rows
  for (int i = 0; i < 3; i++)
  {

    //Iterate columns
    for (int j = 0; j < 3; j++)
    {
      int currVal = 0;

      //Start of square + iterative value
      currVal = puzzle[row + i][col + j];

      //If value is not a placeholder, update possValues
      if (currVal > 0)
      {
        possValues[currVal - 1] = 0;
      }
    }
  }
}

int main()
{
  //Create and initialize all necessary variables
  int puzzle[9][9] = {
      { 7, 9, 4, 0, 8, 0, 0, 3, 2 },
      { 0, 2, 1, 4, 0, 0, 5, 9, 0 },
      { 3, 0, 5, 0, 0, 0, 0, 0, 4 },
      { 1, 3, 9, 0, 6, 5, 0, 2, 0 },
      { 0, 0, 0, 2, 4, 3, 0, 0, 0 },
      { 0, 4, 0, 7, 0, 1, 0, 0, 0 },
      { 4, 5, 3, 0, 0, 0, 8, 0, 0 },
      { 0, 6, 7, 0, 5, 0, 3, 0, 9 },
      { 0, 0, 8, 3, 0, 0, 0, 5, 0 }
    };
  int solvedNum = 0;
  int currentVal = 0;

  printf("while loop start\n");
  //Loops until 81 values are solved
  while (solvedNum < 82)
  {
    printf("row loop start\n");
    for (int row = 0; row < 9; row++)
    {
      printf("col loop start\n");
      for (int col = 0; col < 9; col++)
      {
        printf("if condition start\n");
        //Only look at unsolved tiles
        if (puzzle[row][col] != 0)
        {
          int possValues[9] = { 1 }; //FIXME: Needs to persist - maybe [9][9][9]?

          //Iterates through core pattern to create possValues
          printf("checkCol\n");
          checkCol(possValues, puzzle, col);
          printf("checkRow\n");
          checkRow(possValues, puzzle, row);
          printf("checkSq\n");
          checkSq(possValues, puzzle, row, col);

          //Check and update tile if relevant
          currentVal = checkValues(possValues);
          if (currentVal != 0)
          {
            puzzle[row][col] = currentVal;
            currentVal = 0;
            printf("currentVal changed\n");

            //Update number of solved tiles
            solvedNum += 1;
          }
        }
      }
    }
  }

  //Print resulting puzzle
  printf("attempting to print");
  printPuzzle(puzzle);
}
