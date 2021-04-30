#include <map>
#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <math.h>
#include <string>
#include <utility>
#include <algorithm>
#include <exception>


using namespace std;
namespace ariel
{
///////////////////////////////////////////////////////////////
///////////////////////Private Methods/////////////////////////
///////////////////////////////////////////////////////////////
    
    std::map<string, std::map<string, double>> graph;
    void NumberWithUnits::read_units(ifstream &file)
    {
        string buff, unitA, unitB;
        double n1 = 0, n2 = 0;
        while (file >> n1 >> unitA >> buff >> n2 >> unitB)
        {
            graph[unitA][unitB] = n2;
            double convert_unit = 1/n2;
            graph[unitB][unitA] = convert_unit;
            update_graph(unitA, unitB);
        }
    }
    void NumberWithUnits::update_graph(const string &unitA, const string &unitB)
    {
        // add to the graph in one way
        for (auto &unit : graph[unitB])
        {
            if (unit.first != unitA)
            {
                double new_size = graph[unitA][unitB] * unit.second;
                graph[unitA][unit.first] = new_size;
                graph[unit.first][unitA] = 1 / new_size;
            }
        }

        // add to the graph in opite way
        for (auto &unit : graph[unitA])
        {
            if (unit.first != unitB)
            {
                double new_size = graph[unitB][unitA] * unit.second;
                graph[unitB][unit.first] = new_size;
                graph[unit.first][unitB] = 1 / new_size;
            }
        }
    }
    NumberWithUnits::NumberWithUnits(double n, const string &u)
    {
        if (graph.find(u) == graph.end())
        {
            throw invalid_argument(u + " Invalid Unit");
        }
        this->num = n;
        this->unit = u;
    }
    double NumberWithUnits::adjust_unit(const NumberWithUnits &unit1) const
    {
        if (!(unit == unit1.unit || graph[unit].find(unit1.unit) != graph[unit].end()))
        {
            throw invalid_argument("[-] Diffrent Unit Group");
        }
        if (unit == unit1.unit)
        {
            return unit1.num;
        }
        return unit1.num * graph[unit1.unit][unit];
    }


    ///////////////////////////////////////////////////////////////
    ///////////////////////Public Methods//////////////////////////
    ///////////////////////////////////////////////////////////////

    //===============================================================
    //Arithmetic Operators===========================================
    NumberWithUnits NumberWithUnits::operator+ (const NumberWithUnits& nwu)
    {
        double ans = this->num + this->adjust_unit(nwu);
        return NumberWithUnits(ans, this->unit);
    }
    NumberWithUnits NumberWithUnits::operator+=(const NumberWithUnits& nwu)
    {
        this->num += this->adjust_unit(nwu);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator+ ()
    {return *this;}
    NumberWithUnits NumberWithUnits::operator- (const NumberWithUnits& nwu)
    {
        double ans = this->num - this->adjust_unit(nwu);
        return NumberWithUnits(ans, this->unit);
    }
    NumberWithUnits NumberWithUnits::operator-= (const NumberWithUnits& nwu)
    {
        this->num -= this->adjust_unit(nwu);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-()
    {
        NumberWithUnits ans(-1*this->num,this->unit);
        return ans;
    }
    //===============================================================


    //===============================================================
    //Compartion Operators===========================================
    bool ariel::NumberWithUnits::operator< (const NumberWithUnits& nwu) const
    {
        return (this->num - this->adjust_unit(nwu)) < 0;
    }
    bool ariel::NumberWithUnits::operator<= (const NumberWithUnits& nwu) const
    {
        return (this->num - this->adjust_unit(nwu)) <= Epsilone;
    }
    bool ariel::NumberWithUnits::operator> (const NumberWithUnits& nwu) const
    {
        return this->adjust_unit(nwu)-this->num < 0;
    }
    bool ariel::NumberWithUnits::operator>= (const NumberWithUnits& nwu) const
    {
        return this->adjust_unit(nwu)-this->num <= Epsilone;
    }
    bool ariel::NumberWithUnits::operator== (const NumberWithUnits &nwu) const
    {
        if(this->unit == nwu.unit && this->num == nwu.num) return true;
        
        return abs(this->num - this->adjust_unit(nwu)) < Epsilone;
    }
    bool ariel::NumberWithUnits::operator!= (const NumberWithUnits& nwu) const
    {
        if(*this == nwu) return false;
        return true;
    }
    //===============================================================


    //===============================================================
    //Psotfix Operators==============================================
    NumberWithUnits& NumberWithUnits::operator++ ()
    {
        this->num++;
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator-- ()
    {
        this->num--;
        return *this;
    }
    //===============================================================


    //===============================================================
    //Prefix Operators===============================================
    NumberWithUnits NumberWithUnits::operator++ (int)
    {
        NumberWithUnits prefix(this->num,this->unit);
        this->num++;
        return prefix;
    }
    NumberWithUnits NumberWithUnits::operator-- (int)
    {
        NumberWithUnits prefix(this->num,this->unit);
        this->num--;
        return prefix;
    }
    //==============================================================


    //==============================================================
    //Multiplication Operators======================================
    NumberWithUnits operator* (double num1, const NumberWithUnits &nwu)
    {
        
        NumberWithUnits ans(nwu.num*num1,nwu.unit);
        return ans;
    }
    NumberWithUnits operator* (const NumberWithUnits &nwu, double num1)
    {
    NumberWithUnits ans(nwu.num*num1,nwu.unit);
        return ans;
    }
        //==============================================================
}

    //==============================================================
    //Stream Operators==============================================
    std::ostream &ariel::operator<<(std::ostream &os, const NumberWithUnits &nwu) 
    {
        os<<nwu.num<<"["<<nwu.unit<<"]";
        return os;
    }
    std::istream &ariel::operator>>(std::istream &is, NumberWithUnits &nwu) 
    {
        char cha = 0;
        string unit;
        double n = 0;
        is >> n >> cha >> unit >> cha;

        if (unit[unit.length() - 1] == ']')
        {
            unit.pop_back();
        }
        if (cha == '-')
        {
            is.putback('-');
        }
        if (graph.find(unit) == graph.end())
        {
            throw std::invalid_argument(unit + "[-] Please enter valid unit");
        }
        nwu.num = n;
        nwu.unit = unit;
        return is;
    }
    //==============================================================
