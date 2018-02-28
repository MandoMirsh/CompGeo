/*
 * geom2.cxx
 * 
 * Copyright 2018 Сергей Черевков <seriu007@debcom>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#include <iostream>

const long double EPS = 1E-15;
struct Coord {	
	long double x,y;

	Coord(){
		x=0;
		y=0;
	};

	Coord(long double a,long double b=0){
		x=a;
		y=b;
	};

 bool operator==(Coord ob2){
	 return ((x=ob2.x)&&(y=ob2.y));
 };

 friend std::ostream& operator<< (std::ostream& output, Coord ob){
	output<<'('<<ob.x<<" , "<<ob.y<<')';
	return output;
 };

 friend std::istream& operator>> (std::istream& input, Coord & ob){
	 input>>ob.x>>ob.y;
	 return  input;
 };

 friend int turn( Coord a,Coord b, Coord c);
};

class Segment {

public:
	Coord a,b;
	bool vert;

	Segment(long double x2,long double y2){
		Coord ob1;
		a = ob1;
		Coord ob2(x2,y2);
		b = ob2;
		vert = (a.y == b.y);
	};

	Segment(long double x1,long double y1,long double x2,long double y2){
		Coord ob1(x1,y1), ob2(x2,y2);
		a = ob1;
		b = ob2;
		vert = (a.y == b.y);
	};

  bool operator==(Segment ob2){
	  return (((a==ob2.a)&&(b==ob2.b))||((a==ob2.b)&&(b==ob2.a)));
  };

 friend std::ostream& operator<< (std::ostream& output, Segment ob){
	output<<'{'<<ob.a<<" ; "<<ob.b<<'}';
	return output;
 };

 friend std::istream& operator>> (std::istream& input, Segment & ob){
	 input>>ob.a>>ob.b;
	 return  input;
 }; 

void orientx(){
	if (a.x>b.x)
		{
			Coord s;
			s=a;
			a=b;
			b=s;
		}
}

void orienty(){
	if (a.y>b.y)
		{
			Coord s;
			s=a;
			a=b;
			b=s;
		}
}
};
class IntCoord: public Coord{
public:
	int num;

	IntCoord(const int n,const long double xob, const long double yob){
		x = xob;
		y = yob;
		num = n;
	}

	IntCoord(const int n,Coord ob){
		x = ob.x;
		y = ob.y;
		num = n;
	}

	IntCoord(){
		x=0;
		y=0;
		num=0;
	}

friend void sortx( const int n, IntCoord * p){
	IntCoord ob(1,0,0);
	for (int i=0;i<n-1;i++)
		for (int j=i+1;j<n;j++)
		{
			if (p[i].x>p[j].x)
			{	ob = p[i];
				p[i] = p[j];
				p[j] = ob;
			}
		}
	return;
}

friend void sorty( const int n, IntCoord * p){
	IntCoord ob(1,0,0);
	for (int i=0;i<n-1;i++)
		for (int j=i+1;j<n;j++)
		{
			if (p[i].y>p[j].y)
			{	ob = p[i];
				p[i] = p[j];
				p[j] = ob;
			}
		}
	return;
}

};	

class TestName{
	char c1,c2,c3,c4,c5,c6;
public:

 friend std::ostream& operator<< (std::ostream& output, TestName ob){
	output<<ob.c1<<ob.c2<<ob.c3<<ob.c4<<ob.c5<<ob.c6;
	return output;
}	

 friend std::istream& operator>> (std::istream& input, TestName ob){
	input>>ob.c1>>ob.c2>>ob.c3>>ob.c4>>ob.c5>>ob.c6;
	return input;
}			
};

bool ifinx(const long double x, Segment ob){
ob.orientx();
return ((x >= ob.a.x)&&(x <= ob.b.x));
}

bool ifiny(const long double y, Segment ob){
ob.orienty();
return ((y >= ob.a.y)&&(y <= ob.b.y));
}

int turn(Coord a, Coord b, Coord c){
	long double d11,d12,d21,d22;
	d11 = b.x - a.x;
	d12 = c.x - a.x;
	d21 = b.y - a.y;
	d22 = c.y - a.y;
	if (d11*d22-d21*d12==0)
		return 0;
	if (d11*d22-d21*d12<0)
		return -1;
	return 1;
};

long double wherex(const long double y, Segment ob){
	// до вызова этой функции обязательно должна быть вызвана ifiny!!!
	long double lengthx, lengthy;
    ob.orienty();
	lengthy = ob.b.y-ob.a.y;
	//нужно обойти ситуацию деления на ноль-_-
	//не вызывать её, сцуко, для вертикальных.
	lengthx = ob.b.x-ob.b.y;
	long double len= ob.b.y-y;
	len /= lengthy;
	lengthx*=len;
	return ob.b.x-lengthx;
}

long double wherey(double x, Segment ob){
	// до вызова этой функции обязательно должна быть вызвана ifiny!!!
	long double lengthx, lengthy;
    ob.orientx();
	lengthy = ob.b.y-ob.a.y;
	//нужно обойти ситуацию деления на ноль-_-
	//не вызывать её, сцуко, для вертикальных.
	lengthx = ob.b.x-ob.b.y;
	long double len= ob.b.x-x;
	len /= lengthx;
	lengthy*=len;
	return ob.b.y - lengthy;
}
 
/*inline int area (Coord a, Coord b, Coord c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
 
inline bool intersect_1 (long double a, long double b, long double c, long double d) {
	if (a > b)  swap (a, b);
	if (c > d)  swap (c, d);
	return max(a,c) <= min(b,d);
}
 
bool intersect (Coord a, Coord b, Coord c, Coord d) {
	return intersect_1 (a.x, b.x, c.x, d.x)
		&& intersect_1 (a.y, b.y, c.y, d.y)
		&& area(a,b,c) * area(a,b,d) <= 0
		&& area(c,d,a) * area(c,d,b) <= 0;
}

bool ifcross( Segment&ob1, Segment&ob2)
{
	int t1,t2,t3,t4;
	t1 = turn(ob1.a,ob1.b,ob2.a);
	t2 = turn(ob1.a,ob1.b,ob2.b);
	t3 = turn(ob2.a,ob2.b,ob1.a);
	t4 = turn(ob2.a,ob2.b,ob1.b);
	return (((t1!=t2)||(t1==0))&&((t3!=t4)||(t4==0)))
*/

