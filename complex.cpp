#include <iostream>
#include <cmath>
#include<time.h>

using namespace std;

class complex {
    private:
        double re, im;
    
    public:
        complex(){
            set(rand(), rand());
        };

        complex(double re_, double im_){
            set(re_, im_);
        }

        void set(double re_, double im_){
            re = re_;
            im = im_;
        }

        double get_re() const{
            return re;
        }

        double get_im() const{
            return im;
        }

        double module(){
            return sqrt(get_re()*get_re() + get_im() * get_im());
        }

        friend std::ostream& operator<< (std::ostream &out, const complex&);
        friend std::istream& operator>> (std::istream& in, complex&);

        friend const complex operator+ (complex&, const complex&);
        friend const complex operator- (complex&, const complex&);
        friend const complex operator* (complex&, const complex&);
        friend const complex operator/ (complex&, const complex&);

        friend complex& operator+= (complex&, const complex&);
        friend complex& operator-= (complex&, const complex&);
        friend complex& operator*= (complex&, const complex&);
};

std::istream& operator>> (std::istream& in, complex& x){
    in >> x.re;
    in >> x.im;
 
    return in;
}

std::ostream& operator<< (std::ostream& out, const complex& x){
    out << x.re;
    if(x.im >= 0){
        out << "+";
    }
    out << x.im << "i";
    
    return out;
}

const complex operator+ (complex& c1, const complex& c2){
    return complex(c1.re + c2.re, c1.im + c2.im); 
}

const complex operator- (complex& c1, const complex& c2){
    return complex(c1.re - c2.re, c1.im - c2.im); 
}

const complex operator* (complex& c1, const complex& c2){
    double 
        re1 = c1.re,
        re2 = c2.re, 
        im1 = c1.im,
        im2 = c2.im;
    return complex(re1*re2 - im1*im2 , re1*im2  + re2*im1); 
}

const complex operator/ (complex& c1, const complex& c2){
    double 
        re1 = c1.re,
        re2 = c2.re, 
        im1 = c1.im,
        im2 = c2.im,
        re_part = (re1*re2 + im1*im2)/(re2*re2 + im2*im2),
        im_part = (re2*im1 - re1*im2)/(re2*re2 + im2*im2);
    return complex(re_part , im_part);
}

complex& operator+= (complex& c1, const complex& c2){
    c1.set(c1.re + c2.re, c1.im + c2.im);
    return c1;
}

complex& operator-= (complex& c1, const complex& c2){
    c1.set(c1.re - c2.re, c1.im - c2.im);
    return c1;
}

complex& operator*= (complex& c1, const complex& c2){
    double 
        r1 = c1.re,
        r2 = c2.re,
        i1 = c1.im,
        i2 = c2.im;
    c1.set(r1*r2 - i1*i2, r1*i2 + r2*i1);
    return c1;
}

int main(){
    srand(time(0));
    complex a(5,2);
    complex b;

    cin >> a >> b;
    
    cout << a + b;

    return 0;
}