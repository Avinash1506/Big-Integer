#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;

class BigI
{
    private:

     vector<int> num; // contains the big integer
     int sign; // 1 if its negative else 0

    public:

      // method for addition

      BigI operator + (BigI & obj) {
          if( (this->sign ^ obj.sign) == 0 ) {
              BigI ans;

              if( this->sign == 1 && obj.sign == 1) {
                    ans.sign = 1;
              }

              else {
                    ans.sign = 0;
              }

              vector<int> num1(num);
              vector<int> num2(obj.num);

              vector<int> res;

              if(num1.size() < num2.size()){
                  swap(num1, num2);
              }

              int x = num1.size();
              int y = num2.size();
              int i = x-1, j = y-1, carry = 0, sum;
              while( j >= 0) {

                    int z = num1[i] + num2[j] + carry;

                    carry = z / 10;

                    sum = z % 10;

                    res.push_back( sum );

                    j--;
                    i--;
              }

              while( i >= 0) {

                    int z = num1[i] + carry;

                    sum = z % 10;

                    carry = z / 10;

                    res.push_back( sum );
                    i--;
              }

              if( carry > 0){
                res.push_back( carry );
              }
              reverse( res.begin(), res.end());

              ans.num = res;

              ans.removeStartingZeros();

              return ans;
          }
          else {

              if( this->sign == 0 && obj.sign == 1) {

                BigI num1, num2, ans;
                num1.num = num;
                num2.num = obj.num;
                num1.sign = 0;
                num2.sign = 0;

                ans = num1 - num2;

                ans.removeStartingZeros();

                return ans;
              }
              else {

                BigI num1, num2, ans;
                num1.num = num;
                num2.num = obj.num;
                num1.sign = 0;
                num2.sign = 0;

                ans = num2 - num1;

                ans.removeStartingZeros();

                return ans;

              }
          }
      }

      // method for subtraction

      BigI operator - (BigI & obj) {

            // if both are positive or both are negative
            if( (this->sign ^ obj.sign) == 0 ) {

                BigI ans;
                if( (this->sign == 0 && obj.sign == 0) ) {
                    if(*this > obj) {
                        ans.sign = 0;
                    }
                    else {
                        ans.sign = 1;
                    }
                }

                if( (this->sign == 1 && obj.sign == 1) ) {
                    if(*this > obj) {
                        ans.sign = 0;
                    }
                    else {
                        ans.sign = 1;
                    }
                }

                vector <int> num1(num);
                vector <int> num2(obj.num);
                vector <int> res;
                BigI tmp1 = *this;
                BigI tmp2 = obj;
                tmp1 = abs(tmp1);
                tmp2 = abs(tmp2);
                if( tmp1 < tmp2) {
                    //ans.sign = ans.sign ^ 1;
                    swap(num1, num2);
                }

                int x = num1.size(), y = num2.size();

                int i = x-1, j = y-1, borrow = 0;

                while( j >= 0) {

                    int diff = num1[i] - num2[j] - borrow;

                    if( diff < 0) {
                        borrow = 1;
                        diff += 10;
                    }
                    else {
                        borrow = 0;
                    }

                    res.push_back( diff );

                    i--;
                    j--;

                }

                while( i >= 0) {
                    int diff = num1[i] - borrow;
                    if( diff < 0) {
                        borrow = 1;
                        diff += 10;
                    }
                    else {
                        borrow = 0;
                    }

                    res.push_back( diff );

                    i--;
                }


                reverse(res.begin(), res.end());

                ans.num = res;

                ans.removeStartingZeros();

                return ans;
            }
            else {

                if( this->sign == 0 && obj.sign == 1) {
                    BigI num1, num2, ans;

                    num1.num = num;
                    num2.num = obj.num;
                    num1.sign = 0;
                    num2.sign = 0;

                    ans = num1 + num2;
                    ans.sign = 0;

                    return ans;
                }
                else {
                    BigI num1, num2, ans;

                    num1.num = num;
                    num2.num = obj.num;
                    num1.sign = 0;
                    num2.sign = 0;

                    ans = num1 + num2;

                    ans.sign = 1; // multiplying by -1

                    return ans;
                }
            }

      }

