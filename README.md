# IOT-enabled Auto Rickshaw Solution for Public Transportation

![cover](/resources/cover.png)

## Overview

In multiple Indian cities, traffic is one of the biggest issues — in 2022, New Delhi ranked 11 in the World Congestion Index. One of the most infrastructarally inexpensive solutions is to optimize semi-public forms of transportation like auto-rickshaws in order to maximise vehicular efficiency and safety, while minimizing factors like pollution and congestion by optimizing routes.

In this project, we aim to equip auto-rickshaws with multiple Internet-of-Things enabled sensors and actuators in order to streamline and centralise auto-rickshaw transportation.

This project was built as a part of the course **Internet of Things [EEE F411]** at BITS Pilani, Pilani — taught by [Professor Vinay Chamola](https://scholar.google.com/citations?user=pL5TogoAAAAJ&hl=en). The team consisted of:

- **Parth Sharma** — f20201229@pilani.bits-pilani.ac.in (software)
- **Rishit Tyagi** — f20200355@pilani.bits-pilani.ac.in (machine learning)
- **Avi Tewari** — f20201220@pilani.bits-pilani.ac.in (hardware)
- **Arjun Sinha** — f20200353@pilani.bits-pilani.ac.in (hardware)

[Project Demo (YouTube)](https://www.youtube.com/watch?v=CwdnEVwMsB4)

## Functionality

While our final project only implements certain parts of the proposed functionality due to monetary and time limitations, the proposed solution includes the following features.

![functionality](/resources/features.png)

### Safety and Security

- Since GPS location is tracked and sent to a centralised entity (Indian Government) and control rooms, security and emergency response time can be streamlined to ensure that rider is always on the grid
- Espescially in cities like New Delhi, where violent crime levels are high, female rider security is increased

### ML Powered Heatmap Predictions

- Currently, auto drivers efficiency is not maximised as they are localised to pockets of regions like auto stands
- By using a neural network to predict the average demand for auto rickshaws at any given point in the day, auto drivers can be routed to high demand areas in order to prevent surplus in low-need areas and shortages in high-demand areas
- Ensures faster resolution time for riders as well

### Accelerometer

- By connecting a sensor to monitor the angular rotation of the auto’s wheel axels, we can calculate the speed that the auto rickshaw is going at
- In areas with explicit speed limits, drivers can be alerted (warnings) that they are exceeding the speed limit or even limit the angular rotation to the defined speed constraints for the region to ensure safe driving practices
- We can also model artficial speed limits for areas without explicit limits based on analysing data of surrounding structures (schools, hospitals) or even modelling areas with high frequencies of crashes

### Traffic Violations

- Since GPS tracking is enabled, it allows for a standardised way of tracking traffic rule violations like incorrect way driving and traffic light violations
- Also, can attach a RFID sensor on the top of the auto with the key information about the autos, that directional beams installed on traffic lights can be used to log any traffic violations

### Crash Detections

- By connecting a sensor to monitor the impact on different parts of the auto rickshaw body, we can calculate the average collision impact and act accordingly
- In high impact collisions where driver is unresponsive, can instantly deploy ambulance services to the GPS tracked location with information regarding the collision impact
- Drivers also have a “Report Accident” button that they witnessed on the app — confluence of such reports = deploying ambulance

### Digital Meters

- Accurately calculating the estimated cost of the ride in a manner equitable for both the rider and the driver
- Lack of commission for enabling framework means more cut for the drivers and easier adoption
- Standardization of cost rates means more efficient utlisation of the available auto rickshaw resources

### CNG Ecosystem

- Sensor monitoring the amount of CNG currently available and calculating whether it is enough CNG to succesfully complete upcoming rides
- Sensors at CNG stations that helps model a map of all available CNG stations as well as the optimum destination based on distance and predicted wait at ETA in order to allow less queing at certain CNG stations

### Suspension

- Connecting sensors to suspension of the auto
- Useful data in generating the road-level topology of the city
- Useful data in allocating resources for fixing potholes and road damage — by computing maximum suspension wear and tear and also the traffic density around the point in question

### Vehicular Exhaust

- Accurately calculating the total vehicular exhaust and alerting a driver for a fix whenever exhaust crosses a threshold
- Changes vehicular pollution tracking from a retrospective action to an ongoing and exact distribution tracking of total vehicular exhaust at any time

## Architecture

![arch](/resources/arch.png)

## Frontend

The client application for the IoT E-Auto Rickshaw is built using **React.js.**

### Local Installation

1. Navigate to the client repository.

```bash
  cd e-autorickshaw-iot-stack/erickshaw-client
```

2. Install Node dependencies using **NPM**.

```bash
  npm install
```

3. Run the Development Server.

```bash
  npm run dev
```

### Deployment

**Live Client Application**

- Client deploys live at [erickshaw-iot-stack](https://e-autorickshaw-iot-stack.vercel.app/).

**Setup and Settings**

- The client app deploys using **[Vercel](https://vercel.com).**

## Backend & DevOps (Data Management, AWS IoT Core, MQTT and API)

### Setting up AWS IOT Core

![AWS Core Image](/resources/aws-core.png)

1. Created an IOT Thing on AWS Core `(ap-south-1)`
2. Generated root access policies `iot.*` and `*`
3. Applied policies to device certificate
4. Converted device certificates `(.key)` files to NodeMCU ESP8266 compatible `(.der)` files using **OpenSSL**.

```bash
> openssl x509 -in xxxxxxxxxx-certificate.pem.crt -out cert.der -outform DER
> openssl rsa -in xxxxxxxxxx-private.pem.key -out private.der -outform DER
> openssl x509 -in AmazonRootCA1.pem -out ca.der -outform DER
```

5. Installed **pubsubclient** for MQTT connectivity
6. Successfully connected to AWS IoT Core and subscribed to "outTopic" for data stream

### Using a Flask Server as an API

- MQTT architecture sends data to an AWS IoT Core livestream
- Flask server (hosted on [ide.goorm.io](https://ide.goorm.io)) acts as a validated endpoint for AWS IoT Core to stream data from the outTopic topic
- AWS IOT Core uses the `POST` route to send data to the live Flask server
- server then uses `SQL` to store values in a database
- a `GET` request exists to return most recent value in the updated `SQL` database

**Instructions for running Flask Server**

1. Initialise SQL Database

```bash
> python3 init_db.py
```

2. Run Flask Application

```bash
> new run flask
```

**Finally, we get the resulting API endpoint:**

- [Flask Server — GET route](https://parth-iot-intro.run-ap-south1.goorm.io/aws_iot_get)
  ![Flask GET request Image](/resources/flask-get.png)

## Machine Learning — Traffic Prediction

![ml](/resources/ml.png)

- Clusters 125 possible bases into 5 broad categories with dependent variable being time
- Each minute in a day is encoded to a numerical value such that spikes in various regions are stored against structured data
- Used Sci-kit Learn to train six different classification models on the data using K-Nearest Neighbours, Kernels in Support Vector Machine, Decision Tree Classification, Logistic Regression, Naive Bayes and Random Forest Classification
- The results and accuracy of the models are compared using a confusion matrix, and the one with highest accuracy is used as a predictor for that minute
- An automated email is sent out to the required email account conveying the ideal base to travel to (can be integrated with API)
- Using the UBER New York Traffic Dataset from Kaggle

## Hardware Implementation

![hw](/resources/hw.png)
