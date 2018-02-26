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
class Coord {	
public:
	double x,y;
	Coord(){
		x=0;
		y=0;
	};
	Coord(double a, double b=0){
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
	
	Segment(double x2, double y2){
		Coord ob1;
		a = ob1;
		Coord ob2(x2,y2);
		b = ob2;
		vert = (a.y == b.y);
	};
	Segment(double x1, double y1,double x2, double y2){
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
};

class IntCoord: public Coord{
	int num;
public:S
	IntCoord(const int n,const double xob, const double yob){
		x = xob;
		y = yob;
		num = n;
	}
	IntCoord(const int n,Coord ob){
		x = ob.x;
		y = ob,y;
		num = n;
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
 friend std::istream& operator<< (std::istream& input, TestName ob){
	input>>ob.c1>>ob.c2>>ob.c3>>ob.c4>>ob.c5>>ob.c6;
	return input;
}			

}

int turn(Coord a, Coord b, Coord c){
	float d11,d12,d21,d22;
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

bool function ifcross(Interval ob1,ob2){
	//случай, когда обе вертикальны:
}		
int main(int argc, char **argv)
{
	Interval otr1,otr2;
	TestName test;
	//сначала вводим отрезки
	std::cin>>test>>otr1>>otr2;
	//проверка на тупой случай
	if ((otr1.a==otr2.a)||(otr1.a==otr2.b)||(otr1.b==otr2.a)||(otr1.b==otr2.b))
		{
			std::cout<<test<<" YES\n";
			if ((otr1.a==otr2.a)||(otr1.a==otr2.b))
				std::cout<<otr1.a<<'\n';
			else
				std::cout<<otr1.b<<'\n';
		}
	else
	{
		//теперь упорядочиваем по координате x с сохранением информации о принадлежности.
		IntCoord * arr = new IntCoord[4];
		IntCoord dot1(1,otr1.a),dot2(1,otr1.b),dot3(2,otr2.a),dot4(2,otr2.b);
		//для этого создаём класс упорядоченная точка.
		arr[0] = dot1;
		arr[1] = dot2;
		arr[2] = dot3;
		arr[3] = dot4;
		//теперь сканируем, проверяя то, как расположенны отрезки
	
		//выводим результат
	}
	return 0;
}

