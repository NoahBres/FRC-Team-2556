#include "cscore.h"
#include "networktables/NetworkTable.h"
#include "tables/ITable.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include "HighGoal.h"

namespace grip {

	HighGoal::HighGoal() {
		Table = NetworkTable::GetTable("Vision");
	}
	/**
	* Runs an iteration of the pipeline and updates outputs.
	*/
	void HighGoal::Process(cv::Mat& source0) {
		//Step RGB_Threshold0:
		//input
		cv::Mat rgbThresholdInput = source0;
		double rgbThresholdRed[] = {0.0, 93.99317406143348};
		double rgbThresholdGreen[] = {87.14028776978418, 255.0};
		double rgbThresholdBlue[] = {55.03597122302158, 233.2423208191126};
		rgbThreshold(rgbThresholdInput, rgbThresholdRed, rgbThresholdGreen, rgbThresholdBlue, this->rgbThresholdOutput);
		//Step Mask0:
		//input
		cv::Mat maskInput = source0;
		cv::Mat maskMask = rgbThresholdOutput;
		mask(maskInput, maskMask, this->maskOutput);
		//Step HSV_Threshold0:
		//input
		cv::Mat hsvThresholdInput = maskOutput;
		double hsvThresholdHue[] = {71.22302158273381, 80.17064846416379};
		double hsvThresholdSaturation[] = {107.77877697841726, 255.0};
		double hsvThresholdValue[] = {103.19244604316546, 255.0};
		hsvThreshold(hsvThresholdInput, hsvThresholdHue, hsvThresholdSaturation, hsvThresholdValue, this->hsvThresholdOutput);
		//Step Find_Contours0:
		//input
		cv::Mat findContoursInput = hsvThresholdOutput;
		bool findContoursExternalOnly = false;  // default Boolean
		findContours(findContoursInput, findContoursExternalOnly, this->findContoursOutput);
		//Step Filter_Contours0:
		//input
		std::vector<std::vector<cv::Point> > filterContoursContours = findContoursOutput;
		double filterContoursMinArea = 100.0;  // default Double
		double filterContoursMinPerimeter = 0.0;  // default Double
		double filterContoursMinWidth = 0.0;  // default Double
		double filterContoursMaxWidth = 1000.0;  // default Double
		double filterContoursMinHeight = 0.0;  // default Double
		double filterContoursMaxHeight = 1000.0;  // default Double
		double filterContoursSolidity[] = {0, 100};
		double filterContoursMaxVertices = 1000000.0;  // default Double
		double filterContoursMinVertices = 0.0;  // default Double
		double filterContoursMinRatio = 0.0;  // default Double
		double filterContoursMaxRatio = 1000.0;  // default Double
		filterContours(filterContoursContours, filterContoursMinArea, filterContoursMinPerimeter, filterContoursMinWidth, filterContoursMaxWidth, filterContoursMinHeight, filterContoursMaxHeight, filterContoursSolidity, filterContoursMaxVertices, filterContoursMinVertices, filterContoursMinRatio, filterContoursMaxRatio, this->filterContoursOutput);

		cv::Point center = findBoundingCenter(filterContoursOutput);

		Table->PutNumber("X", center.x);
		Table->PutNumber("Y", center.y);
	}

	/**
	* This method is a generated getter for the output of a RGB_Threshold.
	* @return Mat output from RGB_Threshold.
	*/
	cv::Mat* HighGoal::GetRgbThresholdOutput() {
		return &(this->rgbThresholdOutput);
	}
	/**
	* This method is a generated getter for the output of a Mask.
	* @return Mat output from Mask.
	*/
	cv::Mat* HighGoal::GetMaskOutput() {
		return &(this->maskOutput);
	}
	/**
	* This method is a generated getter for the output of a HSV_Threshold.
	* @return Mat output from HSV_Threshold.
	*/
	cv::Mat* HighGoal::GetHsvThresholdOutput() {
		return &(this->hsvThresholdOutput);
	}
	/**
	* This method is a generated getter for the output of a Find_Contours.
	* @return ContoursReport output from Find_Contours.
	*/
	std::vector<std::vector<cv::Point> >* HighGoal::GetFindContoursOutput() {
		return &(this->findContoursOutput);
	}
	/**
	* This method is a generated getter for the output of a Filter_Contours.
	* @return ContoursReport output from Filter_Contours.
	*/
	std::vector<std::vector<cv::Point> >* HighGoal::GetFilterContoursOutput() {
		return &(this->filterContoursOutput);
	}
	/**
	* Segment an image based on color ranges.
	*
	* @param input The image on which to perform the RGB threshold.
	* @param red The min and max red.
	* @param green The min and max green.
	* @param blue The min and max blue.
	* @param output The image in which to store the output.
	*/
	void HighGoal::rgbThreshold(cv::Mat &input, double red[], double green[], double blue[], cv::Mat &output) {
		cv::cvtColor(input, output, cv::COLOR_BGR2RGB);
		cv::inRange(output, cv::Scalar(red[0], green[0], blue[0]), cv::Scalar(red[1], green[1], blue[1]), output);
	}

