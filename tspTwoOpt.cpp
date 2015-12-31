/***************************
** Program: tspTwoOpt.cpp
** This is the implementation for the tsp algorithm
** optimization that swaps edges and computes if swapping will
** shorten the path
***************************************/

#include <algorithm>
#include <iterator>
#include <vector>

#include "tsp.h"

namespace TSP {

int FindPathDistance(std::vector<City>& S) {
  int result = 0;
  for (unsigned i = 0; i < S.size() - 1; i++) {
    result += S[i].FindDistance(S[i + 1]);
  }
  result += S[0].FindDistance(S[S.size() - 1]);
  return result;
}

/********************************
 ** int twoOpt(std::vector<TSP::City>& S);
 ** Description: Given A-B..C-D try A-C..B-D. If shorter, swap edges.
 **   Store optimized solution in S. call after greedy alg
 ** Parameters: vector list of Cities representing a valid tsp path
 ** returns length of path
 ** pre-conditions: S is a vector of valid City values
 ** post-conditions: S contains the optimized list
 *******************************/

int twoOpt(std::vector<City>& S) {
  bool changed;
  do {
    changed = false;
    for (unsigned int i = 0; i < S.size(); i++) {
      for (unsigned int j = i + 3; j < S.size(); j++) {
        if ((S[i].FindDistance(S[i + 1]) + S[j - 1].FindDistance(S[j])) >
            (S[i].FindDistance(S[j - 1]) + S[i + 1].FindDistance(S[j]))) {
          std::reverse(S.begin() + i + 1, S.begin() + j);
          changed = true;
        }
      }
    }
  } while (changed);
  return FindPathDistance(S);
}

/******************************************************************
 ** int twoHalfOpt(std::vector<TSP::City>&S);
 ** Description: Pick three edges, two adjacent and one non-adjacent.
 **   If path would be shorter, swap edges. Note that two interesting cases
 **   are not covered by two-opt, A-B-C..D-E -> A-C..D-B-E and A-B..C-D-E ->
 *A-D-B..C-E
 **   Store optimized solution in S. call after twoOpt function.
 ** parameters: vector list of Cities representing a valid tsp path
 ** returns length of path
 ** pre-conditions: S is a vector of valid City values
 ** post-conditions: S contains the optimized list
 ******************************************************************/
int twoHalfOpt(std::vector<City>& S) {
  bool changed;
  do {
    changed = false;
    for (int i = 0; i < S.size(); i++) {
      for (int j = i + 3; j < S.size(); j++) {
        // Given A-B-C..D-E try A-C..D-B-E if shorter, swap.
        int opt1_cur = S[i].FindDistance(S[i + 1]) +
                       S[i + 1].FindDistance(S[i + 2]) +
                       S[j - 1].FindDistance(S[j]);
        int option1 = S[i].FindDistance(S[i + 2]) +
                      S[j - 1].FindDistance(S[i + 1]) +
                      S[i + 1].FindDistance(S[j]);
        if (option1 < opt1_cur) {
          TSP::City temp = S[i + 1];
          for (int m = i + 2; m < j; m++) {
            S[m - 1] = S[m];
          }
          S[j - 1] = temp;
          changed = true;
        }
        // Given A-B..C-D-E try A-D-B..C-E if shorter, swap
        int opt2_cur = S[i].FindDistance(S[i + 1]) +
                       S[j - 2].FindDistance(S[j - 1]) +
                       S[j - 1].FindDistance(S[j]);
        int option2 = S[i].FindDistance(S[j - 1]) +
                      S[j - 1].FindDistance(S[i + 1]) +
                      S[j - 2].FindDistance(S[j]);
        if (option2 < opt2_cur) {
          TSP::City temp = S[j - 1];
          for (int m = j - 2; m > i; m--) {
            S[m + 1] = S[m];
          }
          S[i + 1] = temp;
          changed = true;
        }
      }
    }
  } while (changed);
  return FindPathDistance(S);
}
}