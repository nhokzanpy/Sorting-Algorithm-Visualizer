# Sorting Algorithm Visualizer

Desktop application for learning and visualizing four basic internal sorting algorithms using C++ and Qt 6.

## Scope

The project focuses on four in-memory sorting algorithms for integer arrays sorted in ascending order:

- Bubble Sort
- Selection Sort
- Insertion Sort
- Merge Sort

The application supports step-by-step visualization, statistics, benchmark comparison, student practice, and multi-size performance testing.

## Main Features

### Sorting Visualizer

- Custom integer array input
- Random array generation
- Four algorithm choices
- Adjustable animation speed
- Play / Pause / Next Step / Reset
- Step-by-step bar visualization
- Visual states for comparing, swapping, moving, merging, and sorted elements
- Progressive comparison / swap / move counters
- Execution time display

### Algorithm Benchmark

- Runs all four algorithms on the same input data
- Compares comparisons, swaps, moves, and execution time
- Highlights tied best metric values

### Student Lab

- Custom integer array input
- Select any supported algorithm
- Sorted output and statistics
- Recent result history
- Input validation and status feedback

### Multi-size Performance Testing

- Preset sizes: 10, 50, 100, 500, 1000
- Custom comma-separated sizes
- Maximum supported benchmark size: 5000 elements
- Same generated dataset for all four algorithms at each size
- Result table and Time vs Input Size chart
- Lightweight benchmark implementation without animation-step generation

## Technology

- C++17
- Qt 6.5+
- Qt Widgets
- CMake 3.19+
- MinGW 64-bit on Windows

## Project Structure

```text
SortingVisualizer/
├── algorithms/
├── models/
├── benchmark/
├── student/
├── widgets/
├── pages/
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Build on Windows

Open the project in Qt Creator with a Qt 6 kit, or build with CMake.

### Configure

```bash
cmake -S . -B build -G "MinGW Makefiles"
```

### Build

```bash
cmake --build build --config Release
```

### Deploy

The project includes Qt deployment support through `qt_generate_deploy_app_script()`.

```bash
cmake --install build --config Release --prefix dist
```

Use the generated `dist` directory to test the application outside Qt Creator.

## Development Status

All planned development phases are complete.

| Phase | Status |
| --- | --- |
| 1. Project structure and base setup | ✅ |
| 2. Sorting models and statistics | ✅ |
| 3. Bubble Sort implementation | ✅ |
| 4. Bubble Sort visualization | ✅ |
| 5. Selection Sort and Insertion Sort | ✅ |
| 6. Merge Sort | ✅ |
| 7. Algorithm benchmark comparison | ✅ |
| 8. Student sorting module | ✅ |
| 9. Multi-size performance testing | ✅ |
| 10. UI polish and final QA | ✅ |

## Final QA Changes

The final source includes the following stability and cleanup changes:

- Main Visualizer rejects malformed numeric input instead of silently discarding invalid tokens.
- Sorting steps are regenerated whenever the input data or selected algorithm changes.
- `Next Step` stops safely when input is invalid instead of advancing through an empty sequence.
- Multi-size benchmark input is validated and limited to 5000 elements.
- The benchmark runner enforces the same 5000-element safety limit.
- Startup-only Bubble Sort debug output was removed from `main.cpp`.
- Qt Creator user-specific settings and local build artifacts are not part of the repository.
- Core sorting, benchmark, and student-runner checks pass in a standalone C++ test harness.
- A full Qt GUI configure/build was not run in this environment because Qt 6 development files are unavailable here; perform the final Windows Release build in the project Qt 6 / MinGW environment.

## Recommended QA Test Cases

For each algorithm, verify:

```text
5, 4, 3, 2, 1
1, 2, 3, 4, 5
3, 3, 3, 3
-5, 10, 0, -2, 7
8, 3, 6, 1, 5
1
```

Invalid input examples:

```text
8, 3, abc, 5
hello
```

Also verify Play, Pause, Next Step, Reset, Random, algorithm switching, input changes, repeated runs, Student Lab, and Multi-size Benchmark presets 10 / 50 / 100 / 500 / 1000. A valid custom benchmark size such as 2000 should run, while values above 5000 should be rejected.

## Architecture Summary

```text
User Input
    ↓
ControlsPanel
    ↓
VisualizerPage
    ├── Sorting Algorithms
    ├── SortingStep / SortingStatistics
    ├── SortingVisualizer
    ├── BenchmarkPanel
    ├── StudentPanel
    └── MultiSizeBenchmarkPanel

Multi-size Benchmark
    ↓
Lightweight benchmark runner
    ↓
Same generated dataset per input size
    ↓
Table + Time vs Input Size chart
```

## Repository

GitHub repository:
https://github.com/nhokzanpy/Sorting-Algorithm-Visualizer

## Notes

The application intentionally stays within the defined project scope. It does not implement external sorting, distributed processing, parallel sorting, or advanced sorting algorithms outside the four selected algorithms.
