/**
 * @file rr.h
 * Definition of rainbowRipple.
 *
 */
#ifndef _RAINBOWRIPPLE_H_
#define _RAINBOWRIPPLE_H_

#include <utility>
#include <vector>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "stack.h"
#include "queue.h"
using namespace std;
using namespace cs221util;

void rainbowRipple(PNG & image, pair<int,int> start, string sgc);

#endif