bool ifdot(Segment&ob, int&a,int&b,int&c){
	
	a = ob.a.y - ob.b.y;
	b = ob.b.x - ob.a.x;
	c = -a*ob.a.x - b*ob.a.y;
	
	return (ob.a==ob.b);		
}

bool ifcross(Segment & ob1, Segment & ob2, Coord & dot){
	int A1,B1,C1, A2,B2,C2;
	bool dot1, dot2;

	dot1 = ifdot(ob1,A1,B1,C1);
	dot2 = ifdot(ob2,A2,B2,c2);
	if (dot1&&dot2)
		{
			if(ob1.a==ob2.a)
				{
					dot = ob1.a;
					return true;
				}
			else
				return false;
		}
	if (dot1||dot2)
		{
			if (dot1)
				{
					if (ifinx(ob1.a.x,ob2)&&ifiny(ob1.a.y,ob2))
						{
							dot = ob1.a;
							return true;
						}
					else
						return false;
				}
			else
				{
					if (ifinx(ob2.a.x,ob1)&&ifiny(ob2.a.y,ob1))
						{
							dot = ob2.a;
							return true;
						}
					else
						return false;
				}
		}
	 //теперь мы точно имеем 2 отрезка. Ищем точку пересечения их прямых.
	dot.x = C2*B1-B2*C1;
	dot.y = A2*C1-A1*C2;
	int del = A1*B2-A2*B1;
	dot.x/=del;
	dot.y/=del;
	return (ifinx(dot.x,ob1)&&ifiny(dot.y,ob1));
}

int main(int argc, char **argv)
{
	Segment otr1(0,0),otr2(0,0);
	Coord dot;
	TestName test;
	//сначала вводим отрезки
		std::cin>>test>>otr1>>otr2;
		bool  otr1dot = (otr1.a==otr1.b), otr2dot = (otr2.a==otr2.b);
		//проверка на тупой случай
		if ((otr1.a==otr2.a)||(otr1.a==otr2.b)||(otr1.b==otr2.a)||(otr1.b==otr2.b))
			{
				std::cout<<test<<" YES ";
				if ((otr1.a==otr2.a)||(otr1.a==otr2.b))
					std::cout<<otr1.a<<'\n';
				else
					std::cout<<otr1.b<<'\n';
			}
		else
			{
				if (ifcross(otr1,otr2,dot))
					std::cout<<test<<" YES "<<dot<<'\n';
				else
					std::cout<<test<<" NO\n";
			}
	return 0;
}
