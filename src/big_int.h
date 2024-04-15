// AUTOR: Javier Garcia Santana
// FECHA: 10/2/2023
// EMAIL: alu0101391663@ull.edu.es
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos Avanzadas
// PRÁCTICA Nº: 1
// COMENTARIOS: Fichero .h en el que se instancia la
//clase BigInt y todos sus metodos para que posteriormente sea
//posible operar con ellos
//
// COMPILACIÓN: make

#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>

#ifndef BIG_INT_H
#define BIG_INT_H

template <size_t Base = 10>

class BigInt {

 public:
  BigInt(long n = 0);
  BigInt(std::string&);
  BigInt(const char*);
  BigInt(const BigInt<Base>&); // Constructor de copia

  BigInt<Base>& operator=(const BigInt<Base>&);
  
  void read(std::istream& = std::cin);
  void write(std::ostream& = std::cout) const;

  int sign() const; // Signo: 1 o -1
  long DecimalValue() const;
  int SumOfVectorElements() const;
  std::vector<char> OriginalBaseValue(long) const;
  char operator[](int) const; // Acceso al i-ésimo dígito

  friend bool operator==(const BigInt<Base>& big_int, const BigInt<Base>& other_big_int) {
    return !(big_int != other_big_int);
  }

  bool operator!=(const BigInt<Base>&) const;
  
  friend bool operator>(const BigInt<Base>& big_int, const BigInt<Base>& other_big_int) {
    return big_int.DecimalValue() > other_big_int.DecimalValue();
  }

  bool operator>=(const BigInt<Base> &) const;

  friend bool operator<(const BigInt<Base>& big_int, const BigInt<Base>& other_big_int) {
    return !(big_int > other_big_int);
  } 

  bool operator<=(const BigInt<Base>&) const;

  BigInt<Base>& operator++(); 
  BigInt<Base> operator++(int); 
  BigInt<Base>& operator--(); 
  BigInt<Base> operator--(int);

  friend BigInt<Base> operator+(const BigInt<Base>& big_int, const BigInt<Base>& other_big_int) {
    BigInt<Base> result;
    if ((big_int.DecimalValue() * big_int.sign_) + (other_big_int.DecimalValue() * other_big_int.sign_) < 0) {
      result.sign_ = -1;
    } else {
      result.sign_ = 1;
    }
    result.digits_ = result.OriginalBaseValue(((big_int.DecimalValue() * big_int.sign_) + (other_big_int.DecimalValue() * other_big_int.sign_)));
  
    // int sum = 0, carry = 0;
    // std::vector<char> op1, op2, complete_sum;
    // if (big_int < other_big_int) {
    //   op1 = big_int.digits_;
    //   op2 = other_big_int.digits_;
    // } else {
    //   op1 = other_big_int.digits_;
    //   op2 = big_int.digits_;
    // }
    // //std::cout << "Sum debugging:\n";
    // for (int i = op1.size() - 1, j = op2.size() - 1; i >= 0; --i, --j) {
      
    //   sum = op1.at(i) + op2.at(j);
      
    //   if (sum >= Base) {
    //     sum = (sum - Base) + carry;
    //     carry = 1;
    //   } else {
    //     if (carry + sum >= Base) {
    //       sum = (sum - Base) + carry;
    //       carry = 1;
    //     } else {
    //       sum += carry;
    //       carry = 0;
    //     }
    //   }
    //   // std::cout << char(op1.at(i) + 'A' - 10) << " + " << char(op2.at(j) + 'A' - 10) 
    //   // << " + " << carry << " = " << sum << " |" << std::endl;
    //   complete_sum.insert(complete_sum.begin(), sum);
    // }
    // if (big_int.digits_.size() == other_big_int.digits_.size()) {
    //   if (carry == 1) {
    //     complete_sum.insert(complete_sum.begin(), carry);
    //   }
    //   result.digits_ = complete_sum;
    // } else {
    //   for (int i = (op2.size() - op1.size()) - 1; i >= 0; --i) {
    //     sum = op2.at(i) + carry;
    //     if (sum >= Base) {
    //       sum = sum - Base;
    //       carry = 1;
    //     } else {
    //       carry = 0;
    //     }
    //     //std::cout << char(op2.at(i) + 'A' - 10) << " + " << carry << " = " << sum << std::endl;
    //     complete_sum.insert(complete_sum.begin(), sum);
    //   }
    //   if (carry == 1) {
    //     complete_sum.insert(complete_sum.begin(), carry);
    //   }
    //   result.digits_ = complete_sum;
    // }
    return result;
  } 

