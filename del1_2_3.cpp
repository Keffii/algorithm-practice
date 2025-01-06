#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

enum class SensorType
{
	Altitude,
	SpeedInKmh,
	FuelConsumption
};

class SensorData
{
	float value;
	SensorType sensorType;
	time_t time;
public:
	const SensorType GetSensorType() const { return sensorType; }
	float GetValue() const { return value; }
	void SetValue(float v) { value = v; }
	const time_t GetTime() const { return time; }
	SensorData(SensorType sensorType, float value, time_t time)
	{
		this->value = value;
		this->sensorType = sensorType;
		this->time = time;
	}
};

void FillData(vector<SensorData> &v);
time_t CreateTime(int year, int month, int day);

bool CheckMaxSpeedReached(const vector<SensorData>& sensorData) {
	return std::any_of(sensorData.begin(), sensorData.end(), 
		[](const SensorData& sensor) {
			return sensor.GetSensorType() == SensorType::SpeedInKmh && 
				   sensor.GetValue() > 99.9f;
		});
}

void runAllParts()
{
	vector<SensorData> sensorData;
	FillData(sensorData);

	int altitudeCount = std::count_if(sensorData.begin(), sensorData.end(), [](const SensorData& sensor) {
		time_t startTime = CreateTime(2012, 1, 2);
		time_t endTime = CreateTime(2012, 1, 3);
		return sensor.GetSensorType() == SensorType::Altitude &&
			   sensor.GetTime() >= startTime && sensor.GetTime() < endTime;
	});
	cout << "Amount of altitude readings on 2012-01-02: " << altitudeCount << endl;

    time_t latestTime = 0;
    SensorData* latestFuelSensor = nullptr;

	std::sort(sensorData.begin(), sensorData.end(), 
		[](const SensorData& a, const SensorData& b) {
			return a.GetTime() > b.GetTime();
		});

	auto it = std::find_if(sensorData.begin(), sensorData.end(),
		[](const SensorData& sensor) {
			return sensor.GetSensorType() == SensorType::FuelConsumption;
		});

	if (it != sensorData.end()) {
		float currentValue = it->GetValue();
		float newValue = currentValue * 1.75f;
		it->SetValue(newValue);
		cout << "Previous fuel consumption: " << currentValue << endl;
		cout << "Updated fuel consumption: " << newValue << endl;
	}
	
	if(CheckMaxSpeedReached(sensorData)){
		cout << "Maxhastighet uppnådd" << endl;
	}else{
		cout << "Ingen maxhastighet uppnådd" << endl;
	}
}

void FillData(vector<SensorData>& v)
{
	srand(time(NULL));

	time_t tid = CreateTime(2012, 1, 1);
	for (int i = 0; i < 100000; i++)
	{
		SensorType type = static_cast<SensorType>(rand() % 3);
		float value = 0.0f;
		if (type == SensorType::Altitude)
			value = rand() % 1000;
		else if (type == SensorType::FuelConsumption)
			value = rand() * 3.0f;
		else if (type == SensorType::SpeedInKmh)
			value = rand() % 110;
		else
		{
			value = 99;
		}
		v.push_back(SensorData(type, value, tid));
		tid = tid + rand() % 10 + 1;
	}
}

time_t CreateTime(int year, int month, int day)
{
	struct tm tid = { 0 };
	tid.tm_year = year - 1900;
	tid.tm_mon = month - 1;
	tid.tm_mday = day;
	// tid.tm_hour = hour;
	// tid.tm_min = minute;
	// tid.tm_sec = second;
	return mktime(&tid);
}