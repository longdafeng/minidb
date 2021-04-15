// __CR__
// Copyright (c) 2021 LongdaFeng All Rights Reserved
//
// This software contains the intellectual property of LongdaFeng
// or is licensed to LongdaFeng from third parties.  Use of this
// software and the intellectual property contained therein is
// expressly limited to the terms and conditions of the License Agreement
// under which it is provided by or on behalf of LongdaFeng.
// __CR__
//
// Created by Longda on 2021
//

#include "list_test.h"
#include <cmath>
#include <vector>

ListTest::ListTest() {
  // TODO Auto-generated constructor stub
}

ListTest::~ListTest() {
  // TODO Auto-generated destructor stub
}

template <class T> void ListTest::output(std::list<T> &output) {
  auto it = output.begin();
  for (int i = 0; it != output.end(); it++, i++) {
    std::cout << i << ":" << *it << std::endl;
  }

  std::cout << "!!!!!!!!!!!!" << std::endl;
}

bool single_digit(const int &value) { return (value < 10); }

// a predicate implemented as a class:
struct is_odd {
  bool operator()(const int &value) { return (value % 2) == 1; }
};

void ListTest::testRemove() {
  std::list<int> test;

  for (int i = 0; i < 32; i++) {
    test.push_back(i);
  }

  output(test);
  for (std::list<int>::iterator it = test.begin(); it != test.end(); it++) {
    if (*it == 2) {
      test.erase(it++);
      it--;
      // test.erase(it++); //segment fault
    }
  }

  output(test);

  for (std::list<int>::iterator it = test.begin(); it != test.end(); it++) {
    if (*it == 4) {
      test.erase(it); // segment fault
    }
  }

  output(test);

  test.remove(10);
  output(test);

  test.remove(50);
  output(test);

  test.remove_if(single_digit); // 15 36 17 20 39

  test.remove_if(is_odd()); // 36 20

  output(test);
}

void ListTest::testConstructor() {
  std::list<int> first;          // empty list of ints
  std::list<int> second(4, 100); // four ints with value 100
  std::list<int> third(second.begin(),
                       second.end()); // iterating through second
  std::list<int> fourth(third);       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16, 2, 77, 29};
  std::list<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

  std::cout << "The contents of fifth are: ";
  for (std::list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
    std::cout << *it << ' ';

  std::cout << '\n';
}

void ListTest::testAssign() {
  std::list<int> first;
  std::list<int> second;

  first.assign(7, 100); // 7 ints with value 100

  second.assign(first.begin(), first.end()); // a copy of first

  int myints[] = {1776, 7, 4};
  first.assign(myints, myints + 3); // assigning from array

  std::cout << "Size of first: " << int(first.size()) << '\n';
  std::cout << "Size of second: " << int(second.size()) << '\n';

  for (auto it = first.begin(); it != first.end(); it++)
    std::cout << *it << ' ';
}

void ListTest::testEmplaceFront() {
  std::list<std::pair<int, char>> mylist;

  mylist.emplace_front(10, 'a');
  mylist.emplace_front(20, 'b');
  mylist.emplace_front(30, 'c');

  mylist.push_front(std::pair<int, char>(40, 'd'));

  mylist.emplace(mylist.begin(), 100, 'x');
  mylist.emplace(mylist.begin(), 200, 'y');

  std::cout << "mylist contains:";
  for (auto &x : mylist)
    std::cout << " (" << x.first << "," << x.second << ")";

  std::cout << std::endl;
}

void ListTest::testInsert() {
  std::list<int> mylist;
  std::list<int>::iterator it;

  // set some initial values:
  for (int i = 1; i <= 5; ++i)
    mylist.push_back(i); // 1 2 3 4 5

  it = mylist.begin();
  ++it; // it points now to number 2           ^

  mylist.insert(it, 10); // 1 10 2 3 4 5

  std::cout << *it << std::endl;

  // "it" still points to number 2                      ^
  mylist.insert(it, 2, 20); // 1 10 20 20 2 3 4 5

  --it; // it points now to the second 20            ^

  std::vector<int> myvector(2, 30);
  mylist.insert(it, myvector.begin(), myvector.end());
  // 1 10 20 30 30 20 2 3 4 5
  //               ^
  std::cout << "mylist contains:";
  for (it = mylist.begin(); it != mylist.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void ListTest::testSlice() {
  std::list<int> mylist1, mylist2;
  std::list<int>::iterator it;

  // set some initial values:
  for (int i = 1; i <= 4; ++i)
    mylist1.push_back(i); // mylist1: 1 2 3 4

  for (int i = 1; i <= 3; ++i)
    mylist2.push_back(i * 10); // mylist2: 10 20 30

  it = mylist1.begin();
  ++it; // points to 2

  mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4
  // mylist2 (empty)
  // "it" still points to 2 (the 5th element)

  mylist2.splice(mylist2.begin(), mylist1, it);
  // mylist1: 1 10 20 30 3 4
  // mylist2: 2
  // "it" is now invalid.
  it = mylist1.begin();
  std::advance(it, 3); // "it" points now to 30

  output(mylist1);

  mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
  // mylist1: 30 3 4 1 10 20

  output(mylist1);

  output(mylist2);
}

// a binary predicate implemented as a function:
bool same_integral_part(double first, double second) {
  return (int(first) == int(second));
}

// a binary predicate implemented as a class:
struct is_near {
  bool operator()(double first, double second) {
    return (fabs(first - second) < 5.0);
  }
};

void ListTest::testUnique() {
  double mydoubles[] = {12.15, 2.72,  73.0, 73.0, 12.77, 3.14, 12.77,
                        73.35, 72.25, 15.3, 73,   0,     72.25};
  std::list<double> mylist(mydoubles, mydoubles + 11);

  // 必须提前排好序， 否则unique 没有效果
  mylist.unique(); //  2.72,  3.14, 12.15, 12.77
  // 15.3,  72.25, 73.0,  73.35

  mylist.sort(); //  2.72,  3.14, 12.15, 12.77, 12.77,
  // 15.3,  72.25, 72.25, 73.0,  73.35

  output(mylist);

  mylist.unique(same_integral_part); //  2.72,  3.14, 12.15
  // 15.3,  72.25, 73.0

  mylist.unique(is_near()); //  2.72, 12.15, 72.25

  output(mylist);
}

bool mycomparison(double first, double second) {
  return (int(first) < int(second));
}

void ListTest::testMerge() {
  std::list<double> first, second;

  first.push_back(3.1);
  first.push_back(2.2);
  first.push_back(2.9);

  second.push_back(3.7);
  second.push_back(7.1);
  second.push_back(1.4);

  first.sort();
  second.sort();

  // 必须提前sort
  first.merge(second);

  output(first);

  // (second is now empty)

  second.push_back(2.1);

  first.merge(second, mycomparison);

  output(first);
}

void ListTest::testSwap() {
  std::list<int> first(3, 100);  // three ints with a value of 100
  std::list<int> second(5, 200); // five ints with a value of 200

  first.swap(second);

  output(first);

  output(second);
}

void testList() {
  ListTest test;

  // test.testRemove();
  // test.testConstructor();
  // test.testAssign();
  // test.testEmplaceFront();
  // test.testInsert();
  // test.testSlice();
  // test.testUnique();
  // test.testMerge();
  test.testSwap();
}

int main(int argc, char **argv) { return 0; }
