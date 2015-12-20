//  Created by Anurag Singh on 10/12/14.
//  Copyright (c) 2014 Anurag Singh. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void setUtility(int utilityMatrix[][8]){
    utilityMatrix[0][0] = utilityMatrix[0][7] = utilityMatrix[7][7] = utilityMatrix[7][0] = 99;
    utilityMatrix[0][1] = utilityMatrix[0][6] = utilityMatrix[7][6] = utilityMatrix[7][1] = -8;
    utilityMatrix[0][2] = utilityMatrix[0][5] = utilityMatrix[7][5] = utilityMatrix[7][2] = 8;
    utilityMatrix[0][3] = utilityMatrix[0][4] = utilityMatrix[7][4] = utilityMatrix[7][3] = 6;
    utilityMatrix[1][0] = utilityMatrix[1][7] = utilityMatrix[6][7] = utilityMatrix[6][0] = -8;
    utilityMatrix[1][1] = utilityMatrix[1][6] = utilityMatrix[6][6] = utilityMatrix[6][1] = -24;
    utilityMatrix[1][2] = utilityMatrix[1][5] = utilityMatrix[6][5] = utilityMatrix[6][2] = -4;
    utilityMatrix[1][3] = utilityMatrix[1][4] = utilityMatrix[6][4] = utilityMatrix[6][3] = -3;
    utilityMatrix[2][0] = utilityMatrix[2][7] = utilityMatrix[5][7] = utilityMatrix[5][0] = 8;
    utilityMatrix[2][1] = utilityMatrix[2][6] = utilityMatrix[5][6] = utilityMatrix[5][1] = -4;
    utilityMatrix[2][2] = utilityMatrix[2][5] = utilityMatrix[5][5] = utilityMatrix[5][2] = 7;
    utilityMatrix[2][3] = utilityMatrix[2][4] = utilityMatrix[5][4] = utilityMatrix[5][3] = 4;
    utilityMatrix[3][0] = utilityMatrix[3][7] = utilityMatrix[4][7] = utilityMatrix[4][0] = 6;
    utilityMatrix[3][1] = utilityMatrix[3][6] = utilityMatrix[4][6] = utilityMatrix[4][1] = -3;
    utilityMatrix[3][2] = utilityMatrix[3][5] = utilityMatrix[4][5] = utilityMatrix[4][2] = 4;
    utilityMatrix[3][3] = utilityMatrix[3][4] = utilityMatrix[4][4] = utilityMatrix[4][3] = 0;
}