      // method for multiplication

      BigI operator * (BigI & obj ) {
            vector<int> num1,num2;
            num1 = num;
            num2 = obj.num;

            BigI ans;

            if( (this->sign ^ obj.sign) == 0) {
                ans.sign = 0;
            }
            else {
                ans.sign = 1;
            }

            if(num1.size() * num2.size() <= 1000000) {

                vector<int> num3 = naive_mul(num1,num2);
                reverse(num3.begin(), num3.end());
                ans.num = num3;
                ans.removeStartingZeros();
                return ans;

            }

            //vector<int> num3 = this->karatsuba(num1, num2);
            //ans.num = num3;


            //ans.removeStartingZeros();

            //return ans;

            reverse(num1.begin(), num1.end());
            reverse(num2.begin(), num2.end());

            vector<int> num3 = this->fft_mul(num1,num2);

            int carry = 0;

            for(int i = 0; i < (int)num3.size(); i++) {
                num3[i] += carry;
                carry = num3[i]/10;
                num3[i] %= 10;
            }

            ans.num = num3;

            reverse(ans.num.begin(), ans.num.end());

            ans.removeStartingZeros();

            return ans;
      }

      // method for division

      BigI operator / (BigI b) {

          return quotientAndRemainder(*this, b).first;

      }

      // method for modulus

      BigI operator % (BigI &b) {

          return quotientAndRemainder(*this, b).second;

      }

      // performs BigI + int

      BigI operator + (int x) {

            BigI num2;
            num2 = num2.extractBigIFromInt(x);

            return *this + num2;
      }

      // performs BigI - int

      BigI operator - (int x) {

            BigI num2;
            num2 = num2.extractBigIFromInt(x);

            //cout<<num2<<"\n";

            return *this - num2;
      }

      // performs BigI * int

      BigI operator * (int x) {

            BigI num2;
            num2 = num2.extractBigIFromInt(x);

            return *this * num2;
      }

      // performs BigI / int

      BigI operator / (int x) {

            BigI num2 = extractBigIFromInt(x);

            return (*this) / num2;
      }

      // performs BigI % int

      BigI operator % (int x) {

            BigI num2;
            num2 = num2.extractBigIFromInt(x);

            return *this % num2;
      }

      // short-hand notation for +

      BigI & operator += (BigI &num2) {

            *this = *this + num2;

            return *this;
      }

      // short-hand notation for -

      BigI & operator -= (BigI &num2) {

            *this = *this - num2;

            return *this;
      }

      // short-hand notation for *

      BigI & operator *= (BigI &num2) {

            *this = (*this)*(num2);

            return *this;
      }

      // short-hand notation for /

      BigI & operator /= (BigI &num2) {

            *this = (*this)/(num2);

            return *this;
      }

      // short-hand notation for %

      BigI & operator %= ( BigI &num2) {

            *this = (*this) % (num2);

            return *this;
      }

      // short-hand notation for + with int

      BigI & operator += (int num2) {

            *this = *this + num2;

            return *this;
      }

      // short-hand notation for - with int

      BigI & operator -= (int num2) {

            *this = *this - num2;

            return *this;
      }

      // short-hand notation for * with int

      BigI & operator *= (int num2) {

            *this = (*this) * (num2);

            return *this;
      }

      // short-hand notation for / with int

      BigI & operator /= (int num2) {

            *this = (*this) / (num2);

            return *this;
      }

      // short-hand notation for % with int

      BigI & operator %= (int num2) {

            *this = (*this) % (num2);

            return *this;
      }

      // pre-increment operator

      BigI operator ++ () {
          *this = *this + 1;
          return *this;
      }

      // post-increment operator

      BigI operator ++ (int) {
          BigI num1 = *this;
          *this = *this + 1;
          return num1;
      }

      // pre-decrement operator

      BigI operator -- () {
          *this=*this - 1;
          return *this;
      }

      // post-decrement operator

      BigI operator -- (int) {

          BigI num1 = *this;

          *this = *this - 1;

          return num1;
      }

