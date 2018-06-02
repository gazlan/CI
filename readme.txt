// Recompiles with MSVC 6.0   (c)   gazlan@yandex.ru * 2018
// Hashtable BUG fixed.

CI interpreter

* CI is a small interpreter for c language written completely in c itself.

* This project has been developed as part of our Compiler course [1]
  assignment at ISI, Kolkata under the guidance of Dr. Mandar Mitra and Dr.
  Utpal Garain.

* The project is licensed under the terms of the GNU GPL v3.0.

* Lexer and parser are generated using flex and bison.

* The flex and bison files are heavily influenced by the grammar rules
   discussed in K&R book.

* TODO and FIXME:

   1. shady implementation of 2d arrays and pointers.
   2. shady implementation of type. basically, we would like to change
      the current handling of types with a more generic one.
   3. improve error handling module to include more information.
      this will require addition of fields in the ast data structure
      and a data structure to encapsulate the error object.
   4. better commenting and documentation.
   5. provide an installation script, though the compilation from source is
      itself a fairly easy process.

References:

1. http://www.isical.ac.in/~mandar/courses.html#cc
