//  Created by Anurag Singh on 11/18/14.
//  Copyright (c) 2014 Anurag Singh. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>

using namespace std;

class clause {
public:
    string sentence;
    string lhs,rhs;
    void parseString(string input);
};

void clause::parseString(string input){
    sentence = input;
    if (input.find("=>") != string::npos){
        size_t pos = input.find("=>");
        string token;
        lhs = input.substr(0,pos);
        rhs = input.substr(pos+2,input.length());
    }
    else {
        lhs = "";
        rhs = input;
    }
}

bool backwardChaining(string currentQuery, clause *clauses, int numClauses, list<string> &xVals){
    queue<clause> subQueries;
    bool retVal = false;
    
    //cout << "\nCurrent Query: " << currentQuery;
    
    string currentQueryPredicate = currentQuery.substr(0,currentQuery.find("("));
    string currentQueryParam1,currentQueryParam2;
    size_t posOpen,posClose,posComma;
    
    posOpen = currentQuery.find("(");
    posClose = currentQuery.find(")");
    posComma = currentQuery.find(",");
    
    //Get query parameters
    if (posComma == string::npos) {
        currentQueryParam1 = currentQuery.substr(posOpen+1,posClose-posOpen-1);
        currentQueryParam2 = "";
    }
    else {
        currentQueryParam1 = currentQuery.substr(posOpen+1,posComma-posOpen-1);
        currentQueryParam2 = currentQuery.substr(posComma+1,posClose-posComma-1);
    }
    
    //Find all rules which imply the given query
    for (int i=0; i < numClauses; i++) {
        if (!currentQueryPredicate.compare(clauses[i].rhs.substr(0,clauses[i].rhs.find("(")))) {
            //cout << "\n" << clauses[i].sentence;
            string clauseParam1,clauseParam2;
            
            posOpen = clauses[i].rhs.find("(");
            posClose = clauses[i].rhs.find(")");
            posComma = clauses[i].rhs.find(",");
            
            if (posComma == string::npos) {
                clauseParam1 = clauses[i].rhs.substr(posOpen+1,posClose-posOpen-1);
                clauseParam2 = "";
            }
            else {
                clauseParam1 = clauses[i].rhs.substr(posOpen+1,posComma-posOpen-1);
                clauseParam2 = clauses[i].rhs.substr(posComma+1,posClose-posComma-1);
            }
            //cout << "\nCurrentQ Param 1:"<<currentQueryParam1<<" CurrentQ Param 2:"<<currentQueryParam2<<" CurrentCParam1:"<<clauseParam1<<" CurrentCParam2:"<<clauseParam2;
            if (!currentQueryParam1.compare(clauseParam1) && !currentQueryParam2.compare(clauseParam2)) subQueries.push(clauses[i]);
            else if (!currentQueryParam1.compare("x") && !currentQueryParam2.compare(clauseParam2)) subQueries.push(clauses[i]);
            else if (!currentQueryParam1.compare(clauseParam1) && !currentQueryParam2.compare("x")) subQueries.push(clauses[i]);
            else if (!clauseParam1.compare("x") && !currentQueryParam2.compare("x")) subQueries.push(clauses[i]);
            else if (!currentQueryParam1.compare(clauseParam1) && !clauseParam2.compare("x")) subQueries.push(clauses[i]);
            else if (!currentQueryParam1.compare("x") && !clauseParam2.compare("x")) subQueries.push(clauses[i]);
            else if (!clauseParam1.compare("x") && !clauseParam2.compare(currentQueryParam2)) subQueries.push(clauses[i]);
        }
    }
    
    //Loop over all rules to find valid substitutions for query
    while (!subQueries.empty()){
        clause currentClause;
        currentClause = subQueries.front();
        //cout << "\nCurrent Subquery: " << currentClause.sentence;
        subQueries.pop();
        string xValue="x";
        
        string clauseParam1,clauseParam2;
        
        posOpen = currentClause.rhs.find("(");
        posClose = currentClause.rhs.find(")");
        posComma = currentClause.rhs.find(",");
        
        //Get current clause RHS parameters
        if (posComma == string::npos) {
            clauseParam1 = currentClause.rhs.substr(posOpen+1,posClose-posOpen-1);
            clauseParam2 = "";
        }
        else {
            clauseParam1 = currentClause.rhs.substr(posOpen+1,posComma-posOpen-1);
            clauseParam2 = currentClause.rhs.substr(posComma+1,posClose-posComma-1);
        }
        
        //If current clause is a fact, set the retval to true and if the Query contained x,
        //return possible values that x can take
        //Note: Fact will never contain x
        if (currentClause.lhs == ""){
            if ((!currentQueryParam1.compare(clauseParam1) && !currentQueryParam2.compare(clauseParam2)) || (!currentQueryParam1.compare("x") && !currentQueryParam2.compare(clauseParam2)) || (!currentQueryParam1.compare(clauseParam1) && !currentQueryParam2.compare("x"))){
                if (!currentQueryParam1.compare("x")) xVals.push_back(clauseParam1);
                if (!currentQueryParam2.compare("x")) xVals.push_back(clauseParam2);
                retVal = true;
            }
        }
        //Else the current clause is a statement of the form lhs=>rhs
        else {
            list<string> trueXVals;
            queue<string> childQueries;
            string subQueryLHS;
            size_t end=0,start=0;
            
            //If clause contains x and query doesn't, replace x in the query parameter
            //Set xValue=queryParameter,so that it can be used to replace x in lhs
            if (!clauseParam1.compare("x") && currentQueryParam1.compare("x")){
                clauseParam1 = currentQueryParam1;
                xValue = currentQueryParam1;
            }
            else if (!clauseParam2.compare("x") && currentQueryParam2.compare("x")){
                clauseParam2 = currentQueryParam2;
                xValue = currentQueryParam2;
            }
            
            //Find all lhs terms and replace all "x"s with xValue
            end = currentClause.lhs.find("&",end);
            while (end != string::npos){
                subQueryLHS = currentClause.lhs.substr(start,end-start);
                
                if (subQueryLHS.find("(x,") != string::npos) subQueryLHS.replace(subQueryLHS.find("(x,")+1, 1, xValue);
                if (subQueryLHS.find(",x)") != string::npos) subQueryLHS.replace(subQueryLHS.find(",x)")+1, 1, xValue);
                if (subQueryLHS.find("(x)") != string::npos) subQueryLHS.replace(subQueryLHS.find("(x)")+1, 1, xValue);
                
                childQueries.push(subQueryLHS);
                end++;
                start = end;
                end = currentClause.lhs.find("&",end);
            }
            subQueryLHS = currentClause.lhs.substr(start,currentClause.lhs.length()-start);
            
            if (subQueryLHS.find("(x,") != string::npos) subQueryLHS.replace(subQueryLHS.find("(x,")+1, 1, xValue);
            if (subQueryLHS.find(",x)") != string::npos) subQueryLHS.replace(subQueryLHS.find(",x)")+1, 1, xValue);
            if (subQueryLHS.find("(x)") != string::npos) subQueryLHS.replace(subQueryLHS.find("(x)")+1, 1, xValue);
            
            childQueries.push(subQueryLHS);
            
            //Find out if lhs is true
            bool childRetValue=true,first=true;
            while (!childQueries.empty()){
                string currentChildQuery;
                currentChildQuery = childQueries.front();
                childQueries.pop();
                list<string> tempTrueXVals;
                
                //If the childQuery doesn't contain x and if it false, break out of the while loop
                //and check next rule. If it is true, proceed to check next childQuery.
                if ((currentChildQuery.find("(x,") == string::npos) && (currentChildQuery.find("(x)") == string::npos) && (currentChildQuery.find(",x)") == string::npos)){
                    childRetValue = backwardChaining(currentChildQuery, clauses, numClauses, tempTrueXVals);
                    if (!childRetValue) break;
                }
                //If childQuery contains x, find out the x values for which childQuery is true
                else {
                    childRetValue = backwardChaining(currentChildQuery, clauses, numClauses, tempTrueXVals);
                    //If childQuery is false, break out of while loop and check next rule
                    if (!childRetValue) break;
                    //If first childQuery with x, build an array of true xVals
                    if (first){
                        first = false;
                        if (tempTrueXVals.empty()){
                            break;
                        }
                        else {
                            trueXVals = tempTrueXVals;
                        }
                    }
                    //If not the first childQuery with x, remove all xVals from array which are not in the intersection
                    //If xVals becomes empty, then break out as the currentClause is false
                    else {
                        for (list<string>::iterator it1=trueXVals.begin(); it1!=trueXVals.end(); ++it1){
                            bool found = false;
                            if (tempTrueXVals.empty()) found = true;
                            for (list<string>::iterator it2=tempTrueXVals.begin(); it2!=tempTrueXVals.end(); ++it2){
                                if (!(*it1).compare((*it2))) found = true;
                            }
                            if (!found) {
                                trueXVals.erase(it1);
                                --it1;
                            }
                        }
                        
                        if (trueXVals.empty()) {
                            childRetValue = false;
                            break;
                        }
                    }
                }
            }
            //If we have reached here, it means that the current clause is true
            if (childRetValue){
                retVal = true;
                if ((!clauseParam1.compare("x") && !currentQueryParam1.compare("x")) || (!clauseParam1.compare("x") && !currentQueryParam1.compare("x"))){
                    for (list<string>::iterator it1=trueXVals.begin(); it1!=trueXVals.end(); ++it1){
                        xVals.push_back(*it1);
                    }
                }
                else if (clauseParam1.compare("x") && !currentQueryParam1.compare("x")){
                    xVals.push_back(clauseParam1);
                }
                else if (clauseParam2.compare("x") && !currentQueryParam2.compare("x")){
                    xVals.push_back(clauseParam2);
                }
            }
        }
    }
    
    return retVal;
}

int main(){
    ifstream inData;
    ofstream outData;
    string query;
    int numClauses;
    string input;
    clause *clauses;
    list<string> xVals;
    inData.open("input.txt");
    bool ret;
    
    if (inData.is_open()) {
        inData >> query;
        inData >> numClauses;
        clauses = new clause[numClauses];
        for (int i=0; i < numClauses; i++) {
            inData >> input;
            clauses[i].parseString(input);
        }
    }
    
    ret=backwardChaining(query,clauses,numClauses,xVals);
    
    outData.open("output.txt");
    if (ret) {
        //cout << "\nThe KB is true\n";
        outData << "TRUE";
    }
    else {
        //cout << "\nThe KB is false\n";
        outData << "FALSE";
    }
    outData.close();
    
    return 0;
}