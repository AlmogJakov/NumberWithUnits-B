#pragma once
#include <iostream>
#include <map>
#include <sstream>
//#include <fstream>
//#include <bits/stdc++.h>
using namespace std;

namespace ariel {
    class NumberWithUnits {
        static inline map<string,map<string,double>> get_unit;
        double amount;
        string unit;
    public:
        static void read_units(ifstream &infile);
        ///////////////////////////////////////////////////////////////////////////////
        /////////////////////////// Constructor/Destructor ////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
        /* constructor */
        NumberWithUnits(double a, string u) {
            if (!get_unit.count(u)) {throw invalid_argument("Illegal units!");}
            unit = u;
            amount = a;
        };
        ~NumberWithUnits() {};
        ///////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////// Operators //////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
        /* Arithmetic operators */
        friend NumberWithUnits operator-(const NumberWithUnits& a);
        friend NumberWithUnits operator+(const NumberWithUnits& a);
        friend NumberWithUnits operator+(const NumberWithUnits& a1, const NumberWithUnits& a2);
        friend NumberWithUnits operator-(const NumberWithUnits& a1, const NumberWithUnits& a2);
        NumberWithUnits& operator+=(const NumberWithUnits& a2) {
            if (NumberWithUnits::get_unit.count(this->unit)!=0&&NumberWithUnits::get_unit[this->unit].count(a2.unit)!=0) {
                double a2_new_amount = a2.amount*NumberWithUnits::get_unit[a2.unit][this->unit];
                this->amount += a2_new_amount;
                return *this;
            }
            stringstream ss;
            ss << "Units do not match - [" << this->unit << "] cannot be converted to [" << a2.unit <<"]";
            throw invalid_argument(ss.str());
        }
        NumberWithUnits& operator-=(const NumberWithUnits& a2) {
            if (NumberWithUnits::get_unit.count(this->unit)!=0&&NumberWithUnits::get_unit[this->unit].count(a2.unit)!=0) {
                double a2_new_amount = a2.amount*NumberWithUnits::get_unit[a2.unit][this->unit];
                this->amount -= a2_new_amount;
                return *this;
            }
            stringstream ss;
            ss << "Units do not match - [" << this->unit << "] cannot be converted to [" << a2.unit <<"]";
            throw invalid_argument(ss.str());
        }
        /* Boolean operators */
        friend bool operator<(const NumberWithUnits& a1, const NumberWithUnits& a2);
        friend bool operator>(const NumberWithUnits& a1, const NumberWithUnits& a2);
        friend bool operator>=(const NumberWithUnits& a1, const NumberWithUnits& a2);
        friend bool operator<=(const NumberWithUnits& a1, const NumberWithUnits& a2);
        friend bool operator==(const NumberWithUnits& a1, const NumberWithUnits& a2);
        friend bool operator!=(const NumberWithUnits& a1, const NumberWithUnits& a2);
        /* ++/-- operators */
        NumberWithUnits& operator++() { // prefix increment
            this->amount++;
            return *this;
        }
        const NumberWithUnits operator++(int dummy_flag_for_postfix_increment) { // postfix increment
            NumberWithUnits copy = *this;
            this->amount++;
            return copy;
        }
        NumberWithUnits& operator--() { // prefix increment
            this->amount--;
            return *this;
        }
        const NumberWithUnits operator--(int dummy_flag_for_postfix_increment) { // postfix increment
            NumberWithUnits copy = *this;
            this->amount--;
            return copy;
        }
        /* Multiplication by real number operators */
        friend NumberWithUnits operator*(double d, const NumberWithUnits& a);
        friend NumberWithUnits operator*(const NumberWithUnits& a, double d);
        /* Input/Output operators */
        friend ostream& operator<<(ostream& os, const NumberWithUnits& a);
        friend istream& operator>>(istream& input, NumberWithUnits& a);
        ///////////////////////////////////////////////////////////////////////////////
        ////////////////////////////// Map-Print method ///////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
        static void print_map() {
            for (auto const& [key, val] : get_unit) { // val = second map
                for (auto const& [k, v] : val) {           // k = first, v = second
                    cout << key << ' ' << k << ' ' << fixed << v << '\n';
                }
            }
        }
    };
}