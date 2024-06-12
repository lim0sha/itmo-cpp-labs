#pragma once
#include "round_geo_figure.h"

class Ellipse
    : public IGeoFig,
      public IPhysObject,
      public IPrintable,
      public BaseCObject,
      public IDialogInitiable,
      public IFunctionalSystem {
 private:
  double radius_a{};
  double radius_b{};
  double x{};
  double y{};
 public:
  Ellipse();
  Ellipse(double xx, double yy, double ra, double rb) : x(xx), y(yy), radius_b(rb), radius_a(ra) {};
  void set_mass(int m);

  // IGeoFig virtuals
 public:
  double square() override;
  double perimeter() override;
  void vectorize(const CVector2D &vector_2_d) override;

  // IPhysObject virtuals
 public:
  double mass() override;
  CVector2D position() override;
  bool operator==(const IPhysObject &ob) const override;
  bool operator<(const IPhysObject &ob) const override;

  // IPrintable virtuals
  void draw() override;

  // IDialogInitiable virtuals
  void initFromDialog() override;

  // BaseCObject virtuals
  const char *classname() override;
  unsigned int size() override;

  // IFunctionalSystem virtuals
  void storeObject(std::vector<IFunctionalSystem *> &storage) override;
  void addObject(std::vector<IFunctionalSystem *> &storage) override;
  void printAll(std::vector<IFunctionalSystem *> &storage) override;
  double totalSquare(std::vector<IFunctionalSystem *> &storage) override;
  double totalPerimeter(std::vector<IFunctionalSystem *> &storage) override;
  CVector2D systemMassCenter(std::vector<IFunctionalSystem *> &storage) override;
  unsigned long allMemory(std::vector<IFunctionalSystem *> &storage) override;
  void sortObjects(std::vector<IFunctionalSystem *> &storage) override;
  // Helpers
  void printInfo() override;
  double getSquare() override;
  double getPerimeter() override;
  CVector2D getPos() override;
  unsigned int getSize() override;
  double getMass() override;
};