void findValidMoves(char inputMatrix[][8],list<int> &validMoves,char player, char opponent){
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if (inputMatrix[i][j] == '*'){
                bool flag=false;
                bool isValid = false;
                
                //Check in the direction of j+1
                for (int k=j+1; k<8; k++){
                    if (inputMatrix[i][k] == '*') break;
                    if (inputMatrix[i][k] == opponent){
                        flag = true;
                    }
                    if (inputMatrix[i][k] == player && flag == false) break;
                    if (inputMatrix[i][k] == player && flag == true){
                        isValid = true;
                        validMoves.push_back(i);
                        validMoves.push_back(j);
                        break;
                    }
                }
                if (isValid) continue;
                
                flag = false;
                //Check in the direction of i+1,j+1
                for (int m=i+1,k=j+1; m<8 && k<8; m++,k++){
                    if (inputMatrix[m][k] == '*') break;
                    if (inputMatrix[m][k] == opponent){
                        flag = true;
                    }
                    if (inputMatrix[m][k] == player && flag == false) break;
                    if (inputMatrix[m][k] == player && flag == true){
                        isValid = true;
                        validMoves.push_back(i);
                        validMoves.push_back(j);
                        break;
                    }
                }
                if (isValid) continue;
                
                flag = false;
                //Check in the direction of i+1
                for (int k=i+1; k<8; k++){
                    if (inputMatrix[k][j] == '*') break;
                    if (inputMatrix[k][j] == opponent){
                        flag = true;
                    }
                    if (inputMatrix[k][j] == player && flag == false) break;
                    if (inputMatrix[k][j] == player && flag == true){
                        isValid = true;
                        validMoves.push_back(i);
                        validMoves.push_back(j);
                        break;
                    }
                }
                if (isValid) continue;
                
                flag = false;
                //Check in the direction of i+1,j-1
                for (int m=i+1,k=j-1; m<8 && k>-1; m++,k--){
                    if (inputMatrix[m][k] == '*') break;
                    if (inputMatrix[m][k] == opponent){
                        flag = true;
                    }
                    if (inputMatrix[m][k] == player && flag == false) break;
                    if (inputMatrix[m][k] == player && flag == true){
                        isValid = true;
                        validMoves.push_back(i);
                        validMoves.push_back(j);
                        break;
                    }
                }
                if (isValid) continue;
                
                flag = false;
                //Check in the direction of j-1
                for (int k=j-1; k>-1; k--){
                    if (inputMatrix[i][k] == '*') break;
                    if (inputMatrix[i][k] == opponent){
                        flag = true;
                    }
                    if (inputMatrix[i][k] == player && flag == false) break;
                    if (inputMatrix[i][k] == player && flag == true){
                        isValid = true;
                        validMoves.push_back(i);
                        validMoves.push_back(j);
                        break;
                    }
                }
                if (isValid) continue;
                
                flag = false;
                //Check in the direction of i-1,j-1
                for (int m=i-1,k=j-1; m>-1 && k>-1; m--,k--){
                    if (inputMatrix[m][k] == '*') break;
                    if (inputMatrix[m][k] == opponent){
                        flag = true;
                    }
                    if (inputMatrix[m][k] == player && flag == false) break;
                    if (inputMatrix[m][k] == player && flag == true){
                        isValid = true;
                        validMoves.push_back(i);
                        validMoves.push_back(j);
                        break;
                    }
                }
                if (isValid) continue;
                
                flag = false;
                //Check in the direction of i-1
                for (int k=i-1; k>-1; k--){
                    if (inputMatrix[k][j] == '*') break;
                    if (inputMatrix[k][j] == opponent){
                        flag = true;
                    }
                    if (inputMatrix[k][j] == player && flag == false) break;
                    if (inputMatrix[k][j] == player && flag == true){
                        isValid = true;
                        validMoves.push_back(i);
                        validMoves.push_back(j);
                        break;
                    }
                }
                if (isValid) continue;
                
                flag = false;
                //Check in the direction of i-1,j+1
                for (int m=i-1,k=j+1; m>-1 && k<8; m--,k++){
                    if (inputMatrix[m][k] == '*') break;
                    if (inputMatrix[m][k] == opponent){
                        flag = true;
                    }
                    if (inputMatrix[m][k] == player && flag == false) break;
                    if (inputMatrix[m][k] == player && flag == true){
                        isValid = true;
                        validMoves.push_back(i);
                        validMoves.push_back(j);
                        break;
                    }
                }
                if (isValid) continue;
            }
        }
    }
}

