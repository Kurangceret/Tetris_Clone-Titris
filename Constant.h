#ifndef CONSTANT_H
#define CONSTANT_H
#include <SFML/Graphics.hpp>

//tetris gameplay area
//it will automatically add six thanks to the thickness to be set later
const float boundingX = 322.f;
const float boundingY = 640.f;
const float thickness = 1.f;

extern sf::FloatRect globalRect;

//Window sizes
const float winWidth = 480.f;
const float winHeight = 650.f;

#endif