#include "../include/circle.h"
#include "../include/ellipse.h"

int main(int argc, char *argv[]) {
  if (argc > 1 && strcmp(argv[1], "autotest") == 0 || argc > 1 && strcmp(argv[1], "Autotest") == 0) {
    std::cout << "Here's an example of working Circle and Ellipse classes:\n\n";
    Circle c1(1, 2, 5);
    Circle c2(3.5, 7.2, 8);
    Ellipse e1(1, 3, 7.8, 6.9);
    Ellipse e2(4, 5, 3.6, 7.1);

    c1.setMass(10);
    c2.setMass(11);
    e1.set_mass(5);
    e2.set_mass(5);

    std::cout << "Set masses for figures:\n";
    std::cout << "c1: " << c1.mass();
    std::cout << "c2: " << c2.mass();
    std::cout << "e1: " << e1.mass();
    std::cout << "e2: " << e2.mass() << "\n\n";

    if (c1 < c2) {
      std::cout << "Overloaded operators work!\n\n";
    }
    std::cout << "Perimeters of figures:\n";
    std::cout << "Circle c1: " << c1.perimeter() << "\n";
    std::cout << "Circle c2: " << c2.perimeter() << "\n";
    std::cout << "Ellipse e1: " << e1.perimeter() << "\n";
    std::cout << "Ellipse e2: " << e2.perimeter() << "\n\n";

    std::cout << "Squares of figures:\n";
    std::cout << "Circle c1: " << c1.square() << "\n";
    std::cout << "Circle c2: " << c2.square() << "\n";
    std::cout << "Ellipse e1: " << e1.square() << "\n";
    std::cout << "Ellipse e2: " << e2.square() << "\n\n";

    std::cout << "Coordinates of c1 and e1 before vectorize:\n";
    std::cout << "c1 (x,y): " << "(" << c1.position().x << "," << c1.position().y << ")\n";
    std::cout << "e1 (x,y): " << "(" << e1.position().x << "," << e1.position().y << ")\n";
    CVector2D vec(52, 239);
    c1.vectorize(vec);
    e1.vectorize(vec);
    std::cout << "Coordinates of c1 and e1 after vectorize:\n";
    std::cout << "c1 (x,y): " << "(" << c1.position().x << "," << c1.position().y << ")\n";
    std::cout << "e1 (x,y): " << "(" << e1.position().x << "," << e1.position().y << ")\n\n";

    std::cout << "Classes names:\n";
    std::cout << c1.classname() << "\n";
    std::cout << e1.classname() << "\n\n";

    std::cout << "Circle c1 info:\n";
    c1.draw();
    std::cout << "Size of class object (in bytes): " << c1.size() << "\n";

//    Ellipse el_init{};
//    el_init.initFromDialog();
//    std::cout << "Ellipse el_init info:\n";
//    el_init.draw();

//    std::vector<IFunctionalSystem *> storage;
//    e1.addObject(storage);
//    c1.addObject(storage);
//    e2.addObject(storage);
//    c2.addObject(storage);
//
//    Circle c_init{};
//    c_init.addObject(storage);
//    std::cout << "Total square of all figures is: " << c_init.totalSquare(storage) << "\n";
//    std::cout << "Total perimeter of all figures is: " << c_init.totalPerimeter(storage) << "\n";
//    std::cout << "Total mass center (x,y) of all figures is: (" << c_init.systemMassCenter(storage).x << ","
//              << c_init.systemMassCenter(storage).y << ")\n";
//    std::cout << "Total store-using memory (in bytes) of all figures is: " << c_init.allMemory(storage) << "\n";
//    std::cout << "Non-sorted storage of objects: ";
//    c_init.printAll(storage);
//    std::cout << "\nSorted storage of objects by their mass: ";
//    c_init.sortObjects(storage);
//    c_init.printAll(storage);
  } else {
    std::cout << "Here's an example of working Circle and Ellipse classes:\n\n";
    Circle c1(1, 2, 5);
    Circle c2(3.5, 7.2, 8);
    Ellipse e1(1, 3, 7.8, 6.9);
    Ellipse e2(4, 5, 3.6, 7.1);

    c1.setMass(10);
    c2.setMass(11);
    e1.set_mass(5);
    e2.set_mass(5);

    std::cout << "Set masses for figures:\n";
    std::cout << "c1: " << c1.mass();
    std::cout << "c2: " << c2.mass();
    std::cout << "e1: " << e1.mass();
    std::cout << "e2: " << e2.mass() << "\n\n";

    if (c1 < c2) {
      std::cout << "Overloaded operators work!\n\n";
    }
    std::cout << "Perimeters of figures:\n";
    std::cout << "Circle c1: " << c1.perimeter() << "\n";
    std::cout << "Circle c2: " << c2.perimeter() << "\n";
    std::cout << "Ellipse e1: " << e1.perimeter() << "\n";
    std::cout << "Ellipse e2: " << e2.perimeter() << "\n\n";

    std::cout << "Squares of figures:\n";
    std::cout << "Circle c1: " << c1.square() << "\n";
    std::cout << "Circle c2: " << c2.square() << "\n";
    std::cout << "Ellipse e1: " << e1.square() << "\n";
    std::cout << "Ellipse e2: " << e2.square() << "\n\n";

    std::cout << "Coordinates of c1 and e1 before vectorize:\n";
    std::cout << "c1 (x,y): " << "(" << c1.position().x << "," << c1.position().y << ")\n";
    std::cout << "e1 (x,y): " << "(" << e1.position().x << "," << e1.position().y << ")\n";
    CVector2D vec(52, 239);
    c1.vectorize(vec);
    e1.vectorize(vec);
    std::cout << "Coordinates of c1 and e1 after vectorize:\n";
    std::cout << "c1 (x,y): " << "(" << c1.position().x << "," << c1.position().y << ")\n";
    std::cout << "e1 (x,y): " << "(" << e1.position().x << "," << e1.position().y << ")\n\n";

    std::cout << "Classes names:\n";
    std::cout << c1.classname() << "\n";
    std::cout << e1.classname() << "\n\n";

    std::cout << "Circle c1 info:\n";
    c1.draw();
    std::cout << "Size of class object (in bytes): " << c1.size() << "\n";

    Ellipse el_init{};
    el_init.initFromDialog();
    std::cout << "Ellipse el_init info:\n";
    el_init.draw();

    std::vector<IFunctionalSystem *> storage;
    e1.addObject(storage);
    c1.addObject(storage);
    e2.addObject(storage);
    c2.addObject(storage);

    Circle c_init{};
    c_init.addObject(storage);
    std::cout << "Total square of all figures is: " << c_init.totalSquare(storage) << "\n";
    std::cout << "Total perimeter of all figures is: " << c_init.totalPerimeter(storage) << "\n";
    std::cout << "Total mass center (x,y) of all figures is: (" << c_init.systemMassCenter(storage).x << ","
              << c_init.systemMassCenter(storage).y << ")\n";
    std::cout << "Total store-using memory (in bytes) of all figures is: " << c_init.allMemory(storage) << "\n";
    std::cout << "Non-sorted storage of objects: ";
    c_init.printAll(storage);
    std::cout << "\nSorted storage of objects by their mass: ";
    c_init.sortObjects(storage);
    c_init.printAll(storage);
  }
  return 0;
}