void moveAndFlip(int row,int col, char player, char opponent, char computeMatrix[][8],char inputMatrix[][8]){
    computeMatrix[row][col] = player;
    bool flag=false;
    bool isValid=false;
    
    //Check in the direction of col+1
    for (int i=col+1;i<8;i++){
        if (computeMatrix[row][i] == '*') break;
        if (computeMatrix[row][i] == opponent){
            flag = true;
        }
        if (computeMatrix[row][i] == player && flag == false) break;
        if (computeMatrix[row][i] == player && flag == true){
            isValid = true;
            break;
        }
    }
    if (isValid){
        int i=col+1;
        while (inputMatrix[row][i] != player){
            computeMatrix[row][i] = player;
            i++;
        }
    }
    
    isValid = false;
    //Check in the direction of row+1,col+1
    for (int i=row+1,j=col+1;i<8 && j<8;i++,j++){
        if (computeMatrix[i][j] == '*') break;
        if (computeMatrix[i][j] == opponent){
            flag = true;
        }
        if (computeMatrix[i][j] == player && flag == false) break;
        if (computeMatrix[i][j] == player && flag == true){
            isValid = true;
            break;
        }
    }
    if (isValid){
        int i=row+1,j=col+1;
        while (inputMatrix[i][j] != player){
            computeMatrix[i][j] = player;
            i++;
            j++;
        }
    }
    
    isValid = false;
    //Check in the direction of row+1
    for (int i=row+1;i<8;i++){
        if (computeMatrix[i][col] == '*') break;
        if (computeMatrix[i][col] == opponent){
            flag = true;
        }
        if (computeMatrix[i][col] == player && flag == false) break;
        if (computeMatrix[i][col] == player && flag == true){
            isValid = true;
            break;
        }
    }
    if (isValid){
        int i=row+1;
        while (inputMatrix[i][col] != player){
            computeMatrix[i][col] = player;
            i++;
        }
    }
    
    isValid = false;
    //Check in the direction of row+1,col-1
    for (int i=row+1,j=col-1;i<8 && j>-1;i++,j--){
        if (computeMatrix[i][j] == '*') break;
        if (computeMatrix[i][j] == opponent){
            flag = true;
        }
        if (computeMatrix[i][j] == player && flag == false) break;
        if (computeMatrix[i][j] == player && flag == true){
            isValid = true;
            break;
        }
    }
    if (isValid){
        int i=row+1,j=col-1;
        while (inputMatrix[i][j] != player){
            computeMatrix[i][j] = player;
            i++;
            j--;
        }
    }
    
    isValid = false;
    //Check in the direction of col-1
    for (int i=col-1;i>-1;i--){
        if (computeMatrix[row][i] == '*') break;
        if (computeMatrix[row][i] == opponent){
            flag = true;
        }
        if (computeMatrix[row][i] == player && flag == false) break;
        if (computeMatrix[row][i] == player && flag == true){
            isValid = true;
            break;
        }
    }
    if (isValid){
        int i=col-1;
        while (inputMatrix[row][i] != player){
            computeMatrix[row][i] = player;
            i--;
        }
    }
    
    isValid = false;
    //Check in the direction of row-1,col-1
    for (int i=row-1,j=col-1;i>-1 && j>-1;i--,j--){
        if (computeMatrix[i][j] == '*') break;
        if (computeMatrix[i][j] == opponent){
            flag = true;
        }
        if (computeMatrix[i][j] == player && flag == false) break;
        if (computeMatrix[i][j] == player && flag == true){
            isValid = true;
            break;
        }
    }
    if (isValid){
        int i=row-1,j=col-1;
        while (inputMatrix[i][j] != player){
            computeMatrix[i][j] = player;
            i--;
            j--;
        }
    }
    
    isValid = false;
    //Check in the direction of row-1
    for (int i=row-1;i>-1;i--){
        if (computeMatrix[i][col] == '*') break;
        if (computeMatrix[i][col] == opponent){
            flag = true;
        }
        if (computeMatrix[i][col] == player && flag == false) break;
        if (computeMatrix[i][col] == player && flag == true){
            isValid = true;
            break;
        }
    }
    if (isValid){
        int i=row-1;
        while (inputMatrix[i][col] != player){
            computeMatrix[i][col] = player;
            i--;
        }
    }
    
    isValid = false;
    //Check in the direction of row-1,col+1
    for (int i=row-1,j=col+1;i>-1 && j<8;i--,j++){
        if (computeMatrix[i][j] == '*') break;
        if (computeMatrix[i][j] == opponent){
            flag = true;
        }
        if (computeMatrix[i][j] == player && flag == false) break;
        if (computeMatrix[i][j] == player && flag == true){
            isValid = true;
            break;
        }
    }
    if (isValid){
        int i=row-1,j=col+1;
        while (inputMatrix[i][j] != player){
            computeMatrix[i][j] = player;
            i--;
            j++;
        }
    }
}

int findUtility(char player, char opponent, char computeMatrix[][8], int utilityMatrix[][8]){
    int utility=0;
    bool foundPlayer,foundOpponent;
    foundPlayer = false;
    foundOpponent = false;
    
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (computeMatrix[i][j] == player){
                utility = utility + utilityMatrix[i][j];
                foundPlayer = true;
            }
            if (computeMatrix[i][j] == opponent){
                utility = utility - utilityMatrix[i][j];
                foundOpponent = true;
            }
        }
    }
    
    if (!foundPlayer && !foundOpponent) utility = -1000;
    
    return utility;
}

