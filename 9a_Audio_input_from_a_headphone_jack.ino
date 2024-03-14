// Tutorial 9a. Audio input from a headphone jack

// Main parts: Adafruit Metro Mini, 3,5mm TRS headphone jack adapter,
// capacitor, resistors

// Variables that remain constant
const byte pinAudioIn = 0; // Analog input pin from L channel audio cable
const byte timeIntervalSampling = 30; // Sampling window width time in milliseconds
const int levelShift = 512; // Level shifting and re-fitting

// Variables that can change
int audioInRaw; // Raw audio input
int audioInRectified; // Rectified audio input

void setup()
{
  Serial.begin(115200); // Serial printing only necessary when observing values in the serial plotter

  //analogReference(EXTERNAL); // Use 3,3V AREF as reference voltage, bias = 1,65V
  //analogReference(INTERNAL); // Use 1,1V AREF as reference voltage, bias = 0,55V
}

void loop()
{
  unsigned long timeSamplingStart = millis(); // Timestamp
  
  uint16_t audioMin = 1023;
  uint16_t audioMax = 0;

  while (millis() - timeSamplingStart < timeIntervalSampling) // Sample for timeIntervalSampling milliseconds
  {
    audioInRaw = analogRead(pinAudioIn) + 0; // ADC correction factor +- # at 5V, +- # at 3.3V, +- # at 1.1V
    audioInRectified = abs(audioInRaw - levelShift); // Rectify and re-fit to 0

    audioMin = min(audioInRectified, audioMin); // Find the minimum input value
    audioMax = max(audioInRectified, audioMax); // Find the maximum input value
  }

  //Serial.print("audioInRaw:"); Serial.print(audioInRaw); Serial.print(" ");
  //Serial.print("audioInRectified:"); Serial.println(audioInRectified);

  //Serial.print("audioMin:"); Serial.print(audioMin); Serial.print(" ");
  //Serial.print("audioMax:"); Serial.println(audioMax);
}