      // returns 1 if b1 > b2, -1 if b1 < b2 and 0 if b1 == b2

      int assignmentOperators(const BigI & b1, const BigI & b2) {
            if( (b1.sign ^ b2.sign) == 0)   {

                vector<int> num1,num2;

                num1 = b1.num;
                num2 = b2.num;

                if( num1.size() > num2.size() ) {
                    if(b1.sign == 1) {
                        return -1;
                    }
                    return 1;
                }

                if( num1.size() < num2.size()) {
                    if(b1.sign == 1) {
                        return 1;
                    }
                    return -1;
                }

                for(int i = 0; i < (int)num1.size(); i++) {

                    if(num1[i] > num2[i]) {
                        if(b1.sign == 1) {
                            return -1;
                        }
                        return 1;
                    }

                    if(num1[i] < num2[i]) {
                        if(b2.sign == 1) {
                            return 1;
                        }
                        return -1;
                    }

                }

            }
            else if( b1.sign == 1 && b2.sign == 0) {

                return -1;

            }
            else if( b1.sign == 0 && b2.sign == 1) {

                return 1;

            }

            return 0;
      }

      // greater than operator

      bool operator > ( BigI & b) {

            return assignmentOperators((*this), b) > 0;

      }

      // greater than or equal to operator

      bool operator >= ( BigI & b) {

            return assignmentOperators((*this), b) >= 0;

      }

      // less than operator

      bool operator < ( BigI &b) {

            return assignmentOperators((*this), b) < 0;

      }

      // less than or equal to operator

      bool operator <= ( BigI &b) {

            return assignmentOperators((*this), b) <= 0;

      }

      // equal to operator

      bool operator == ( BigI &b) {

            return assignmentOperators((*this), b) == 0;

      }

      // not equal to operator

      bool operator != (  BigI &b ) {

            return assignmentOperators((*this), b) != 0;

      }

      // greater than operator BigI > int

      bool operator > ( int x ) {

            BigI num2 = this->extractBigIFromInt(x);

            return (*this) > num2;
      }

      // greater than or equal to operator BigI >= int

      bool operator >= ( int x ) {

            BigI num2 = this->extractBigIFromInt(x);

            return (*this) >= num2;
      }

      // less than to operator BigI < int

      bool operator < ( int x ) {

            BigI num2 = this->extractBigIFromInt(x);

            return (*this) < num2;
      }

      // less than or equal to operator BigI <=int

       bool operator <= ( int x ) {

            BigI num2 = this->extractBigIFromInt(x);

            return (*this) <= num2;
      }

      // equal to operator BigI == int

       bool operator == ( int x ) {

            BigI num2 = this->extractBigIFromInt(x);

            return (*this) == num2;
      }

      // not equal to operator BigI != int

       bool operator != ( int x ) {

            BigI num2 = this->extractBigIFromInt(x);

            return (*this) != num2;
      }

      // brute-force multiplication

      vector<int> naive_mul(vector<int> v1, vector<int> v2) {

            int n1 = v1.size(), n2 = v2.size(),val;
            vector<int> ans(n1 + n2, 0);
            for(int i = n1 - 1; i >= 0; i--) {
                int carry = 0;
                if(v1[i]) {
                    int idx = n1 - 1 - i ;
                    for(int j = n2 - 1; j >= 0; j--) {
                        val = ans[idx] + v1[i]*v2[j] + carry;
                        ans[idx] = val % 10;
                        carry = val / 10;
                        idx++;
                    }
                    while(carry > 0) {
                        val = ans[idx] + carry ;
                        ans[idx] = val % 10;
                        carry = val / 10;
                        idx++;
                    }
                }
            }
            return ans;
      }

      // this method is implementation of karatsuba algorithm

