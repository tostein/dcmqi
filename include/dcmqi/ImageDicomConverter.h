#ifndef DCMQI_IMAGE_CONVERTER_H
#define DCMQI_IMAGE_CONVERTER_H

// ZLIB includes
#ifdef WITH_ZLIB
#include <zlib.h>           /* for zlibVersion() */
#endif


// DCMQI includes
#include "dcmqi/ConverterBase.h"
#include "dcmqi/JSONSegmentationMetaInformationHandler.h"

using namespace std;

namespace dcmqi {

  class ImageDICOMConverter : public ConverterBase {
	    public:
    static DcmDataset* image2dcm(ShortImageType::Pointer image, const string &metaData);
	
  };
}

#endif //DCMQI_IMAGE_CONVERTER_H