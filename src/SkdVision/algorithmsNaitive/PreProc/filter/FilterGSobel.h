#ifndef FilterGSobel_H
#define FilterGSobel_H

#include "algorithmbaseNaitive.h"   // AlgorithmBaseNaitive

/*
 *   // Find text in an image.
  HTextResult FindText(const HTextModel& TextModel) const;

  // Classify a byte image using a look-up table.
  HRegion ClassifyImageClassLut(const HClassLUT& ClassLUTHandle) const;

  // Classify an image with a k-Nearest-Neighbor classifier.
  HRegion ClassifyImageClassKnn(HImage* DistanceImage, const HClassKnn& KNNHandle, double RejectionThreshold) const;

  // Add training samples from an image to the training data of a k-Nearest-Neighbor classifier.
  void AddSamplesImageClassKnn(const HRegion& ClassRegions, const HClassKnn& KNNHandle) const;

  // Classify an image with a Gaussian Mixture Model.
  HRegion ClassifyImageClassGmm(const HClassGmm& GMMHandle, double RejectionThreshold) const;

  // Add training samples from an image to the training data of a Gaussian Mixture Model.
  void AddSamplesImageClassGmm(const HRegion& ClassRegions, const HClassGmm& GMMHandle, double Randomize) const;

  // Classify an image with a support vector machine.
  HRegion ClassifyImageClassSvm(const HClassSvm& SVMHandle) const;

  **/

class FilterGSobel : public AlgorithmBaseNaitive
{
public:

};

#endif // FilterGSobel_H
