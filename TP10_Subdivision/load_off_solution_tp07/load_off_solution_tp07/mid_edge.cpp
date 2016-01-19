/*
  mid_edge.cpp

  RICM3 - TP VM  
*/


#include "mid_edge.h"



mid_edge::mid_edge(){}
mid_edge::mid_edge(const mid_edge& _m)
{
  position_mid_point=_m.position_mid_point;
  index_of_mid_point=_m.index_of_mid_point;
}
mid_edge::~mid_edge(){position_mid_point.resize(0);index_of_mid_point.resize(0);}

int mid_edge::init(int N_vertex)
{
  position_mid_point.resize(N_vertex);
  index_of_mid_point.resize(N_vertex);

  return 0;
}

int mid_edge::add_mid_point(int index_vertex_0,int index_vertex_1,int _index_mid_point)
{
  if(position_mid_point[index_vertex_0].add(index_vertex_1)==-1
     ||
     position_mid_point[index_vertex_1].add(index_vertex_0)==-1
     )
    return -1;

  index_of_mid_point[index_vertex_0].add(_index_mid_point);
  index_of_mid_point[index_vertex_1].add(_index_mid_point);

  return 0;
}
int mid_edge::existing_mid_point(int index_vertex_0,int index_vertex_1) const
{
  if(index_vertex_0<0 || index_vertex_0>=int(position_mid_point.size()))
    {printf("Error in existing_mid_point(%d,%d) in mid_edge, position_mid_point.size()=%d",index_vertex_0,index_vertex_1,position_mid_point.size());exit(-1);}

  int k_position=0,N_position=position_mid_point[index_vertex_0].size();
  for(k_position=0;k_position<N_position;k_position++)
    if(index_vertex_1==position_mid_point[index_vertex_0][k_position])//find the position
      return 1;

  return 0;//did not find it
}

int mid_edge::index_mid_point(int index_vertex_0,int index_vertex_1) const
{
  if(index_vertex_0<0 || index_vertex_0>=int(position_mid_point.size()))
    {printf("Error in index_mid_point(%d,%d) in mid_edge, position_mid_point.size()=%d",index_vertex_0,index_vertex_1,position_mid_point.size());exit(-1);}

  
  int k_position=0,N_position=position_mid_point[index_vertex_0].size();
  for(k_position=0;k_position<N_position;k_position++)
    if(index_vertex_1==position_mid_point[index_vertex_0][k_position]) //find the position
      return index_of_mid_point[index_vertex_0][k_position];
  
  //else [index_vertex_0,index_vertex_1] not recorded
  printf("Error in index_mid_point(%d,%d) in mid_edge, could not find this edge\n",index_vertex_0,index_vertex_1);
  exit(-1);
}


std::ostream& operator<< (ostream& stream,const mid_edge& m)
{
  int k0=0,k1=0;
  for(k0=0;k0<int(m.position_mid_point.size());k0++)
    {
      for(k1=0;k1<int(m.position_mid_point[k0].size());k1++)
	{
	  std::cout<<"["<<k0<<","<<m.position_mid_point[k0][k1]<<"] => "<<m.index_of_mid_point[k0][k1]<<std::endl;
	}
    }
  return stream;
}