	/**
	* Filter out an area of an image using a binary mask.
	*
	* @param input The image on which the mask filters.
	* @param mask The binary image that is used to filter.
	* @param output The image in which to store the output.
	*/
	void HighGoal::mask(cv::Mat &input, cv::Mat &mask, cv::Mat &output) {
		mask.convertTo(mask, CV_8UC1);
		cv::bitwise_xor(output, output, output);
		input.copyTo(output, mask);
	}

	/**
	* Segment an image based on hue, saturation, and value ranges.
	*
	* @param input The image on which to perform the HSL threshold.
	* @param hue The min and max hue.
	* @param sat The min and max saturation.
	* @param val The min and max value.
	* @param output The image in which to store the output.
	*/
	void HighGoal::hsvThreshold(cv::Mat &input, double hue[], double sat[], double val[], cv::Mat &out) {
		cv::cvtColor(input, out, cv::COLOR_BGR2HSV);
		cv::inRange(out, cv::Scalar(hue[0], sat[0], val[0]), cv::Scalar(hue[1], sat[1], val[1]), out);
	}

	/**
	* Finds contours in an image.
	*
	* @param input The image to find contours in.
	* @param externalOnly if only external contours are to be found.
	* @param contours vector of contours to put contours in.
	*/
	void HighGoal::findContours(cv::Mat &input, bool externalOnly, std::vector<std::vector<cv::Point> > &contours) {
		std::vector<cv::Vec4i> hierarchy;
		contours.clear();
		int mode = externalOnly ? cv::RETR_EXTERNAL : cv::RETR_LIST;
		int method = cv::CHAIN_APPROX_SIMPLE;
		cv::findContours(input, contours, hierarchy, mode, method);
	}


	/**
	* Filters through contours.
	* @param inputContours is the input vector of contours.
	* @param minArea is the minimum area of a contour that will be kept.
	* @param minPerimeter is the minimum perimeter of a contour that will be kept.
	* @param minWidth minimum width of a contour.
	* @param maxWidth maximum width.
	* @param minHeight minimum height.
	* @param maxHeight  maximimum height.
	* @param solidity the minimum and maximum solidity of a contour.
	* @param minVertexCount minimum vertex Count of the contours.
	* @param maxVertexCount maximum vertex Count.
	* @param minRatio minimum ratio of width to height.
	* @param maxRatio maximum ratio of width to height.
	* @param output vector of filtered contours.
	*/
	void HighGoal::filterContours(std::vector<std::vector<cv::Point> > &inputContours, double minArea, double minPerimeter, double minWidth, double maxWidth, double minHeight, double maxHeight, double solidity[], double maxVertexCount, double minVertexCount, double minRatio, double maxRatio, std::vector<std::vector<cv::Point> > &output) {
		std::vector<cv::Point> hull;
		output.clear();
		for (std::vector<cv::Point> contour : inputContours) {
			cv::Rect bb = boundingRect(contour);
			if (bb.width < minWidth || bb.width > maxWidth) continue;
			if (bb.height < minHeight || bb.height > maxHeight) continue;
			double area = cv::contourArea(contour);
			if (area < minArea) continue;
			if (arcLength(contour, true) < minPerimeter) continue;
			cv::convexHull(cv::Mat(contour, true), hull);
			double solid = 100 * area / cv::contourArea(hull);
			if (solid < solidity[0] || solid > solidity[1]) continue;
			if (contour.size() < minVertexCount || contour.size() > maxVertexCount)	continue;
			double ratio = (double)bb.width / (double)bb.height;
			if (ratio < minRatio || ratio > maxRatio) continue;
			output.push_back(contour);
		}
	}

	cv::Point HighGoal::findBoundingCenter(std::vector<std::vector<cv::Point> > &inputContours) {
		int minX = sizeof(int),
			minY = sizeof(int),
			maxX = sizeof(int),
			maxY = sizeof(int);

		for (std::vector<cv::Point> contour : inputContours) {
			cv::Rect bb = boundingRect(contour);
			if (bb.x < minX)
				minX = bb.x;
			if (bb.y < minY)
				minY = bb.y;
			if (bb.x + bb.width > maxX)
				maxX = bb.x + bb.width;
			if (bb.y + bb.height > maxY)
				maxY = bb.y + bb.height;
		}

		return cv::Point((minX + maxX) / 2, (minY + maxY) / 2);
	}

} // end grip namespace