      vector<int> karatsuba(vector<int> num1, vector<int> num2) {

            int len = makeEqualLength(num1, num2);

            if(len == 1) {

                vector<int> vec;

                int x = num1[0] * num2[0];

                int zeroesdigit = x % 10;

                vec.push_back(zeroesdigit);

                x /= 10;

                if(x != 0) {
                    vec.push_back(x);
                }

                reverse(vec.begin(), vec.end());

                return vec;
            }

            int left = len / 2;

            int right = len - left;

            vector<int> num1l, num1r, num2l, num2r;

            for(int i = 0; i < left; i++) {
                num1l.push_back(num1[i]);
                num2l.push_back(num2[i]);
            }

            for(int i = left ; i < len; i++) {
                num1r.push_back(num1[i]);
                num2r.push_back(num2[i]);
            }

            vector<int> X = karatsuba(num1l, num2l);
            vector<int> Y = karatsuba(num1r, num2r);

            BigI b1l,b1r,b2l,b2r;
            b1l.sign = b1r.sign = b2l.sign = b2r.sign = 0;

            b1l.num = num1l;
            b1r.num = num1r;
            b2l.num = num2l;
            b2r.num = num2r;

            BigI b1 = b1l + b1r;
            BigI b2 = b2l + b2r;


            vector<int> num1lr_and_num2lr = karatsuba(b1.num, b2.num);

            BigI a1, a2;

            a1.num = X;
            a1.sign = 0;
            a2.num = Y;
            a2.sign = 0;

            BigI a3;
            a3.sign = 0;
            a3.num = num1lr_and_num2lr;

            a3 = a3 - a1 - a2;


            for(int i = 0; i < 2*right; i++) {
                a1.num.push_back(0);
            }

            for(int i = 0; i < right; i++) {
                a3.num.push_back(0);
            }

            BigI ans;

            ans = a1 + a3 + a2;

            return ans.num;

      }

      // this method either applies fft or inverse fft based on the value of isInverse
      // if its true then it applies inverse fft else it applies fft

      void fftAndIfft(vector<complex<double>> &vec, bool isInverse,const double pie) {

            if(vec.size() == 1) {
                return ;
            }

            int n = vec.size();

            vector< complex<double> > evenvec(n/2),oddvec(n/2);

            for(int i = 0; 2 * i < n; i++) {

                evenvec[i] = vec[2*i];
                oddvec[i] = vec[2*i+1];

            }

            fftAndIfft(evenvec, isInverse, pie);
            fftAndIfft(oddvec, isInverse, pie);

            //2*pie/n if fft else -2*pie/n if inverse fft

            double angle = 2.0 * pie / n;

            if(isInverse) {
                angle = -angle;
            }

            //w = cosx + i sinx

            complex <double> nth_roots(1), w(cos(angle), sin(angle));

            for(int i = 0; 2*i < n; i++) {

                vec[i] = evenvec[i] + nth_roots * oddvec[i];

                vec[i + n/2] = evenvec[i] - nth_roots * oddvec[i];

                if(isInverse) {
                    vec[i] /= 2;
                    vec[i + n/2] /= 2;
                }

                nth_roots *= w; // 1, w, w^2, w^3 .....

            }

      }

      // this method calculates fft of num1 and num2 and multiplies them
      // finally calculates inverse fft of the result
      // then returns the result which is the multiplication of 2 BigI numbers

      vector<int> fft_mul(vector<int> num1, vector<int> num2) {

            vector< complex<double> > num1_com(num1.begin(), num1.end()), num2_com(num2.begin(), num2.end());

            // making n as perfect power of 2 and size greater than num1.size() + num2.size()
            // because when we multiply 2 n-digit numbers then the resultant contains 2*n digits

            int n = 1;

            while(n < (int)(num1.size() + num2.size())) {
                n <<= 1;
            }

            num1_com.resize(n);
            num2_com.resize(n);

            const double pie = acos(-1);

            // fft
            fftAndIfft(num1_com, false, pie);

            // fft
            fftAndIfft(num2_com, false, pie);

            for(int i = 0; i < n; i++) {
                num1_com[i] *= num2_com[i];
            }

            // inverse fft

            fftAndIfft(num1_com, true, pie);

            // converting the complex num1_com into int

            vector<int> ans(n);

            for(int i = 0; i < n; i++) {
                ans[i] = round(num1_com[i].real());
            }

            return ans;
      }

