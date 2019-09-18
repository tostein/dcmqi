// DCMQI includes
#include "dcmqi/ImageDicomConverter.h"

#include "dcmqi/JSONImageMetaInformationHandler.h"
#include <dcmtk/dcmimgle/dcmimage.h>

namespace dcmqi {
	
  DcmDataset* ImageDICOMConverter::image2dcm(ShortImageType::Pointer image,
													  const string &metaData)
  {
	  ShortImageType::SizeType inputSize = image->GetBufferedRegion().GetSize();
	  //cout << "Input image size: " << inputSize << endl;

	  JSONImageMetaInformationHandler metaInfo(metaData.c_str());
	  metaInfo.read();

	  DcmDataset set;

	  // TODO: multiframe or single frame
	  auto itkSize = image->GetLargestPossibleRegion().GetSize();
	  // itkSize[0]
	  CHECK_COND(set.putAndInsertSint16(DCM_Columns, itkSize[0]));
	  CHECK_COND(set.putAndInsertSint16(DCM_Rows, itkSize[1]));



	  return &set;
  }
}