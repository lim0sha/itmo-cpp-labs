#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string_view>
#include <cstring>
#include <cstdint>
#include <cmath>
#pragma once

// Вектор
class CVector2D {
 public:
  double x, y;
};

// Интерфейс "Геометрическая фигура".
class IGeoFig {
 public:
  // Площадь.
  virtual double square() = 0;
  // Периметр.
  virtual double perimeter() = 0;
  // Перемещение на заданный вектор
  virtual void vectorize(const CVector2D &vector_2_d) = 0;
};

// Интерфейс "Физический объект".
class IPhysObject {
 public:
  double mass_{};
  // Масса, кг.
  virtual double mass() = 0;
  // Координаты центра масс, м.
  virtual CVector2D position() = 0;
  // Сравнение по массе.
  virtual bool operator==(const IPhysObject &ob) const = 0;
  // Сравнение по массе.
  virtual bool operator<(const IPhysObject &ob) const = 0;
};

// Интерфейс "Отображаемый"
class IPrintable {
 public:
  // Отобразить на экране (выводить в текстовом виде параметры фигуры).
  virtual void draw() = 0;
};

// Интерфейс для классов, которые можно задать через диалог с пользователем.
class IDialogInitiable {
  // Задать параметры объекта с помощью диалога с пользователем.
  virtual void initFromDialog() = 0;
};

// Интерфейс "Класс"
class BaseCObject {
 public:
// Имя класса (типа данных).
  virtual const char *classname() = 0;
// Размер занимаемой памяти.
  virtual unsigned int size() = 0;
};

// Интерфейс функционал системы
class IFunctionalSystem {
 public:
  // Хранение множества фигур
  virtual void storeObject(std::vector<IFunctionalSystem *> &storage) = 0;
  // Динамическое добавление фигур пользователем (через консоль)
  virtual void addObject(std::vector<IFunctionalSystem *> &storage) = 0;
  // Отобразить все фигуры
  virtual void printAll(std::vector<IFunctionalSystem *> &storage) = 0;
  // Суммарная площадь всех фигур
  virtual double totalSquare(std::vector<IFunctionalSystem *> &storage) = 0;
  // Суммарный периметр всех фигур
  virtual double totalPerimeter(std::vector<IFunctionalSystem *> &storage) = 0;
  // Центр масс всей системы
  virtual CVector2D systemMassCenter(std::vector<IFunctionalSystem *> &storage) = 0;
  // Память, занимаемая всеми экземплярами классов
  virtual unsigned long allMemory(std::vector<IFunctionalSystem *> &storage) = 0;
  // Сортировка фигур между собой по массе
  virtual void sortObjects(std::vector<IFunctionalSystem *> &storage) = 0;

  // Helpers
  virtual void printInfo() = 0;
  virtual double getSquare() = 0;
  virtual double getPerimeter() = 0;
  virtual CVector2D getPos() = 0;
  virtual unsigned int getSize() = 0;
  virtual double getMass() = 0;

  static bool compareBySize(IFunctionalSystem *a, IFunctionalSystem *b) {
    return a->getMass() < b->getMass();
  }
};
