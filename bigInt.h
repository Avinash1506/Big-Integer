#include<bits/stdc++.h>
using namespace std;
class BigI
{
    private:

     vector<int> num; // contains the big integer
     int sign; // 1 if its negative else 0

    public:

      //method for addition

      BigI operator + (BigI obj) {
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

      //method for subtraction

      BigI operator - (BigI obj) {

            // if both are positive or both are negative
            if( (this->sign ^ obj.sign) == 0 ) {

                BigI ans;
                if( (this->sign == 0 && obj.sign == 0) ) {
                    ans.sign = 0;
                }

                if( (this->sign == 1 && obj.sign == 1) ) {
                    ans.sign = 1;
                }

                vector <int> num1(num);
                vector <int> num2(obj.num);
                vector <int> res;
                if( *this < obj) {
                    ans.sign = ans.sign ^ 1;
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

                    return ans;
                }
                else {
                    BigI num1, num2, ans;

                    num1.num = num;
                    num2.num = obj.num;
                    num1.sign = 0;
                    num2.sign = 0;

                    ans = num1 + num2;

                    ans.sign = ans.sign ^ 1; // multiplying by -1

                    return ans;
                }
            }

      }


      //method for multiplication

      BigI operator * ( BigI obj ) {
            vector<int> num1,num2;
            num1 = num;
            num2 = obj.num;
            vector<int> num3 = this->karatsuba(num1, num2);
            BigI ans;
            ans.num = num3;
            if( (this->sign ^ obj.sign) == 0) {
                ans.sign = 0;
            }
            else {
                ans.sign = 1;
            }

            ans.removeStartingZeros();

            return ans;
      }

      //method for division

      BigI operator / (BigI b) {

            BigI ans;
            ans.sign = sign ^ b.sign;

            sign = 0;
            b.sign = 0;

            if( *this < b ) {

                BigI zero;
                zero = extractBigIFromInt(0);

                return zero;

            }

            if( *this == b ) {

                BigI one;
                one = extractBigIFromInt(1);

                return one;

            }

            BigI zero;
            int dividendSize = num.size();
            zero = extractBigIFromInt(0);

            if(b == zero) {
                cerr<<"Division by zero error: ";
                BigI ans = extractBigIFromInt(-1);
                return ans;
            }

            BigI t;
            t.sign = 0;

            t.num.push_back(num[0]);

            int i;

            for(i = 1; i < dividendSize; i++) {
                if( t >= b ) {
                    break;
                }

                t.num.push_back( num[i] );
            }

            pair<int, vector<int> > quotientAndRemainder = this->divideBySubtraction(t, b);

            ans.num.push_back( quotientAndRemainder.first );
            vector<int> remainder = quotientAndRemainder.second;

            while( i < dividendSize) {

                remainder.push_back(num[i]);
                BigI remainder_bigi;
                remainder_bigi.sign = 0;
                remainder_bigi.num = remainder;
                remainder_bigi.removeStartingZeros();
                i++;

                pair<int, vector<int> > quotientAndRemainder1 = this->divideBySubtraction(remainder_bigi, b);

                ans.num.push_back( quotientAndRemainder1.first );

                remainder = quotientAndRemainder1.second;

            }

            return ans;

      }

      //method for modulus

      BigI operator % (BigI b) {
            BigI ans;
            ans.sign = sign ^ b.sign;

            sign = 0;
            b.sign = 0;

            if( *this < b ) {

                return *this;

            }

            if( *this == b ) {

                BigI zero;
                zero = extractBigIFromInt(0);

                return zero;

            }

            BigI zero;
            int dividendSize = num.size();
            zero = extractBigIFromInt(0);

            if(b == zero) {
                BigI ans = extractBigIFromInt(-1);
                return ans;
            }
            BigI t;
            t.sign = 0;

            t.num.push_back(num[0]);

            int i;

            for(i = 1; i < dividendSize; i++) {
                if( t >= b ) {
                    break;
                }

                t.num.push_back( num[i] );
            }

            pair<int, vector<int> > quotientAndRemainder = t.divideBySubtraction(t, b);

            ans.num.push_back( quotientAndRemainder.first );
            vector<int> remainder = quotientAndRemainder.second;

            while( i < dividendSize) {

                remainder.push_back(num[i]);
                BigI remainder_bigi;
                remainder_bigi.sign = 0;
                remainder_bigi.num = remainder;
                remainder_bigi.removeStartingZeros();
                i++;

                pair<int, vector<int> > quotientAndRemainder1 = remainder_bigi.divideBySubtraction(remainder_bigi, b);

                remainder = quotientAndRemainder1.second;

            }

            ans.num = remainder;

            return ans;
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

      //short-hand notation for +

      BigI & operator += (const BigI &num2) {

            *this = *this + num2;

            return *this;
      }

      //short-hand notation for -

      BigI & operator -= (const BigI &num2) {

            *this = *this - num2;

            return *this;
      }

      //short-hand notation for *

      BigI & operator *= (const BigI &num2) {

            *this = (*this)*(num2);

            return *this;
      }

      //short-hand notation for /

      BigI & operator /= (const BigI &num2) {

            *this = (*this)/(num2);

            return *this;
      }

      //short-hand notation for %

      BigI & operator %= (const BigI &num2) {

            *this = (*this) % (num2);

            return *this;
      }

      //short-hand notation for + with int

      BigI & operator += (int num2) {

            *this = *this + num2;

            return *this;
      }

      //short-hand notation for - with int

      BigI & operator -= (int num2) {

            *this = *this - num2;

            return *this;
      }

      //short-hand notation for * with int

      BigI & operator *= (int num2) {

            *this = (*this) * (num2);

            return *this;
      }

      //short-hand notation for / with int

      BigI & operator /= (int num2) {

            *this = (*this) / (num2);

            return *this;
      }

      //short-hand notation for % with int

      BigI & operator %= (int num2) {

            *this = (*this) % (num2);

            return *this;
      }


      //pre-increment operator

      BigI operator ++ () {
          *this = *this + 1;
          return *this;
      }

      //post-increment operator

      BigI operator ++ (int) {
          BigI num1 = *this;
          *this = *this + 1;
          return num1;
      }

      //pre-decrement operator

      BigI operator -- () {
          *this=*this - 1;
          return *this;
      }


      //post-decrement operator

      BigI operator -- (int) {

          BigI num1 = *this;

          *this = *this - 1;

          return num1;
      }

      //greater than operator

      bool operator > (BigI b) {

            if( this->sign == 0 && b.sign == 0) {
                vector<int> num1,num2;

                num1 = num;
                num2 = b.num;

                if( num1.size() > num2.size() )
                    return true;

                if( num1.size() < num2.size())
                    return false;

                for(int i = 0; i < (int)num1.size(); i++) {

                    if(num1[i] > num2[i])
                        return true;

                    if(num1[i] < num2[i])
                        return false;

                }

                return false;
            }
            else if( this->sign == 1 && b.sign == 1) {
                BigI b1, b2;
                b1.sign = b2.sign = 0;
                b1.num = num;
                b2.num = b.num;
                return b1 < b2;
            }
            else if( this->sign == 1 && b.sign == 0) {
                return false;
            }
            else {
                return true;
            }
      }

      //greater than or equal to operator

      bool operator >= (BigI b) {

            if( this->sign == 0 && b.sign == 0) {
                vector<int> num1,num2;

                num1 = num;
                num2 = b.num;

                if( num1.size() > num2.size() )
                    return true;

                if( num1.size() < num2.size())
                    return false;

                for(int i = 0; i < (int)num1.size(); i++) {

                    if(num1[i] > num2[i])
                        return true;

                    if(num1[i] < num2[i])
                        return false;

                }

                return true;
            }
            else if( this->sign == 1 && b.sign == 1) {
                BigI b1, b2;
                b1.sign = b2.sign = 0;
                b1.num = num;
                b2.num = b.num;

                return b1 <= b2;
            }
            else if( this->sign == 1 && b.sign == 0 ) {
                return false;
            }
            else {
                return true;
            }
      }

      //less than operator

      bool operator < (BigI b) {

            if( this->sign == 0 && b.sign == 0) {
                vector<int> num1,num2;

                num1 = num;
                num2 = b.num;

                if( num1.size() < num2.size() )
                    return true;

                if( num1.size() > num2.size())
                    return false;

                for(int i = 0; i < (int)num1.size(); i++) {

                    if(num1[i] < num2[i])
                        return true;

                    if(num1[i] > num2[i])
                        return false;

                }

                return false;
            }
            else if( this->sign == 1 && b.sign == 1 ) {

                BigI b1, b2;
                b1.sign = 0;
                b2.sign = 0;
                b1.num = num;
                b2.num = b.num;

                return b1 > b2;
            }
            else if( this->sign == 1 && b.sign ==0 )
                return true;

            else
                return false;
      }

      //less than or equal to operator

      bool operator <= (BigI b) {

            if( this->sign == 0 && b.sign == 0 ) {

                vector<int> num1,num2;

                num1 = num;
                num2 = b.num;

                if( num1.size() < num2.size() )
                    return true;

                if( num1.size() > num2.size())
                    return false;

                for(int i = 0; i < (int)num1.size(); i++) {

                    if(num1[i] < num2[i])
                        return true;

                    if(num1[i] > num2[i])
                        return false;

                }

                return true;
            }
            else if( this->sign ==1 && b.sign == 1 ) {

                BigI b1,b2;

                b1.sign = 0;
                b2.sign = 0;

                b1.num = num;
                b2.num = b.num;

                return b1 >= b2;

            }
            else if( this->sign == 1 && b.sign == 0) {
                return true;
            }
            else {
                return false;
            }
      }

      //equal to operator

      bool operator == (BigI b) {

            if( (this->sign ^ b.sign) == 1) {
                return false;
            }

            if( num.size() != b.num.size() ) {
                return false;
            }

            for(int i = 0; i < (int)num.size(); i++) {
                if( num[i] != b.num[i] ) {
                    return false;
                }
            }

            return true;

      }

      //not equal to operator

      bool operator != ( BigI b ) {
            if( (this->sign ^ b.sign) == 1) {
                return true;
            }

            if( num.size() != b.num.size() ) {
                return true;
            }

            for(int i = 0; i < (int)num.size(); i++) {
                if( num[i] != b.num[i] ) {
                    return true;
                }
            }

            return false;
      }

      //greater than operator BigI > int

      bool operator > ( int x ) {

            BigI num2 = this->extractBigIFromInt(x);

            return (*this) > num2;
      }

      //greater than or equal to operator BigI >= int

      bool operator >= ( int x ) {

            BigI num2 = this->extractBigIFromInt(x);

            return (*this) >= num2;
      }

      //less than to operator BigI < int

      bool operator < ( int x ) {

            BigI num2 = this->extractBigIFromInt(x);

            return (*this) < num2;
      }

      //less than or equal to operator BigI <=int

       bool operator <= ( int x ) {

            BigI num2 = this->extractBigIFromInt(x);

            return (*this) <= num2;
      }

      //equal to operator BigI == int

       bool operator == ( int x ) {

            BigI num2 = this->extractBigIFromInt(x);

            return (*this) == num2;
      }

      //not equal to operator BigI != int

       bool operator != ( int x ) {

            BigI num2 = this->extractBigIFromInt(x);

            return (*this) != num2;
      }

     // type-casting from int to BigI

     // operator BigI() const {

       //     BigI b;
       //    if(x < 0) {
       //         b.sign = 1;
       //         x = -x;
       //     }
       //     else {
       //         b.sign = 0;
       //     }
       //     vector<int> vec;
       //     if(x == 0) {
       //         vec.push_back(0);
       //     }
       //     while(x > 0) {
       //         vec.insert(vec.begin(), x%10);
       //         x/=10;
       //     }
       //     b.num = vec;
       //     return b;

       //}


      //this method is used to convert int to BigI

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

      //this method is used to remove the starting zeros (if any)

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

      //this method is used to make both num1 and num2 to equal length

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

      //this method is implementation of karatsuba algorithm

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

      //this method is used to divide dividend and divisor using subtraction

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

      friend ostream & operator << (ostream & , BigI & );
      friend istream & operator >> (istream & , BigI & );
      friend BigI abs(BigI);
      friend BigI sqrt(BigI);
      friend BigI fact(BigI);
      friend BigI pow(BigI, BigI);
      friend BigI gcd(BigI, BigI);
};

ostream & operator << (ostream & out, BigI & b){

    if(b.sign) {
        out << "-";
    }
    for(int val:b.num){
        out << val;
    }
    return out;

}

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

//this method calculates absolute value

BigI abs(BigI b) {
    b.sign = 0;
    return b;
}

//this method calculates max value between 2 BigI numbers

BigI max(BigI num1, BigI num2) {

    if( num1 > num2 ) {
        return num1;
    }

    return num2;

}

//this method calculates min value between 2 BigI numbers

BigI min(BigI num1, BigI num2) {

    if( num1 > num2 ) {
        return num2;
    }

    return num1;

}

//this method calculates square root of BigI

BigI sqrt(BigI b) {
    if(b.sign == 1) {

        BigI ans;
        ans = ans.extractBigIFromInt(-1);

        return ans;
    }

    BigI d;
    d = d.extractBigIFromInt(1);

    while(1) {

        BigI sqd = d * d;

        if( b < sqd ) {
            break;
        }

        d = d * 2;

    }

    BigI ans;
    ans = ans.extractBigIFromInt(0);

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

//this method calculates factorial of BigI

BigI fact(BigI b) {
    BigI i;
    i = i.extractBigIFromInt(1);

    BigI ans;
    ans = ans.extractBigIFromInt(1);

    while( i <= b) {
        ans = ans * i;
        i = i + 1;
    }

    return ans;
}

//this method calculates BigI power BigI

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

//this method calculates gcd

BigI gcd(BigI num1, BigI num2) {
    BigI zero,temp;
    zero = zero.extractBigIFromInt(0);
    while(1) {
        if(num2 == zero) {
            return num1;
        }

        temp = num2;
        num2 = num1 % num2;
        num1 = temp;
    }

}

//this method calculates lcm

BigI lcm(BigI num1, BigI num2) {

    return (num1/(gcd(num1,num2)))*num2;
}