int greedy(char player, char opponent, char inputMatrix[][8], int utilityMatrix[][8]){
    char resultMatrix[8][8],computeMatrix[8][8];
    int maxUtilityValue=-1000;
    ofstream outData;
    list<int> validMoves;
    
    findValidMoves(inputMatrix, validMoves, player, opponent);
    
    //Handle the case when there is no move
    if (validMoves.empty()){
        //cout << "No moves";
        outData.open("output.txt");
        for (int i=0;i<8;i++){
            for (int j=0;j<8;j++){
                outData << inputMatrix[i][j];
            }
            outData << "\n";
        }
        outData.close();
        return 0;
    }
    
    //Code to test findValidMoves
    /*cout << "\nThe valid moves for the given configuration are:";
    for (list<int>::const_iterator it=validMoves.begin(), end = validMoves.end(); it != end; ++it){
        cout << "\nRow: " << *it;
        ++it;
        cout << " Column: " << *it;
    }
    cout << "\n";*/
    
    for (list<int>::const_iterator it=validMoves.begin(), end = validMoves.end(); it != end; ++it){
        int row,col,utility;
        row = *it;
        ++it;
        col = *it;
        
        //Create a temp copy of the input Matrix to compute new moves and to check the utility value
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                computeMatrix[i][j] = inputMatrix[i][j];
            }
        }
        
        moveAndFlip(row,col,player,opponent,computeMatrix,inputMatrix);
        
        //Code to test newly generated matrices
        /*cout << "\nNew Matrix when player positions at row=" << row << " col=" << col <<":\n";
        for (int i=0;i<8;i++){
            for (int j=0;j<8;j++){
                cout << computeMatrix[i][j] << " ";
            }
            cout << "\n";
        }*/
        
        utility = findUtility(player,opponent,computeMatrix,utilityMatrix);
        if (utility > maxUtilityValue){
            maxUtilityValue = utility;
            for (int i=0;i<8;i++){
                for (int j=0;j<8;j++){
                    resultMatrix[i][j] = computeMatrix[i][j];
                }
            }
        }
       //cout << "Utility: " << utility << "\n";
    }
    
    //Code to test for best output matrix
    /*cout << "\nThe best matrix with Utility " << maxUtilityValue << " is:\n";
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            cout << resultMatrix[i][j];
        }
        cout << "\n";
    }*/
    
    outData.open("output.txt");
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            outData << resultMatrix[i][j];
        }
        outData << "\n";
    }
    outData.close();
    
    return 1;
}

int maxValue(char player, char opponent, char inputMatrix[][8], int utilityMatrix[][8], int cutoff, int depth, ofstream &outdata, int alpha, int beta, int currentRow, int currentCol);

bool endGame(char inputMatrix[][8]){
    bool foundX,foundO,matrixFull;
    foundX = false;
    foundO = false;
    matrixFull = true;
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if (inputMatrix[i][j] == 'X') foundX = true;
            if (inputMatrix[i][j] == 'O') foundO = true;
            if (inputMatrix[i][j] == '*') matrixFull = false;
        }
    }
    
    if (matrixFull) return true;
    if (!foundO || !foundX) return true;
    
    return false;
}

void printMinimax (int currentRow, int currentCol, int utility, int depth, char inputMatrix[][8], char player, ofstream &outdata){
    char colChar;
    char startChar = 'a';
    
    colChar = startChar + currentCol;
    if (depth == 0) outdata << "root,";
    else if (currentCol == -1) outdata << "pass,";
    else if (inputMatrix[currentRow][currentCol] == player) outdata << "pass,";
    else outdata << colChar << currentRow+1 << ",";
    
    outdata << depth << ",";
    
    if (utility == -1000) outdata << "-Infinity\n";
    else if (utility == 1000) outdata << "Infinity\n";
    else outdata << utility << "\n";
}

