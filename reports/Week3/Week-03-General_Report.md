# Objectives for Week 2

1. Build a custom C++ library from scratch to load data, analyze it, and turn it into charts.
2. Create separate branches for every individual member.
3. Break the project down into separate parts so everyone on the team can work on their assigned module.
4. Write the basic setup and header files for all project parts and get the mathematical logic for the statistics module working.

# Activities Carried Out

1. All members created separate branches.
2. Members were assigned different parts of the project.
3. Header files were created by the members according to their assigned modules.

# Team Members Work Allocations

1. TWINOMUJUNI ROMEO – Axis
2. AHUMUZA BLESSING – Statistics
3. ADONGA PHILLIP – Data Loader
4. SERUGYA FAHAD – Histogram
5. EGERU MICHAEL – Count Plot
6. ATWINE JEANES – Data Processing
7. WALUGEMBE MUHAISINAH N. – Annotations
8. NAMUBIRU LOUISE – Image Exporter
9. MUGERWA SHADRACK STEPHEN – KDE Plot
10. KISAKYE JEMIMA – Renderer

# Challenges Experienced

1. Header File Conflicts: Avoiding circular includes between different files so that #include directives do not cause compilation errors.
2. Complex Mathematics Without External Libraries: Writing mathematical algorithms such as KDE curves and binning logic from scratch in plain C++ without relying on heavy external math libraries.
3. Data Format Consistency: Making sure everyone uses the same data formats, such as vectors of doubles or key-value pairs, so that data passes smoothly between data loaders, statistical calculations, and plot renderers.

# References

AI was used to assist in creating header files in addition to our C++ knowledge.

Seaborn was referenced for KDE plots, histograms, and count plots. NumPy histogram concepts were referenced for calculating bin counts from numerical data. SciPy gaussian_kde was referenced for Gaussian KDE implementation, including bandwidth and evaluation. Matplotlib hist was referenced for histogram plotting.