//
//  Cluster.cpp
//  PA2 ~ Intermediate
//
//  Created by Joshua Brummet on 2/15/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include <cassert>
#include <sstream>
#include "Cluster.h"
namespace Clustering
{
    LNode::LNode(const Point &p, LNodePtr n) : point(p)
    {
        point = p;
        next = n;
    }
    
    Cluster::Cluster() {
        
        __size = 0;
        __points = nullptr;
        
        
    }
    
    
    /********Big Three*****/
    
    //copy constructor
    Cluster::Cluster(const Cluster &p) : Cluster()
    {
        for (int i = 0; i <p.getSize(); i ++)
            add(p[i]);
        
        
    }
    
    //Destructor
    Cluster::~Cluster()
    {
        LNodePtr d;
        
        while(__points != nullptr) // irrating through the points deleting one at a time until the end 'nullptr'
        {
            d= __points;
            __points = d->next;
            
            delete d;
        }
        
        
    }
    //overload = assignment operator
    Cluster &Cluster::operator=(const Cluster & p)
    {
       
        
            LNodePtr cursor;
            
            cursor = __points;
            
            while(__points!= nullptr)
            {
                
                
                cursor = __points;
                __points = __points->next;
                
                delete cursor; // freeing up memory :)
                --__size;
            }
        
        
        for (int i =0; i < p.getSize(); ++i)
            add(p[i]);
        
        
        
        return *this;
    }
    
    //getting size of cluster
    int Cluster::getSize() const {
        
        return __size;
    }
    
    void Cluster::add(const Point & p)
    {

        LNodePtr cursor;
        LNodePtr prev;
        cursor = __points;
        prev = __points;
        
        
        LNodePtr ptr = new LNode(p, nullptr);
        
        if (__points == nullptr) // if the list is empty
        {
            __points = ptr;
            ++__size;
            return;
        }
        
        
        else if (__points->next==nullptr) // handle case if its the first point
        {
            if(p<__points->point)
            {
                __points = ptr;
                ptr->next=prev;
                
                ++__size;
                
                return;
                
            }
            else
            {
                __points->next = ptr;
                __size++;
                return;
            }
            
            
        }
        
            cursor=cursor->next;
        
            if(p < prev->point) // handle case if its not the first point
            {
                __points = ptr;
                ptr->next=prev;
                __size++;
                return;
            }
            while(cursor!=nullptr)
            {
                
                if(p < cursor->point)
                {
                    prev->next= ptr;
                    ptr->next=cursor;
                    __size++;
                    return;
                }
                
                cursor = cursor->next;
                prev = prev->next;
            }
            prev->next=ptr;
            __size++; //keeping size aligned with how many points there are

        
    }
    
    const Point &Cluster::remove(const Point &p)
    {
        LNodePtr curr, prev;
        prev = nullptr;
        curr = __points;
        
        if (contains(p)) //point is in the list.
        {
            
            while (curr != nullptr)
            {
                if (curr->point == p) //the cursor found the point in the loop.
                {
                    
                    if (prev == nullptr) //Handle case if its the first point in the list.
                    {
                        __points = curr->next;
                        
                        delete curr;
                        
                        --__size;
                        
                        break;
                    }
                    
                    else
                    {                           // to handle case if its not the first point in the list.
                        prev->next = curr->next;
                        delete curr;
                        
                        --__size;
                        
                        break;
                    }
                    
                    
                }
                
                prev = curr;
                curr = curr->next;
            }
            
            
        }
        
        return p;
        
    }
    
    const Point &Cluster::operator[](unsigned int index) const
    {
        LNodePtr curr = __points;
        
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        
        return curr->point;
        
        
    }
    
    
    bool Cluster::contains(const Point &p)
    {
        
        LNodePtr curr = __points;
        
        while (curr != nullptr)
        {
            
            if (curr->point.getId() == p.getId()) // if Point is in the list. return true else it returns false.
                
                return true;
            
            else
                curr= curr->next;
            
            
        }
        
        return false;
        
    }
    
    //Point Arguments
    
    Cluster &Cluster::operator-=(const Point&p)
    {
        
        remove(p);
        
        return *this;
        
    }
    
    Cluster &Cluster::operator+=(const Point&p)
    {
        add(p);
        
        return *this;
        
    }
    
    //Cluster Arguments
    
    Cluster &Cluster::operator+=(const Cluster &p)
    {
        for(int i = 0; i < p.getSize(); i++)
        {
            if(!contains(p[i]))
                add(p[i]);
            
        }
        return *this;
    }
    
    
    Cluster &Cluster::operator-=(const Cluster &p)
    {
        
        for(int i = 0; i <p.__size; i++)
        {
            if(contains(p[i]))
            remove(p[i]);
        }
        
        return *this;
        
        
    }
    
    std::istream &operator>>(std::istream &data, Cluster &p)
    {
        
        std::string s;
        
        while(getline(data,s))
        {
            
           
            int size = (int)std::count(s.begin(), s.end(), ',');
            Point in(size +1);
            
            std::istringstream ss(s);
            ss >> in;
            
            p.add(in);
            
        }
        
        return data;
        
    }
    
    std::ostream &operator<<(std::ostream &out, const Cluster & p)
    {
        
        for (int i = 0; i < p.__size; i++)
        {
            out << p[i] << " , " << std::endl;
            
        }
        
        
        return out;
    }
    
    //Comparisons
    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {
        
        if (lhs.getSize() != rhs.getSize()) //checking to see if cluster size match for comparison
            return false;
        
        for (int i = 0; i < lhs.getSize(); i++)
        {
            if (lhs[i] != rhs[i])           //seeing to make sure that each point in the cluser are equal to make compariosn
                return false;
            
            
        }
        
        return true;
        
    }
    
    bool operator !=(const Cluster &lhs, const Cluster &rhs)
    {
        return !(lhs == rhs);
        
        
    }
    
    //Arithmetic (Cluster and Point)
    const Cluster operator +(const Cluster &lhs, const Point &rhs)
    {
        
        Cluster sum(lhs);
        
        sum += rhs;
        
        return sum;
        
        
    }
    
    
    const Cluster operator - (const Cluster &lhs, const Point &rhs)
    {
        Cluster sum(lhs);
        
        sum -= rhs;
        
        return sum;
        
        
    }
    
    // Arithemtic (Two Clusters)
    const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
    {
        
        Cluster sum(lhs);
        sum += rhs;
        
        return sum;
        
        
    }
    
    const Cluster operator - (const Cluster &lhs, const Cluster &rhs)
    {
        
        Cluster sum(lhs);
        
        sum -= rhs;
        
        return sum;
        
        
    }
    
}
