import React from "react";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";
import { Line } from "react-chartjs-2";

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

export const options = {
  responsive: true,
  plugins: {
    legend: {
      position: "top",
    },
    title: {
      display: false,
      text: "Acceleration Data",
    },
  },
};

export default function Chart(props) {
  return (
    <Line
      options={options}
      data={{
        labels: props.labels,
        datasets: [
          {
            label: "Acceleration Data",
            data: props.data,
            borderColor: "rgba(65, 120, 245, 1)",
            backgroundColor: "rgba(65, 120, 245, 1)",
          },
        ],
      }}
    />
  );
}