  BigInt<Base> operator-(const BigInt<Base> &) const;
  BigInt<Base> operator-() const;
  BigInt<Base> operator*(const BigInt<Base>&) const;

  friend BigInt<Base> operator/(const BigInt<Base>& big_int, const BigInt<Base>& other_big_int) {
    BigInt<Base> result;
    if (big_int.sign_ == -1 || other_big_int.sign_ == -1) {
      result.sign_ = -1;
    }
    result.digits_ = result.OriginalBaseValue(big_int.DecimalValue() / other_big_int.DecimalValue());
    return result;
  }

  BigInt<Base> operator%(const BigInt<Base>&) const;

  // Potencia a^b
  friend BigInt<Base> pow(const BigInt<Base>& big_int, const BigInt<Base>& other_big_int) {
    BigInt<Base> result;
    int multiplicator = 1;
    if (big_int.sign_ == -1 ) {
      result.sign_ = -1;
    }

    for (int i = 0; i < other_big_int.DecimalValue(); ++i) {
      multiplicator *= big_int.DecimalValue();
    }
    result.digits_ = result.OriginalBaseValue(multiplicator);
    return result;
  }

  operator BigInt<2>() {
    long operand = DecimalValue();
    char aux;
    std::string result;
    if (operand < 0) {
      operand *= -1;
    }
    if (operand == 0) {
      result.push_back(0);
      return result;
    }
    while (operand > 0) {
      aux = (operand % 2) + '0';//char conversion
      result.push_back(aux);
      operand /= 2;
      
    }
    reverse(result.begin(), result.end());
    return BigInt<2>(result);
  }

 private:
  std::vector<char> digits_;
  int sign_;
};


template<size_t Base>
BigInt<Base>::BigInt(long n) {
  digits_.push_back(n);
}

template<size_t Base>
BigInt<Base>::BigInt(std::string& input) {

  if (input[0] == '-') {
    sign_ = -1;
    input.erase(input.begin());
  } else {
    sign_ = 1;
  }
  
  for (int i = 0; i < input.size(); ++i) {
    if ((input[i] - '0') < Base) {
      digits_.push_back(input[i] - '0');
    } else if (input[i] - 'A' + 10 < Base) {
      digits_.push_back(input[i] - 'A' + 10);
    } else {
      std::cerr << "El numero no se puede representar en la base indicada" << std::endl;
      exit(EXIT_FAILURE);
    }
  } 
}

template<size_t Base>
BigInt<Base>::BigInt(const char* input) {
  std::string usable_input = input;

  if (input[0] == '-') {
    sign_ = -1;
    usable_input.erase(usable_input.begin());
  } else {
    sign_ = 1;
  }
  
  for (int i = 0; i < usable_input.size(); ++i) {
    if ((usable_input[i] - '0') < Base) {
      digits_.push_back(usable_input[i] - '0');
    } else if (usable_input[i] - 'A' + 10 < Base) {
      digits_.push_back(usable_input[i] - 'A' + 10);
    } else {
      std::cerr << "El numero no se puede representar en la base indicada" << std::endl;
      exit(EXIT_FAILURE);
    }
  } 
}

template<size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& other_big_int) {
  digits_ = other_big_int.digits_;
  sign_ = other_big_int.sign_;
}

template<size_t Base>
BigInt<Base> &BigInt<Base>::operator=(const BigInt<Base>& other_big_int) {
  digits_ = other_big_int.digits_;
  sign_ = other_big_int.sign_;
  return *this;
}

template<size_t Base>
void BigInt<Base>::write(std::ostream& os) const {
  if (sign_ == -1) {
    os << "-";
  }
  for (int i = 0; i < digits_.size(); ++i) {
    if (digits_.at(i) < 10) {
      os << char(digits_.at(i) + '0');
    } else if (digits_.at(i) >= 10 && digits_.at(i) < 16) {
      os << char(digits_.at(i) + 'A' - 10);
    }
  }
  os << std::endl;
}

template<size_t Base> 
void BigInt<Base>::read(std::istream& in) {

  std::string input;
  in >> input;
  int size = input.size();
  for (int i = size - 1; i >= 0; --i) {
    digits_.push_back(input[i] - '0');
  }
}

