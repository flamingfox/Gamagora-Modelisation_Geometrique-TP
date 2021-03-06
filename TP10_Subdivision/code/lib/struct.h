#ifndef POINT3_H
#define POINT3_H


#include <iostream>
#include <math.h>



using namespace std ;



# define M_PI		3.14159265358979323846



/******************* point3 ******************/

class	point3{   

public:

	double      x;

	double      y;

	double      z;

	

	point3();                                        // (0,0,0) par defaut

	point3(const double X,const double Y,const double Z);

	

	bool         operator==(const point3 &op)const;

	point3&     operator=(const point3 &op);

	point3      operator+(const point3 &op)const;
	
	point3      operator-(const point3 &op)const;

	point3&     operator*=(const double op);          //produit par un scalaire

	point3      operator*(const double op)const;                 //idem

	float		operator*(const point3& op)const;

	point3&     operator/=(const double op);         //division par un scalaire

	point3      operator/(const double op)const;                 //idem

	point3&		operator^=(const point3& op);

	point3		operator^(const point3& op)const;
	

	void		Permutation(point3 *A, point3 *B);	     // Permutation de deux points

	friend ostream&  operator<<(ostream& p, point3 op);

	friend istream&  operator>>(istream& p, point3 &op);

	float		norme();
	point3&		normalize();

    float dotProduct(const point3& vec2) const;

};

#endif // POINT3_H