int minimaxValue(char player, char opponent, char inputMatrix[][8], int utilityMatrix[][8], int cutoff, int depth, int type, ofstream &outdata, int currentRow, int currentCol){
    char resultMatrix[8][8],computeMatrix[8][8];
    int bestUtilityValue,row,col,utility;
    list<int> validMoves;
    
    if (type == 1) bestUtilityValue = -1000;
    else bestUtilityValue = 1000;
    utility = bestUtilityValue;
    //Testing Code
    /*cout << "\nCurrent Depth: " << depth;
    cout << "\nCurrent Matrix is:\n";
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            cout << inputMatrix[i][j] << " ";
        }
        cout << "\n";
    }*/
    
    if (depth == cutoff || endGame(inputMatrix)){
        
        //if (depth == 0) printMinimax(currentRow, currentCol, utility, depth, inputMatrix, player, outdata);
        
        if (type == 1) bestUtilityValue = findUtility(player, opponent, inputMatrix, utilityMatrix);
        else bestUtilityValue = findUtility(opponent, player, inputMatrix, utilityMatrix);
        
        printMinimax(currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        
        if (depth == 0){
            outdata.close();
            outdata.open ("matrix.txt");
            for (int i=0; i<8; i++){
                for (int j=0; j<8; j++){
                    outdata << inputMatrix[i][j];
                }
                outdata << "\n";
            }
            outdata.close();
        }
       
        return bestUtilityValue;
    }
    
    findValidMoves(inputMatrix, validMoves, player, opponent);
    
    if (validMoves.empty()){
        if (depth == 0){
            
            printMinimax(currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            bestUtilityValue = minimaxValue(opponent, player, inputMatrix, utilityMatrix, cutoff, depth+1, (type+1)%2, outdata, currentRow, currentCol);
            
            printMinimax(currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            outdata.close();
            outdata.open ("matrix.txt");
            for (int i=0; i<8; i++){
                for (int j=0; j<8; j++){
                    outdata << inputMatrix[i][j];
                }
                outdata << "\n";
            }
            outdata.close();
        }
        else if (currentCol == -1){
            
            printMinimax(currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            if (type == 1) bestUtilityValue = findUtility(player, opponent, inputMatrix, utilityMatrix);
            else  bestUtilityValue = findUtility(opponent, player, inputMatrix, utilityMatrix);
            
            printMinimax(currentRow, currentCol, bestUtilityValue, depth+1, inputMatrix, player, outdata);
            printMinimax(currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        }
        else if (inputMatrix[currentRow][currentCol] == player){
            
            printMinimax(currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            if (type == 1) bestUtilityValue = findUtility(player, opponent, inputMatrix, utilityMatrix);
            else  bestUtilityValue = findUtility(opponent, player, inputMatrix, utilityMatrix);
            
            printMinimax(currentRow, currentCol, bestUtilityValue, depth+1, inputMatrix, player, outdata);
            printMinimax(currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        }
        else {
            
            printMinimax(currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            bestUtilityValue =  minimaxValue(opponent, player, inputMatrix, utilityMatrix, cutoff, depth+1, (type+1)%2, outdata, currentRow, currentCol);
            
            printMinimax(currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        }
        
        return bestUtilityValue;
    }
    
    for (list<int>::const_iterator it=validMoves.begin(), end = validMoves.end(); it != end; ++it){
        row = *it;
        ++it;
        col = *it;
        
        //Create a temp copy of the input Matrix to compute new moves and to check the utility value
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                computeMatrix[i][j] = inputMatrix[i][j];
            }
        }
        
        moveAndFlip(row, col, player, opponent, computeMatrix, inputMatrix);
        
        //Code to print the log
        printMinimax(currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        
        utility = minimaxValue(opponent, player, computeMatrix, utilityMatrix, cutoff, depth+1, (type+1)%2, outdata,row,col);
        
        if (type == 1){
            if (utility > bestUtilityValue){
                bestUtilityValue = utility;
                for (int i=0; i<8; i++){
                    for (int j=0; j<8; j++){
                        resultMatrix[i][j] = computeMatrix[i][j];
                    }
                }
            }
        }
        else {
            if (utility < bestUtilityValue){
                bestUtilityValue = utility;
                for (int i=0; i<8; i++){
                    for (int j=0; j<8; j++){
                        resultMatrix[i][j] = computeMatrix[i][j];
                    }
                }
            }
        }
    }
    
    //Code to print the log
    printMinimax(currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
    
    if (depth == 0){
        outdata.close();
        outdata.open ("matrix.txt");
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                outdata << resultMatrix[i][j];
            }
            outdata << "\n";
        }
        outdata.close();
    }
    
    return bestUtilityValue;
}

int minimaxDecision(char player, char opponent, char inputMatrix[][8], int utilityMatrix[][8],int cutoff){
    ofstream outdata;
    ifstream input;
    string str;
    
    outdata.open("log.txt");
    outdata << "Node,Depth,Value\n";
    
    minimaxValue(player, opponent, inputMatrix, utilityMatrix, cutoff, 0, 1, outdata,-1,-1);
    
    outdata.open("output.txt");
    input.open("matrix.txt");
    
    if (input.is_open()){
        while (getline(input,str)){
            outdata << str << "\n";
        }
    }
    input.close();
    
    input.open("log.txt");
    
    if (input.is_open()){
        while (getline(input,str)){
            outdata << str << "\n";
        }
    }
    input.close();
    outdata.close();
    
    //test code
    /*input.open("output.txt");
    while (getline(input,str)){
        cout << str << "\n";
    }
    input.close();*/
    
    return 1;
}

void printAlphaBeta(int alpha, int beta, int currentRow, int currentCol, int utility, int depth, char inputMatrix[][8], char player, ofstream &outdata){
    char colChar;
    char startChar = 'a';
    
    colChar = startChar + currentCol;
    if (depth == 0) outdata << "root,";
    else if (currentCol == -1) outdata << "pass,";
    else if (inputMatrix[currentRow][currentCol] == player) outdata << "pass,";
    else outdata << colChar << currentRow+1 << ",";
    
    outdata << depth << ",";
    
    if (utility == -1000) outdata << "-Infinity,";
    else if (utility == 1000) outdata << "Infinity,";
    else outdata << utility << ",";
    
    if (alpha == -1000) outdata << "-Infinity,";
    else if (alpha == 1000) outdata << "Infinity,";
    else outdata << alpha << ",";
    
    if (beta == -1000) outdata << "-Infinity\n";
    else if (beta == 1000) outdata << "Infinity\n";
    else outdata << beta << "\n";
}

int minValue(char player, char opponent, char inputMatrix[][8], int utilityMatrix[][8], int cutoff, int depth, ofstream &outdata, int alpha, int beta, int currentRow, int currentCol){
    char resultMatrix[8][8],computeMatrix[8][8];
    int bestUtilityValue,row,col,utility;
    list<int> validMoves;
    
    bestUtilityValue = 1000;
    
    if (depth == cutoff || endGame(inputMatrix)){
        
        //if (depth == 0) printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        
        bestUtilityValue = findUtility(opponent, player, inputMatrix, utilityMatrix);
        
        printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        
        if (depth == 0){
            outdata.close();
            outdata.open ("matrix.txt");
            for (int i=0; i<8; i++){
                for (int j=0; j<8; j++){
                    outdata << inputMatrix[i][j];
                }
                outdata << "\n";
            }
            outdata.close();
        }
        
        return bestUtilityValue;
    }
    
    findValidMoves(inputMatrix, validMoves, player, opponent);
    
    if (validMoves.empty()){
        if (depth == 0){
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            bestUtilityValue = maxValue(opponent, player, inputMatrix, utilityMatrix, cutoff, depth+1, outdata, alpha, beta, currentRow, currentCol);
            if (beta > bestUtilityValue) beta = bestUtilityValue;
            
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            
            outdata.close();
            outdata.open ("matrix.txt");
            for (int i=0; i<8; i++){
                for (int j=0; j<8; j++){
                    outdata << inputMatrix[i][j];
                }
                outdata << "\n";
            }
            outdata.close();
        }
        else if (currentCol == -1){
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            bestUtilityValue = findUtility(opponent, player, inputMatrix, utilityMatrix);
            
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth+1, inputMatrix, player, outdata);
            
            if (bestUtilityValue <= alpha) {
                printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
                return bestUtilityValue;
            }
            
            if (beta > bestUtilityValue) beta = bestUtilityValue;
            
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        }
        else if (inputMatrix[currentRow][currentCol] == player){
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            bestUtilityValue = findUtility(opponent, player, inputMatrix, utilityMatrix);
            
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth+1, inputMatrix, player, outdata);
            
            if (bestUtilityValue <= alpha) {
                printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
                return bestUtilityValue;
            }
            
            if (beta > bestUtilityValue) beta = bestUtilityValue;
            
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        }
        else{
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            bestUtilityValue = maxValue(opponent, player, inputMatrix, utilityMatrix, cutoff, depth+1, outdata, alpha, beta, currentRow, currentCol);
            
            if (bestUtilityValue <= alpha) {
                printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
                return bestUtilityValue;
            }
            
            if (beta > bestUtilityValue) beta = bestUtilityValue;
            
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        }
        
        return bestUtilityValue;
    }
    
    for (list<int>::const_iterator it=validMoves.begin(), end = validMoves.end(); it != end; ++it){
        row = *it;
        ++it;
        col = *it;
        
        //Create a temp copy of the input Matrix to compute new moves and to check the utility value
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                computeMatrix[i][j] = inputMatrix[i][j];
            }
        }
        
        printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        
        moveAndFlip(row, col, player, opponent, computeMatrix, inputMatrix);
        
        utility = maxValue(opponent, player, computeMatrix, utilityMatrix, cutoff, depth+1, outdata, alpha, beta, row, col);
        if (utility < bestUtilityValue){
            bestUtilityValue = utility;
            for (int i=0; i<8; i++){
                for (int j=0; j<8; j++){
                    resultMatrix[i][j] = computeMatrix[i][j];
                }
            }
        }
        
        if (bestUtilityValue <= alpha) {
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            return bestUtilityValue;
        }
        
        if (beta > bestUtilityValue) beta = bestUtilityValue;
        
    }
    
    printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
    
    if (depth == 0){
        outdata.close();
        outdata.open ("matrix.txt");
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                outdata << resultMatrix[i][j];
            }
            outdata << "\n";
        }
        outdata.close();
    }
    return bestUtilityValue;
}

int maxValue(char player, char opponent, char inputMatrix[][8], int utilityMatrix[][8], int cutoff, int depth, ofstream &outdata, int alpha, int beta, int currentRow, int currentCol){
    char resultMatrix[8][8],computeMatrix[8][8];
    int bestUtilityValue,row,col,utility;
    list<int> validMoves;
    
    bestUtilityValue = -1000;
    
    if (depth == cutoff || endGame(inputMatrix)){
        
        //if (depth == 0) printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        
        bestUtilityValue = findUtility(player, opponent, inputMatrix, utilityMatrix);
        
        printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        
        if (depth == 0){
            outdata.close();
            outdata.open ("matrix.txt");
            for (int i=0; i<8; i++){
                for (int j=0; j<8; j++){
                    outdata << inputMatrix[i][j];
                }
                outdata << "\n";
            }
            outdata.close();
        }
        
        return bestUtilityValue;
    }
    
    findValidMoves(inputMatrix, validMoves, player, opponent);
    
    if (validMoves.empty()){
        if (depth == 0){
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            bestUtilityValue = minValue(opponent, player, inputMatrix, utilityMatrix, cutoff, depth+1, outdata, alpha, beta, currentRow, currentCol);
            
            if (bestUtilityValue >= beta) {
                printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
                return bestUtilityValue;
            }
            
            if (alpha < bestUtilityValue) alpha = bestUtilityValue;
            
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            outdata.close();
            outdata.open ("matrix.txt");
            for (int i=0; i<8; i++){
                for (int j=0; j<8; j++){
                    outdata << inputMatrix[i][j];
                }
                outdata << "\n";
            }
            outdata.close();
        }
        else if (currentCol == -1){
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            bestUtilityValue = findUtility(player, opponent, inputMatrix, utilityMatrix);
            
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth+1, inputMatrix, player, outdata);
            
            if (bestUtilityValue >= beta) {
                printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
                return bestUtilityValue;
            }
            
            if (alpha < bestUtilityValue) alpha = bestUtilityValue;
            
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        }
        else if (inputMatrix[currentRow][currentCol] == player){
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            bestUtilityValue = findUtility(player, opponent, inputMatrix, utilityMatrix);
            
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth+1, inputMatrix, player, outdata);
            
            if (bestUtilityValue >= beta) {
                printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
                return bestUtilityValue;
            }
            
            if (alpha < bestUtilityValue) alpha = bestUtilityValue;
            
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        }
        else{
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            
            bestUtilityValue = minValue(opponent, player, inputMatrix, utilityMatrix, cutoff, depth+1, outdata, alpha, beta, currentRow, currentCol);
            
            if (bestUtilityValue >= beta) {
                printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
                return bestUtilityValue;
            }
            
            if (alpha < bestUtilityValue) alpha = bestUtilityValue;
            
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        }
        
        return bestUtilityValue;
    }
    
    for (list<int>::const_iterator it=validMoves.begin(), end = validMoves.end(); it != end; ++it){
        row = *it;
        ++it;
        col = *it;
        
        //Create a temp copy of the input Matrix to compute new moves and to check the utility value
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                computeMatrix[i][j] = inputMatrix[i][j];
            }
        }
        
        printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
        
        moveAndFlip(row, col, player, opponent, computeMatrix, inputMatrix);
        
        utility = minValue(opponent, player, computeMatrix, utilityMatrix, cutoff, depth+1, outdata, alpha, beta, row, col);
        if (utility > bestUtilityValue){
            bestUtilityValue = utility;
            for (int i=0; i<8; i++){
                for (int j=0; j<8; j++){
                    resultMatrix[i][j] = computeMatrix[i][j];
                }
            }
        }
        
        if (bestUtilityValue >= beta) {
            printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
            return bestUtilityValue;
        }
        
        if (alpha < bestUtilityValue) alpha = bestUtilityValue;
        
    }
    
    printAlphaBeta(alpha, beta, currentRow, currentCol, bestUtilityValue, depth, inputMatrix, player, outdata);
    
    if (depth == 0){
        outdata.close();
        outdata.open ("matrix.txt");
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                outdata << resultMatrix[i][j];
            }
            outdata << "\n";
        }
        outdata.close();
    }
    
    return bestUtilityValue;
}

