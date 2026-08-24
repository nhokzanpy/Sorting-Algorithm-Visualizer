# Sorting Algorithm Visualizer

Simulation and visualization of basic internal sorting algorithms using C++ and Qt.

## Project

Course project #32: Basic Internal Sorting Algorithms Simulation.

## Algorithms

- Bubble Sort
- Selection Sort
- Insertion Sort
- Merge Sort

## Main Features

- Step-by-step sorting visualization
- Play, Pause, Next Step, Reset
- Random and custom array input
- Adjustable animation speed
- Comparison and swap/move statistics
- Execution time measurement
- Algorithm benchmarking
- Student data sorting demonstration
- Algorithm theory and complexity information

## Technology

- C++17
- Qt 6
- Qt Widgets
- CMake
- MinGW 64-bit

## Project Structure

```text
SortingVisualizer/
├── algorithms/
├── models/
├── benchmark/
├── widgets/
├── pages/
├── resources/
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
├── CMakeLists.txt
├── .gitignore
└── README.md
```

---

# Project Progress

## Phase 1 - Project Structure and Base Setup ✅

Completed:

- Created the initial Qt Widgets project
- Configured CMake
- Added `.gitignore`
- Added README
- Removed build and Qt Creator cache files from Git tracking
- Prepared the project folder structure:
  - `algorithms`
  - `models`
  - `benchmark`
  - `widgets`
  - `pages`
  - `resources`

---

## Phase 2 - Sorting Models ✅

Implemented the core data models used by the sorting engine.

### SortingStep

Stores information about each individual sorting action.

Supported step types:

- Compare
- Swap
- Move
- MarkSorted
- Merge
- Complete

Each step can contain:

- Current array state
- First active index
- Second active index
- Step type
- Description

### SortingStatistics

Tracks:

- Comparisons
- Swaps
- Moves
- Execution time

---

## Phase 3 - Bubble Sort Algorithm ✅

Implemented Bubble Sort with step-by-step execution data.

Features:

- Compare steps
- Swap steps
- Sorted-position markers
- Early exit optimization
- Comparison counting
- Swap counting
- Move counting
- Execution time measurement

### Test Example

Input:

```text
8 3 6 1 5
```

Output:

```text
1 3 5 6 8
```

Statistics:

```text
Comparisons: 10
Swaps: 7
Moves: 21
```

The result was verified through the Qt Application Output.

---

## Phase 4 - Bubble Sort Visualization ✅

Implemented the first complete visualization module.

### Input Controls

- Custom array input
- Random array generation
- Bubble Sort algorithm selector
- Adjustable animation speed

### Playback Controls

- Play
- Pause
- Next Step
- Reset

### Visualization

- Bar chart visualization
- Value labels
- Array index labels
- Step-by-step updates
- Persistent sorted positions
- Complete-state visualization

### Visual States

| State | Color |
| --- | --- |
| Normal | Gray |
| Comparing | Amber |
| Swapping | Red |
| Sorted | Green |

### Statistics

Statistics update progressively during the animation:

- Comparisons
- Swaps
- Moves

Execution time is also displayed after the sorting steps are generated.

### UI Improvements

- Dark theme
- Styled input fields
- Styled buttons
- Blue Play button
- Orange/Red Reset button
- Visualization container
- Statistics cards
- Status bar
- Color legend
- Improved margins and spacing
- Clear section labels:
  - Input Data
  - Algorithm
  - Speed

### Tested Behavior

Verified:

- Next Step
- Compare highlighting
- Swap highlighting
- Play
- Pause
- Reset
- Progressive statistics
- Persistent sorted bars
- All bars turn green when sorting is complete

---

# Development Roadmap

- [x] Phase 1 - Project structure and base setup
- [x] Phase 2 - Sorting step and statistics models
- [x] Phase 3 - Bubble Sort implementation
- [x] Phase 4 - Bubble Sort visualization
- [ ] Phase 5 - Selection Sort and Insertion Sort
- [ ] Phase 6 - Merge Sort
- [ ] Phase 7 - Algorithm benchmark comparison
- [ ] Phase 8 - Student sorting module
- [ ] Phase 9 - Theory page
- [ ] Phase 10 - UI polish and final testing

---

# Current Status

The project currently supports a complete Bubble Sort workflow:

```text
Input Array
    ↓
Bubble Sort Engine
    ↓
SortingStep Sequence
    ↓
Sorting Visualizer
    ↓
Play / Pause / Next / Reset
    ↓
Statistics + Visual State
```

The next development stage is:

```text
Phase 5
Selection Sort + Insertion Sort
```
