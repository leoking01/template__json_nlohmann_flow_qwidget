#ifndef AlgorithmBaseNaitive_H
#define AlgorithmBaseNaitive_H

#include <string>

#include <iostream>
#include <iomanip>
#include <fstream>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <memory>
#include <array>

#include <iterator>
#include <vector>
#include <map>
#include <random>
#include <unordered_map>

#include <opencv2/opencv.hpp>

#include "SKDVISION_global.h"

#ifdef   USING_HALCON_DEFINED_LK
#include "HalconCpp.h"
using namespace HalconCpp;
#endif


class  SKDVISION_EXPORT AlgorithmBaseNaitive
{
public:
    std::string class_name ;
};

#endif // AlgorithmBaseNaitive_H
