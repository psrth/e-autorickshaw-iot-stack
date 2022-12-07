import React, { useState } from "react";
import { Flex, Text } from "@chakra-ui/react";
import Chart from "./Chart";

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
    >
      <Flex
        width="90vw"
        m="auto"
        flexDir="column"
        height="fit-content"
        mt="20px"
      >
        <Flex flexDir="row" justifyContent="space-between" m="0 5px 10px 5px">
          <Text color="white">IoT Auto Rickshaw</Text>
          <Text color="white">Auto #432</Text>
        </Flex>

        <Flex
          width="100%"
          flexDir="column"
          mt="10px"
          mb="10px"
          bg="#282A33"
          borderRadius="10px"
          justifyContent="flex-start"
          p="10px 20px"
        >
          <Text color="#A3A3A3">CURRENT SPEED</Text>
          <Flex flexDir="row">
            <Text color="#A3A3A3">{speed[0]}</Text>
            <Text color="#A3A3A3">m/sec</Text>
          </Flex>
          <Flex mt="20px" />
          <Chart labels={speedLabels} data={speed} />
          <Flex mb="10px" />
        </Flex>
      </Flex>
    </Flex>
  );
}

export default App;
