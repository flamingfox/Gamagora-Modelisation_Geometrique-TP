/*
  mid_edge.h

  RICM3 - TP VM  
*/


#ifndef   	MID_EDGE_H_
# define   	MID_EDGE_H_


#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <string>
#include <errno.h>
#include <stdio.h>

#include <vector>
using namespace std;

#include "int_vector.h"

class mid_edge
{
 public:

  mid_edge();
  mid_edge(const mid_edge& );
  ~mid_edge();

  /// init the size to N_vertex
  int init(int N_vertex);

  /// add the index "index_mid_point" to the edge [index_vertex_0,index_vertex_1]
  int add_mid_point(int index_vertex_0,int index_vertex_1,int _index_mid_point);

  /// Check if there the edge [index_vertex_0,index_vertex_1] is recorded
  /** return 1 if recorded, 0 if not */
  int existing_mid_point(int index_vertex_0,int index_vertex_1) const;

  /// return the index of the mid_point for the edge [index_vertex_0,index_vertex_1]
  /** must be recorded */
  int index_mid_point(int index_vertex_0,int index_vertex_1) const;

  /// cout<<
  friend std::ostream& operator<< (std::ostream& stream,const mid_edge& m);

 private:
  
  std::vector <int_vector> position_mid_point;
  std::vector <int_vector> index_of_mid_point; //indexed by position
};


#endif
