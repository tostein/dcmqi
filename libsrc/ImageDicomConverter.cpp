// DCMQI includes
#include "dcmqi/ImageDicomConverter.h"

#include <dcmtk/dcmimgle/dcmimage.h>

namespace dcmqi {
	
  DcmDataset* ImageDICOMConverter::image2dcm(ShortImageType::Pointer image,
													  const string &metaData)
  {

	  DcmDataset set;
	  //CHECK_COND(set.putAndInsertString(DCM_, bodyPartAssigned.c_str()));
	  // TODO: multiframe or single frame
	  auto itkSize = image->GetLargestPossibleRegion().GetSize();
	  // itkSize[0]
	  CHECK_COND(set.putAndInsertSint16(DCM_Columns, itkSize[0]));
	  CHECK_COND(set.putAndInsertSint16(DCM_Rows, itkSize[1]));

	  return &set;
  }
}