      // this method returns both quotient and remainder

      pair<BigI, BigI> quotientAndRemainder(BigI &dividend, BigI &divisor) {

            BigI b1,b2;
            b1 = dividend;
            b2 = divisor;

            BigI quotient,remainder_bigI;

            quotient.sign = (b1.sign ^ b2.sign);
            remainder_bigI.sign = (b1.sign ^ b2.sign);

            b1.sign = 0;
            b2.sign = 0;

            if( b1 < b2 ) {

                BigI zero = this->extractBigIFromInt(0);

                return {zero, b1};

            }

            if( b1 == b2 ) {

                BigI one = this->extractBigIFromInt(1);

                BigI zero = this->extractBigIFromInt(0);

                return {one, zero};

            }

            b1.sign = b2.sign = 0;

            BigI zero;
            int dividendSize = b1.num.size();
            zero = extractBigIFromInt(0);

            if(b2 == zero) {
                cerr<<"Division by zero error: ";
                BigI ans = extractBigIFromInt(-1);
                return {ans,ans};
            }

            BigI t;
            t.sign = 0;

            t.num.push_back(b1.num[0]);

            int i;

            for(i = 1; i < dividendSize; i++) {
                if( t >= b2 ) {
                    break;
                }

                t.num.push_back( b1.num[i] );
            }

            pair<int, vector<int> > quotientAndRemainderVar = this->divideBySubtraction(t, b2);

            quotient.num.push_back( quotientAndRemainderVar.first );
            vector<int> remainder = quotientAndRemainderVar.second;

            while( i < dividendSize) {

                remainder.push_back(b1.num[i]);
                BigI remainder_bigi;
                remainder_bigi.sign = 0;
                remainder_bigi.num = remainder;
                remainder_bigi.removeStartingZeros();
                i++;

                pair<int, vector<int> > quotientAndRemainder1 = this->divideBySubtraction(remainder_bigi, b2);

                quotient.num.push_back( quotientAndRemainder1.first );

                remainder = quotientAndRemainder1.second;

            }

            remainder_bigI.num = remainder;

            BigI tmp;
            tmp = tmp.extractBigIFromInt(0);
            if(remainder_bigI.num == tmp.num) {
                remainder_bigI.sign = 0;
            }
            return {quotient,remainder_bigI};

      }

      // this method is used to divide dividend and divisor using subtraction

      pair<int, vector<int> > divideBySubtraction(BigI dividend, BigI divisor) {
            int quotient = 0;
            vector<int> remiander;
            BigI zero;
            zero = extractBigIFromInt(0);
            while( 1 ) {
                dividend = dividend - divisor;

                if( dividend < zero ) {
                    dividend = dividend + divisor;
                    break;
                }
                else {
                    quotient++;
                }
            }
            return {quotient, dividend.num};
      }

      // this method is used to convert int to BigI

      BigI extractBigIFromInt(int x) {
            BigI number;
            if(x < 0) {
                number.sign = 1;
                x = -x;
            }
            else {
                number.sign = 0;
            }
            vector<int> vec;
            if(x == 0) {
                vec.push_back(0);
            }
            while(x > 0) {
                vec.insert(vec.begin(), x%10);
                x/=10;
            }
            number.num = vec;
            return number;
      }

      // this method is used to make both num1 and num2 to equal length

      int makeEqualLength(vector<int> &num1, vector<int> &num2) {

            int diff;

            if(num1.size() == num2.size()) {
                return num1.size();
            }

            if( num1.size() > num2.size()) {
                diff = num1.size() - num2.size();
                for(int i = 0; i < diff; i++) {
                    num2.insert(num2.begin(), 0);
                }

                return num1.size();
            }

            diff = num2.size() - num1.size();
            for(int i = 0; i < diff; i++) {
                num1.insert(num1.begin(), 0);
            }

            return num2.size();

      }

      // this method is used to remove the starting zeros (if any)

