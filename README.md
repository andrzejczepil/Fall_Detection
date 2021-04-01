# Fall_Detection #Arduino #free-fall #Arduino Nano #Websockets
Fall detection system for elderly and ill people
It is a wearable-free fall detection system, dedicated to the elderly and those suffering from disorders related to imbalance and loss of proper body posture. The fall detection method is based on an algorithm that detects exceeding the threshold values of acceleration and verifying changes in the orientation of the subject's body. The detection of exceeding the acceleration threshold is carried out by monitoring the indications of the triaxial accelerometer, while the changes in body position are recorded by measuring the indications of the triaxial gyroscope. Communication with the device takes place via the WI-FI standard and the GSM standard. The WebSocket technology is used to constantly transmit live values recorded by the sensors, to the webpage for data presentation, thanks to which the device fits into the concept of the Internet of Things (IoT). 

This project shows application of websockets technology for live displaying online graph of a subjects movement. 

Note: keep in mind that only selected libraries work well with the code. some updated ones seem to fail during compilation or work improperly.


FILES:
.ino "fall detection" is a complete file including translated to base_64 webpage to be displayed. Included libraries are necessary for the project to work.
