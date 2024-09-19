#include <iostream>
#include <vector>

using namespace std;

class Facade {
public:
    virtual double getArea() = 0;
    virtual double getPrice() = 0;
    virtual void showInfo() = 0;
    virtual ~Facade() {}
};

// для плівкових фасадів
class FilmSolidFacade : public Facade {
    double width, height, pricePerSqM;
public:
    FilmSolidFacade(double w, double h) : width(w), height(h), pricePerSqM(100) {}

    double getArea() override {
        return width * height;
    }

    double getPrice() override {
        return getArea() * pricePerSqM;
    }

    void showInfo() override {
        cout << "Film solid facade, size: " << width << "x" << height
            << ", area: " << getArea() << " m^2, price: " << getPrice() << " USD\n";
    }
};

class FilmWindowFacade : public Facade {
    double width, height, pricePerSqM;
public:
    FilmWindowFacade(double w, double h) : width(w), height(h), pricePerSqM(120) {}

    double getArea() override {
        return width * height;
    }

    double getPrice() override {
        return getArea() * pricePerSqM;
    }

    void showInfo() override {
        cout << "Film window facade, size: " << width << "x" << height
            << ", area: " << getArea() << " m^2, price: " << getPrice() << " USD\n";
    }
};

class PaintedSolidFacade : public Facade {
    double width, height, pricePerSqM;
public:
    PaintedSolidFacade(double w, double h) : width(w), height(h), pricePerSqM(150) {}

    double getArea() override {
        return width * height;
    }

    double getPrice() override {
        return getArea() * pricePerSqM;
    }

    void showInfo() override {
        cout << "Painted solid facade, size: " << width << "x" << height
            << ", area: " << getArea() << " m^2, price: " << getPrice() << " USD\n";
    }
};

class PaintedWindowFacade : public Facade {
    double width, height, pricePerSqM;
public:
    PaintedWindowFacade(double w, double h) : width(w), height(h), pricePerSqM(170) {}

    double getArea() override {
        return width * height;
    }

    double getPrice() override {
        return getArea() * pricePerSqM;
    }

    void showInfo() override {
        cout << "Painted window facade, size: " << width << "x" << height
            << ", area: " << getArea() << " m^2, price: " << getPrice() << " USD\n";
    }
};

// для пластикових фасадів
class PlasticSolidFacade : public Facade {
    double width, height, pricePerSqM;
public:
    PlasticSolidFacade(double w, double h) : width(w), height(h), pricePerSqM(200) {}

    double getArea() override {
        return width * height;
    }

    double getPrice() override {
        return getArea() * pricePerSqM;
    }

    void showInfo() override {
        cout << "Plastic solid facade, size: " << width << "x" << height
            << ", area: " << getArea() << " m^2, price: " << getPrice() << " USD\n";
    }
};

class PlasticWindowFacade : public Facade {
    double width, height, pricePerSqM;
public:
    PlasticWindowFacade(double w, double h) : width(w), height(h), pricePerSqM(220) {}

    double getArea() override {
        return width * height;
    }

    double getPrice() override {
        return getArea() * pricePerSqM;
    }

    void showInfo() override {
        cout << "Plastic window facade, size: " << width << "x" << height
            << ", area: " << getArea() << " m^2, price: " << getPrice() << " USD\n";
    }
};

// для створення фасадів
class FacadeFactory {
public:
    virtual Facade* createSolidFacade(double width, double height) = 0;
    virtual Facade* createWindowFacade(double width, double height) = 0;
    virtual ~FacadeFactory() {}
};

//  для кожного типу фасаду
class FilmFacadeFactory : public FacadeFactory {
public:
    Facade* createSolidFacade(double width, double height) override {
        return new FilmSolidFacade(width, height);
    }

    Facade* createWindowFacade(double width, double height) override {
        return new FilmWindowFacade(width, height);
    }
};

class PaintedFacadeFactory : public FacadeFactory {
public:
    Facade* createSolidFacade(double width, double height) override {
        return new PaintedSolidFacade(width, height);
    }

    Facade* createWindowFacade(double width, double height) override {
        return new PaintedWindowFacade(width, height);
    }
};

class PlasticFacadeFactory : public FacadeFactory {
public:
    Facade* createSolidFacade(double width, double height) override {
        return new PlasticSolidFacade(width, height);
    }

    Facade* createWindowFacade(double width, double height) override {
        return new PlasticWindowFacade(width, height);
    }
};

// Клас замовлення
class Order {
    vector<Facade*> facades;
    FacadeFactory* factory;
public:
    Order(FacadeFactory* f) : factory(f) {}

    void addSolidFacade(double width, double height) {
        facades.push_back(factory->createSolidFacade(width, height));
    }

    void addWindowFacade(double width, double height) {
        facades.push_back(factory->createWindowFacade(width, height));
    }

    double calculateTotalPrice() {
        double total = 0;
        for (auto& facade : facades) {
            total += facade->getPrice();
        }
        return total;
    }

    void showOrderDetails() {
        for (auto& facade : facades) {
            facade->showInfo();
        }
        cout << "Total price: " << calculateTotalPrice() << " USD\n";
    }

    ~Order() {
        for (auto& facade : facades) {
            delete facade;
        }
    }
};

int main() {
    
    FacadeFactory* factory = new FilmFacadeFactory();

    Order order(factory);

    // Додаємо фасади до замовлення
    order.addSolidFacade(2.0, 1.5);
    order.addWindowFacade(1.2, 1.8);

    order.showOrderDetails();

    delete factory;

    return 0;
}
