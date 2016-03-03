//
//  Point.cpp
//  PA2 ~ Intermediate
//
//  Created by Joshua Brummet on 2/15/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include "Point.h"
#include "Cluster.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
namespace Clustering
{
    
    
    unsigned int Point::__idGen = 0; // Id Generator
    
    //Constructor
    Point::Point(int dimensions)
    {
        __id = __idGen;
        
        __dim= dimensions;
        
        __values = new double[__dim];
        
        for (int i =0; i < __dim; ++i)
            __values[i] = 0;
        
        __idGen++;
        
    }
    
    Point::Point(int dimensions, double *array)
    {
        
        __id = __idGen;
        ++__idGen;
        
        __dim = dimensions;
        
        __values = new double[__dim];
        for (int i = 0; i < __dim; i++)
        {
            
            __values[i] = array[i];
            
        }
        
        
    }
    
    //Copy Constructor
    Point::Point(const Point & cpy)
    {
        
        __dim = cpy.__dim;
        __values = new double[__dim];
        __id = cpy.__id;
        //copy values into cpy array
        for (int i =0; i < __dim; i++)
            __values[i] = cpy.__values[i];
        
    }
    
    //Overloading operator=
    Point& Point::operator=(const Point & rhs)
    {
        
        
        if (this != &rhs)
        {
            // delete & copy
            
            __id = rhs.__id;
            __dim = rhs.__dim;
            
            __values = new double[__dim];
            
            for (int i = 0; i < __dim; i++)
                __values[i] = rhs.__values[i];
            
        }
        
        return *this;
        
    }
    Point::~Point()
    {
        
        delete [] __values;
    }
    
    
    //Accessors
    int Point::getId() const
    {
        
        return __id;
        
    }
    int Point::getDims() const
    {
        
        return __dim;
        
    }
    
    void Point::setValue(int new_dim,double Value)
    {
        
        
        __values[new_dim] = Value;
        
        
    }
    
    double Point::getValue(int index) const
    {
        
        return __values[index];
        
    }
    
    //Distance Function for two poins objects
    double Point::distanceTo(const Point & other) const
    {
        double total = 0;
        
        if (__dim != other.__dim)
            return false;
        
        for (int i = 0; i <__dim; ++i)
            
            total += ((other.getValue(i) - getValue(i)) * (other.getValue(i) - getValue(i)) );
        
        return sqrt(total);
        
    }
    
    
    //Compound assignment operatores
    Point& Point::operator*=(double rhs)
    {
        
        for(int i =0; i< __dim; i++)
            __values[i] *= rhs;
        
        return *this;
        
    }
    
    Point& Point::operator/=(double rhs)
    {
        for (int i =0; i<__dim; i++)
            __values[i]  /= rhs;
        
        return *this; // returing this object
        
    }
    
    const Point Point::operator*(double rhs) const
    {
        
        return Point (*this) *= rhs;
        
        
        
    }
    
    const Point Point::operator/(double rhs) const
    {
        
        return Point (*this) /= rhs;
        
        
        
    }
    
    //index operatore - return the index of a value
    double& Point::operator[](int index)
    {
        
        return __values[index];
        
    }
    
    Point & operator+=(Point &lhs, const Point& rhs)
    {
        
        if (&lhs == &rhs) //checking to see if points are equal
        {
            for (int count = 0; count < lhs.__dim; count++)
                lhs.__values[count] += rhs.__values[count];
        }
        
        else if (lhs.__dim == rhs.__dim) //if demensions are equal
            
        {
            for (int count = 0; count < lhs.__dim; count++)
                lhs.__values[count] += rhs.__values[count];
        }
        
        return lhs;
        
        
    }
    
    Point & operator -=(Point &lhs, const Point &rhs)
    {
        if (&lhs == &rhs)
        {
            for (int count = 0; count < lhs.__dim; count++) {
                lhs.__values[count] = 0;
            }
        }
        else if (lhs.__dim == rhs.__dim)
        {
            for (int count = 0; count < lhs.__dim; count++)
                lhs.__values[count] -= rhs.__values[count];
        }
        
        return lhs;
        
    }
    
    
    const Point operator + (const Point & lhs, const Point & rhs)
    {
        
        Point sum = lhs;
        sum += rhs; // using the overloaded compound assignment operator
        return sum;
        
    }
    
    const Point operator - (const Point & lhs, const Point & rhs)
    {
        
        Point sum = lhs;
        sum -= rhs;
        return sum;
        
    }
    
    
    
    //**Comparison Functions**
    
    bool operator ==( const Point & lhs, const Point & rhs)
    {
        if(lhs.__id != rhs.__id)
            return false;
        
        for (int i = 0; i < lhs.__dim; i++)
        {
            
            if  (lhs.getValue(i) != rhs.getValue(i))
                return false;
            
            
        }
        
        return true;
        
    }
    
    bool operator !=( const Point & lhs, const Point & rhs)
    {
        
        return ! (lhs == rhs);
        
        
    }
    
    bool operator < (const Point & lhs, const Point & rhs)
    {
        int localdim = std::max(lhs.__dim, rhs.__dim);
        
        
        if (lhs.__dim == rhs.__dim )
            
            for ( int i =0; i < localdim; i++)
                
                if (lhs.getValue(i) < rhs.getValue(i))
                    return true;
        
        return false;
        
    }
    
    bool operator > (const Point & lhs, const Point & rhs)
    {
        return (rhs < lhs);
        
    }
    
    bool operator <= (const Point &lhs, const Point &rhs)
    {
        
        return ! (lhs > rhs);
        
    }
    
    bool operator >=( const Point &lhs, const Point &rhs)
    {
        
        return !(lhs < rhs);
    }
    
    //**File streaming Functions**
    std::istream &operator >> (std::istream &data, Point &p)
    {
        
        //Creating a stringstream of input using getline & stringstream with data from datafile.
 
        int i = 0;
        std::string localVal;
        
        while ( getline(data, localVal, ','))
        {
            
            std::stringstream localstream(localVal);
          
            localstream >> p.__values[i];
            
            ++i;
            
        }
        
        return data;
        
    }
    
    
    
    std::ostream &operator << (std::ostream &data,const Point & p)
    {
        int i = 0;
                  
        for (; i < p.__dim; ++i)
            data << p.__values[i] << ',';
        
        data << p.__values[i];
        
        return data;
        
    }
    
}
