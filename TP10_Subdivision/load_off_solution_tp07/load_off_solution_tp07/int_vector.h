/*
  int_vector.h

  RICM3 - TP VM  
*/


#ifndef   	INT_VECTOR_H_
# define   	INT_VECTOR_H_

#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <string>
#include <errno.h>
#include <stdio.h>

#include <vector>
using namespace std;

class int_vector
{
 public:
  int_vector();
  int_vector(const int_vector&);
  int_vector(const std::vector<int>&);
  ~int_vector();

  int size() const;
  int resize(int _size);

  int &operator[](int k_vertex);
  int operator[](int k_vertex) const;
  int_vector& operator=(const int_vector&);

  int add_unique(int k_index);
  int add(int k_vertex);
  int add(const std::vector <int>& _int_list);

  /// check if the index exist.
  /** If the index already exists, returns its index
      Else return -1*/
  int exists(int index_to_find) const;

  /// convert to vector
  std::vector<int>& to_vector();
  /// convert to vector
  const std::vector<int>& to_vector() const;


  /// get the vector
  std::vector <int>& get_vector();
  /// get the vector
  const std::vector <int>& get_vector() const;

  friend bool operator==(const int_vector& cont_1,const int_vector& cont_2);
  friend bool operator!=(const int_vector& cont_1,const int_vector& cont_2);

  /// add a constant to every index
  friend int_vector operator+(const int_vector&, int);

  friend ostream& operator<< (ostream& stream, const int_vector& v);

 private:
  
  std::vector <int> int_list;
};


#endif 	    /* !INT_VECTOR_H_ */
