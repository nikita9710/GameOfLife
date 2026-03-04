<h1 align="center">Conway’s Game of Life</h1>
<h3 align="center">High-Performance Modular C++ Implementation</h3>

<p align="center">
Modern C++ • Bit-packed memory layout • Multithreading • Compile-time composition
</p>

<hr/>

<h2>Overview</h2>

<p>
This project is a performance-oriented implementation of Conway’s Game of Life written in modern C++.
It focuses on memory efficiency, compile-time configurability, multithreading strategies,
and zero-overhead abstractions.
</p>

<p>
Rather than treating Game of Life as a toy problem, this repository explores
cache behavior, parallel execution models, and architectural tradeoffs
in performance-critical systems.
</p>

<hr/>

<h2>Key Engineering Features</h2>

<ul>
  <li><b>Template-driven modular architecture</b></li>
  <li><b>Bit-packed grid representation</b> (1 bit per cell)</li>
  <li><b>Multithreaded simulation</b> (static partitioning + worker pool)</li>
  <li><b>Runtime Simulation Factory</b> bridging CLI and template composition</li>
  <li><b>Extensive unit testing</b></li>
  <li><b>CLI-driven configuration</b></li>
  <li><b>CI integration</b></li>
</ul>

<hr/>

<h2>Architecture & Design</h2>

<h3>Compile-Time Feature Composition</h3>

<p>
The simulation core is heavily templated to allow compile-time configuration of:
</p>

<ul>
  <li>Grid representation (standard vs bit-packed)</li>
  <li>Edge behavior (toroidal vs clamped)</li>
  <li>Tick/update strategy (single core vs naive multicore vs worker pool)</li>
  <li>Rule configuration</li>
</ul>

<p>
This enables zero-overhead abstractions, eliminates runtime branching in hot paths,
and maximizes compiler optimization opportunities.
</p>

<p>
A <b>Simulation Factory</b> bridges runtime CLI configuration and template instantiation,
preserving flexibility without sacrificing performance.
</p>

<hr/>

<h3>Memory-Optimized Bit-Packed Grid</h3>

<ul>
  <li>1 cell = 1 bit</li>
  <li>~8× lower memory usage vs byte-per-cell grids</li>
  <li>Improved cache locality</li>
  <li>Up to 2–3× performance improvement on large grids</li>
</ul>

<p>
Per-word update optimizations reduce bit extraction overhead and favor contiguous memory access.
</p>

<hr/>

<h3>Multithreading Strategies</h3>

<ul>
  <li><b>Static grid partitioning</b> — simple parallel split</li>
  <li><b>Worker pool with chunk scheduling</b> — improved load balancing</li>
</ul>

<p>
The design minimizes synchronization and keeps memory access largely independent per thread.
</p>

<hr/>

<h2>CLI Usage</h2>

<pre><code>./GameOfLife --size 2000 \
               --tick MultiCorePool \
               --grid Dense \
               --edge Toroidal \
               --seed 42
</code></pre>

<p>Full configuration:</p>

<pre><code>./GameOfLife --help
</code></pre>

<p>
Supported initial states:
</p>

<ul>
  <li>Predefined ASCII patterns</li>
  <li>Random initialization (optionally seeded)</li>
</ul>

<hr/>

<h2>Testing & CI</h2>

<ul>
  <li>Extensive unit testing across core components</li>
  <li>Validation of grid logic, rules, edge behavior, and multithreaded correctness</li>
  <li>CI pipeline for automated builds and tests</li>
</ul>

<p>
Given the template-heavy design, special attention is paid to validating feature combinations.
</p>

<hr/>

<h2>Technical Highlights</h2>

<ul>
  <li>Modern C++</li>
  <li>Template metaprogramming</li>
  <li>Factory pattern</li>
  <li>Cache-aware memory layout</li>
  <li>Bitwise algorithms</li>
  <li>Parallel execution strategies</li>
  <li>Strong separation of concerns</li>
  <li>Automated testing practices</li>
</ul>

<hr/>

<h2>Roadmap</h2>

<ul>
  <li>Cross-platform compilation</li>
  <li>RLE pattern parsing</li>
  <li>Enhanced telemetry (memory usage, FPS)</li>
  <li>Input processing (set sim speed, pause, step, reset)</li>
  <li>Benchmark suite to compare tick strategies and configurations</li>
  <li>Scripts to build and run demos</li>
  <li>Word-level data-parallel (bitwise) calculations</li>
  <li>WebGPU grid rendering</li>
  <li>GUI frontend</li>
  <li>Variadic-template rule system</li>
  <li>GPU backend exploration (CUDA)</li>
</ul>

<hr/>

<h2>Project Focus</h2>

<p>
While Conway’s Game of Life is conceptually simple, optimizing it at scale
exposes deeper system-level challenges:
</p>

<ul>
  <li>Optimiized memory layout vs abstraction trade-offs</li>
  <li>Cache efficiency</li>
  <li>Parallel execution design</li>
  <li>Compile-time vs runtime configuration</li>
  <li>Zero-cost abstraction principles</li>
</ul>

<p>
This repository serves as a focused exploration of performance-critical C++ design.
</p>

<hr/>
