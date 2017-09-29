// Workaround for working with GCC 5.4. Do not remove
#define _GLIBCXX_USE_CXX11_ABI 0

#include "cscore.h"
#include "networktables/NetworkTable.h"
#include "tables/ITable.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include "llvm/StringRef.h"
#include "llvm/ArrayRef.h"
#include <thread>
#include <string>
#include <chrono>
#include <iostream>
#include "HighGoal.h"

#define SERVER_PORT 5805
#define CAMERA_NUM 2
#define RESOLUTION_X 320
#define RESOLUTION_Y 240
#define FPS 30

cs::UsbCamera SetUsbCamera(int cameraId, cs::MjpegServer& server);
cs::VideoCamera SetHttpCamera(llvm::StringRef cameraName, cs::MjpegServer& server);

int main() {
	NetworkTable::SetClientMode();
	NetworkTable::SetTeam(2556);
	NetworkTable::Initialize();

	std::shared_ptr<NetworkTable> Table = NetworkTable::GetTable("Vision");

	grip::HighGoal vision;

	cs::MjpegServer inputStream("MJPEG Server", SERVER_PORT);

	cs::UsbCamera *Cameras[CAMERA_NUM];
	for (int i = 0; i < CAMERA_NUM; i++){
		Cameras[i] = new cs::UsbCamera(("Camera " + std::to_string(i)).c_str(), i);

		Cameras[i]->SetResolution(RESOLUTION_X, RESOLUTION_Y);
		Cameras[i]->SetFPS(FPS);
	}

	cs::CvSink *Sinks[CAMERA_NUM];
	for (int i = 0; i < CAMERA_NUM; i++){
		Sinks[i] = new cs::CvSink(("Sink " + std::to_string(i)).c_str());

		Sinks[i]->SetSource(*Cameras[i]);
	}

	cs::CvSource Source("Camera Source", cs::VideoMode::PixelFormat::kMJPEG, RESOLUTION_X, RESOLUTION_Y, FPS);
	inputStream.SetSource(Source);

	/*cs::UsbCamera camera = SetUsbCamera(0, inputStream);

	camera.SetResolution(640,480);
	camera.SetFPS(20);

	cs::CvSink imageSink("CV Image Grabber");
	imageSink.SetSource(*Cameras[0]);

	cs::CvSource imageSource("CV Image Source", cs::VideoMode::PixelFormat::kMJPEG, 640, 480, 20);
	cs::MjpegServer cvStream("CV Image Stream", 1186);
	cvStream.SetSource(imageSource);*/

	cv::Mat inputImage;

	//double LastCamera = -1.0;

	while (true) {
		//if (Table->GetNumber("Camera", -1.0) < 0) continue;
		auto frameTime = Sinks[Table->GetNumber("Camera", 0.0) < CAMERA_NUM ? Table->GetNumber("Camera", 0.0) >= 0 ? (int)Table->GetNumber("Camera", 0.0) : 0 : CAMERA_NUM - 1]->GrabFrame(inputImage);
		if (frameTime == 0) continue;

		/*if (LastCamera != Table->GetNumber("Camera", -1.0)){
			std::cout << Table->GetNumber("Camera", -1.0) << std::endl;
				
			inputStream.SetSource(*Sinks[(int)Table->GetNumber("Camera", -1.0)]);
			LastCamera = Table->GetNumber("Camera", -1.0);
		}*/

		//vision.Process(inputImage);

		Source.PutFrame(Table->GetBoolean("Processed", false) ? *vision.GetRgbThresholdOutput() : inputImage);
		/*cvtColor(inputImage, hsv, cv::COLOR_BGR2HSV);

		imageSource.PutFrame(hsv);*/
	}
}

cs::UsbCamera SetUsbCamera(int cameraId, cs::MjpegServer& server){
	cs::UsbCamera camera("CoprocessorCamera", cameraId);
	server.SetSource(camera);
	return camera;
}

cs::VideoCamera SetHttpCamera(llvm::StringRef cameraName, cs::MjpegServer& server) {
	auto publishingTable = NetworkTable::GetTable("CameraPublisher");

	while (true) {
		if (publishingTable->GetSubTables().size() > 0) {
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	if (!publishingTable->ContainsSubTable(cameraName)) {
		return cs::VideoCamera();
	}
	auto cameraTable = publishingTable->GetSubTable(cameraName);
	auto urls = cameraTable->GetStringArray("streams", llvm::ArrayRef<std::string>());
	if (urls.size() == 0) {
		return cs::VideoCamera();
	}
	llvm::SmallVector<std::string, 8> fixedUrls;
	for (auto&& i : urls) {
		llvm::StringRef url{i};
		if (url.startswith("mjpg")) {
			fixedUrls.emplace_back(url.split(":").second);
		}
	}
	cs::HttpCamera camera("CoprocessorCamera", fixedUrls);
	server.SetSource(camera);
	return camera;
}
