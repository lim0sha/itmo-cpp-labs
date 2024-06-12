#include "ellipse.h"

Ellipse::Ellipse() = default;

void Ellipse::set_mass(int m) {
  this->mass_ = m;
}

double Ellipse::square() {
  return M_PI * radius_a * radius_b;
}

double Ellipse::perimeter() {
  return 2 * M_PI * sqrt((radius_a * radius_a + radius_b * radius_b) / 2);
}

void Ellipse::vectorize(const CVector2D &vector_2_d) {
  this->x += vector_2_d.x;
  this->y += vector_2_d.y;
}

double Ellipse::mass() {
  return this->mass_;
}

CVector2D Ellipse::position() {
  CVector2D pos(this->x, this->y);
  return pos;
}

bool Ellipse::operator==(const IPhysObject &ob) const  {
  return (ob.mass_ == this->mass_);
}

bool Ellipse::operator<(const IPhysObject &ob) const {
  return (this->mass_ < ob.mass_);
}

void Ellipse::draw() {
  std::cout << "Coordinates (x;y) of an Ellipse: (" << this->x << ";" << this->y << ")\n";
  std::cout << "Two Radii (radius_a;radius_b) of an Ellipse: (" << this->radius_a << ";" << this->radius_b << ")\n";
  std::cout << "Mass of an Ellipse: " << this->mass_ << "\n";
}

void Ellipse::initFromDialog() {
  std::cout << "Let's initialize an Ellipse\n";
  std::cout << "Enter coordinates for position:\n";
  std::cin >> this->x >> this->y;
  std::cout << "Enter two radii (a and b):\n";
  std::cin >> this->radius_a >> this->radius_b;
  std::cout << "Enter mass:\n";
  std::cin >> this->mass_;
}

const char *Ellipse::classname() {
  return "This is an Ellipse class";
}

unsigned int Ellipse::size() {
  return sizeof(*this);
}

void Ellipse::printInfo() {
  this->draw();
}

double Ellipse::getSquare() {
  return this->square();
}

double Ellipse::getPerimeter() {
  return this->perimeter();
}

CVector2D Ellipse::getPos() {
  return this->position();
}

unsigned int Ellipse::getSize() {
  return this->size();
}

double Ellipse::getMass() {
  return this->mass();
}

void Ellipse::storeObject(std::vector<IFunctionalSystem *> &storage) {
  storage.push_back(this);
}

void Ellipse::addObject(std::vector<IFunctionalSystem *> &storage) {
  Ellipse *e_init = new Ellipse();
  e_init->initFromDialog();
  storage.push_back(e_init);
}

void Ellipse::printAll(std::vector<IFunctionalSystem *> &storage) {
  for (int i = 0; i < storage.size(); ++i) {
    storage[i]->printInfo();
  }
}

double Ellipse::totalSquare(std::vector<IFunctionalSystem *> &storage) {
  double totalsq = 0;
  for (int i = 0; i < storage.size(); ++i) {
    totalsq += storage[i]->getSquare();
  }
  return totalsq;
}

double Ellipse::totalPerimeter(std::vector<IFunctionalSystem *> &storage) {
  double totalper = 0;
  for (int i = 0; i < storage.size(); ++i) {
    totalper += storage[i]->getPerimeter();
  }
  return totalper;
}

CVector2D Ellipse::systemMassCenter(std::vector<IFunctionalSystem *> &storage) {
  CVector2D center{storage[0]->getPos().x, storage[0]->getPos().y};
  for (int i = 0; i < storage.size(); ++i) {
    center.x = (center.x + storage[i]->getPos().x) / 2;
    center.y = (center.y + storage[i]->getPos().y) / 2;
  }
  return center;
}

unsigned long Ellipse::allMemory(std::vector<IFunctionalSystem *> &storage) {
  unsigned long totalmem = 0;
  for (int i = 0; i < storage.size(); ++i) {
    totalmem += storage[i]->getSize();
  }
  return totalmem;
}

void Ellipse::sortObjects(std::vector<IFunctionalSystem *> &storage) {
  std::sort(storage.begin(), storage.end(), compareBySize);
}