int alphabeta(char player, char opponent, char inputMatrix[][8], int utilityMatrix[][8], int cutoff){
    ofstream outdata;
    ifstream input;
    string str;
    int utility;
    
    outdata.open("log.txt");
    outdata << "Node,Depth,Value,Alpha,Beta\n";
    
    utility = maxValue(player, opponent, inputMatrix, utilityMatrix, cutoff, 0, outdata, -1000, 1000, -1, -1);
    
    outdata.open("output.txt");
    input.open("matrix.txt");
    
    if (input.is_open()){
        while (getline(input,str)){
            outdata << str << "\n";
        }
    }
    input.close();
    
    input.open("log.txt");
    
    if (input.is_open()){
        while (getline(input,str)){
            outdata << str << "\n";
        }
    }
    input.close();
    outdata.close();
    
    //test code
    /*input.open("output.txt");
    while (getline(input,str)){
        cout << str << "\n";
    }*/
    input.close();
    
    return 1;
}

int main (){
    ifstream inData;
    char player,opponent,inputMatrix[8][8];
    int task,cutoffDepth;
    int utilityMatrix[8][8];
    
    inData.open("input.txt");
    
    if(inData.is_open()){
        inData >> task;
        inData >> player;
        inData >> cutoffDepth;
        
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                inData >> inputMatrix[i][j];
            }
        }
    }
    inData.close();
    
    if (player == 'X') opponent = 'O';
    else opponent = 'X';
    
    setUtility(utilityMatrix);
    
    switch (task){
        case 1: greedy(player,opponent,inputMatrix,utilityMatrix);
            break;
            
        case 2: minimaxDecision(player, opponent, inputMatrix, utilityMatrix, cutoffDepth);
            break;
            
        case 3: alphabeta(player, opponent, inputMatrix, utilityMatrix, cutoffDepth);
            break;
            
        default:
            break;
    }
    return 0;
}
