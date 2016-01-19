/*
  int_vector.cpp

  RICM3 - TP VM
*/



#include "int_vector.h"

int_vector::int_vector():
int_list()
{
  int_list.resize(0);
}

int_vector::int_vector(const int_vector &_V):
  int_list()
{
  int_list.resize(_V.int_list.size());
  for(int k=0;k<int(int_list.size());int_list[k]=_V.int_list[k],k++);
}
int_vector::int_vector(const std::vector<int>& _V):
  int_list()
{
  int_list.resize(_V.size());
  for(int k=0;k<int(int_list.size());int_list[k]=_V[k],k++);  
}

int_vector::~int_vector()
{
  int_list.resize(0);
}

int int_vector::size() const
{
  return int_list.size();
}

int int_vector::resize(int _size)
{
  if(_size>=0)
    {
      int_list.resize(_size);
      return(0);
    }
  else
    {printf("error in resize in int_vector, size[%d] is not correct\n",_size);exit(-1);}

  return(-1);
}

int& int_vector::operator[](int k_vertex)
{
  if(k_vertex<0 || k_vertex>=int(int_list.size()))
    {printf("Error in operator [] in int_vector, k_vertex [%d] is not correct because int_list.size()=[%d] \n",k_vertex,int_list.size());exit(-1);}
  return int_list[k_vertex];
}  
int int_vector::operator[](int k_vertex) const
{
  if(k_vertex<0 || k_vertex>=int(int_list.size()))
    {printf("Error in operator [] in int_vector, k_vertex [%d] is not correct because int_list.size()=[%d] \n",k_vertex,int_list.size());exit(-1);}
  return int_list[k_vertex];
}  


int_vector& int_vector::operator=(const int_vector& _V)
{
  int_list.resize(_V.int_list.size());
  for(int k=0;k<int(_V.int_list.size());k++)
    int_list[k] = _V.int_list[k];
  return *this;
}


int int_vector::add_unique(int k_index)
{
  int k=0;
  for(k=0;k<int(int_list.size());k++)//go through the entire list
    if(int_list[k]==k_index)//if already exists
      return(-1);

  int_list.push_back(k_index);//in the other case, add the vertex number
  return 0;
}

int int_vector::add(int k_vertex)
{
  int_list.push_back(k_vertex);
  return(0);
}

int int_vector::add(const std::vector <int>& _int_list)
{
  int k=0;
  for(k=0;k<int(_int_list.size());k++)
    add(_int_list[k]);
  return 0;
}

int int_vector::exists(int index_to_find) const
{
  int k=0;
  int N=size();
  for(k=0;k<N;k++)
    if(index_to_find==int_list[k])
      return k;
  return -1;
}

bool operator==(const int_vector& cont_1,const int_vector& cont_2)
{
  if(cont_1.size()!=cont_2.size())
    return 0;
  for(int k=0;k<cont_1.size();k++)
    if(cont_1[k]!=cont_2[k])
      return 0;
  return 1;
}
bool operator!=(const int_vector& cont_1,const int_vector& cont_2)
{
  if(cont_1==cont_2)
    return 0;
  return 1;
}

std::vector <int>& int_vector::get_vector() {return int_list;}
const std::vector <int>& int_vector::get_vector() const {return int_list;}

ostream& operator<< (ostream& stream, const int_vector& v)
{
  if(v.size()<=0)
    return stream;
  for(int k=0;k<v.size()-1;k++)
    stream<<v[k]<<",";
  stream<<v[v.size()-1];
  return stream;
  
}

int_vector operator+(const int_vector& _vec,int to_add)
{
  int_vector new_vec;
  int k=0,N=_vec.size();
  for(k=0;k<N;k++)
    new_vec.add(_vec[k]+to_add);
  return new_vec;
}


std::vector<int>& int_vector::to_vector() {return int_list;}
const std::vector<int>& int_vector::to_vector() const {return int_list;}
