
#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::ostream;

class Point
{
 private:
  int c_[2];

 public:
  Point (int x, int y)
  {
      c_[0] = x;
      c_[1] = y;
  }

  Point &operator= (const Point &other)
  {
      if (this != &other) // self-assignment check
      {
          _x = other._x;
          _y = other._y;
      }
      return *this;
  }

  // Copy constructor
  Point (const Point &other) : _x (other._x), _y (other._y)
  {}

  int get_x () const
  { return c_[0]; }
  int get_y () const
  { return c_[1]; }

  /* Operator defined as member function is called on instance of the class. */
  bool operator== (Point const &o) const
  {
      return (this->c_[0] == o.c_[0] && this->c_[1] == o.c_[1]);
  }

  // addition of another Point
  Point &operator+= (const Point &rhs)
  {
      this->c_[0] += rhs.c_[0];
      this->c_[1] += rhs.c_[1];
      return *this;
  }

  // addition of int
  Point &operator+= (const int xx)
  {
      this->c_[0] += xx;
      this->c_[1] += xx;
      return *this;
  }

  // return -Point, do not change this
  Point operator- ()
  {
      Point p (-c_[0], -c_[1]);
      return p;
  }

  // pre increment
  Point &operator++ ()
  {
      c_[0]++;
      c_[1]++;
      return *this;
  }

  // post increment
  Point operator++ (int)
  {
      Point x = Point (*this);
      c_[0]++;
      c_[1]++;
      return x;
  }

  /* const access version
     Acceptable indices 0,1. Others can result in run-time error */
  const int &operator[] (const unsigned short coord) const
  {
      return this->c_[coord];
  }

  // non-const access
  int &operator[] (const unsigned short coord)
  {
      return c_[coord];
  }

  /* Friends (note being a friend is not essential in this case) */

  // Returns a Point that is the result of addition of two Points.
  friend Point operator+ (Point const &lhs, Point const &rhs)
  {
      return Point (lhs.c_[0] + rhs.c_[0], lhs.c_[1] + rhs.c_[1]);
  }

  // Outputs coordinates delimited by single space.
  friend std::ostream &operator<< (std::ostream &os, const Point &p)
  {
      return os << p.c_[0] << ' ' << p.c_[1];
  }

  // Inputs coordinates delimited by single space.
  friend std::istream &operator>> (std::istream &os, Point &p)
  {
      return os >> p.c_[0] >> p.c_[1];
  }
};

/* Operator defined outside as non-member function */
bool operator< (const Point &lhs, const Point &rhs)
{
    return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
}

#endif //_POINT_H_
