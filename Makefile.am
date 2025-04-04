bin_PROGRAMS = pdf_viewer
pdf_viewer_SOURCES = main.c \
    v_file.c \
    v_pdf.c \
    v_menu.c

AM_CFLAGS = $(GTK_CFLAGS) -g -O0
AM_LDFLAGS = $(GTK_LIBS) -lmupdf

pdf_viewer_SOURCES += assets_embedded.c
EXTRA_DIST = assets/hamburger_menu.png

assets_embedded.c: assets/hamburger_menu.png
	xxd -i assets/hamburger_menu.png > assets_embedded.c
