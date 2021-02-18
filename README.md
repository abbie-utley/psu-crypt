Name: Abbigail Utley
email: abbie.utley101@gmail.com

PSU-crypt
=========

This is Feistel cipher that uses a block encryption algorithm. This is based on _Twofish_ by Bruce Schneier, John Kelsey,
Doug Whiting, David Wagner, and Chris Hall and _SKIPJACK_ by the NSA combined.

PSU-crypt uses a 64 bit key in a 64 bit block. 

This project will be in C.

---

Encryption - How to Build
-------------------------

This section will describe how to build for encryption.

Running `make clean` before anything else will get rid of the .o files, as well as the ciphertext.txt and plaintext.txt files.

1. To encrypt, a file called **plaintext.txt** must exist in the directory. 
2. Once it's there, run `make encrypt` to compile the program.[^1][^2]
3. To start the program, run the following command: `./encrypt key.txt plaintext.txt` 
4. The files do not _have_ to be named accordingly, since this program uses the `argv` implementation. However, the output will be
delivered to a file called **ciphertext.txt** and if you wish to use this file for decryption, remember that.
5. The output that is printed to the shell will have the following:[^3] 
* plaintext
* key
* ciphertext
The ciphertext will be displayed as a concatenation in case the plaintext was originally longer than 64 bits.
6. The output will also be written to a file called **ciphertext.txt**. If one exists already, it will be rewritten.

[^1]:`make` will also do this, since encrypt is the default

[^2]:A warning will show up on the first compilation, but will not show up later.

[^3]:For encryption, please note that HEX inputs that are more than 64 bits will only encrypt the first 64 bits. 

---

Decryption - How to Build
-------------------------

This section will describe how to build for decryption.

As above, running `make clean` will clear all .o files and ciphertext.txt as well as plaintext.txt.

1. To decrypt, a file called **ciphertext.txt** must exist in the directory.
2. Once it's there run `make encrypt` to compile the program.[^1]
3. To start the program, run the following command: `./decrypt key.txt ciphertext.txt`
4. The files do not _have_ to be named accordingly, since this program uses the `argv` implementation. However the output will be 
delivered to a file called **plaintext.txt** and if you wish to use this file for encryption, remember that.
5. The output that is printed to the shell will have the following:[^2]
* ciphertext
* key
* plaintext in hex
* plaintext in ascii
- please note that if what you are decrypting was originally in hex, and does not correspond with a hex value, it may look like garbage. - 
6. The plaintext that was decrypted will be written to a file called **plaintext.txt**. If one exists already, it will be rewritten.

[^1]:`make` will **not** run decryption. It has to be `make decrypt`.

[^2]:ciphertext input has to be separated into 64 bit blocks by a new line

---

List of Files
-------------

This is a list of the files that _must_ be included in the directory for the program to run

* `main_enc.c` 
      This file contains the main code for _encryption_, including the forward key schedule, and reading in plaintext.
* `main_dec.c`
      This file contains the main code for _decryption_, including the backwards key schedule, and reading in ciphertext.
* `wholesched.c`
      This file contains the schedule for the entire encryption and decryption process. It implements the r values, and runs 
      the F and G functions. It also is responsible for outputting the results in their respective files, as well as other
      functions that didn't fit in other files such as `convert_to_hex`. 
* `FandG_function.c`
      True to their namesake, this file has the F and G functions. This is where T0 and T1 are also being implemented. 
* `ftable.c`
      This file reads in the ftable from a text file, and puts it in a global 2D array called `F_table`.
* `ftable.txt`
      This text file is the Ftable that was given to us by the project description.
* `keyschedule.c`
      This file has the functions needed for the key schedule, and computes the key schedule into a 2D array called keysched.
* `key.txt`
      This file does not have to be named this, but this program needs a 64 bit key to run. It must be in hex. Whatever you choose 
      to name it as, make sure you call it properly when executing the program.
* `defs.h`
      This file is the main header file. This includes all `#includes` as well as every function declaration.
* `Makefile`
      This is the Makefile that holds the recipe for building. It is not necessary to run, however it is more convenient to keep.
      It also helps in cleanup functionality.

---

NOTE: there are commented out print statements all throughout the code. If you need these for debugging, just uncomment them, 
they're very helpful.
