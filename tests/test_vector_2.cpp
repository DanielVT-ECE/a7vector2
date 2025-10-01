// test_vector_iterator.cpp
//#define CATCH_CONFIG_MAIN // must be in one
#include "catch2/catch.hpp"
#include <algorithm>  //for std::max
#include "vector.hpp"
#include "matrix.hpp"

TEST_CASE("non-const iterator dereference") {
    dsa::Vector<int> v; bool ok{true};
    for (int i{1}; i<=5; i++) 
        v.push_back(i);
    auto it = v.begin();
    ok = ok && (*it == 1);
    *it = 10;
    ok = ok && (v[0] == 10);
    
    REQUIRE(ok);
}

TEST_CASE("iterator increment and traversal") {
    dsa::Vector<int> v; for (int i=0;i<5;++i) v.push_back(i);
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) sum += *it;
    REQUIRE(sum == (0+1+2+3+4));
}

TEST_CASE("iterator post-increment returns old value") {
    dsa::Vector<int> v; v.push_back(1); v.push_back(2);
    auto it = v.begin();
    auto it_old = it++;
    REQUIRE(*it_old == 1);
    REQUIRE(*it == 2);
}

TEST_CASE("iterator decrement works") {
    dsa::Vector<int> v; for (int i=1;i<=3;++i) v.push_back(i);
    auto it = v.end(); --it; // now points to last
    REQUIRE(*it == 3);
    it--;
    REQUIRE(*it == 2);
}

TEST_CASE("iterator use to insert and erase") {
    dsa::Vector<int> v; for (int i=0;i<3;++i) v.push_back(i); // [0,1,2]
    auto it = v.begin(); ++it; // points to 1
    v.insert(it, 99); // insert before 1
    REQUIRE(v.size() == 4);
    REQUIRE(v[1] == 99);
    // erase the inserted element using iterator
    auto it2 = v.begin(); ++it2;
    v.erase(it2);
    REQUIRE(v.size() == 3);
    REQUIRE(v[1] == 1);
}

// const iterator tests
TEST_CASE("const iterator dereference and traversal") {
    dsa::Vector<int> v; for (int i=0;i<5;++i) v.push_back(i*2);
    const dsa::Vector<int>& cv = v;
    int sum = 0;
    for (auto it = cv.begin(); it != cv.end(); ++it) sum += *it;
    REQUIRE(sum == (0+2+4+6+8));
}

TEST_CASE("const iterator post-increment") {
    dsa::Vector<int> v; v.push_back(7); v.push_back(8);
    const dsa::Vector<int>& cv = v;
    auto it = cv.begin();
    auto old = it++;
    REQUIRE(*old == 7);
    REQUIRE(*it == 8);
}

TEST_CASE("const iterator equality and inequality") {
    dsa::Vector<int> v; for (int i=0;i<3;++i) v.push_back(i);
    const dsa::Vector<int>& cv = v;
    auto a = cv.begin();
    auto b = cv.begin();
    REQUIRE(a == b);
    ++b;
    REQUIRE(a != b);
}

TEST_CASE("const iterator begin/end at empty") {
    dsa::Vector<int> v;
    const dsa::Vector<int>& cv = v;
    REQUIRE(cv.begin() == cv.end());
}

// matrix tests
TEST_CASE("matrix construction and element access") {
    dsa::Matrix m(2,3);
    m(0,0) = 1; m(1,2) = 5;
    REQUIRE(m(0,0) == 1);
    REQUIRE(m(1,2) == 5);
}

TEST_CASE("matrix addition") {
    dsa::Matrix a(1,2), b(1,2);
    a(0,0)=1; a(0,1)=2;
    b(0,0)=3; b(0,1)=4;
    auto c = a + b;
    REQUIRE(c(0,0) == 4);
    REQUIRE(c(0,1) == 6);
}

TEST_CASE("matrix dimensions must match for addition") {
    dsa::Matrix a(2,2), b(1,2);
    REQUIRE_THROWS_AS(a + b, std::out_of_range);
}

TEST_CASE("matrix default zero initialization") {
    dsa::Matrix m(3,1);
    for (int i=0;i<3;++i) REQUIRE(m(i,0) == 0);
}