      void removeStartingZeros() {
          int i;

          for( i = 0; i < (int)this->num.size(); i++) {
                if(this->num[i] != 0) {
                    break;
                }
          }

          if( i == (int)this->num.size() ) {
            this->num.clear();
            this->num.push_back( 0 );
            this->sign = 0;
          }

          else {
            this->num.erase(this->num.begin(), this->num.begin() + i);
          }

      }

      // this will return the length of the BigI number

      int size() {
          return num.size();
      }

      friend ostream & operator << (ostream & , const BigI &);
      friend istream & operator >> (istream & , BigI &);
      friend BigI abs(BigI &);
      friend BigI max(BigI &, BigI &);
      friend BigI min(BigI &, BigI &);
      friend BigI sqrt(BigI &);
      friend BigI fact(BigI &);
      friend BigI pow(BigI, BigI);
      friend BigI gcd(BigI, BigI);
      friend BigI lcm(BigI &, BigI &);
};

// overloading << operator for producing BigI as output using cout

ostream & operator << (ostream & out, const BigI & b){

    if(b.sign) {
        out << "-";
    }
    for(int val:b.num){
        out << val;
    }
    return out;

}

// overloading >> operator for taking BigI as input using cin

istream & operator >> (istream & in, BigI & b){
    string str;
    int i = 0;
    in >> str;
    int n = str.length();
    if(str[0] == '-'){
        b.sign = 1;
        i++;
    }
    else{
        b.sign = 0;
    }

    b.num.clear();

    for(;i < n; i++) {
        if(str[i] >= '0' && str[i] <= '9') {
            b.num.push_back( str[i] - '0' );
        }
        else {
            break;
        }
    }

    if(b.num.size() == 0) {
        b.num.push_back(0);
    }

    b.removeStartingZeros();

    return in;
}

// this method calculates absolute value

BigI abs(BigI & b) {
    b.sign = 0;
    return b;
}

// this method calculates max value between 2 BigI numbers

BigI max(BigI & num1,BigI & num2) {

    if( num1 > num2 ) {
        return num1;
    }

    return num2;

}

// this method calculates min value between 2 BigI numbers

BigI min(BigI & num1, BigI & num2) {

    if( num1 > num2 ) {
        return num2;
    }

    return num1;

}

// this method calculates square root of BigI

BigI sqrt(BigI & b) {
    if(b.sign == 1) {

        BigI ans = b.extractBigIFromInt(-1);

        return ans;
    }

    BigI d = b.extractBigIFromInt(1);

    while(1) {

        BigI sqd = d * d;

        if( b < sqd ) {
            break;
        }

        d = d * 2;

    }

    BigI ans = b.extractBigIFromInt(0);

    while(1) {

        BigI te = ans + d;

        BigI te1 = te * te ;

        if( b < te1 );
        else {
            ans = te;
        }

        d = d / 2;

        if(d.num.size() == 1) {
            if(d.num[0] == 0) {
                break;
            }
        }

    }

    return ans;
}

// this method calculates factorial of BigI

BigI fact(BigI &b) {

    BigI i = b.extractBigIFromInt(1);

    BigI ans = b.extractBigIFromInt(1);

    while( i <= b) {
        ans = ans * i;
        i = i + 1;
    }

    return ans;
}

// this method calculates BigI power BigI

BigI pow(BigI b1, BigI b2) {

    BigI ans;
    ans = ans.extractBigIFromInt(1);

    BigI zero;
    zero = zero.extractBigIFromInt(0);

    while( b2 > zero ) {

        int sze = b2.num.size();

        if( b2.num[sze - 1] % 2 == 0 ) {

            b1 = b1 * b1;

            b2 = b2 / 2;

        }
        else {

            ans = ans * b1;
            b2--;

        }
    }

    return ans;

}

// this method calculates gcd

BigI gcd(BigI num1, BigI num2) {

    BigI zero,temp;

    zero = zero.extractBigIFromInt(0);

    abs(num1);
    abs(num2);

    while(1) {

        if(num2 == zero) {
            return num1;
        }

        temp = num2;
        num2 = num1 % num2;
        num1 = temp;
    }

}

// this method calculates lcm

BigI lcm(BigI &num1, BigI &num2) {

    return (num1/(gcd(num1,num2)))*num2;

}
