noteable features:
- modularity and template-heavy implementation
- multithreaded implementation (naive concurrent static separation and worker pool chunk processing)
- heavy unit testing of all features and options
- bit-packed grid implementation (allows much bigger grids and much less memory use, with up to 2-3x performance)
- bit-wise SIMD processing ()
- full customized runs with cli args (full info in --help todo)
- factory class for templated simulations in runtime, allowing any combination of features
- predefined (ASCII string, RLE todo), fully or seeded random initial states

todo:
- ~~predefined initial state~~, ~~ascii to state~~, rle to state, ~~seed~~
- ~~unit tests~~
- ~~TickStrategy via template~~
- ~~console commands for quick settings~~ (-c console, -g gui, -v verbose, etc), --help text, ~~Simulation factory~~, ~~settings (size, tick engine, rules)~~
- ~~edges rule (toroidal vs clamped, template on gridState)~~
- better telemetry (memory use, fps, etc)
- ~~multicore~~
~~- memory use optimization (bit-packed grid)~~
- bitGrid alg (simd)
- input (sim speed, pause, step, reset)
- webGPU grid rendering
- benchmarking
- rules via variadic template, custom rule strings
- comments, doxygen?
- gui
- gpu (cuda?)
- ci/cd
- update readme