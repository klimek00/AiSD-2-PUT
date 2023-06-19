#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>

template<class T> class objectDB {
	public:
		objectDB() = default;
		~objectDB() = default;
		void addObject(T);
		void remObject(int);
		void displayObject();

	std::vector<T> objectList;

	private:
		int counter = 0;

};

template<class T> void objectDB<T>::addObject(T item) {
	if (objectList.size() < 6) {
		counter++;
		objectList.push_back(item);
	}
}

template<class T> void objectDB<T>::remObject(int index) {
	if (index <= counter) {
		//swap in order to rem last item
		std::iter_swap(objectList.begin() + index, objectList.end() - 1);
		// std::swap(objectList[index - 1], objectList[counter - 1]);
		objectList.pop_back();
	}
}

template<class T> void objectDB<T>::displayObject() {
  std::sort(objectList.begin(), objectList.end());

	for (auto obj : this->objectList) {
		obj.info();
		std::cout << " ";
	}

}

class Animal {
	public:
		Animal() = default;
		~Animal() = default;
		Animal(std::string, float, int, std::string);
		void info() {
			std::cout << this->name << " " << this->weight << " " << this->birth_year << " " << this->id_label;
		}
    friend bool operator<(Animal&, Animal&);

	private:
		std::string name;
		float weight;
		int birth_year;
		std::string id_label;

};

Animal::Animal(std::string name, float weight, int birth_year, std::string id_label) {
	this->name = name;
	this->weight = weight;
	this->birth_year = birth_year;
	this->id_label = id_label;
}

bool operator<(Animal& objA, Animal& objB) {
  if (objA.birth_year > objB.birth_year) {
    return true;
  } else if (objA.birth_year == objB.birth_year) {
    if (objA.weight < objB.weight) {
      return true;
    }
  }

  return false;
}


class Building {
	public:
		Building() = default;
		~Building() = default;
		Building(std::string, float, float, float);
		void info() {
			std::cout << this->name << " " << this->pos_x << " " << this->pos_y << " " << this->height;
		}
    friend bool operator<(Building& objA, Building& objB);

	private:
		std::string name;
		float pos_x;
		float pos_y;
		float height;

};

Building::Building(std::string name, float pos_x, float pos_y, float height) {
	this->name = name;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->height = height;
}

bool operator<(Building& objA, Building& objB) {
  int sumA = objA.pos_x + objA.pos_y;
  int sumB = objB.pos_x + objB.pos_y;

  return (sumA < sumB ? true : false);
}

int main() {
	objectDB<class Animal> animalsDB;
	objectDB<class Building> buildingsDB;

	//for animals
	for (int i = 0; i < 4; i++) {
		int birth_year;
		float weight;
		std::string temp, name_a, id_label;

		std::cin >> name_a;
		
		while (true) {
			std::cin >> temp;
			try {
				weight = stof(temp);
				if (weight > 0) { break; }
			}
			catch (std::invalid_argument& e) {}
		}
		while (true) {
			std::cin >> temp;
			try {
				birth_year = stoi(temp);
				if (birth_year > 0) { break; }
			}
			catch (std::invalid_argument& e) {}
		}
		
		std::cin >> id_label;
		Animal pinguin(name_a, weight, birth_year, id_label);
		animalsDB.addObject(pinguin);
	}

	//for buildings
	for (int i = 0; i < 4; i++) {
		float height, pos_x, pos_y;
		std::string temp, name_b;

		std::cin >> name_b;
		
		while (true) {
			std::cin >> temp;
			try {
				pos_x = stof(temp);
				if (pos_x >= -180.0 && pos_x <= 180.0) { break; }
			}
			catch (std::invalid_argument& e) {}
		}
		while (true) {
			std::cin >> temp;
			try {
				pos_y = stof(temp);
				if (pos_y >= -90.0 && pos_y <= 90.0) { break; }
			}
			catch (std::invalid_argument& e) {}
		}		
		while (true) {
			std::cin >> temp;
			try {
				height = stof(temp);
				if (height > 0) { break; }
			}
			catch (std::invalid_argument& e) {}
		}

		Building ataner(name_b, pos_x, pos_y, height);
		buildingsDB.addObject(ataner);
	}

	int rem_animal;
	std::cin >> rem_animal;
	animalsDB.remObject(rem_animal);

  animalsDB.displayObject();
  buildingsDB.displayObject();

	return 0;
}