template<size_t Base>
std::ostream& operator<<(std::ostream& out, const BigInt<Base>& big_int) {
  big_int.write(out);
  return out;
}

template<size_t Base>
std::istream& operator>>(std::istream& in, BigInt<Base>& big_int) {
  big_int.read(in);
  return in;
}

template<size_t Base>
int BigInt<Base>::sign() const { // Signo: 1 o -1
  return sign_;
}  

template<size_t Base>
std::vector<char> BigInt<Base>::OriginalBaseValue(long input) const {

  std::vector<char> result;
  if (input < 0) {
    input *= -1;
  }
  if (input == 0) {
    result.push_back(0);
    return result;
  }
  while (input > 0) {
    result.push_back(input % Base);
    input /= Base;
  }
  reverse(result.begin(), result.end());
  return result;
}

template<size_t Base>
char BigInt<Base>::operator[](int i) const{ // Acceso al i-ésimo dígito
  return digits_.at(i);
}

template<size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& other_big_int) const {
  bool flag = false;
  if (digits_.size() == other_big_int.digits_.size() && sign_ == other_big_int.sign_) {
    for (int i = 0; i < digits_.size(); ++i) {
      if (digits_.at(i) != other_big_int.digits_.at(i)) {
        flag = true;
      }
    }
    return flag;
  } 
  return true;
}

template<size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base> & other_big_int) const {

  if (*this > other_big_int || *this == other_big_int) {
    return true;
  }
  return false;
}

template<size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base> & other_big_int) const {

  if (*this < other_big_int || *this == other_big_int) {
    return true;
  }
  return false;
}

template<size_t Base>
BigInt<Base> &BigInt<Base>::operator++(){
  int i, n = digits_.size();
  for (i = 0; i < n && digits_[i] == 9;i++)
      digits_[i] = 0;
  if(i == n)
      digits_.push_back(1);
  else
      digits_[i]++;
  return *this;
}

template<size_t Base>
BigInt<Base> BigInt<Base>::operator++(int temp){
  BigInt<Base> aux;
  aux = *this;
  ++(*this);
  return aux;
}

template<size_t Base>
BigInt<Base> &BigInt<Base>::operator--(){
  if(digits_[0] == 0 && digits_.size() == 1)
      throw("UNDERFLOW");
  int i, n = digits_.size();
  for (i = 0; digits_[i] == 0 && i < n;i++)
      digits_[i] = 9;
  digits_[i]--;
  if(n > 1 && digits_[n - 1] == 0)
      digits_.pop_back();
  return *this;
}

template<size_t Base>
BigInt<Base> BigInt<Base>::operator--(int temp){
  BigInt aux;
  aux = *this;
  --(*this);
  return aux;
}

template<size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base>& other_big_int) const {
  BigInt<Base> result;
  if ((DecimalValue() * sign_) - (other_big_int.DecimalValue() * other_big_int.sign_) < 0) {
    result.sign_ = -1;
  } else {
    result.sign_ = 1;
  }
  result.digits_ = OriginalBaseValue(((DecimalValue() * sign_) - (other_big_int.DecimalValue() * other_big_int.sign_)));
  // std::cout << "op1= " << *this << DecimalValue() << std::endl <<
  // "op2= " << other_big_int << other_big_int.DecimalValue() << " " << std::endl;
  return result;
}

template<size_t Base>
long BigInt<Base>::DecimalValue() const {

  long sum = 0;
  for (int i = 0; i < digits_.size(); ++i) {
    sum += (digits_.at(i) * pow(Base, (digits_.size() - 1) - i));
  }
  return sum;
}

template<size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base>& other_big_int) const {
  BigInt<Base> result;
  if (sign_ == -1 || other_big_int.sign_ == -1) {
    result.sign_ = -1;
  }
  result.digits_ = OriginalBaseValue(DecimalValue() * other_big_int.DecimalValue());
  return result;
}

template<size_t Base>
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base>& other_big_int) const {
  BigInt<Base> result;
  if (sign_ == -1 || other_big_int.sign_ == -1) {
    result.sign_ = -1;
  }
  result.digits_ = OriginalBaseValue(DecimalValue() % other_big_int.DecimalValue());
  return result;
}



#endif