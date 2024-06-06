**Optimal Computer Allocation for HTTP Request Management**

### README

# Optimal Computer Allocation for HTTP Request Management

## Overview

This project aims to determine the minimum number of computers required in a web hosting firm to ensure that the average waiting time of a client for each HTTP request does not exceed a specified amount. By analyzing HTTP request logs and simulating their processing, the program calculates the average waiting time and estimates the necessary computer resources for efficient request handling.

## Project Description

In this project, I aim to:

1. Read and parsed a log file containing HTTP request data.
2. Simulated the processing of these requests by a varying number of computers.
3. Calculated the average waiting time for each configuration.
4. Determined the minimum number of computers needed to keep the average waiting time below a given threshold.

## Input File Format

The input file is a Unix-style text file with the following format:

- The first line contains the number of requests.
- Each subsequent line contains information about a single request: `id`, `priority`, `request time`, and `process time`. These values are integers separated by a whitespace.

### Example

```
4
1 9 3 5
2 8 5 2
3 9 6 1
4 7 8 3
```

In this example:
- There are 4 requests.
- The first request has an ID of 1, priority 9, was sent 3 milliseconds after the log file creation, and requires 5 milliseconds to process.

## Processing Protocol

1. The request with the highest priority should be processed first.
2. If two requests have the same highest priority, the request sent earlier should be processed first.
3. If more than one computer is available, the computer with the lower ID processes the request.
4. Once a request is assigned to a computer, it starts processing immediately and is unavailable until the processing is complete.

## Assumptions

1. The data file will always be valid and composed of integers.
2. The requests are sorted by their sent times in the data file.
3. There can be any number of requests in the log file.
4. Dynamic memory allocation will be used for handling the requests.
5. A heap-based priority queue must be used to store requests waiting for a computer.

## Implementation Details

The program simulates the allocation and processing of requests using a heap-based priority queue to manage the pending requests. The number of computers is incrementally increased until the average waiting time of the requests falls below the specified threshold.

## How to Run the Program

The program takes two command-line arguments:
1. The name of the input file.
2. The maximum average waiting time (in milliseconds).

### Command

```bash
./optimal_computer_allocation <input_file> <max_average_waiting_time>
```

### Example

```bash
./optimal_computer_allocation requests.log 10
```

In this example, the program reads the `requests.log` file and determines the minimum number of computers required to ensure the average waiting time does not exceed 10 milliseconds.

## Dependencies

- C++11 or higher
- Standard Template Library (STL)

## Contributing

Contributions are welcome! Please open an issue to discuss what you would like to change or improve.

furkan.kizil@ug.bilkent.edu.tr

## License

This project is licensed under the MIT License. See the LICENSE file for details.
