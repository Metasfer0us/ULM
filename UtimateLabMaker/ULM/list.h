#pragma once
#include "common.h"

template <typename I>
class List 
{
public:

  // �����������
  List() 
  {
    size_ = 0;
    list_ = new I[size_];
  }

  // ����������
  ~List() 
  {
    delete[] list_;
  }

  // ������ � �������
  void 
    addFront (I* item) 
  {
    I*  list = new I[size_ + 1];

    memcpy(list + 1, list_, sizeof(I) * size_);
    *list = *item;

    delete[] list_;

    size_++;
    list_ = list;
  }

  // ������ � �����
  void
    addBack (I* item)
  {
    I* list = new I[size_ + 1];

    memcpy (list, list_, sizeof(I) * size_);
    *(list + size_) = *item;

    delete[] list_;

    size_++;
    list_ = list;
  }

  // ������ �������
  void
    setItem (I* item, unsigned int index)
  {
    *(list_ + index) = *item;
  }

  // �������� �������� �� �������
  I* 
    getItem (unsigned int index) 
  {
    return list_ + index;
  }

  // �������� � �������
  void
    removeFront()
  {
    size_--;

    I* list = new I[size_];

    memcpy(list, list + 1, size_);

    delete[] list_;

    list_ = list;
  }

  // �������� � ����
  void 
    removeBack()
  {
    size_--;

    I*  list = new I[size_];

    memcpy (list, list_, sizeof(I) * size_);

    delete[] list_;

    list_ = list;
  }


private:

  // ������
  I*           list_;
  // ����� ������
  unsigned int size_;


  
  // ������� �������

  // ������ ����� � �������
  void
    resizeFront (int value) 
  {
    int size = value + size_;
    int byteSize = sizeof(I*) * min(size_, size);
    I*  list = new I[size];
    I*  destination = list + (value > 0 ? value : 0);
    I*  source = list_ + (-value > 0 ? value : 0);

    memcpy(destination, source, byteSize);

    delete[] list_;

    size_ = size;
    list_ = list;
  }

  // ������ ����� � ����
  void
    resizeBack (int value) 
  {
    int size     = size_ + value;
    int bytesize = sizeof(T*) * min(size_, size);
    I*  list     = new I[size];

    memcpy(list, list_, bytesize);

    delete[] list_;

    size_ = size;
    list_ = list;
  }

  // ������ �����
  void  
    resize (int front, int back) 
  {
    int size = front + size_ + back;
    int byteSize    = sizeof(I*) * min(size_, size);
    I*  list        = new I[size];
    I*  destination = list + (front > 0 ? front : 0);
    I*  source      = list_ + (-front > 0 ? front : 0);

    memcpy (destination, source, byteSize);

    delete[] list_;

    size_ = size;
    list_ = list;
  }

};
