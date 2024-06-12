#include "circle.h"

Circle::Circle() = default;
Circle::Circle(const Circle &other) {
  this->x = other.x;
  this->y = other.y;
  this->radius = other.radius;
}
void Circle::setMass(int m) {
  this->mass_ = m;
}

double Circle::square() {
  return M_PI * radius * radius;
}

double Circle::perimeter() {
  return 2 * M_PI * radius;
}

void Circle::vectorize(const CVector2D &vector_2_d) {
  this->x += vector_2_d.x;
  this->y += vector_2_d.y;
}

double Circle::mass() {
  return this->mass_;
}

CVector2D Circle::position() {
  CVector2D pos(this->x, this->y);
  return pos;
}

bool Circle::operator==(const IPhysObject &ob) const {
  return (ob.mass_ == this->mass_);
}

bool Circle::operator<(const IPhysObject &ob) const {
  return (this->mass_ < ob.mass_);
}

void Circle::draw() {
  std::cout << "Coordinates (x;y) of a Circle: (" << this->x << ";" << this->y << ")\n";
  std::cout << "Radius of a Circle: " << this->radius << "\n";
  std::cout << "Mass of a Circle: " << this->mass_ << "\n";
}

void Circle::initFromDialog() {
  std::cout << "Lets initialize Circle\n";
  std::cout << "Enter coordinates for position:\n";
  std::cin >> this->x >> this->y;
  std::cout << "Enter radius:\n";
  std::cin >> this->radius;
  std::cout << "Enter mass:\n";
  std::cin >> this->mass_;
}

const char *Circle::classname() {
  return "This is a Circle class";
}

unsigned int Circle::size() {
  return sizeof(*this);
}

void Circle::printInfo() {
  this->draw();
}

double Circle::getSquare() {
  return this->square();
}

double Circle::getPerimeter() {
  return this->perimeter();
}

CVector2D Circle::getPos() {
  return this->position();
}

unsigned int Circle::getSize() {
  return this->size();
}

double Circle::getMass() {
  return this->mass();
}

void Circle::storeObject(std::vector<IFunctionalSystem *> &storage) {
  storage.push_back(this);
}

void Circle::addObject(std::vector<IFunctionalSystem *> &storage) {
  Circle *c_init = new Circle();
  c_init->initFromDialog();
  storage.push_back(c_init);
}

void Circle::printAll(std::vector<IFunctionalSystem *> &storage) {
  for (int i = 0; i < storage.size(); ++i) {
    storage[i]->printInfo();
  }
}

double Circle::totalSquare(std::vector<IFunctionalSystem *> &storage) {
  double totalsq = 0;
  for (int i = 0; i < storage.size(); ++i) {
    totalsq += storage[i]->getSquare();
  }
  return totalsq;
}

double Circle::totalPerimeter(std::vector<IFunctionalSystem *> &storage) {
  double totalper = 0;
  for (int i = 0; i < storage.size(); ++i) {
    totalper += storage[i]->getPerimeter();
  }
  return totalper;
}

CVector2D Circle::systemMassCenter(std::vector<IFunctionalSystem *> &storage) {
  CVector2D center{storage[0]->getPos().x, storage[0]->getPos().y};
  for (int i = 0; i < storage.size(); ++i) {
    center.x = (center.x + storage[i]->getPos().x) / 2;
    center.y = (center.y + storage[i]->getPos().y) / 2;
  }
  return center;
}

unsigned long Circle::allMemory(std::vector<IFunctionalSystem *> &storage) {
  unsigned long totalmem = 0;
  for (int i = 0; i < storage.size(); ++i) {
    totalmem += storage[i]->getSize();
  }
  return totalmem;
}

void Circle::sortObjects(std::vector<IFunctionalSystem *> &storage) {
  std::sort(storage.begin(), storage.end(), compareBySize);
}