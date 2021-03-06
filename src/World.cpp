#include "../include/World.hpp"
#include <iostream>
#include <cmath>
#include "assert.h"

namespace world {


bool World::can_move(const Point &from, const Point &to) const {
    if (to.x_ < 10 || to.x_ > (621 - 10) || to.y_ < 10 || to.y_ > (471 - 10)) {
        return false;
    }
    for (auto &polygon : obstaclesArray_) {
        if (segment_and_polygon_intersection(Segment{from, to}, polygon)) {
            return false;
        }
    }
    return true;
}

Point World::get_good_position() const {
    while (true) {
        Point cur{};
        bool flag = true;
        for (auto polygon : obstaclesArray_) {
            if (point_in_polygon(cur, polygon)) {
                flag = false;
            }
        }
        if (flag) {
            return cur;
        } 
    }
}

template<typename ANIMAL, typename FOOD>
void World::eating(ANIMAL& animal, std::vector<FOOD>& foodArray, int nutrition) {
    for (auto& food : foodArray) {
        if (dist(animal.position_, food.position_) < 1.5 * animal.velocity_ &&
            animal.nextAction_ == Action::EAT) {

            animal.hunger_ -= nutrition;
            animal.nextAction_ = Action::GO;
            swap(food, foodArray.back());
        }
    }
    if (animal.nextAction_ == Action::GO) { 
        foodArray.pop_back();
    }
    animal.nextAction_ = Action::GO;
}

template<typename ANIMAL>
void World::reproduce(std::vector<ANIMAL>& animalArray) {
    for (size_t i = 0; i < animalArray.size(); i++) {
        if (animalArray[i].nextAction_ == Action::REPRODUCE) {
            if (animalArray[i].sex_ == Sex::FEMALE) {
                if (lionsArray_.size() + zebrasArray_.size() < MAX_ANIMAL) {
                    ANIMAL new_animal;
                    new_animal.position_ = animalArray[i].position_;
                    animalArray.push_back(new_animal);
                }
            }
            animalArray[i].nextAction_ = Action::GO;
            animalArray[i].reprodCd_ = -1;
        }
    }
}

template <typename ANIMAL, typename FOOD>
void World::update_species(std::vector<ANIMAL>& animalArray, std::vector<FOOD>& foodArray, int nutrition) {
    int numbAlive = 0;
    for (auto& animal : animalArray) {
        if (animal.nextAction_ == Action::GO) {
            animal.make_move();
        }
        if (animal.nextAction_ == Action::EAT) {
            eating<ANIMAL, FOOD>(animal, foodArray, nutrition);
        }
        if (animal.nextAction_ != Action::REPRODUCE) {
           ++animal.age_;
           ++animal.reprodCd_;
           ++animal.hunger_;
        }
        
        if (animal.nextAction_ != Action::DIE) {
            animalArray[numbAlive] = animal;
            ++numbAlive;
        } 
    }
    animalArray.resize(numbAlive);
    reproduce<ANIMAL>(animalArray);
}

void World::update() {
    update_species<Lion, Zebra>(lionsArray_, zebrasArray_, ZEBRAS_NUTRITION);
    update_species<Zebra, Grass>(zebrasArray_, grassArray_, GRASS_NUTRITION);

    if (rand() % FREQUENCY == 0 && grassArray_.size() < MAX_GRASS) {
        Grass new_grass;
        new_grass.position_ = get_good_position();
        grassArray_.push_back(new_grass);
    }
}

} //namespace world
