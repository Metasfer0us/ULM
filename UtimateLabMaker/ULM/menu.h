#pragma once
#include "list.h"

typedef int (*Function)(void);

class Menu
{
public:

  // ����������� ���� ��� ��������� ��������
  Menu(char* title)
  {
    size_ = 1;

    title_ = new char[strlen(title) + 1];
    names_      = new char*[size_];
    functions_  = new Function[size_];

    strcpy(title_, title);
    *names_     = nullptr;
    *functions_ = []() {return 0; };
  }
  
  // ����������� ���� � �������� ���������
  Menu(char* title, char* name)
  {
    size_       = 1;

    title_      = new char[strlen(title) + 1];
    names_      = new char*[size_];
    *names_     = new char[strlen(name) + 1];
    functions_  = new Function[size_];

    strcpy(title_ , title);
    strcpy(*names_, name);
    *functions_ = []() {return 0; };
  }

  // ����������
  ~Menu() 
  {
    if (title_) {
      delete[] title_;
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
    if (functions_)
    {
      delete[] functions_;
    }
  }  

  // ������ � ����� ����� � ������� ��'�� �� ������� ��������
  void
    add(char* name, Function function)
  {
    char**    names     = new char*   [size_ + 1];
    *(names + size_)    = new char    [strlen(name) + 1];
    Function* functions = new Function[size_ + 1];

    memcpy(names    , names_    , sizeof(char*) * size_);
    memcpy(functions, functions_, sizeof(Function) * size_);

    strcpy(*(names + size_), name);
    *(functions + size_) = function;


    if (names_)
    {
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

  // ������ � ����
  int 
    cycle() 
  {
    unsigned int select = 1;
    while (select != 0)
    {
      system("cls");
      out();
      input("������� ������", "³������ ������", (unsigned int)(*names_ ? 0 : 1), size_ - 1, select);
      if (select != 0)
      {
        system("cls");
        call(select);
      }
    }
    return select;
  }


private:

  // ��������� ����
  char*  title_;
  
  // �����
  char** names_;

  // �������
  Function* functions_;

  // �����
  unsigned int size_;

  // ���� ����
  void
    out()
  {
    std::cout << title_ << "\n\n";
    for (unsigned int i = 1; i < size_; i++)
    {
      std::cout << i << ". " << *(names_ + i) << '\n';
    }
    if (*names_)
    {
      std::cout << "0. " << *names_ << '\n';
    }
    std::cout << std::endl;
  }

  // ������ �������
  void
    call(unsigned int number)
  {
    if (number < size_) {
      (*(functions_ + number))();
    }
  }

};
