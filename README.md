# A7: Vector (Part 2)

* You will complete

  * simplified, std::vector like dynamic array called dsa::Vector<T>. 
  * use the vector class to create Matrix class with overload + operator for matrix addition.

* The pseudocode for the functions to help is written in vector.hpp and matrix.hpp

  * std::vector must not be used to implement any of these functions 
    * (No points if std::vector is used even all test cases are passed at Gradescope)

* Starter code is given in 

  * include/vector.hpp
    * Please copy the implementation from part 1 in this vector.hpp or add additional functions (as required in this assignment) in the vector.hpp of part 1.

  * include/matrix.hpp
  * There are two files for testing
    * test_vector_1.cpp (you may copy all of the previous test cases in this)
    * test_vector_2.cpp (this file is to write new test cases for part 2 of the assignment)
    * CMakeLists.txt is configured to use both test files
    * Please note \#define CATCH_CONFIG_MAIN should be in only one test file. This has been commented in test_vector_2.cpp.

* Submissions:

  * Below Files should be submitted

    * vector.hpp

    * matrix.hpp

    * test_vector_2.cpp

    * optional test_vector_1.cpp (this is from Part 1, you may update cases if you want but will not be graded)
  
    * Please don't submit the build or executable folder [negative two points if submitted]
  
  * Autograder [43 Points]
  
    * vector.hpp
  
    * matrix.hpp
  
    * No points if std::vector used even autograder passes all tests
  
  * test_vector_2.cpp [12 points]
  
    * at least four different test cases for iterator
  
      * ```cpp
        // create vector for test cases
        dsa::Vector<int> v;
        for (int i{0}; i < 5; ++i) 
            v.push_back(i);
        ```
  
    * at least four different test cases for const iterator
  
      * ```cpp
        // create const vector for test cases
        dsa::Vector<int> v;
        for (int i{0}; i < 5; ++i) 
            v.push_back(i);
        const dsa::Vector<int>& cv = v;
        ```
  
    * atleast four test cases for matrix (including one for addition)
  
      * ```cpp
        dsa::Matrix a(1, 2), b(1, 2) // declare matrix with default 0
        // assign values as below or in loop
        a(0,0)=1; a(0,1)=2;
        b(0,0)=3; b(0,1)=4;
        ```
  

