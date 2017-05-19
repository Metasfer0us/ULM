#pragma once
#include "list.h"

typedef void(*Function)(void);

class SignedFunction
{
public:

  // �����������
  SignedFunction(char* sign, Function function)
  {
    sign_ = new char[strlen(sign) + 1];
    strcpy(sign_, sign);

    function_ = function;
  }

  // �����������
  SignedFunction(char* sign)
  {
    sign_ = new char[strlen(sign) + 1];
    strcpy(sign_, sign);

    function_ = defaultFunction;

  }

  // �����������
  SignedFunction(Function function)
  {
    sign_ = new char[strlen(defaultSign) + 1];
    strcpy(sign_, defaultSign);

    function_ = function;
  }

  // �����������
  SignedFunction()
  {
    sign_ = new char[strlen(defaultSign) + 1];
    strcpy(sign_, defaultSign);

    function_ = defaultFunction;
  }

  // ����������
  ~SignedFunction()
  {
    if (sign_) {
      delete[] sign_;
    }
  }

  // ������ �����
  void
    setSign(char* sign)
  {
    delete[] sign_;
    sign_ = new char[strlen(sign) + 1];
    strcpy(sign_, sign);
  }

  SignedFunction&
    operator= (char* sign) {
    setSign(sign);
    return *this;
  }

  // ������ �������
  void
    setFunction(Function function)
  {
    function_ = function;
  }

  SignedFunction&
    operator= (Function function) {
    setFunction(function);
    return *this;
  }

  // ������ ����� �� �������
  void
    set(char* sign, Function function)
  {
    setSign(sign);
    setFunction(function);
  }

  SignedFunction&
    operator= (SignedFunction& signedFunction) {
    setSign(signedFunction.getSign());
    setFunction(signedFunction.getFunction());
    return *this;
  }

  // �������� �����
  char*
    getSign()
  {
    return sign_;
  }

  // �������� �������
  Function
    getFunction()
  {
    return function_;
  }

  // ������ �������
  void
    call()
  {
    function_();
  }


private:

  // ϳ����
  char* sign_;

  // �������
  Function
    function_;

  char* defaultSign = "�����";

  Function
    defaultFunction = []()
  {
    system("cls");
    std::cout << "����� ������� \n";
  };

};

class FunctionsList : List<SignedFunction>
{
public:

  // ������ � ������� ����� ������� � ������� �������
  void
    addFront(char* sign)
  {
    List::addFront(new SignedFunction(sign));
  }

  // ������ � ������� ������ ������� � ������ �������
  void
    addFront(Function function)
  {
    List::addFront(new SignedFunction(function));
  }

  // ������ � ������� ����� ������� � ������ �������
  void
    addFront()
  {
    List::addFront(new SignedFunction);
  }

  // ������ � ����� ����� ������� � ������� �������
  void
    addBack(char* sign)
  {
    List::addBack(new SignedFunction(sign));
  }

  // ������ � ����� ������ ������� � ������ �������
  void
    addBack(Function function)
  {
    List::addBack(new SignedFunction(function));
  }

  // ������ � ����� ����� ������� � ������ �������
  void
    addBack()
  {
    List::addBack(new SignedFunction);
  }

};

class Menu
{
public:
  
  // �����������
  Menu()
  {
    functions_ = new Function(nullptr);
    names_     = new char*(nullptr);
    size_      = 0;
  }

  // ����������
  ~Menu() 
  {
    if (functions_)
    {
      delete[] functions_;
    }

    if (names_)
    {
      while (size_ > 0) 
      {
        size_--;
        if (*(names_ + size_))
        {
          delete[] *(names_ + size_);
        }
      }
      delete[] names_;
    }
  }


  // ������ � ������� ����� � ������� ��'�� �� ��������
  void
    addFront(char* name, Function function)
  {
    char**    names     = new char*[size_ + 1];
    Function* functions = new Function[size_ + 1];

    memcpy(names + 1    , names_    , sizeof(char*) * size_);
    memcpy(functions + 1, functions_, sizeof(Function) * size_);

    *names = new char[strlen(name) + 1];
    strcpy(*names, name);
    *functions_ = function;


    if (names_)
    {
      if (*names_)
      {
        delete[] *names_;
      }
      delete[] names_;
    }
    if (functions_)
    {
      delete[] functions_;
    }

    names_     = names;
    functions_ = functions;

    size_++;
  }

  // ������ � ������� ����� � ������ ��'�� �� ��������
  void
    addFront(Function function)
  {
    addFront(defaultName, function);
  }

  // ������ � ������� ����� � ������� ��'�� �� ������ ��������
  void
    addFront(char* name)
  {
    addFront(name, defaultFunction);
  }

  // ������ � ������� ����� � ������ ��'�� �� ������ ��������
  void
    addFront()
  {
    addFront(defaultName, defaultFunction);
  }


  // ������ � ����� ����� � ������� ��'�� �� ������� ��������
  void
    addBack(char* name, Function function)
  {
    char**    names     = new char*   [size_ + 1];
    Function* functions = new Function[size_ + 1];

    memcpy(names    , names_    , sizeof(char*) * size_);
    memcpy(functions, functions_, sizeof(Function) * size_);

    *(names + size_) = new char[strlen(name) + 1];
    strcpy(*(names + size_), name);
    *(functions_ + size_) = function;


    if (names_)
    {
      if (*(names_ + size_))
      {
        delete[] *(names_ + size_);
      }
      delete[] names_;
    }
    if (functions_)
    {
      delete[] functions_;
    }

    names_     = names;
    functions_ = functions;

    size_++;
  }

  // ������ � ����� ����� � ������ ��'�� �� ������� ��������
  void
    addBack(Function function)
  {
    addBack(defaultName, function);
  }

  // ������ � ����� ����� � ������� ��'�� �� ������ ��������
  void
    addBack(char* name)
  {
    addBack(name, defaultFunction);
  }

  // ������ � ����� ����� � ������ ��'�� �� ������ ��������
  void
    addBack()
  {
    addBack(defaultName, defaultFunction);
  }


  // �������� �� �������
  void
    removeFront()
  {
    size_--;

    char**    names     = new char*[size_];
    Function* functions = new Function[size_];

    memcpy(names    , names_ + 1    , sizeof(char*) * size_);
    memcpy(functions, functions_ + 1, sizeof(Function) * size_);

    if (names_)
    {
      if (*(names_ - 1))
      {
        delete[] *(names_ - 1);
      }
      delete[] names_;
    }
    if (functions_)
    {
      delete[] functions_;
    }

    names_     = names;
    functions_ = functions;
  }

  // �������� � ����
  void
    removeBack()
  {
    size_--;

    char**    names     = new char*[size_];
    Function* functions = new Function[size_];

    memcpy(names    , names_, sizeof(char*) * size_);
    memcpy(functions, functions_, sizeof(Function) * size_);

    if (names_)
    {
      if (*(names_ + size_))
      {
        delete[] * (names_ + size_);
      }
      delete[] names_;
    }
    if (functions_)
    {
      delete[] functions_;
    }

    names_     = names;
    functions_ = functions;
  }

  //
  void
    call(int itemNo)
  {
    (*(functions_ + --itemNo))();
  }

private:
  // �������
  Function* functions_;
  // �����
  char**    names_;
  // �����
  int size_;

  // ����� �������
  Function 
    defaultFunction = []() 
  {
    system("cls");
    std::cout << "\n ����� ������� \n";
  };

  // ����� ��'�
  char* defaultName = new char[6]{ "�����" };

};
