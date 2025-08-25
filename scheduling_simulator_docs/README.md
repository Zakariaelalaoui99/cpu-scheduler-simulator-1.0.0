# Scheduling Simulator Documentation

This project uses **Doxygen** to generate developer documentation.

## How to build the docs

1. Install doxygen (Linux/macOS: `sudo apt-get install doxygen` or `brew install doxygen`; Windows: download from [doxygen.nl](https://www.doxygen.nl/)).

2. From the project root, run:

```bash
cd scheduling_simulator_docs
doxygen Doxyfile
```

3. Open the generated documentation:

- HTML docs: `docs_output/html/index.html`
- Browse with your browser of choice.

## Notes

- The documentation covers all headers in `include/` and implementations in `src/`.
- All algorithms (FCFS, SJF, RR, RRP) and scheduling modes (ProcessOnly, ThreadKernel, ThreadUser) are documented.
- You can extend by adding new `.hpp`/`.cpp` files; Doxygen will pick them up automatically.
