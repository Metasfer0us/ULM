#pragma once
#include "list.h"

typedef void(*Function)(void);

class SignedFunction
{
public:

  // Конструктор
  SignedFunction(char* sign, Function function)
  {
    sign_ = new char[strlen(sign) + 1];
    strcpy(sign_, sign);

    function_ = function;
  }

  // Конструктор
  SignedFunction(char* sign)
  {
    sign_ = new char[strlen(sign) + 1];
    strcpy(sign_, sign);

    function_ = defaultFunction;

  }

  // Конструктор
  SignedFunction(Function function)
  {
    sign_ = new char[strlen(defaultSign) + 1];
    strcpy(sign_, defaultSign);

    function_ = function;
  }

  // Конструктор
  SignedFunction()
  {
    sign_ = new char[strlen(defaultSign) + 1];
    strcpy(sign_, defaultSign);

    function_ = defaultFunction;
  }

  // Деструктор
  ~SignedFunction()
  {
    if (sign_) {
      delete[] sign_;
    }
  }

  // Задати підпис
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

  // Задати функцію
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

  // Задати підпис та функцію
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

  // Отримати підпис
  char*
    getSign()
  {
    return sign_;
  }

  // Отримати функцію
  Function
    getFunction()
  {
    return function_;
  }

  // Виклик функції
  void
    call()
  {
    function_();
  }


private:

  // Підпис
  char* sign_;

  // Функція
  Function
    function_;

  char* defaultSign = "Пусто";

  Function
    defaultFunction = []()
  {
    system("cls");
    std::cout << "Пуста функція \n";
  };

};

class FunctionsList : List<SignedFunction>
{
public:

  // Додати в початок пусту функцію з заданим підписом
  void
    addFront(char* sign)
  {
    List::addFront(new SignedFunction(sign));
  }

  // Додати в початок задану функцію з пустим підписом
  void
    addFront(Function function)
  {
    List::addFront(new SignedFunction(function));
  }

  // Додати в початок пусту функцію з пустим підписом
  void
    addFront()
  {
    List::addFront(new SignedFunction);
  }

  // Додати в кінець пусту функцію з заданим підписом
  void
    addBack(char* sign)
  {
    List::addBack(new SignedFunction(sign));
  }

  // Додати в кінець задану функцію з пустим підписом
  void
    addBack(Function function)
  {
    List::addBack(new SignedFunction(function));
  }

  // Додати в кінець пусту функцію з пустим підписом
  void
    addBack()
  {
    List::addBack(new SignedFunction);
  }

};

class Menu
{
public:
  
  // Конструктор
  Menu()
  {
    functions_ = new Function(nullptr);
    names_     = new char*(nullptr);
    size_      = 0;
  }

  // Деструктор
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


  // Додати в початок пункт з заданим ім'ям та функцією
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

  // Додати в початок пункт з пустим ім'ям та функцією
  void
    addFront(Function function)
  {
    addFront(defaultName, function);
  }

  // Додати в початок пункт з заданим ім'ям та пустою функцією
  void
    addFront(char* name)
  {
    addFront(name, defaultFunction);
  }

  // Додати в початок пункт з пустим ім'ям та пустою функцією
  void
    addFront()
  {
    addFront(defaultName, defaultFunction);
  }


  // Додати в кінець пункт з заданим ім'ям та заданою функцією
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

  // Додати в кінець пункт з пустим ім'ям та заданою функцією
  void
    addBack(Function function)
  {
    addBack(defaultName, function);
  }

  // Додати в кінець пункт з заданим ім'ям та пустою функцією
  void
    addBack(char* name)
  {
    addBack(name, defaultFunction);
  }

  // Додати в кінець пункт з пустим ім'ям та пустою функцією
  void
    addBack()
  {
    addBack(defaultName, defaultFunction);
  }


  // Видалити на початку
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

  // Видалити в кінці
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
  // Функції
  Function* functions_;
  // Імена
  char**    names_;
  // Розмір
  int size_;

  // Пуста функція
  Function 
    defaultFunction = []() 
  {
    system("cls");
    std::cout << "\n Пуста функція \n";
  };

  // Пусте ім'я
  char* defaultName = new char[6]{ "Пусто" };

};
