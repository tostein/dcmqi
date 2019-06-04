// CLP includes
#include "itkimage2imageCLP.h"

// DCMQI includes
#undef HAVE_SSTREAM // Avoid redefinition warning
#include "dcmqi/ImageDicomConverter.h"
#include "dcmqi/internal/VersionConfigure.h"

typedef dcmqi::Helper helper;

int main(int argc, char *argv[])
{
	std::cout << dcmqi_INFO << std::endl;

	PARSE_ARGS;

	//if(helper::isUndefinedOrPathDoesNotExist(metaDataFileName, "Input metadata file")) {
	//  return EXIT_FAILURE;
	//}

	imageFile = "E:\\Daten\\decathlonKidneys\\testImages\\78_3023019448_20180301_CT\\scans\\19_Abdomen pv 3.0  B31f DE mint  F_0.5\\converted_files\\kidney78_0000.nii.gz";
	metaDataFileName = "C:\\Daten\\meta_image2dicom.json";
	outputImageFileName = "C:\\Daten\\outout.dcm";

	ShortReaderType::Pointer reader = ShortReaderType::New();
	reader->SetFileName(imageFile);
	reader->Update();
	ShortImageType::Pointer inputImage = reader->GetOutput();


	ifstream metainfoStream(metaDataFileName.c_str(), ios_base::binary);
	std::string metadata((std::istreambuf_iterator<char>(metainfoStream)),
		(std::istreambuf_iterator<char>()));

	Json::Value metaRoot;
	istringstream metainfoisstream(metadata);
	metainfoisstream >> metaRoot;

	if (metaRoot.isMember("Modality")) {
		std::cout << metaRoot["Modality"] << std::endl;
	}

	try {
		DcmDataset* result = dcmqi::ImageDICOMConverter::image2dcm(inputImage, metadata);

		if (result == NULL) {
			std::cerr << "ERROR: Conversion failed." << std::endl;
			return EXIT_FAILURE;
		}
		else {
			DcmFileFormat segdocFF(result);
			bool compress = false;
			if (compress) {
				CHECK_COND(segdocFF.saveFile(outputImageFileName.c_str(), EXS_DeflatedLittleEndianExplicit));
			}
			else {
				CHECK_COND(segdocFF.saveFile(outputImageFileName.c_str(), EXS_LittleEndianExplicit));
			}

			COUT << "Saved image as " << outputImageFileName << endl;
		}

		if (result != NULL)
			delete result;
		return EXIT_SUCCESS;
	}
	catch (int e) {
		std::cerr << "Fatal error encountered." << std::endl;
	}
}
