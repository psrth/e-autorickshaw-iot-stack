import React, { useState } from "react";
import { Flex, Text, Image } from "@chakra-ui/react";
import Chart from "./Chart";
import auto from "./auto.png";

function App() {
  const [speed, setSpeed] = useState(["24.4", "22", "21"]);
  const [speedLabels, setSpeedLabels] = useState(["1", "2", "3"]);

  return (
    <Flex
      width="100vw"
      minHeight="100vh"
      bg="#202229"
      m="0"
      p="0"
      flexDir="column"
      pb="20px"
    >
      <Flex
        width="90vw"
        m="auto"
        flexDir="column"
        height="fit-content"
        mt="20px"
      >
        <Image boxSize="75px" src={auto} m="auto" mb="20px" />
        <Flex flexDir="row" justifyContent="space-between" m="0 5px 10px 5px">
          <Text color="white" fontWeight="600">
            IoT Auto Rickshaw
          </Text>
          <Text color="white" fontWeight="600">
            Auto #432
          </Text>
        </Flex>

        <Flex
          width="100%"
          flexDir="column"
          mt="10px"
          mb="10px"
          bg="#282A33"
          borderRadius="10px"
          justifyContent="flex-start"
          p="20px 30px"
        >
          <Text color="#A3A3A3" fontWeight="600">
            CURRENT SPEED
          </Text>
          <Flex flexDir="row" alignItems="flex-end">
            <Text fontWeight="900" fontSize="54px" color="#4178F5" mr="20px">
              {speed[0]}
            </Text>
            <Text color="#fff" fontWeight="700" fontSize="24px" mb="12px">
              m/sec
            </Text>
          </Flex>
          <Flex mt="20px" />
          <Chart labels={speedLabels} data={speed} />
          <Flex mb="10px" />
        </Flex>

        <Flex
          width="100%"
          flexDir="column"
          mt="10px"
          mb="10px"
          bg="#282A33"
          borderRadius="10px"
          justifyContent="flex-start"
          p="20px 30px"
        >
          <Text color="#A3A3A3" fontWeight="600">
            CRASH DETECTION
          </Text>
          <Text color="#00DF67" fontWeight="700" fontSize="24px" mt="2px">
            No crashes detected.
          </Text>
        </Flex>

        <Flex
          width="100%"
          flexDir="column"
          mt="10px"
          mb="10px"
          bg="#282A33"
          borderRadius="10px"
          justifyContent="flex-start"
          p="20px 30px"
        >
          <Text color="#A3A3A3" fontWeight="600">
            GYROSCOPE READING
          </Text>
          <Text color="#00DF67" fontWeight="700" fontSize="24px" mt="2px">
            24.54
          </Text>
        </Flex>

        <Flex
          width="100%"
          flexDir="column"
          mt="10px"
          mb="10px"
          bg="#282A33"
          borderRadius="10px"
          justifyContent="flex-start"
          p="20px 30px"
        >
          <Text color="#A3A3A3" fontWeight="600" mb="10px">
            LIVE LOCATION TRACKING
          </Text>
          <iframe
            src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d990.2622145034308!2d75.58928641565416!3d28.364600609573266!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x391319a0c2bd4d19%3A0x6adb7e0148e63169!2sQT%20(Quadrangle%20Theatre)%2C%20LTC!5e0!3m2!1sen!2sin!4v1670407844817!5m2!1sen!2sin"
            width="290"
            height="300"
            allowfullscreen=""
            loading="lazy"
            referrerpolicy="no-referrer-when-downgrade"
          ></iframe>
        </Flex>
      </Flex>
    </Flex>
  );
}

export default App;
