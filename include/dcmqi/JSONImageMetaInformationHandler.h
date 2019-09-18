#ifndef DCMQI_JSONIMAGEMETAINFORMATIONHANDLER_H
#define DCMQI_JSONIMAGEMETAINFORMATIONHANDLER_H

// DCMQI includes
#include "dcmqi/JSONMetaInformationHandlerBase.h"

using namespace std;

namespace dcmqi {


	class JSONImageMetaInformationHandler : public JSONMetaInformationHandlerBase {

	public:
		JSONImageMetaInformationHandler() {}
		JSONImageMetaInformationHandler(string jsonInput);
		~JSONImageMetaInformationHandler();

		void setContentCreatorName(const string &creatorName);
		void setClinicalTrialCoordinatingCenterName(const string &coordinatingCenterName);
		void setClinicalTrialSeriesID(const string &seriesID);
		void setClinicalTrialTimePointID(const string &timePointID);

		string getContentCreatorName() const { return contentCreatorName; }
		string getClinicalTrialCoordinatingCenterName() const { return coordinatingCenterName; }
		string getClinicalTrialSeriesID() const { return clinicalTrialSeriesID; }
		string getClinicalTrialTimePointID() const { return clinicalTrialTimePointID; }

		string getJSONOutputAsString();

		// vector contains one item per input itkImageData label
		// each item is a map from labelID to segment attributes
		vector<map<unsigned, SegmentAttributes*> > segmentsAttributesMappingList;

		void read();
		bool write(string filename);

		SegmentAttributes* createAndGetNewSegment(unsigned labelID);

	protected:

		string contentCreatorName;
		string coordinatingCenterName;
		string clinicalTrialSeriesID;
		string clinicalTrialTimePointID;

		void readSegmentAttributes();

		Json::Value createAndGetSegmentAttributes();
	};

}


#endif //DCMQI_JSONIMAGEMETAINFORMATIONHANDLER_H
