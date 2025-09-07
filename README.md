# Image Filter Project (C)

This project applies different filters to BMP images:
- **Grayscale**
- **Reflect**
- **Blur**
- **Edge detection**

## Build
Compile with:
bash
make
make clean
./filter -g images/input.bmp images/output.bmp
Options:

-g → Grayscale

-r → Reflect

-b → Blur

-e → Edges

│── .gitignore
│── Makefile
│── README.md
│── bmp.h
│── filter.c   # (your main program)
│── helpers.c
│── helpers.h
│── images/    # (put test .bmp files here)

Notes

Only supports 24-bit uncompressed BMPs (CS50-style).

Sample images are in images/.
